#include "wait.h"

#include "current_milliseconds.h"

namespace dep {

void
wait(size_t milliseconds)
{
  milliseconds += currentMilliseconds();

  while (currentMilliseconds() < milliseconds) {}
}
  
}