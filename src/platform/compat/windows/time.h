/* Windows compatibility for time.h */
#ifndef TIME_H_COMPAT
#define TIME_H_COMPAT

#include <time.h>
#include <windows.h>

/* POSIX clock types from POSIX.1-2008 (clock_gettime parameter) */
#ifndef CLOCK_MONOTONIC
  #define CLOCK_MONOTONIC 1    /* Monotonic clock: cannot go backwards, unaffected by time adjustments */
#endif

#ifndef CLOCK_REALTIME
  #define CLOCK_REALTIME 0     /* Real-time clock: wall-clock time, affected by NTP/manual changes */
#endif

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

static inline int clock_gettime(int clk_id, struct timespec *tp) {
  static LARGE_INTEGER frequency = {0};
  LARGE_INTEGER counter;

  if (frequency.QuadPart == 0) {
    QueryPerformanceFrequency(&frequency);
  }

  QueryPerformanceCounter(&counter);

  tp->tv_sec = (time_t)(counter.QuadPart / frequency.QuadPart);
  tp->tv_nsec = (long)((counter.QuadPart % frequency.QuadPart) * 1000000000 / frequency.QuadPart);

  return 0;
}

#endif
