/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.  Yikes!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//programd oes not need to accept command-line args - KISS!
int main(void)
{
    // open file for CF card
    FILE* file = fopen("card.raw", "r");
    
    // verify file, return error if there's a problem
    if (file == NULL)
    {
        fclose(file);
        fprintf(stderr, "\nThere is a problem with the file, received NULL\n");
        return 1;
    }
    
    // counter generates file names in order found
    int filenum = 0;
    // two sets of 4 bytes to look for, identifies jpegs
    uint8_t jpegscan_1[4] = {0xff,0xd8, 0xff, 0xe0};
    uint8_t jpegscan_2[4] = {0xff,0xd8, 0xff, 0xe1};
    // sets buffer size to 512, ideal for jpegs
    uint8_t bytenum[4];
    uint8_t buffsize[512];
    fread(buffsize, 512, 1, file);    
    // used to check if the out file is open or not
    int foutopen = 0;
    FILE* fout;
    // creates filename array
    char fname[8];
    
    // scan for proper first four bytes/open output file 
    while (fread(buffsize, 512, 1, file) > 0)
    {
        for (int i = 0; i <= 3; i++)
        {
            bytenum[i] = buffsize[i];
        }
        
       if (memcmp(jpegscan_1, bytenum, 4) == 0 || memcmp(jpegscan_2, bytenum, 4) == 0)
       {
           // make a file with the right name
           
           sprintf(fname, "%03d.jpg", filenum);
           if (foutopen == 0)
           {
               fout = fopen(fname, "w");
               fwrite(buffsize, sizeof(buffsize), 1, fout);
               foutopen = 1;
           } 
           if (foutopen == 1)
           {
               fclose(fout);
               fout = fopen(fname, "w");
               fwrite(buffsize, sizeof(buffsize), 1, fout);
               filenum++;
           }
       }
       else if (foutopen == 1)
       {
           fwrite(buffsize, sizeof(buffsize), 1, fout);
       }
    }
    
    // close the file
    if (fout)
    {
        fclose(file);
        return 0;
    }
    
}
