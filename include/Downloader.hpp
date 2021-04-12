// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_DOWNLOADER_HPP_
#define INCLUDE_DOWNLOADER_HPP_

#include <boost/asio.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../third-party/beast/example/common/root_certificates.hpp"
#include "WorkTypenames.hpp"

namespace http = boost::beast::http;
namespace ssl = boost::asio::ssl;

class Downloader{
 public:
  Downloader() = default;
  Page DownloadPage(const std::string& URL);
 private:
  [[maybe_unused]] std::string GetHttpPage(std::string&& domain, std::string&& target);
  [[maybe_unused]] static std::string GetHttpsPage(std::string&& domain, std::string&& target);

 private:

};

#endif // INCLUDE_DOWNLOADER_HPP_
