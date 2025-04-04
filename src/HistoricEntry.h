//
// Created by eal on 01/04/25.
//

#ifndef HISTORICENTRY_H
#define HISTORICENTRY_H

struct HistoricEntry
{
  int year;
  int month;
  int day;
  int hour;
  int pulses;
  int price;
  bool operator==(std::vector<HistoricEntry>::const_reference value) const
  {
    return year == value.year && month == value.month && day == value.day && hour == value.hour && pulses == value.pulses && price == value.price;
  }
};


#endif //HISTORICENTRY_H
