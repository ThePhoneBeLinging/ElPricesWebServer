//
// Created by eal on 12/03/25.
//

#ifndef ELPRICESWEBSERVERCONTROLLER_H
#define ELPRICESWEBSERVERCONTROLLER_H

#define CROW_LOG_LEVEL_NONE
#include <crow/app.h>

class ElPricesWebServerController
{
public:
  ElPricesWebServerController();
  ~ElPricesWebServerController();
private:
  void launch();
  crow::SimpleApp app_;
  std::thread thread_;
};



#endif //ELPRICESWEBSERVERCONTROLLER_H
