// Copyright 2020 Your Name <your_email>

#include "Manager.hpp"

#include <utility>

Manager::Manager()
    : work_(true),
      outputFile_("IMG_references.txt"),
      depth_(2),
      downloadPool_(4),
      parsePool_(4),
      findQueue_(),
      parseQueue_(),
      writeQueue_() {}
Manager::Manager(std::string& filename, size_t& max_level,
                 size_t& num_downloaders, size_t& num_parsers)
    : work_(true),
      outputFile_(filename),
      depth_(max_level),
      downloadPool_(num_downloaders),
      parsePool_(num_parsers),
      findQueue_(),
      parseQueue_(),
      writeQueue_() {}
bool Manager::WriteIMGlinks() {
  std::ofstream file;
  EndPoint item;
  std::string imgUrl;
  file.open(outputFile_);
  if (file.is_open()) {
    while (writeQueue_.Pop(item)) {
      imgUrl = ModifyToUrl(item);
      if (imgUrl != "Unknown url") {
        file << imgUrl << std::endl;
      }
    }
    file.close();
    return true;
  } else {
    return false;
  }
}
void Manager::StartWork(std::string start_URL) {
  findQueue_.Push({std::move(start_URL), 1});
  Url url_item;
  Page page_item;

  while (work_) {
      while (findQueue_.Pop(url_item)) {
        if (url_item.level <= depth_) {
          downloadPool_.enqueue(
              [this](Url item) {
                ++counter;
                Downloader::DownloadPage(item.url, item.level, &parseQueue_);
              },
              url_item);
        }
//        else {
//          work_ = false;
//          break;
//        }
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(5));

      while (parseQueue_.Pop(page_item)) {
        if (page_item.level <= depth_) {
          parsePool_.enqueue(
              [this](Page page) {
                HtmlParser::ParsePage(page, writeQueue_, findQueue_, depth_);
                --counter;
              },
              page_item);
        }
      }

      if (parseQueue_.Empty() && findQueue_.Empty() && !counter) {
        work_ = false;
      }
  }
  WriteIMGlinks();
}
