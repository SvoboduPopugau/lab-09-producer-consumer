#ifndef INCLUDE_MYQUEUE_HPP_
#define INCLUDE_MYQUEUE_HPP_

#include <mutex>
#include <queue>
#include "Downloader.hpp"

template <typename T>
class MyQueue{
 public:
  MyQueue(): queue_(), mutex_(){};
  void Push(T& other){
    std::lock_guard{mutex_};
    queue_.push(other);
  }
  void Push(T&& other){
    std::lock_guard{mutex_};
    queue_.push(std::move(other));
  }
  void Push(std::vector<T>&& others){
    std::lock_guard{mutex_};
    for(auto& x : others)
      queue_.push(x);
  }
  void Push(std::future<T>& other){
    std::lock_guard{mutex_};
    queue_.push(other.get());
  }
  void Push(std::future<T>&& other){
    std::lock_guard{mutex_};
    queue_.push(std::move(other.get()));
  }
  void Push(std::vector<std::future<T> >&& other){
    std::lock_guard{mutex_};
    for(auto& x : other)
      queue_.push(x.get());
  }
  bool Empty(){
    return queue_.empty();
  }
  bool Pop(T& item) {
    if (queue_.empty()) return false;

    item = std::move(queue_.front());
    queue_.pop();
    return true;
  }
 private:
  std::queue<T> queue_;
  std::mutex mutex_;
};

#endif // INCLUDE_MYQUEUE_HPP_