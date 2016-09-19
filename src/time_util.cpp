#include <ctime>
#include "time_util.hpp"

std::string time_util::formatRemainingTime(
  double startClockSec,
  int currentIndex,
  int numberOfData)
{
  double currentClockSec = std::clock() / double(CLOCKS_PER_SEC);

  if (currentIndex == 0 || startClockSec == currentClockSec) {
    char buffer[1024];
    sprintf(buffer, "%d/%d ??d day(s) ??:??:??\n", currentIndex, numberOfData);
    return buffer;
  }

  double secPerFile = (currentClockSec - startClockSec) / currentIndex;
  int remainedSec = (numberOfData - currentIndex) * secPerFile;
  int second = remainedSec % 60;
  int minute = remainedSec / 60 % 60;
  int hour = remainedSec / 3600 % 24;
  int day = remainedSec / 86400;
  char buffer[1024];
  sprintf(buffer, "%d/%d %d day(s) %d:%02d:%02d\n",
    currentIndex, numberOfData, day, hour, minute, second);
  return buffer;
}