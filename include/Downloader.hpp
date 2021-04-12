// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_DOWNLOADER_HPP_
#define INCLUDE_DOWNLOADER_HPP_

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include "../third-party/beast/example/common/root_certificates.hpp"

namespace http = boost::beast::http;
namespace ssl = boost::asio::ssl;

struct Page
{
  std::string protocol;
  std::string domain;
  std::string html_text;
};

struct EndPoint{
  std::string protocol;
  std::string domain;
  std::string target;
  auto operator=(EndPoint&& tmp)  noexcept -> EndPoint&;
};

class Downloader{
 public:
  Downloader() = default;
  Page DownloadPage(std::string URL);
 private:
  [[maybe_unused]] std::string GetHttpPage(std::string&& domain, std::string&& target);
  [[maybe_unused]] static std::string GetHttpsPage(std::string&& domain, std::string&& target);

 private:

};

#endif // INCLUDE_DOWNLOADER_HPP_
