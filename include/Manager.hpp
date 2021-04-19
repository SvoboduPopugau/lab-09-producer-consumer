//
// Created by vladislav on 13.04.2021.
//

#ifndef LAB_09_PRODUCER_CONSUMER_MANAGER_HPP
#define LAB_09_PRODUCER_CONSUMER_MANAGER_HPP

#include <ThreadPool.h>

#include <fstream>

#include "Downloader.hpp"
#include "HtmlParser.hpp"
#include "MyQueue.hpp"
#include "WorkTypenames.hpp"

class Manager {
 public:
  Manager();
  Manager(std::string& filename, size_t& max_level, size_t& num_downloaders,
          size_t& num_parsers);
  void StartWork(std::string URL);
  bool WriteIMGlinks();
  ~Manager() = default;

 private:
  bool work_;
  std::string outputFile_;
  size_t depth_;
  ThreadPool downloadPool_;
  ThreadPool parsePool_;
  MyQueue<Url> findQueue_;
  MyQueue<Page> parseQueue_;
  MyQueue<EndPoint> writeQueue_;
};

#endif  // LAB_09_PRODUCER_CONSUMER_MANAGER_HPP
