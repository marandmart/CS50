# gets the string input
text = input("Text: ")

# creates letter counter set to zero and add +1 when the char is cointained in the
# data given in the if structure
letters = 0
for i in range(len(text)):
    if text[i] in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ":
        letters += 1

# counts the ammount of times a string can be split in its spaces
words = len(text.split())

# counts the ammount of split the string can have based on the symbol used
sentences = (len(text.split("!")) - 1) + (len(text.split("?")) - 1) + (len(text.split(".")) - 1)

# calculates the cli number
cli = round(0.0588 * (letters / words) * 100 - 0.296 * (sentences / words) * 100 - 15.8)

# uses the cli number to return the correct grade level
if cli > 16:
    print("Grade 16+")
elif cli < 1:
    print("Before Grade 1")
else:
    print("Grade " + str(cli))
