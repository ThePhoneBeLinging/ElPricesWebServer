//
// Created by eal on 13/03/25.
//

#ifndef ENDPOINT_H
#define ENDPOINT_H
#include "string"
#include "functional"

class EndPoint
{
public:
  EndPoint(const std::string& path, const std::function<void()>& function): path_(path), function_(function)
  {}

  const std::string& getPath() const { return path_; }
  const std::function<void()>& getFunction() const { return function_; }

private:
  const std::string& path_;
  std::function<void()> function_;
};

#endif //ENDPOINT_H
