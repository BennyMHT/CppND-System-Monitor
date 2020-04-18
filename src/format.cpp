#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  long hour = seconds/60/60;
  long minute = seconds/60%60;
  long second = seconds%60;
  string Hour = (hour > 10? "" : "0")+to_string(hour);
  string Minute = (minute > 10? "" : "0")+to_string(minute);
  string Second = (second > 10? "" : "0")+to_string(second);
  return Hour + ":" + Minute + ":" + Second;
}