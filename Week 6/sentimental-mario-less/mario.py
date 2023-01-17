# Make sure input is within parameters
while True:
    try:
        height = int(input("How high?(1-8) "))
    except ValueError:
        continue
    if 0 < height < 9:
        break
# Now printing time:
# outer loop
for i in range(1, height + 1):
    blanks = height - i
    print(" " * blanks, end="")
    # inner loop
    for j in range(1, i + 1):
        print("#", end="")
    print()