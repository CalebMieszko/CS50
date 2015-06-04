#include <stdio.h>
#include <cs50.h>

//declaring prototype
void PrintName(string name);

int main (void)
{
    printf("Your name: \n");
    string s = GetString();
    PrintName(s);
}

void PrintName(string name)
{
    printf("Hello, %s!\n", name);
}
