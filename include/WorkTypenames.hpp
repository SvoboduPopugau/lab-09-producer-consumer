//
// Created by vladislav on 12.04.2021.
//

#ifndef LAB_09_PRODUCER_CONSUMER_WORKTYPENAMES_H
#define LAB_09_PRODUCER_CONSUMER_WORKTYPENAMES_H

#include <string>
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
};


#endif  // LAB_09_PRODUCER_CONSUMER_WORKTYPENAMES_H
