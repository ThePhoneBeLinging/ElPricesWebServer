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
  CROW_ROUTE(app_,"/")([]()-> std::string
  {
    auto page = Utility::readFromFile("../../FilesToServe/index.html");
    return page;
  });
  CROW_ROUTE(app_,"/input")([]()-> std::string
  {
    auto page = Utility::readFromFile("../../FilesToServe/input.html");
    return page;
  });

  CROW_ROUTE(app_, "/getDataBetweenDates")([](const crow::request& req)
  {
    try
    {
      std::string date1 = req.url_params.get("date1");
      std::string hour1 = req.url_params.get("hour1");
      std::string date2 = req.url_params.get("date2");
      std::string hour2 = req.url_params.get("hour2");


      return crow::response(200);
    }
    catch (...)
    {
      return crow::response(400);
    }
  });

  app_.port(18080);
  app_.run();
}
