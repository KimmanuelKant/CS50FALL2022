#include <stdio.h>
#include <cs50.h>

int main(void)
// get name, print name
{
    string name = get_string("What's ur name yo? ");
    printf("Hello, %s\n", name);
}