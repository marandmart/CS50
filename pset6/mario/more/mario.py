from cs50 import get_int
# gets the number of blocks as input
while True:
    number_of_blocks = get_int("Height: ")
    if number_of_blocks >= 1 and number_of_blocks <= 8:
        break

for n in range(1, number_of_blocks + 1):
    print((number_of_blocks - n) * " " + n * "#" + "  " + n * "#")