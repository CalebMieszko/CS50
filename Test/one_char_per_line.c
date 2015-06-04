#include <stdio.h>
#include <cs50.h>
#include <string.h>

/* This program requests a string from the user, then prints one char
   from that string per line in order from left to right.
*/

int main(void)
{
    string s = GetString();
    if (s != NULL)
    {   
        printf("\nYour result: \n\n");
        for (int i = 0, j = strlen(s); i < j; i++)
        {
        printf("%c\n", s[i]);
        }
        printf("\n");
    }
}
