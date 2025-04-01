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
  app_.loglevel(crow::LogLevel::Error);
  thread_ = std::thread(&ElPricesWebServerController::launch, this);
}

void ElPricesWebServerController::launch()
{
  app_.route_dynamic("/")([]()-> std::string
  {
    auto page = Utility::readFromFile("../../FilesToServe/index.html");
    return page;
  });
  app_.route_dynamic("/input")([]()-> std::string
  {
    auto page = Utility::readFromFile("../../FilesToServe/input.html");
    return page;
  });

  app_.route_dynamic("/<string>/<string>")([](std::string from, std::string to)-> std::string
  {
    return from + " " + to;
  });

  app_.port(18080);
  app_.run();
}
