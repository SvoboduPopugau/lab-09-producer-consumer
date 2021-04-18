// Copyright 2020 Your Name <your_email>

#include <Downloader.hpp>

void ParseUri(const std::string& s_url, EndPoint& ep) {
  size_t dots_pos = s_url.find_first_of(':');
  ep.protocol = s_url.substr(0, dots_pos);
  size_t path_start = s_url.find('/', dots_pos + 3);
  if (path_start == std::string::npos) {
    ep.domain = s_url.substr(dots_pos + 3, s_url.size() - dots_pos - 2);
    ep.target = "/";
  } else {
    ep.domain = s_url.substr(dots_pos + 3, path_start - dots_pos - 3);
    ep.target = s_url.substr(path_start, s_url.size() - path_start + 1);
  }
}

[[maybe_unused]] std::string Downloader::GetHttpPage(std::string&& domain,
                                                     std::string&& target) {
  boost::asio::io_context io;

  boost::asio::ip::tcp::resolver resolver(io);
  boost::beast::tcp_stream tcpStream(io);

  auto result = resolver.resolve(domain, "80");

  tcpStream.connect(result);

  http::request<http::string_body> req{http::verb::get, target, 11};
  req.set(http::field::host, domain);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  http::write(tcpStream, req);

  boost::beast::flat_buffer buffer;
  http::response<http::string_body> res;

  http::read(tcpStream, buffer, res);

  boost::beast::error_code ec;
  tcpStream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

  return res.body();
}
[[maybe_unused]] std::string Downloader::GetHttpsPage(std::string&& domain,
                                                      std::string&& target) {
  boost::asio::io_context io;
  ssl::context ctx{ssl::context::sslv23_client};

  load_root_certificates(ctx);
  ctx.set_verify_mode(ssl::verify_none);

  boost::asio::ip::tcp::resolver resolver(io);
  ssl::stream<boost::asio::ip::tcp::socket> stream{io, ctx};
  if (!SSL_set_tlsext_host_name(stream.native_handle(), domain.data())) {
    boost::system::error_code ec{static_cast<int>(::ERR_get_error()),
                                 boost::asio::error::get_ssl_category()};
    throw boost::system::system_error{ec};
  }
  auto const results = resolver.resolve(domain, "443");

  boost::asio::connect(stream.next_layer(), results.begin(), results.end());

  stream.handshake(ssl::stream_base::client);

  http::request<http::string_body> req{http::verb::get, target, 11};
  req.set(http::field::host, domain);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  http::write(stream, req);

  boost::beast::flat_buffer buffer;

  http::response<http::string_body> res;

  http::read(stream, buffer, res);

  boost::beast::error_code ec;
  stream.shutdown(ec);

  return res.body();
}
void Downloader::DownloadPage(const std::string& URL, size_t lev,
                              MyQueue<Page>* parseQueue) {
  EndPoint endPoint;
  ParseUri(URL, endPoint);
  endPoint.level = lev;

  std::string html_content;

  if (endPoint.protocol == "http")
    html_content =
        GetHttpPage(std::move(endPoint.domain), std::move(endPoint.target));
  else if (endPoint.protocol == "https")
    html_content =
        GetHttpsPage(std::move(endPoint.domain), std::move(endPoint.target));

  Page page{endPoint.protocol, endPoint.domain, html_content, endPoint.level};

  //  Загрузить html_content в очередь парсинга
  parseQueue->Push(page);
}
