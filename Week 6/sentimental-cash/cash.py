# define the number of coins for each type of coin
quartersValue = 25
dimesValue = 10
nickelsValue = 5
penniesValue = 1

# ask the user for the total amount of money
while True:
    try:
        totalAmount = float(input('Enter the total amount of money in dollars and cents: '))
    except ValueError:
        continue
    if 0 < totalAmount:
        break

# convert the total amount of money to cents
cents = int(totalAmount * 100)

# calculate the number of quarters needed
quartersNeeded = cents // quartersValue
# calculate the remaining amount of money after the quarters are used
remainingCents = cents % quartersValue
# calculate the number of dimes needed
dimesNeeded = remainingCents // dimesValue
# calculate the remaining amount of money after the dimes are used
remainingCents = remainingCents % dimesValue
# calculate the number of nickels needed
nickelsNeeded = remainingCents // nickelsValue
# calculate the remaining amount of money after the nickels are used
remainingCents = remainingCents % nickelsValue
# calculate the number of pennies needed
num_pennies_needed = remainingCents // penniesValue

# print the number of coins needed for each type of coin
print('Number of quarters needed:', quartersNeeded)
print('Number of dimes needed:', dimesNeeded)
print('Number of nickels needed:', nickelsNeeded)
print('Number of pennies needed:', num_pennies_needed)
print('Total coins:', num_pennies_needed + nickelsNeeded + dimesNeeded + quartersNeeded)