#ifdef USE_SYSTEM_MODULE
#ifdef USE_CONCURRENCY_COMPONENTS

#ifndef _H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED
#define _H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED

#include <cstdint>

#ifdef _WIN32
#include <intrin.h>
#elif defined __gnu_linux__
#include <pthread.h>
#endif

#include "system/errors/module.h"

namespace System
{
    inline long AtomicCompareExchange(volatile int32_t* value, int32_t exchange, int32_t compare)
	{
#ifdef _WIN32
		return _InterlockedCompareExchange((volatile long*)value, (long)exchange, (long)compare);
#elif defined __gnu_linux__
        //TODO: Implement
        (void)value;
        (void)exchange;
        (void)compare;
        throw PunkNotImplemented(L"Not implemented");
#endif

	}

    inline long AtomicIncrement32(volatile int32_t* value)
	{
#ifdef _WIN32
		return _InterlockedIncrement((volatile long*)value);
#elif defined __gnu_linux__
        (void)value;
        throw PunkNotImplemented();
#endif
	}

    inline short AtomicIncrement16(volatile int16_t* value)
	{
#ifdef _WIN32
		return _InterlockedIncrement16(value);
#elif defined __gnu_linux__
        (void)value;
        throw PunkNotImplemented();
#endif
	}

    inline long AtomicDecrement32(volatile int32_t* value)
	{
#ifdef _WIN32
		return _InterlockedDecrement((volatile long*)value);
#elif defined __gnu_linux__
        (void)value;
        throw PunkNotImplemented();
#endif
	}

    inline long AtomicDecrement16(volatile int16_t* value)
	{
#ifdef _WIN32
		return _InterlockedDecrement16(value);
#elif defined __gnu_linux__
        (void)value;
        throw PunkNotImplemented();
#endif
	}
}

#endif	//	_H_PUNK_SYSTEM_CONCURRENCY_INTERLOCKED
#endif
#endif

