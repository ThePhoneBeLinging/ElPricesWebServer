#include <iostream>

#include "ElPricesWebServer/ElPricesWebServerController.h"

int main()
{
  auto var = std::make_unique<ElPricesWebServerController>();
  var->startServer();
  std::this_thread::sleep_for(std::chrono::seconds(25));
  return 0;
}
