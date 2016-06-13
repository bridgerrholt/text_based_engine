#include <chrono>

namespace dep {

long
currentMilliseconds()
{
  using namespace std::chrono;

  return duration_cast<milliseconds>(
    system_clock::now().time_since_epoch()
  ).count();
}
  
}