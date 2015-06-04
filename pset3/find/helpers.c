/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1) 
    {
        return false;
    }
    sort(values, n);
    int mid;
    int low = 0, high = n - 1;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (values[mid] == value)
        {
            return true;
        }
        else if (values[mid] < value)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool did_swap = true;   
    int i;
    
    while (did_swap == true)
    {
        int new_value;
        did_swap = false;
        for (i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i + 1])
            {
                new_value = values[i + 1];
                values[i + 1] = values[i];
                values[i] = new_value;
                did_swap = true;
            }
        }
    }
    return;
}
