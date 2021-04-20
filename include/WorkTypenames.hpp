// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_WORKTYPENAMES_HPP_
#define INCLUDE_WORKTYPENAMES_HPP_

#include <string>
struct Page {
  std::string protocol;
  std::string domain;
  std::string html_text;
  size_t level;
};

struct EndPoint {
  std::string protocol;
  std::string domain;
  std::string target;
  size_t level;
};

struct Url {
  std::string url;
  size_t level;
};

#endif  // INCLUDE_WORKTYPENAMES_HPP_
