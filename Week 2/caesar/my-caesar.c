#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int only_digits(string input);
char rotate(char c, int n);
void print_ciphertext(string plaintext, int key);

int main(int argc, string argv[])

{
    // Make sure program was run with just one command-line argument
    if (argc > 2 || argc <= 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // make sure every char is a digit
    int hasDigit = only_digits(argv[1]);
    if (hasDigit == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    print_ciphertext(plaintext, key);
}

// make sure every char is a digit
int only_digits(string input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
        {
            return 0;
        }
    }
    return 1;
}

char rotate(char c, int n)
{
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
    {
        return c;
    }

    // Sett til stor A, fordi Erlend hater else
    int offset = 'A';

    // hvis lower case
    if (islower(c))
    {
        offset = 'a';
    }

    // hvis ikke, kjør på
    int rotated_char = ((c - offset + n) % 26) + offset;
    // send det tilbake
    return (char)rotated_char;
}

void print_ciphertext(string plaintext, int key)
{
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
}