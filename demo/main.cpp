
//TODO: Почему не работают add_options() в po

//#include <boost/program_options.hpp>
//#include <boost/program_options/options_description.hpp>
//
//namespace opt = boost::program_options;
//
//int main(int argc, char** argv)
//{
//  opt::option_description desc;
//  desc.add_options()
//      ("help", "produce help")
//      ("time", opt::value<double>()-> default_value(10), "user\'s time value")
//      ;
//}

//-------------------------------------------------------------------------------------
//#include <iostream>
//#include <vector>
//#include <chrono>
//
//#include "../third-party/ThreadPool/ThreadPool.h"
//
//int func(int i){
//  std::this_thread::sleep_for(std::chrono::seconds(5));
////  mutex.lock();
//  std::cout <<"world " << i <<  "-" << std::endl;
////  mutex.unlock();
//  return i*i;
//
//}
//
//int main()
//{
//
//  ThreadPool pool(4);
//  std::vector< std::future<int> > results;
//  std::mutex m;
//  for(int i = 1; i < 8; ++i) {
//    results.emplace_back(
//        pool.enqueue(func, i)
//    );
//  }
//
//  for(auto && result: results)
//    std::cout << result.get() << "_ ";
//  std::cout << std::endl;
//
//  return 0;
//}
//#include <Downloader.hpp>
//int main(){
//  Downloader downloader;
//  Page page = downloader.DownloadPage("https://en.wikipedia.org/wiki/Samurai");
//  std::cout << page.html_text << std::endl;
//}

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

#include "gumbo.h"

static void search_for_links(GumboNode* node) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    std::cout << href->value << std::endl;
  }

  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    search_for_links(static_cast<GumboNode*>(children->data[i]));
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: find_links <html filename>.\n";
    exit(EXIT_FAILURE);
  }
  const char* filename = argv[1];

  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (!in) {
    std::cout << "File " << filename << " not found!\n";
    exit(EXIT_FAILURE);
  }

  std::string contents;
  in.seekg(0, std::ios::end);
  contents.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&contents[0], contents.size());
  in.close();

  GumboOutput* output = gumbo_parse(contents.c_str());
  search_for_links(output->root);
  gumbo_destroy_output(&kGumboDefaultOptions, output);
}