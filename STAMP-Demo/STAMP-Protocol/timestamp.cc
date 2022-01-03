#include "stamp.h"

#include <sys/time.h>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <QDebug>

// 获取ntp时间戳
Packet get_timestamp()
{
    timespec tn;
    clock_gettime(CLOCK_REALTIME, &tn);
    tn.tv_nsec = hton_any<uint32_t>(tn.tv_nsec);
    tn.tv_sec = hton_any<uint32_t>(tn.tv_sec);
    Packet timestamp(8);
    memcpy(timestamp.get(), &(tn.tv_sec), 4);
    memcpy(timestamp.get() + 4, &(tn.tv_nsec), 4);
    return timestamp;
}
