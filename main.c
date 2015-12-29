/* 
 * File:   main.c
 * Author: OJL
 *
 * Created on 2015年12月30日, 上午 12:46
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    /*
        "Sunday"    0
        "Monday"    1
        "Tuesday"   2
        "Wednesday" 3
        "Thursday"  4
        "Friday"    5
        "Saturday"  6
     */
    const char* week[] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };
    
    const int doomsday_month[12] = {
        3,                  //January 3(common years), January 4(leap years)
        28,                 //February 28(common years), February 29(leap years)
        7,                  //March 0 -> March 0+7
        4,                  //April 4   
        9,                  //May 9  
        6,                  //June 6
        11,                 //July 11
        8,                  //August 8
        5,                  //September 5
        10,                 //October 10
        7,                  //November 7
        12                 //December 12
    };
    
    const int doomsday_century[4] = {
        2,                //century mod 400 is equal 0 such as 0, 400, 800, 2000 doomsday is 2(Tues)
        0,                //century mod 400 is equal 100 such as 100, 500, 900, 1700 doomsday is 0(Sun)
        5,                //century mod 400 is equal 200 such as 200, 600, 1000, 1800 doomsday is 5(Fri)    
        3                 //century mod 400 is equal 300 such as 300, 700, 1100, 1900 doomsday is 3(Weds)
    };
    
    int year, month, day;
    int year_part;
    int offset;
    int doomsday;
    int century;
    int result;
    
    printf("enter year: ");
    scanf("%d", &year);
    printf("enter month: ");
    scanf("%d", &month);
    printf("enter day: ");
    scanf("%d", &day);
    
    /*
     *step1: get year last two digits
     *step2: calulate doomsday century
     *step3: every leap year the doomsday is increased by one
     *      so we can get doomsday offest by
     *      (doomsday century +　year last two digits + Floor(year last two digits / 4) ) % 7
     *step4: find the doomsday for month
     *step5: caluate day and doomsday offset
     *step6: add doomsday offest find the result
     */
    
    //step1: get year last two digits
    year_part = year % 100;
    
    //step2: calulate doomsday century
    century = (year / 100) % 4;
    
    /*
     step3: every leap year the doomsday is increased by one
            so we can get doomsday by
            (doomsday century +　year last two digits + Floor(year last two digits / 4) ) % 7
     */
    offset = (doomsday_century[century] + year_part + year_part / 4) % 7;
    
    //step4: find the doomsday for month
    doomsday = doomsday_month[month - 1];
    if(month < 3){//Jan or Feb
        if(is_leap(year))
            doomsday++; // January 4(leap years), February 29(leap years)
    }
    
    //step5: caluate day and doomsday offset
    if(day >= doomsday){
        result = (day - doomsday) % 7;
    }else{
        result = 7- ((doomsday - day) % 7);
    }
    //step6: add doomsday offest find the result
    result = (result + offset) % 7;
    
    printf("%d %d %d is %s\n", year, month, day, week[result]);
    return (EXIT_SUCCESS);
}

int is_leap(int year) {
    /*
     * pseudocode determine whether a year is a leap year
     * 
     * leap year is divisble 400 or not divisble 100 and divisble 4
    if (year is not exactly divisible by 4) then (it is a common year)
    else if (year is not exactly divisible by 100) then (it is a leap year)
    else if (year is not exactly divisible by 400) then (it is a common year)
    else (it is a leap year)
     
     */
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
        return 1;
    } else {
        return 0;
    }
}