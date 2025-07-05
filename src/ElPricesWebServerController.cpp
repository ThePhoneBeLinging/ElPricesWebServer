//
// Created by eal on 12/03/25.
//

#include "ElPricesWebServer/ElPricesWebServerController.h"

#include <DatabaseAccessController/DatabaseAccessController.h>

#include "HistoricEntry.h"
#include "include/ElPricesWebServer/DataController.h"
#include "Utility/ConfigController.h"
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
  CROW_ROUTE(app_, "/example")([]()-> std::string
  {
    auto page = Utility::readFromFile("../../FilesToServe/example.html");
    return page;
  });
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

  CROW_WEBSOCKET_ROUTE(app_, "/ws")
    .onopen([&](crow::websocket::connection& conn)
                                   {
                                     {
                                       DataController::addSubscriber(&conn);
                                     }
                                   })
  .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary)
                                   {
                                     std::this_thread::sleep_for(std::chrono::seconds(1));
                                     DataController::initialLoad();
                                   })
    .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t)
                                   {
                                     DataController::removeSubscriber(&conn);
                                   });


  CROW_ROUTE(app_, "/getDataBetweenDates")([](const crow::request& req)
  {
    std::vector<HistoricEntry> historicEntries;
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


      auto pulseDBLock = DatabaseAccessController::getDatabase("PULSEDB");
      auto priceDBLock = DatabaseAccessController::getDatabase("PRICEDB");

      while (year1 != year2 || month1 != month2 || day1 != day2 || hour1 != hour2)
      {
        HistoricEntry historicEntry = HistoricEntry();
        std::string dayString = "";
        if (day1 < 10)
        {
          dayString += "0";
        }
        dayString += std::to_string(day1);
        dayString += ".";
        if (month1 < 10)
        {
          dayString += "0";
        }

        dayString += std::to_string(month1);
        dayString += ".";
        dayString += std::to_string(year1);

        std::string getPriceQuery = "SELECT * FROM Prices WHERE Hour == ? AND Date==?";
        SQLite::Statement getPriceStatement(*priceDBLock->getDatabase(), getPriceQuery);
        getPriceStatement.bind(1, hour1);
        getPriceStatement.bind(2, dayString);

        while (getPriceStatement.executeStep())
        {
          historicEntry.price = getPriceStatement.getColumn(1).getInt();
          historicEntry.price += getPriceStatement.getColumn(2).getInt();
        }

        std::string getPulseIDQuery = "SELECT ID FROM PulseDates WHERE Year==? AND Month==? AND Day==?";
        SQLite::Statement getPulseIDStatement(*pulseDBLock->getDatabase(), getPulseIDQuery);
        getPulseIDStatement.bind(1, year1);
        getPulseIDStatement.bind(2, month1);
        getPulseIDStatement.bind(3, day1);
        while (getPulseIDStatement.executeStep())
        {
          int pulseDateID = getPulseIDStatement.getColumn(0).getInt();
          std::string getPulsesQuery = "SELECT * FROM PulseHours WHERE PulseDateID==? AND Hour==?";
          SQLite::Statement getPulsesStatement(*pulseDBLock->getDatabase(), getPulsesQuery);
          getPulsesStatement.bind(1, pulseDateID);
          getPulsesStatement.bind(2, hour1);
          while (getPulsesStatement.executeStep())
          {
            historicEntry.pulses = getPulsesStatement.getColumn(2).getInt();
          }
        }
        historicEntry.hour = hour1;
        historicEntry.day = day1;
        historicEntry.month = month1;
        historicEntry.year = year1;
        historicEntries.push_back(historicEntry);
        hour1++;
        if (hour1 == 24)
        {
          hour1 = 0;
          day1++;
          if (day1 == 32)
          {
            day1 = 1;
            month1++;
            if (month1 == 13)
            {
              month1 = 1;
              year1++;
            }
          }
        }
      }
      int totalWHUsed = 0;
      int totalPrice = 0;
      // Create JSON string with a list of historicEntries
      std::string returnString;
      returnString += "{\n";
      returnString += "\"historicPrices\": ";
      returnString += "[\n";
      for (auto entry : historicEntries)
      {
        double price = entry.price / 10000.0;
        returnString += "{\n";
        returnString += "\"Year\":" + std::to_string(entry.year) + ",\n";
        returnString += "\"Month\":" + std::to_string(entry.month) + ",\n";
        returnString += "\"Day\":" + std::to_string(entry.day) + ",\n";
        returnString += "\"Hour\":" + std::to_string(entry.hour) + ",\n";
        returnString += "\"Price\":" + std::to_string(price) + ",\n";
        returnString += "\"Pulses\":" + std::to_string(entry.pulses) + ",\n";
        returnString += "\"UsageDKK\":" + std::to_string(price * entry.pulses / 1000) + "\n";
        returnString += "}";
        totalWHUsed += entry.pulses;
        totalPrice += price * entry.pulses / 1000;
        if (entry != historicEntries.back())
        {
          returnString += ",\n";
        }
      }
      returnString += "],\n";
      returnString += "\"TotalPrice\":" + std::to_string(totalPrice) + ",\n";
      returnString += "\"TotalWH\":" + std::to_string(totalWHUsed) + "\n";
      returnString += "}";
      return crow::response(returnString);
    }
    catch (const std::exception& e)
    {
      std::string msg = e.what();
      return crow::response(400, msg);
    }
  });
  int webServerPort = ConfigController::getConfigInt("WebServerPort");
  app_.port(webServerPort);
  app_.run();
}
