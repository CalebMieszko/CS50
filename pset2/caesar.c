#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // set some variables, others worked properly further on
    int cypher, i;
    bool cypher_valid = false;
    // make sure user entered only a single argument at the command line
    if (argc != 2)
    {
        // yell at user to follow the directions we assume they have?
        printf("Please try again, but this time with just one entry.\n");
        return 1;
    }
    else
    {
        // perform conversion of command line argument stored as char to int
        cypher = atoi(argv[1]);
        // make sure user actually gave us a positive number
        if (cypher > 0)
        {
            // if user provided positive number, validate the cypher request
            cypher_valid = true;
        }
        
    }
    // double check to make sure cypher was validated
    if (cypher_valid == true)
    {
        // prompt for the secret message to be encrypted
        char* smsg = GetString();
        // set more variables related to the secret message, yay! 
        size_t smsg_len = strlen(smsg);
        char smsg_encrypt[smsg_len];
        // iterate the following over the length of the secret message:
        for (i = 0; i < smsg_len; i++)
        {
            // encrypt capital letters in secret message
            if ((smsg[i] >= 'A') && (smsg[i] <= 'Z'))
            {
                smsg_encrypt[i] = ((((smsg[i] - 65) + cypher) % 26) + 65);
            }
            // now encrypt lower case letters
            else if ((smsg[i] >= 'a') && (smsg[i] <= 'z'))
            {
                smsg_encrypt[i] = ((((smsg[i] - 97) + cypher) % 26) + 97); 
            } 
            else
            // if neither, no changes - doesn't work for certain characters yet.
            {
                smsg_encrypt[i] = smsg[i];
            }
        }
        // print the encrypted message!
        printf("%s\n", smsg_encrypt);
    }
}
