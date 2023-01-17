
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)

{
    char card_number[20];

    // Prompt user to enter a card number
    printf("Enter a card number: ");
    scanf("%s", card_number);

    // Check if the card number is a Visa card
    if (strlen(card_number) == 16 && card_number[0] == '4')
    {
        printf("VISA\n");
    }

    // Check if the card number is a Mastercard
    else if (strlen(card_number) == 16 && card_number[0] == '5' && (card_number[1] >= '1' && card_number[1] <= '5'))
    {
        printf("MASTERCARD\n");
    }

    // Check if the card number is an American Express card
    else if (strlen(card_number) == 15 && (card_number[0] == '3' && (card_number[1] == '4' || card_number[1] == '7')))
    {
        printf("AMEX\n");
    }

    // If the card number does not match any of the above criteria, it is not a valid card
    else
    {
        printf("INVALID\n");
    }

    return 0;
}