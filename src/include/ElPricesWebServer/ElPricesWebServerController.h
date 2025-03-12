//
// Created by eal on 12/03/25.
//

#ifndef ELPRICESWEBSERVERCONTROLLER_H
#define ELPRICESWEBSERVERCONTROLLER_H

#define CROW_LOG_LEVEL_NONE
#include <crow/app.h>

#include "EndPoint.h"
#include "ServePoint.h"
#include "IElPricesWebServer.h"

class ElPricesWebServerController : public IElPricesWebServer
{
public:
  ElPricesWebServerController() = default;
  ~ElPricesWebServerController();
  void startServer();
  void addServePoint(const std::string& path, const std::string& pathOfFileToServe) override;
  void addEndPoint(const std::string& path, const std::function<void()>& function) override;
private:
  void launch();
  std::vector<std::unique_ptr<ServePoint>> servePoints_;
  std::vector<std::unique_ptr<EndPoint>> endPoints_;
  crow::SimpleApp app_;
  std::thread thread_;
};



#endif //ELPRICESWEBSERVERCONTROLLER_H
