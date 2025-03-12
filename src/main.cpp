#include "include/ElPricesWebServer/ElPricesWebServerController.h"

int main()
{
  auto var = new ElPricesWebServerController();
  var->addServePoint("/","../../FilesToServe/index.html");
  var->startServer();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return 0;
}
