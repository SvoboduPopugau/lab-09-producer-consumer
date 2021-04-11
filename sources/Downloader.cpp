// Copyright 2020 Your Name <your_email>

#include <Downloader.hpp>

//TODO:
auto EndPoint::operator=(EndPoint&& tmp) noexcept -> EndPoint&{
  if(this == &tmp){
    std::cout << "Equal objects" << std::endl;
  }
  protocol = tmp.protocol;
  domain = tmp.domain;
  target = tmp.target;
  return *this;
}

void ParseUri(const std::string& s_url, EndPoint& ep){
//    https://github.com/boostorg/beast
  size_t dots_pos = s_url.find_first_of(':');
  ep.protocol = s_url.substr(0, dots_pos);
  size_t path_start = s_url.find('/', dots_pos+3);
  if (path_start == std::string::npos){
    ep.domain = s_url.substr(dots_pos + 3, s_url.size() - dots_pos - 2);
    ep.target = "/";
  } else {
    ep.domain = s_url.substr(dots_pos + 3, path_start - dots_pos - 3);
    ep.target = s_url.substr(path_start, s_url.size() - path_start + 1);
  }
};

std::string Downloader::GetHttpPage(std::string&& domain,
                                    std::string&& target) {
boost::asio::io_context io;

boost::asio::ip::tcp::resolver resolver(io);
boost::beast::tcp_stream tcpStream(io);

auto result = resolver.resolve(domain, "80");

tcpStream.connect(result);

http::request<http::string_body> req{http::verb::get, target, 11};
req.set(http::field::host, domain);
req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

}
