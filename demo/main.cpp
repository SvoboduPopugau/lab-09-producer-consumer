
//TODO: Почему не работают add_options() в po
//TODO: Как подключить долбаный ThreadPool на которвый идет ссылка https://github.com/progschj/ThreadPool
//  А может и ну его, просто сделаем, блин, по классике через вектор

//#include <boost/program_options.hpp>
//#include <boost/program_options/options_description.hpp>
//
//namespace opt = boost::program_options;
//
//int main(int argc, char** argv)
//{
//  opt::option_description desc;
//  desc.add_options()
//      ("help", "produce help")
//      ("time", opt::value<double>()-> default_value(10), "user\'s time value")
//      ;
//}

//-------------------------------------------------------------------------------------
//#include <iostream>
//#include <vector>
//#include <chrono>
//
//#include "ThreadPool.h"
//
//int main()
//{
//
//  ThreadPool pool(1);
//  std::vector< std::future<int> > results;
//  std::mutex m;
//  for(int i = 4; i < 8; ++i) {
//    results.emplace_back(
//        pool.enqueue([i]{
//          std::cout << "hello " << i << "--" << std::endl;
//          std::this_thread::sleep_for(std::chrono::seconds(5));
//          std::cout << "world " << i <<  "-" << std::endl;
//          return i*i;
//        })
//    );
//  }
//
//  for(auto && result: results)
//    std::cout << result.get() << "_ ";
//  std::cout << std::endl;
//
//  return 0;
//}


//-----------------------------------------------------------------------------------------------------
//#include "ThreadPool.h"
//#include "root_certificates.hpp" // прописать свой путь
//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <boost/asio/ssl/error.hpp>
//#include <boost/asio/ssl/stream.hpp>
//#include <cstdlib>
//#include <iostream>
//#include <string>
//#include <fstream>
//
//using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
//namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
//namespace http = boost::beast::http;    // from <boost/beast/http.hpp>
//
//// Performs an HTTP GET and prints the response
//int main(int argc, char** argv)
//{
//  try
//  {
//    "Usage: http-client-sync-ssl <host> <port> <target> [<HTTP version: 1.0 or 1.1(default)>]\n"
//    "Example:\n"
//    "    http-client-sync-ssl www.example.com 443 /\n"
//    "    http-client-sync-ssl www.example.com 443 / 1.0\n";
//
//    // адрес страницы для скачивания: https://www.boost.org/doc/libs/1_69_0/libs/beast/example/http/client/sync-ssl/http_client_sync_ssl.cpp
//
//    auto const host = "www.boost.org";
//    auto const port = "443"; // https - 443, http - 80
//    auto const target = "/doc/libs/1_69_0/libs/beast/example/http/client/sync-ssl/http_client_sync_ssl.cpp"; //
//    int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;
//
//    // The io_context is required for all I/O
//    boost::asio::io_context ioc;
//
//    // The SSL context is required, and holds certificates
//    ssl::context ctx{ ssl::context::sslv23_client };
//
//    // This holds the root certificate used for verification
//    load_root_certificates(ctx);
//
//    // Verify the remote server's certificate
//    //ctx.set_verify_mode(ssl::verify_peer);
//
//    // These objects perform our I/O
//    tcp::resolver resolver{ ioc };
//    ssl::stream<tcp::socket> stream{ ioc, ctx };
//
//    // Set SNI Hostname (many hosts need this to handshake successfully)
//    if (!SSL_set_tlsext_host_name(stream.native_handle(), host))
//    {
//      boost::system::error_code ec{ static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category() };
//      throw boost::system::system_error{ ec };
//    }
//
//    // Look up the domain name
//    auto const results = resolver.resolve(host, port);
//
//    // Make the connection on the IP address we get from a lookup
//    boost::asio::connect(stream.next_layer(), results.begin(), results.end());
//
//    // Perform the SSL handshake
//    stream.handshake(ssl::stream_base::client);
//
//    // Set up an HTTP GET request message
//    http::request<http::string_body> req{ http::verb::get, target, version };
//    req.set(http::field::host, host);
//    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
//
//    // Send the HTTP request to the remote host
//    http::write(stream, req);
//
//    // This buffer is used for reading and must be persisted
//    boost::beast::flat_buffer buffer;
//
//    // Declare a container to hold the response
//    http::response<http::dynamic_body> res;
//
//    // Receive the HTTP response
//    http::read(stream, buffer, res);
//
//    // Write the message to out
//    std::ofstream ofs{"out.txt"}; // запись html-страницы в файл
//    ofs << res;
//    ofs.close();
//
//    // Gracefully close the stream
//    boost::system::error_code ec;
//    stream.shutdown(ec);
//    if (ec == boost::asio::error::eof)
//    {
//      // Rationale:
//      // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
//      ec.assign(0, ec.category());
//    }
//    if (ec)
//      throw boost::system::system_error{ ec };
//
//    // If we get here then the connection is closed gracefully
//  }
//  catch (std::exception const& e)
//  {
//    std::cerr << "Error: " << e.what() << std::endl;
//    return EXIT_FAILURE;
//  }
//  return EXIT_SUCCESS;
//}