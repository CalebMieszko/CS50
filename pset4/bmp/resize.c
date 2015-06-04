/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP, just because. Wheeeeeeee, baby!
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize sizefactor infile outfile\n");
        return 1;
    }

    // remember filenames
    int sizefactor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // make sure size factor is positive
    if (sizefactor < 1 || sizefactor > 100)
    {
        printf("Usage: ./resize sizefactor infile outfile.  Please enter a positive integer <= 100 for sizefactor.\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER - naughty name!
    BITMAPFILEHEADER bf, bf_out;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_out = bf;

    // read infile's BITMAPINFOHEADER - spankies!
    BITMAPINFOHEADER bi, bi_out;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_out = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // set new params for outfile
    bi_out.biHeight = bi.biHeight * sizefactor;
    bi_out.biWidth = bi.biWidth * sizefactor;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_new =  (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine image outfile dimensions
    bi_out.biSizeImage = ((sizeof(RGBTRIPLE) * bi_out.biWidth + padding_new) * abs(bi_out.biHeight));
    bf_out.bfSize = bf.bfSize + bi_out.biSizeImage - bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over each scanline "factor" times
        for (int j = 0; j < sizefactor; j++)
        {
        
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                // write sizefactor iterations of RGB triple to outfile
                for (int l = 0; l < sizefactor; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // add padding
            for (int m = 0; m < padding_new; m++)
            {
                fputc(0x00, outptr);
            }
        
            // set scanline position
            if (j < sizefactor - 1)
            {
                fseek(inptr,  sizeof(RGBTRIPLE) * (-bi.biWidth), SEEK_CUR);
            }
        }
        
        // skip over any extra padding
        fseek(inptr, padding, SEEK_CUR);
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
