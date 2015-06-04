#include <stdio.h>
#include <cs50.h>
#include <string.h>

/* This program requests user's cc# and prints the provider's name
   if it is a valid cc# from AMEX, VISA, or MASTERCARD, if not, it 
   prints INVALID.
   
   Citing: While all of these things may have been in course materials, 
   I did receive guidance and help identifying and fixing bugs, learning
   completely new things to me, and finding resources and inspiration 
   for new ideas from coworkers, posts on web sites, and further chapters
   in both the Programming in C and C for Absolute Beginners books that are
   recommended reading.  
*/

// Requests cc# when called, stores/accepts potentially valid results
long long user_reply(const char* cc_request)
{
    // Declaring vars
    long long result;
    bool valid_reply;
    do
    {
        printf("%s", cc_request);
        result = GetLongLong();
        if (result < 0)
        {
            valid_reply = false;
        }
    }
    while (valid_reply);
    return result;
}

// Necessary result used in Luhn's algorithm as part of valid_cc_num
int arr_elem_sum(int elem)
{
    // Supports Luhn's algorithm
    int result = elem % 10 + elem / 10;
    return result;
}    

// Verifies validity of cc# vs. Luhn's algorithm when called
bool valid_cc_num(char* cc_pointer)
{
    // Declaring vars
    int cc_arr_elem;
    int luhn_sum = 0;
    bool every_other = true;
    // Applies Luhn's algorithm to provided cc#
    for (int i = (strlen(cc_pointer) - 1); i >= 0; i--)
    {
        // Sets tracker for 'i'th element of cc_pointer w/bug fix (- '0')
        cc_arr_elem = cc_pointer[i] - '0';
        // Luhn's algorithm in combination with arr_elem_sum and boolean check
        luhn_sum += every_other ? cc_arr_elem : arr_elem_sum(cc_arr_elem * 2);
        every_other = !every_other;
    }
    if (!(luhn_sum % 10))
    {
        return true;
    }
    else 
    {
        return false;
    }
}

/* Requests cc# from user, , verifies it against Luhn's algorithm, 
   verifies validity of cc# against AMEX, VISA, and MASTERCARD cc# 
   params, then prints provider name or INVALID 
*/
int main(int argc, char* argv[])
{
    // Sets maximum input for cc length 
    const int cc_len_max = 16;
    // Initializes cc_arr to defined max # digits for cc# input
    char cc_arr[cc_len_max];
    // Requests user's cc#, stores valid results as long long
    long long cc_entry = user_reply("\nPlease enter your credit "
    "card number without any hyphens or spaces!\nCC#: ");
    // Converts user's input to char str to be used by cc_arr
    sprintf(cc_arr, "%lld", cc_entry);
    /* Verifies CC# validity and first digits vs. card provider params,
       then prints card provider name or INVALID and terminates program
    */
    if (cc_arr[0] == '3' && (cc_arr[1] == '4' || 
    cc_arr[1] == '7') && valid_cc_num(cc_arr)) 
    {
        printf("AMEX\n");
    }
    else if (cc_arr[0] == '4' && valid_cc_num(cc_arr))
    {
        printf("VISA\n");
    } 
    else if (cc_arr[0] == '5' && (cc_arr[1] >= '1' && 
    cc_arr[1] <= '5') && valid_cc_num(cc_arr))
    {
        printf("MASTERCARD\n");
    }
    else 
    {
        printf("INVALID\n");
    }
    return 0;
}
