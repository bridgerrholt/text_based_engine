/// @file sleep_event.h
/// Complete definitions of the dep::BasicSleepEvent class, helper functions, and typedefs.

/// @class dep::BasicSleepEvent
/// Contains methods for sleeping a specified amount of time.
/// You may use BasicSleepEventDefault if you are using T's default type.

#ifndef _DEPENDENCIES_DEP_SLEEP_EVENT_H
#define _DEPENDENCIES_DEP_SLEEP_EVENT_H

#include <iostream>
#include <thread>
#include <chrono>

namespace dep {

// Forward declarations

template <class T>
class BasicSleepEvent;

// BasicSleepEvent helper functions
/// Flushes the stream and sleeps.
/// @param[in] out        The out stream being operated on.
/// @param[in] BasicSleepEvent The passed BasicSleepEvent.
/// @return The modified (flushed) stream (parameter @p out).
template <class T>
std::ostream&
operator<<(std::ostream             & out,
           BasicSleepEvent<T> const & BasicSleepEvent);

// BasicSleepEvent class
template <class T = std::chrono::milliseconds>
class BasicSleepEvent
{
  public:
    /// Primary constructor.
    /// @param[in] amountSet Used to construct @ref duration_.
    BasicSleepEvent(std::size_t duration);

    /// Sleeps for the amount specified by @ref duration_.
    void sleep() const;

    /// Constructs @ref duration_ with the given value.
    /// @param[in] duration Passed to the construction of @ref duration_.
    void setDuration(std::size_t duration);

    /// Returns the underlying value in @ref duration_.
    std::size_t getDuration() const;


  private:
    /// Mutable variable holding the amount of time to sleep.
    T duration_;
};

/// User-friendly default template type for BasicSleepEvent.
typedef BasicSleepEvent<> SleepEvent;



// Function definitions

template <class T>
BasicSleepEvent<T>::BasicSleepEvent(size_t duration) :
  duration_(duration)
{

}



template <class T>
void
BasicSleepEvent<T>::sleep() const
{
  std::this_thread::sleep_for(duration_);
}



template <class T>
std::ostream&
operator<<(std::ostream& out, BasicSleepEvent<T> const & BasicSleepEvent)
{
  out.flush();
  BasicSleepEvent.sleep();

  return out;
}



template <class T>
void
BasicSleepEvent<T>::setDuration(size_t duration)
{
  duration_ = T(duration);
}



template <class T>
size_t
BasicSleepEvent<T>::getDuration() const
{
  return duration_.count();
}



}

#endif