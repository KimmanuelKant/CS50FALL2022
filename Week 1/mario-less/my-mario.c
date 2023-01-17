#include <cs50.h>
#include <stdio.h>

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
        for (int space = 0; space < y - 1; space++)
        {
            printf(" ");
        }
        for (int x = 0; x <= height - y; x++)
        {
            printf("#");
        }
        printf("\n");
    }
}