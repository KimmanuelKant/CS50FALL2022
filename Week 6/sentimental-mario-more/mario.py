# Make sure input is within parameters
while True:
    try:
        height = int(input("How high?(1-8) "))
    except ValueError:
        continue
    if 0 < height < 9:
        break
# Now printing time:
# outer loop/rows
for i in range(1, height + 1):
    # print blanks in front of pyramide along with the row.
    blanks = height - i
    print(" " * blanks, end="")
    # inner loop
    # build pyramide, left first.
    for j in range(1, i + 1):
        print("#", end="")
    # then midlle
    print("  ", end="")
    # then the right one.
    for x in range(1, i + 1):
        print("#", end="")
    # New line after printing the whole row.
    print()