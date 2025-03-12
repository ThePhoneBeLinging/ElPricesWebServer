#include "include/ElPricesWebServer/ElPricesWebServerController.h"

int main()
{
  auto var = new ElPricesWebServerController();
  var->addServePoint("/","../../FilesToServe/index.html");
  var->addEndPoint("/hello",[] () -> void { std::cout << "Hello World!" << std::endl; });
  var->startServer();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return 0;
}
