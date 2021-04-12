//
// Created by vladislav on 12.04.2021.
//

#ifndef LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H
#define LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H

#include <string>
#include <vector>
#include "WorkTypenames.hpp"
#include <gumbo.h>

class HtmlParser {
 public:
//  Парсим страницу, находим href =
  static std::vector<EndPoint> GetLinks(const Page&& html_page);
//  Из данных получаемых на вход выделяем ссылки изображений,
//  Links изменяем так, чтобы в нем больше не было ссылок на фотографии
  static std::vector<EndPoint> GetPng(std::vector<EndPoint>& Links);
};


//TODO: При выводе ссылок, чтобы избежать ссылок вида http://http:// и подобных,
// при выписывании проверять, находится ли имя домена или протокола в теле target,
// если нет то выписывать Endpoint как "protocol + :// + domain + target" сделать
// это необходимо на этапе распределения ссылок по очередям записи и очередям скачивания
//


#endif  // LAB_09_PRODUCER_CONSUMER_HTMLPARSER_H
