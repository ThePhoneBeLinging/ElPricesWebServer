//
// Created by eal on 13/03/25.
//

#ifndef SERVEPOINT_H
#define SERVEPOINT_H
#include "string"
class ServePoint
{
public:
  ServePoint(const std::string& path, const std::string& pathOfFileToServe)
  {
    path_ = path;
    pathOfFileToServe_ = pathOfFileToServe;
  }

  const std::string& getPath()
  {
    return path_;
  }

  const std::string& getPathOfFileToServe()
  {
    return pathOfFileToServe_;
  }

private:
  std::string path_;
  std::string pathOfFileToServe_;
};


#endif //SERVEPOINT_H
