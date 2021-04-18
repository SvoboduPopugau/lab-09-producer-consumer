//
// Created by vladislav on 12.04.2021.
//

#ifndef LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H
#define LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H

#include <gumbo.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "MyQueue.hpp"
#include "WorkTypenames.hpp"

std::string ModifyToUrl(EndPoint& ep);

class HtmlParser {
 public:
  HtmlParser() = default;
  static void ParsePage(Page& page, MyQueue<EndPoint>& writeQueue,
                        MyQueue<Url>& findQueue, bool& Is_working,
                        size_t& depth);
  ~HtmlParser() = default;

 private:
  //  Парсим страницу, находим href =
  static std::vector<EndPoint> GetLinks(const Page& html_page);
  //  Из данных получаемых на вход выделяем ссылки изображений,
  //  Links изменяем так, чтобы в нем больше не было ссылок на фотографии
  static std::vector<EndPoint> GetPng(std::vector<EndPoint>& Links);
};

#endif  // LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H
