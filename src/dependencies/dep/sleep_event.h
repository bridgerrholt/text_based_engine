/// @file sleep_event.h
/// Complete definitions

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
template <class T = std::chrono::milliseconds>
class SleepEvent
{
  public:
    /// Primary constructor.
    /// @param[in] amountSet Sets amount.
    SleepEvent(size_t amount);

    /// Sleeps for the amount specified by @ref amount.
    void sleep() const;

    /// Flushes the stream and sleeps.
    /// @param[in] out The out stream being operated on.
    /// @param[in] sleepEvent The passed SleepEvent.
    friend
    std::ostream& operator<< <T>(std::ostream     & out,
                                 SleepEvent const & sleepEvent);

    /// Constructs @ref amount_ with the given value.
    /// @param[in] amount Passed to the construction of @ref amount_
    void   setAmount(size_t amount);

    /// Returns the underlying amount in @ref amount_;
    size_t getAmount() const;

  private:
    /// Mutable variable holding the amount of time to sleep.
    T amount_;
};

/// User-friendly default template type for SleepEvent.
typedef SleepEvent<> SleepEventDefault;



// Function definitions

template <class T>
SleepEvent<T>::SleepEvent(size_t amount) :
  amount_(amount)
{

}



template <class T>
void
SleepEvent<T>::sleep() const
{
  std::this_thread::sleep_for(amount_);
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
SleepEvent<T>::setAmount(size_t amount)
{
  amount_ = T(amount);
}



template <class T>
size_t
SleepEvent<T>::getAmount() const
{
  return amount_.count();
}



}

#endif