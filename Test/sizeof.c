#include <stdio.h>
#include <cs50.h>

void PrintName(string name)
{
    printf("Hello, %s!\n", name);
}

int main (void)
{
    printf("Your name: \n");
    string s = GetString();
    PrintName(s);
}
