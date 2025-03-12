//
// Created by eal on 12/03/25.
//

#include "ElPricesWebServerController.h"

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

void ElPricesWebServerController::launch()
{

  CROW_ROUTE(app_, "/")([](){
    auto page = Utility::readFromFile("../../FilesToServe/index.html");
    return page;
  });
  app_.port(18080);
  app_.run();
}
