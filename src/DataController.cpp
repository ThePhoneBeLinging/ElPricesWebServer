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
  std::unique_lock lock(mutex_);
  timeJSONObject_ = timeJSONObject;
  lock.unlock();
  notifyTime();
}

void DataController::setPriceJSONObject(const nlohmann::json& priceJSONObject)
{
  std::unique_lock lock(mutex_);
  priceJSONObject_ = priceJSONObject;
  lock.unlock();
  notifyPrice();
}

void DataController::setPowerJSONObject(const nlohmann::json& powerJSONObject)
{
  std::unique_lock lock(mutex_);
  powerJSONObject_ = powerJSONObject;
  lock.unlock();
  notifyPower();
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

void DataController::initialLoad()
{
  std::lock_guard lock(mutex_);
  for (auto res : subscribers_)
  {
    try
    {
      nlohmann::json json;
      json["Power"] = powerJSONObject_;
      json["Price"] = priceJSONObject_;
      json["Time"] = timeJSONObject_;
      res->send_text(json.dump());
    }
    catch (...)
    {
      // Optional: log the error
    }
  }
}

void DataController::notifyTime()
{
  std::lock_guard lock(mutex_);
  for (auto res : subscribers_)
  {
    try
    {
      nlohmann::json json;
      json["Time"] = timeJSONObject_;
      res->send_text(json.dump());
    }
    catch (...)
    {
      // Optional: log the error
    }
  }
}

void DataController::notifyPrice()
{
  std::lock_guard lock(mutex_);
  for (auto res : subscribers_)
  {
    try
    {
      nlohmann::json json;
      json["Price"] = priceJSONObject_;
      res->send_text(json.dump());
    }
    catch (...)
    {
      // Optional: log the error
    }
  }
}

void DataController::notifyPower()
{
  std::lock_guard lock(mutex_);
  for (auto res : subscribers_)
  {
    try
    {
      nlohmann::json json;
      json["Power"] = powerJSONObject_;
      res->send_text(json.dump());
    }
    catch (...)
    {
      // Optional: log the error
    }
  }
}
