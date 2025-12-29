#include <stdio.h>
#include <time.h>
int main()
{
    time_t raw_time; 
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time)
}