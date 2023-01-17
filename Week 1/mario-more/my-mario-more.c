#include <cs50.h>
#include <stdio.h>
// uendret fra mario-less

int main(void)
{
    // Sett noen standardverdier
    int height = 0;
    const int maxHeight = 8;
    const int minHeight = 1;

    // Sjekk at tallene er mellom min/max
    while (height > maxHeight || height < minHeight)
    {
        height = get_int("How high?");
    }

    // bygge pyramide
    for (int y = height; y >= minHeight; y--)
    {
        // venstre pyramide
        for (int x = 0; x <= height; x++)
        {
            if (x < y)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        // mellomrom
        printf("  ");
        // høyre pyramide
        for (int x = 0; x <= height - y; x++)
        {

            printf("#");
        }

        printf("\n");
    }
}