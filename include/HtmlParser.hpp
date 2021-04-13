//
// Created by vladislav on 12.04.2021.
//

#ifndef LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H
#define LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H

#include <string>
#include <vector>
#include "WorkTypenames.hpp"
#include <gumbo.h>
#include "MyQueue.hpp"

class HtmlParser {
 public:
  static void ParsePage(Page& page, MyQueue<Page>* parseQueue, MyQueue<EndPoint>* writeQueue, MyQueue<Url>* findQueue);
 private:
//  Парсим страницу, находим href =
  static std::vector<EndPoint> GetLinks(const Page&& html_page);
//  Из данных получаемых на вход выделяем ссылки изображений,
//  Links изменяем так, чтобы в нем больше не было ссылок на фотографии
  static std::vector<EndPoint> GetPng(std::vector<EndPoint>& Links);
};


#endif  // LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H
