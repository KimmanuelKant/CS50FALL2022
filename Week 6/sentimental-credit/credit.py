def checkLuhn(cardNumber):
    n = len(cardNumber)
    sum = 0
    alternate = False

    # Iterate over the digits in the card number in reverse order
    for i in range(n - 1, -1, -1):
        digit = int(cardNumber[i])

        # If this is an alternate digit, double it
        if alternate:
            digit *= 2

            # If the doubled digit is greater than 9, subtract 9 from it
            if digit > 9:
                digit -= 9

        # Add the digit to the sum
        sum += digit

        # Toggle the alternate flag
        alternate = not alternate

    # If the sum is divisible by 10, the card number passes Luhn's algorithm
    return sum % 10 == 0


# Prompt user to enter a card number
cardNumber = input("Card number: ")

# Check if the card number passes Luhn's algorithm
if not checkLuhn(cardNumber):
    print("INVALID")

# Check if the card number is a Visa card
elif (len(cardNumber) == 16 or len(cardNumber) == 13) and cardNumber[0] == '4':
    print("VISA")

# Check if the card number is a Mastercard
elif len(cardNumber) == 16 and cardNumber[0] == '5' and cardNumber[1] in ['1', '2', '3', '4', '5']:
    print("MASTERCARD")

# Check if the card number is an American Express card
elif len(cardNumber) == 15 and cardNumber[0] == '3' and cardNumber[1] in ['4', '7']:
    print("AMEX")

# If the card number does not match any of the above criteria, it is not a valid card
else:
    print("INVALID")