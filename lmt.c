#include <stdio.h>
#include <time.h>

/* lmt.c: Shows your Local Mean Time (LMT) */
/* Copyright (C) 2024 Ellie McNeill */
/* For simplicity's sake, GMT = UTC = UT1 */
/* When leap seconds are abolished, they will drift apart */

#define LONGITUDE -3.75 /* Put YOUR (decimal) longitude here */

int main(){

    time_t posix;   /* POSIX time, seconds since 1970-01-01T00:00:00 */
    struct tm *gmt; /* Actually UTC, but close enough! */
    double lmt;     /* Local mean time in DECIMAL hours/mins/secs */
    float mins;
    int secs;

    time(&posix);   /* Get current POSIX time */
    gmt = gmtime(&posix);  /* Get current GMT (UTC) from POSIX */
    lmt = (gmt->tm_hour) + (float)(gmt->tm_min)/60 +
        (float)(gmt->tm_sec)/3600;  /* LMT initially set to GMT */

    lmt = lmt + (LONGITUDE / 15);	/* 15 degrees per hour rotation */
    if(lmt > 24)
        lmt = lmt - 24; /* Apply correction on overflow */
    if(lmt < 0)
        lmt = lmt + 24; /* Apply correction on underflow */

    mins = 60*(lmt-(int)lmt);
    secs = 60*(mins-(int)mins);

    printf("LMT is %02d:%02d:%02d\n", (int)lmt, (int)mins, secs);
}
