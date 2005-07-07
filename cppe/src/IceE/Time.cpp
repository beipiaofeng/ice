// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICEE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceE/Time.h>

#ifndef _WIN32_WCE
#  if defined(_WIN32)
#    include <sys/timeb.h>
#    include <time.h>
#  else
#    include <sys/time.h>
#  endif
#endif

using namespace Ice;

Time::Time() :
    _usec(0)
{
}

Time
Ice::Time::now()
{
#if defined(_WIN32_WCE)
    //
    // Note that GetTickCount returns the number of ms since the
    // device was started. Time cannot be used to represent an
    // absolute time on CE since GetLocalTime doesn't have millisecond
    // resolution.
    //
    return Time(GetTickCount() * 1000);
#elif defined(_WIN32)
    struct _timeb tb;
    _ftime(&tb);
    return Time(tb.time * static_cast<Int64>(1000000) + tb.millitm * static_cast<Int64>(1000));
#else
    struct timeval tv;
    gettimeofday(&tv, 0);
    return Time(tv.tv_sec * static_cast<Int64>(1000000) + tv.tv_usec);
#endif
}

Time
Ice::Time::seconds(Int64 t)
{
    return Time(t * static_cast<Int64>(1000000));
}

Time
Ice::Time::milliSeconds(Int64 t)
{
    return Time(t * static_cast<Int64>(1000));
}

Time
Ice::Time::microSeconds(Int64 t)
{
    return Time(t);
}

Ice::Time::operator timeval() const
{
    timeval tv;
    tv.tv_sec = static_cast<long>(_usec / 1000000);
    tv.tv_usec = static_cast<long>(_usec % 1000000);
    return tv;
}

Int64
Ice::Time::toSeconds() const
{
    return _usec / 1000000;
}

Int64
Ice::Time::toMilliSeconds() const
{
    return _usec / 1000;
}

Int64
Ice::Time::toMicroSeconds() const
{
    return _usec;
}

double
Ice::Time::toSecondsDouble() const
{
    return _usec / 1000000.0;
}

double
Ice::Time::toMilliSecondsDouble() const
{
    return _usec / 1000.0;
}

double
Ice::Time::toMicroSecondsDouble() const
{
    return static_cast<double>(_usec);
}

Time::Time(Int64 usec) :
    _usec(usec)
{
}
