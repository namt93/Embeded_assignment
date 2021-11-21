#include<stdio.h>
#include<time.h>
#include<sys/time.h>


int main(void) {
    int hours, minutes, seconds, day, month, year;

    time_t now;

    time(&now);

    printf("Today is: %s", ctime(&now));

    struct tm *local = localtime(&now);

    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;

    day = local->tm_mday;
    month = local -> tm_mon + 1;
    year = local -> tm_year + 1900;

    if(hours < 12){
        printf("Time is: %02d:%02d:%02d am\n", hours, minutes, seconds);   
    } 
    else{
        printf("Time is: %02d:%02d:%02d pm\n", hours - 12, minutes, seconds); 
    }
    
    printf("Date is: %02d/%02d/%d\n", day, month, year);
    return 0;
}
