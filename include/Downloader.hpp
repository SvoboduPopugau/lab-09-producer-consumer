// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_DOWNLOADER_HPP_
#define INCLUDE_DOWNLOADER_HPP_

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace http = boost::beast::http;

struct EndPoint{
  std::string protocol;
  std::string domain;
  std::string target;
  auto operator=(EndPoint&& tmp)  noexcept -> EndPoint&;
};

class Downloader{
 public:
  Downloader() = default;
  std::string DownloadPage(std::string URL);
 private:
  std::string GetHttpPage(std::string&& domain, std::string&& target);
  std::string GetHttpsPage(std::string&& domain, std::string&& target);
};

#endif // INCLUDE_DOWNLOADER_HPP_
