#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    // set some variables, others worked properly further on
    string cypher;
    int cypher_len; 
    int i, counter;
    bool cypher_valid = false;
    
    // make sure user entered only a single argument at the command line
    if (argc != 2)
    {
        // yell at user to follow the directions
        printf("Please try again with only one alphabetical entry.\n");
        return 1;
    }
    else
    {
        cypher = argv[1];
        cypher_len = strlen(argv[1]);
        // iterate the following over the length of the entered cypher:
        for (i = 0; i < cypher_len; i++)
        {
            if (!isalpha(argv[1][i]))
            // yell at user to follow the directions
            {
                printf("Please try again with only  one alphabetical entry.\n");
                return 1;
            }
            else 
            {
                // validate the cypher since no violations occurred
                cypher_valid = true;
            }   
        }
    }
     
    
    // double check to make sure cypher was validated
    if (cypher_valid == true)
    {
        // prompt for the secret message that will be encrypted
        char* smsg = GetString();
        // set more variables related to the secret message, yay! 
        size_t smsg_len = strlen(smsg);
        char smsg_encrypt[smsg_len];
        int element = 0;
        counter = 0;
        // iterate the following over the length of the secret message:
        for (i = 0; i < smsg_len; i++)
        {
            // encrypt upper/lowercase letters in secret message
            if (isalpha(smsg[i]))
            {
                element = counter % cypher_len;
                if (islower(smsg[i]))
                {
                    if (islower(cypher[element]))
                    {
                        smsg_encrypt[i] = ((((smsg[i] - 97) + cypher[element] - 97) % 26) + 97);
                    }
                    else
                    {
                        smsg_encrypt[i] = ((((smsg[i] - 97) + cypher[element] - 65) % 26) + 97);
                    }
                }
            }
            if (isupper(smsg[i]))
            {
                if (islower(cypher[element]))
                {
                    smsg_encrypt[i] = ((((smsg[i] - 65) + cypher[element] - 97) % 26) + 65);
                }
                else
                {
                    smsg_encrypt[i] = ((((smsg[i] - 65) + cypher[element] - 65) % 26) + 65);
                }
            }
            counter++;
        }
        // print the encrypted message! Crap... not quite rght, but I'm out of time! So close!
        printf("%s\n", smsg_encrypt);
    }
}
