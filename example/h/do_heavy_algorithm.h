#pragma once

#ifdef __linux__
#include <sys/select.h>
#include <sys/time.h>
#endif

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

inline void org_msec_sleep(uint32_t msec)
{
#ifdef __linux__  // ubuntu 20.04のバグのワークアラウンド
    struct timeval tv = {msec / 1000, msec * 1000};
    select(0, NULL, NULL, NULL, &tv);
#elif __CYGWIN__
    std::this_thread::sleep_for(std::chrono::milliseconds{msec});
#else
    static_assert(false, "not support");
#endif
}

inline std::string do_heavy_algorithm(std::string str)
{
    org_msec_sleep(200);

    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    return str;
}
