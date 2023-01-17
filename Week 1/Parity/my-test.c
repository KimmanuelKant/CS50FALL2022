#include <cs50.h>
#include <stdio.h>

int main(void)
{
   /* int i = 0;
    while (i < 8)
        {
            printf("# \n");
            i++;
        } */
    int height = get_int ("How high?");

    for (int y = height; y > 0; y--)
    {
        for (int x = 0; x < height - y; x++)
        {
            printf("#");
        }
        printf("\n");
    }

}