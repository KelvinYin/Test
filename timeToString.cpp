#include <time.h>
#include <sys/time.h>
#include <cstdio>
#include <iostream>

// 当前时间转换成字符串格式 
// 格式：YYYYMMDD HH:mm:ss.uuuuuu
//       YYYYMMDD HH:mm:ss
// showMicroseconds：是否显示微秒时间 false-不显示 true-显示
std::string timeToString(bool showMicroseconds)
{  
    char buf[32] = {0};
    struct timeval tv;
    gettimeofday(&tv, NULL);
    time_t seconds = static_cast<time_t>(tv.tv_sec);
    struct tm tm_time;
    localtime_r(&seconds, &tm_time); // local timezone

    if (showMicroseconds)
    {
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                static_cast<unsigned int>(tv.tv_usec));
    }
    else
    {
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
    return buf;
}

int main()
{
    std::cout << timeToString(false) << std::endl;
    std::cout << timeToString(true) << std::endl;
    
    return 0;
}
