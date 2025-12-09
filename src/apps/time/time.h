#ifndef TIME_H
#define TIME_H

#include <stdint.h>

void set_timezone(int new);
int get_timezone();

void init_rtc();
int get_time(int *h, int *m, int *s);

#endif