#include <stdint.h>
#include "interprer/ports/ports.h"

#define rtc_index 0x70
#define rtc_data 0x71

#define seconds 0x00
#define minutes 0x02
#define hours 0x04

int time_zone = 3;

void set_timezone(int new)
{
    time_zone = new;
}

int get_tinezone()
{
    return time_zone;
}

static void rtc_wait()
{
    outb(rtc_index, 0x0a);
    while (inb(rtc_data) & 0x80)
        outb(rtc_index, 0x0a);
}

void init_rtc()
{
    outb(rtc_index, 0x0b);
    uint8_t reg_b = inb(rtc_data);
    reg_b |= 0x02;
    reg_b |= 0x40;
    outb(rtc_index, 0x0b);
    outb(rtc_data, reg_b);
}

int read_rtc(uint8_t index)
{
    outb(rtc_index, index);
    return inb(rtc_data);
}
uint8_t bcd_to_bin(uint8_t bcd) { return (bcd >> 4) * 10 + (bcd & 0x0F); }

int get_time(int *h, int *m, int *s)
{
    rtc_wait();

    *s = bcd_to_bin(read_rtc(seconds) & 0x7f);
    *m = bcd_to_bin(read_rtc(minutes) & 0x7f);
    *h = (bcd_to_bin(read_rtc(hours) & 0x3f) + time_zone) % 24;
}