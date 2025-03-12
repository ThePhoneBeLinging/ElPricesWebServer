//
// Created by eal on 12/03/25.
//

#include "ElPricesWebServer/ElPricesWebServerController.h"
#include "Utility/Utility.h"


ElPricesWebServerController::~ElPricesWebServerController()
{
  app_.stop();
  thread_.join();
}

void ElPricesWebServerController::startServer()
{
  thread_ = std::thread(&ElPricesWebServerController::launch,this);
}

void ElPricesWebServerController::addServePoint(const std::string& path, const std::string& pathOfFileToServe)
{
  servePoints_.push_back(std::make_unique<ServePoint>(path, pathOfFileToServe));
}

void ElPricesWebServerController::addEndPoint(const std::string& path, const std::function<void()>& function)
{
  endPoints_.push_back(std::make_unique<EndPoint>(path, function));
}

void ElPricesWebServerController::launch()
{
  for (const auto& endPoint : servePoints_)
  {
      app_.route_dynamic(endPoint->getPath())([](){
        auto page = Utility::readFromFile("../../FilesToServe/index.html");
        return page;
      });
  }

  for (const auto& endPoint : endPoints_)
  {
    app_.route_dynamic(endPoint->getPath())([&endPoint]()
    {
      endPoint->getFunction()();
      return "";
    });
  }

  app_.port(18080);
  app_.run();
}
