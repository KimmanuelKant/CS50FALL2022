#include <stdio.h>
#include <string.h>

// Function prototype
int check_luhn(char *);
int check_visa(char *);
int check_mastercard(char *);
int check_amex(char *);

int main()
{
    char card_number[20];

    // Prompt user to enter a card number
    printf("Enter a card number: ");
    scanf("%s", card_number);

    // Check if the card number passes Luhn's algorithm
    if (check_luhn(card_number))
    {
        // if it does, check if it's a valid card
        check_visa(card_number);
        check_mastercard(card_number);
        check_amex(card_number);
    }

    if (!check_luhn(card_number) && !check_visa(card_number) && !check_mastercard(card_number) && !check_amex(card_number))
    {
        printf("INVALID\n");
    }

    return 0;
}

// Function to check if a card number passes Luhn's algorithm
int check_luhn(char *card_number)
{
    int n = strlen(card_number);
    int sum = 0;
    int alternate = 0;

    // Iterate over the digits in the card number in reverse order
    for (int i = n - 1; i >= 0; i--)
    {
        int digit = card_number[i] - '0';

        // If this is an alternate digit, double it
        if (alternate)
        {
            digit *= 2;

            // If the doubled digit is greater than 9, subtract 9 from it
            if (digit > 9)
            {
                digit -= 9;
            }
        }

        // Add the digit to the sum
        sum += digit;

        // Toggle the alternate flag
        alternate = !alternate;
    }

    // If the sum is divisible by 10, the card number passes Luhn's algorithm
    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_visa(char *card_number)
{
    
    if ((strlen(card_number) == 16 || strlen(card_number) == 13) && card_number[0] == '4')
    {
        printf("VISA\n");
        return 1;
    }
    return 0;
}

int check_mastercard(char *card_number)
{
    if (strlen(card_number) == 16 && card_number[0] == '5' && (card_number[1] >= '1' && card_number[1] <= '5'))
    {
        printf("MASTERCARD\n");
        return 1;
    }
    return 0;
}

int check_amex(char *card_number)
{
    if (strlen(card_number) == 15 && (card_number[0] == '3' && (card_number[1] == '4' || card_number[1] == '7')))
    {
        printf("AMEX\n");
        return 1;
    }
    return 0;
}