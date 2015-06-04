#include <stdio.h>
#include <cs50.h>
/* This program will create two half-pyramids in the theme of 
   World 1-1 from Nintendo's Super Mario Brothers.  It requests 
   theheight of the pyramids from the user and will accept the 
   input of any whole number from 0 through 23, then creates
   two appropriately sized left-aligned half-pyramids.
   
   Citing: While all of these things may have been in course materials, 
   I did receive guidance and help identifying and fixing bugs, learning
   completely new things to me, and finding resources and inspiration 
   for new ideas from coworkers, posts on web sites, and further chapters
   in both the Programming in C and C for Absolute Beginners books that are
   recommended reading.  
*/

// Generates the user request with a built-in test for validity
int user_reply(char* height_req)
{
    // Declaring vars
    int result;
    bool valid_reply = false;
    // Prompt and check
    do 
    {
        // The request is implemented here
        printf("%s", height_req);
        result = GetInt();
        // The user's reply is validated here
        if (result >= 0 && result <= 23)
        {
            valid_reply = true;
        }
    }
    while (valid_reply == false);
    return result;
}

/* This defines the prompt the user will see, then formats and generates
   the half-pyramids to the valid height specifed by the user
*/
int main(void)
{
    // Defines user prompt
    int height = user_reply("\nPlease tell me the height of the pyramid "
    "you'd like Mario to jump across! I need a whole number from 0 through "
    "23.\n\nPyramid Height: ");
    // Formats and generates half-pyramids of appropriate height and spacing
    for (int i = 0; i < height; i++)
    {
        // Creates half-pyramid on the left side
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        { 
            printf("#");
        }
        // Sets spacing between half-pyramids
        printf("  ");
        // Creates half-pyramid on the right side
        for (int j = 0; j < i + 1; j++)
        { 
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
