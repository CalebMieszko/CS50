#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// This program requests a user's name and returns their initials, capitalized.

int main(int argc, char* argv[])
{
    int i, length;
    char* name;
    // request the name
    name = GetString();
    length = strlen(name);
    // verify name is not NULL
    if (name != NULL)
    {
        // print capitalized first initial
        printf("%c", toupper(name[0]));
        // set up to find other iniials
        for (i = 0; i < length; i++)
        {
            if (name[i] == ' ')
            {
                // print the other initials
                printf("%c", toupper(name[i + 1]));
            }
        }
        printf("\n");
    }
    return 0;
}
