#include "wait.h"

#include "current_milliseconds.h"

namespace dep {

void
sleepMilliseconds(size_t milliseconds)
{
  milliseconds += currentMilliseconds();

  while (currentMilliseconds() < milliseconds) {}
}



Wait::Wait(MillisecondType amountSet) :
  amount(amountSet)
{

}



std::ostream&
operator<<(std::ostream& out, Wait const & wait)
{
  out.flush();
  sleepMilliseconds(wait.amount);

  return out;
}



}