#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <iostream>

#include "Manager.hpp"

namespace opt = boost::program_options;

int main(int argc, char** argv)
{
  opt::options_description desc;
  desc.add_options()
      ("help", "produce help")
      ("url", opt::value<std::string>(), "starting url address")
      ("depth", opt::value<size_t>(), "parse depth")
      ("network_threads", opt::value<size_t>(), "number of downloading threads")
      ("parser_threads", opt::value<size_t>(), "number of parsing threads")
      ("output", opt::value<std::string>(), "output absolute filename")
      ;
  opt::variables_map mp;

  opt::store(opt::parse_command_line(argc, argv, desc), mp);
  opt::notify(mp);

  if (mp.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }

  std::string url{};
  size_t depth{};
  size_t netThreads{};
  size_t parseThreads{};
  std::string filename{};

  if (mp.count("url"))
    url = mp["url"].as<std::string>();
  else
    url = "https://bmstu.ru/";

  if (mp.count("depth"))
    depth = mp["depth"].as<size_t>();
  else
    depth = 1;

  if (mp.count("network_threads"))
    netThreads = mp["network_threads"].as<size_t>();
  else
    netThreads = 1;

  if (mp.count("parser_threads"))
    parseThreads = mp["parser_threads"].as<size_t>();
  else
    parseThreads = 1;

  if (mp.count("output"))
    filename = mp["output"].as<std::string>();
  else
    filename = "images.txt";

  Manager manager(filename, depth, netThreads, parseThreads);
  manager.StartWork(url);
}
