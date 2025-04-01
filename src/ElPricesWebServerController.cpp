//
// Created by eal on 12/03/25.
//

#include "ElPricesWebServer/ElPricesWebServerController.h"

#include <DatabaseAccessController/DatabaseAccessController.h>

#include "HistoricEntry.h"
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
  CROW_ROUTE(app_, "/")([]()-> std::string
  {
    auto page = Utility::readFromFile("../../FilesToServe/index.html");
    return page;
  });
  CROW_ROUTE(app_, "/input")([]()-> std::string
  {
    auto page = Utility::readFromFile("../../FilesToServe/input.html");
    return page;
  });

  CROW_ROUTE(app_, "/getDataBetweenDates")([](const crow::request& req)
  {
    try
    {
      std::string year1String = req.url_params.get("year1");
      std::string month1String = req.url_params.get("month1");
      std::string day1String = req.url_params.get("day1");
      std::string hour1String = req.url_params.get("hour1");
      std::string year2String = req.url_params.get("year2");
      std::string month2String = req.url_params.get("month2");
      std::string day2String = req.url_params.get("day2");
      std::string hour2String = req.url_params.get("hour2");

      int year1 = std::stoi(year1String);
      int month1 = std::stoi(month1String);
      int day1 = std::stoi(day1String);
      int hour1 = std::stoi(hour1String);

      int year2 = std::stoi(year2String);
      int month2 = std::stoi(month2String);
      int day2 = std::stoi(day2String);
      int hour2 = std::stoi(hour2String);

      std::vector<HistoricEntry> historicEntries;

      while (year1 != year2 && month1 != month2 && day1 != day2 && hour1 != hour2)
      {
        HistoricEntry historicEntry;


        historicEntries.push_back(historicEntry);
        hour1++;
        if (hour1 == 24)
        {
          hour1 = 0;
          day1++;
          if (day1 == 32)
          {
            day1 = 0;
            month1++;
            if (month1 == 13)
            {
              month1 = 1;
              year1++;
            }
          }
        }
      }


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
