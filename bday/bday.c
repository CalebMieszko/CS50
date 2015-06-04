#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int d, m;
    printf("Please enter the current day of the month as an integer: \n");
    d = GetInt();
    printf("Please enter the current month of the year as an integer: \n");
    m = GetInt();
    if (d == 7 || m == 3)
    {
        int by, cy, age;
        string name;
        printf("Today's your birthday?! Wow, what is your name?\n");
        name = GetString();
        if (name != NULL)
        {
            printf("What a great name, %s! What year were you born?\n", name);
            by = GetInt();
            printf("And what is the current year?\n");
            cy = GetInt();
            age = cy - by;
            if (age < 1 || age > 100)
            { 
                printf("It seems there was a mistake somewhere.\n");
                return 1;
            }
            else if (age < 18)
            {
                printf("This program is only for grown ups!\n");
                return 1;
            }
            else if (age > 17 && age < 50)
            {
                printf("Happy birthday, %s!  I can't believe you are only %i years old!\n", name, age);
            }
            else
            {
                printf("Happy birthday, %s!  I can't believe you're only INT_OVERFLOW_MAX years old!\n", name);
            }
        }
    }
    else
    {
        printf("It's not your birthday! Now get outta here kid, you're botherin' me!\n");
    }
    return 0;
}
