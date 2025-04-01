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

  app_.route_dynamic("/getDataBetweenDates")([](const crow::request& req)
  {
    std::string date1 = req.url_params.get("date1");
    std::string hour1 = req.url_params.get("hour1");
    std::string date2 = req.url_params.get("date2");
    std::string hour2 = req.url_params.get("hour2");
    return crow::response(200, date1);
  });

  app_.port(18080);
  app_.run();
}
