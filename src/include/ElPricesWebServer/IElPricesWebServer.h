//
// Created by eal on 13/03/25.
//

#ifndef IELPRICESWEBSERVER_H
#define IELPRICESWEBSERVER_H
#include "functional"
#include "string"
class IElPricesWebServer
{
public:
  virtual ~IElPricesWebServer() = default;
  virtual void addServePoint(const std::string& path, const std::string& pathOfFileToServe) = 0;
  virtual void addEndPoint(const std::string& path, const std::function<void()>& function) = 0;
};

#endif //IELPRICESWEBSERVER_H
