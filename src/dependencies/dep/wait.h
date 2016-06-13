#ifndef _DEPENDENCIES_DEP_WAIT_H
#define _DEPENDENCIES_DEP_WAIT_H

#include <iostream> // size_t

namespace dep {

typedef size_t MillisecondType;

void sleepMilliseconds(MillisecondType milliseconds);

class Wait
{
  public:
    Wait(MillisecondType amountSet);

    friend
    std::ostream& operator<<(std::ostream& out, Wait const & wait);

    MillisecondType amount;
};

  
}

#endif