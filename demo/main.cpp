
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
#include <iostream>
#include <vector>
#include <chrono>

#include "../third-party/ThreadPool/ThreadPool.h"

int func(int i){
  std::this_thread::sleep_for(std::chrono::seconds(5));
//  mutex.lock();
  std::cout <<"world " << i <<  "-" << std::endl;
//  mutex.unlock();
  return i*i;

}

int main()
{

  ThreadPool pool(4);
  std::vector< std::future<int> > results;
  std::mutex m;
  for(int i = 1; i < 8; ++i) {
    results.emplace_back(
        pool.enqueue(func, i)
    );
  }

  for(auto && result: results)
    std::cout << result.get() << "_ ";
  std::cout << std::endl;

  return 0;
}
