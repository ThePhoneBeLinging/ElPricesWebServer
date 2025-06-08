//
// Created by eal on 08/06/25.
//

#include "ElPricesWebServer/DataController.h"

nlohmann::json DataController::getTimeJSONObject()
{
  std::lock_guard lock(mutex_);
  return timeJSONObject_;
}

nlohmann::json DataController::getPriceJSONObject()
{
  std::lock_guard lock(mutex_);
  return priceJSONObject_;
}

nlohmann::json DataController::getPowerJSONObject()
{
  std::lock_guard lock(mutex_);
  return powerJSONObject_;
}

void DataController::setTimeJSONObject(const nlohmann::json& timeJSONObject)
{
  std::lock_guard lock(mutex_);
  timeJSONObject_ = timeJSONObject;
}

void DataController::setPriceJSONObject(const nlohmann::json& priceJSONObject)
{
  std::lock_guard lock(mutex_);
  priceJSONObject_ = priceJSONObject;
}

void DataController::setPowerJSONObject(const nlohmann::json& powerJSONObject)
{
  std::lock_guard lock(mutex_);
  powerJSONObject_ = powerJSONObject;
}

void DataController::addSubscriber(crow::websocket::connection* res)
{
  std::lock_guard lock(mutex_);
  subscribers_.insert(res);
}

void DataController::removeSubscriber(crow::websocket::connection* res)
{
  subscribers_.erase(res);
}

void DataController::notifyPower()
{
  std::lock_guard lock(mutex_);
  for (auto res : subscribers_) {
    try {
      nlohmann::json combined;
      combined["Price"] = priceJSONObject_;
      combined["Power"] = powerJSONObject_;
      combined["Time"] = timeJSONObject_;
      res->send_text(combined.dump());
    } catch (...) {
      // Optional: log the error
    }
  }
}
