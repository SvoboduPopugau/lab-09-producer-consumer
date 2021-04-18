//
// Created by vladislav on 12.04.2021.
//

#ifndef LAB_09_PRODUCER_CONSUMER_WORKTYPENAMES_H
#define LAB_09_PRODUCER_CONSUMER_WORKTYPENAMES_H

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

#endif  // LAB_09_PRODUCER_CONSUMER_WORKTYPENAMES_H
