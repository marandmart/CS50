# Gets credit card number
cdnmb = input("Number: ")
# Sum variable
sum = 0
# If a string with length 16 was given
if len(cdnmb) > 13:
    # reverses the string numbers
    reversenmb = cdnmb[::-1]
    # Goes through every other number of the credit card
    for i in reversenmb[1::2]:
        # Checks if the multiplication will give two digit number and
        # then adds those values individually
        if len(str(int(i)*2)) != 1:
            sum = sum + int(str(int(i) * 2)[-1]) + int(str(int(i) * 2)[0])
        # adds double of those values to the sum
        else:
            sum = sum + int(i) * 2

    # adds the remaining elements of the credit card to the sum
    for i in reversenmb[::2]:
        sum = sum + int(i)

    # Checks if the last digit of sum was zero and then checks each value for the specific card beginning numbers
    if int(str(sum)[-1]) == 0:
        if int(cdnmb[:2:]) == 34 or int(cdnmb[:2:]) == 37:
            print("AMEX")
        elif int(cdnmb[:2:]) == 51 or int(cdnmb[:2:]) == 52 or int(cdnmb[:2:]) == 53 or int(cdnmb[:2:]) == 54 or int(cdnmb[:2:]) == 55:
            print("MASTERCARD")
        elif int(cdnmb[:1:]) == 4:
            print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")