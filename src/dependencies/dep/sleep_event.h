/// @file sleep_event.h
/// Declaration and definition of the class template dep::BasicSleepEvent and
/// its associated functions and instansiated typedefs.

#ifndef _DEPENDENCIES_DEP_SLEEP_EVENT_H
#define _DEPENDENCIES_DEP_SLEEP_EVENT_H

#include <iostream>
#include <thread>
#include <chrono>

namespace dep {

// Forward declarations

template <class T>
class BasicSleepEvent;



// BasicSleepEvent's associated functions

/// Flushes the stream and sleeps.
/// @param[in] out        The out stream being operated on.
/// @param[in] sleepEvent The passed BasicSleepEvent object.
/// @return The modified (flushed) stream (parameter @p out).
template <class T>
std::ostream&
operator<<(std::ostream             & out,
           BasicSleepEvent<T> const & sleepEvent);



/// Contains methods for sleeping a specified amount of time.
/// You may use SleepEvent if you are using T's default type.
/// @param T The duration type to use.
template <class T = std::chrono::milliseconds>
class BasicSleepEvent
{
  public:
    /// Primary constructor.
    /// @param[in] duration The amount of time (of unit @ref T) to sleep for.
    ///                     Used in the construction of @ref duration_.
    BasicSleepEvent(std::size_t duration);

    /// Sleeps for the amount last specified (@ref duration_).
    void sleep() const;

    /// Changes the amount of time to sleep for (@ref duration_).
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
BasicSleepEvent<T>::BasicSleepEvent(std::size_t duration) :
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
void
BasicSleepEvent<T>::setDuration(std::size_t duration)
{
  duration_ = T(duration);
}



template <class T>
std::size_t
BasicSleepEvent<T>::getDuration() const
{
  return duration_.count();
}



template <class T>
std::ostream&
operator<<(std::ostream& out, BasicSleepEvent<T> const & BasicSleepEvent)
{
  out.flush();
  BasicSleepEvent.sleep();

  return out;
}



}

#endif