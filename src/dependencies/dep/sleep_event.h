/// @file sleep_event.h
/// Complete definitions of the dep::SleepEvent class and helper functions.

#ifndef _DEPENDENCIES_DEP_SLEEP_EVENT_H
#define _DEPENDENCIES_DEP_SLEEP_EVENT_H

#include <iostream>
#include <thread>
#include <chrono>

namespace dep {

// Forward declarations

template <class T>
class SleepEvent;

// SleepEvent friend functions
template <class T>
std::ostream&
operator<<(std::ostream        & out,
           SleepEvent<T> const & sleepEvent);



/// Contains methods for sleeping a specified amount of time.
/// You may use SleepEventDefault if you are using T's default type.
template <class T = std::chrono::milliseconds>
class SleepEvent
{
  public:
    /// Primary constructor.
    /// @param[in] amountSet Used to construct @ref duration_.
    ///                      
    SleepEvent(size_t duration);

    /// Sleeps for the amount specified by @ref duration_.
    void sleep() const;

    /// Flushes the stream and sleeps.
    /// @param[in] out        The out stream being operated on.
    /// @param[in] sleepEvent The passed SleepEvent.
    /// @return The modified (flushed) stream (parameter @p out).
    friend
    std::ostream& operator<< <T>(std::ostream     & out,
                                 SleepEvent const & sleepEvent);

    /// Constructs @ref duration_ with the given value.
    /// @param[in] duration Passed to the construction of @ref duration_.
    void   setDuration(size_t duration);

    /// Returns the underlying value in @ref duration_.
    size_t getDuration() const;


  private:
    /// Mutable variable holding the amount of time to sleep.
    T duration_;
};

/// User-friendly default template type for SleepEvent.
typedef SleepEvent<> SleepEventDefault;



// Function definitions

template <class T>
SleepEvent<T>::SleepEvent(size_t duration) :
  duration_(duration)
{

}



template <class T>
void
SleepEvent<T>::sleep() const
{
  std::this_thread::sleep_for(duration_);
}



template <class T>
std::ostream&
operator<<(std::ostream& out, SleepEvent<T> const & sleepEvent)
{
  out.flush();
  sleepEvent.sleep();

  return out;
}



template <class T>
void
SleepEvent<T>::setDuration(size_t duration)
{
  duration_ = T(duration);
}



template <class T>
size_t
SleepEvent<T>::getDuration() const
{
  return duration_.count();
}



}

#endif