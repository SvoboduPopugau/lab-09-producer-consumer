// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_MANAGER_HPP_
#define INCLUDE_MANAGER_HPP_

#include <ThreadPool.h>

#include <fstream>
#include <string>

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
  std::atomic_size_t counter = 0;
  bool work_;
  std::string outputFile_;
  size_t depth_;
  ThreadPool downloadPool_;
  ThreadPool parsePool_;
  MyQueue<Url> findQueue_;
  MyQueue<Page> parseQueue_;
  MyQueue<EndPoint> writeQueue_;
};

#endif  // INCLUDE_MANAGER_HPP_
