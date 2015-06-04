#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Please give me an int: \n");
    int n = GetInt();
    
    if (n > 0)
    {
        printf("You picked a positive int!\n");
    }
    else if (n == 0) 
    {
        printf("You picked zero!\n"); 
    }
    else
    {
        printf("You picked a negative int!\n");
    }
}
