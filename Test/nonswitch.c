#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Please give me an int between 1 and 10: \n");
    int n = GetInt();
    if (n >= 1 && n <= 3)
    {
        printf("You picked a small int!\n");
    }
    else if (n >= 4 && n <= 7)
    {
        printf("You picked a medium int!\n");
    }
    else if (n >= 8 && n <= 10)
    {
        printf("You picked a large int!\n");
    }
    else 
    {
        printf("You picked an invalid int!\n");
    }
}
