//
// Created by vladislav on 13.04.2021.
//

#include "Manager.hpp"

std::string ModifyToUrl(EndPoint& ep){
  if(ep.target.find("http")){
    return ep.target;
  }
  if(ep.target.substr(0, 2) == "//"){
    return ep.protocol + ':' + ep.target;
  }else if(ep.target.substr(0, 1) == "/"){
    return ep.protocol + "://" + ep.domain + ep.protocol;
  }
  return UNKNOWN_TARGET;
}

Manager::Manager(): work_(true),
                     outputFile_("IMG_references.txt"),
                     depth_(1),
                     downloadPool_(2),
                     parsePool_(2),
                     findQueue_(),
                     parseQueue_(),
                     writeQueue_() {}
Manager::Manager(std::string& filename, size_t& max_level, size_t& num_downloaders,
                 size_t& num_parsers): work_(true),
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
  if (file.is_open()){
    while (writeQueue_.Pop(item)){
      imgUrl = ModifyToUrl(item);
      if (imgUrl != UNKNOWN_TARGET){
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
  findQueue_.Push({start_URL, 1});
  Url url_item;
  Page page_item;

  while (work_){
    if(findQueue_.Empty()){
      continue;
    }
    else{
      while (findQueue_.Pop(url_item)){
        parseQueue_.Push(
            downloadPool_.enqueue(Downloader::DownloadPage,
                                  std::move(url_item.url),
                                  std::move(url_item.level)));
      }
    }

    if(parseQueue_.Empty())
      continue;
    else{
      while (parseQueue_.Pop(page_item)){
        writeQueue_.Push(
            parsePool_.enqueue([&page_item, this]{
              std::vector<EndPoint> Links = HtmlParser::GetLinks(std::move(page_item));
              std::vector<EndPoint> ImgLinks = HtmlParser::GetPng(Links);
              std::vector<Url> find_url;

              find_url.reserve(Links.size());
              for(auto& x : Links){
                find_url.push_back({ModifyToUrl(x), x.level});
              }

              findQueue_.Push(std::move(find_url));
              if (Links[0].level > depth_)
                work_ = false;
              return ImgLinks;
            })
        );
      }
    }
  }
  WriteIMGlinks();
}
