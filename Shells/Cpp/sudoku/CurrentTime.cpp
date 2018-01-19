#include"CurrentTime.hpp"
long currentTimeMillis(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return time;
}


