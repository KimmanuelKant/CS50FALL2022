#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int tallet = get_int("n: ");


    if (tallet % 2 == 0)
    {
        printf("even\n");
    }
    else
    {
        printf("odd\n");
    }



}