#include <iostream>
#include "Utility/Utility.h"
#include <crow/app.h>

#include "ElPricesWebServerController.h"

int main()
{
  auto var = new ElPricesWebServerController();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return 0;
}
