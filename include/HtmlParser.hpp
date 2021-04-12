//
// Created by vladislav on 12.04.2021.
//

#ifndef LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H
#define LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H

#include <string>
#include <vector>

struct Page
{
    std::string html_text;
    std::string domain;
    std::string protocol;
};

class HtmlParser {
  std::vector<std::string> GetLinks(Page html_page);
  std::vector<std::string> GetPng(std::vector<std::string> Links);
};

#endif  // LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H
