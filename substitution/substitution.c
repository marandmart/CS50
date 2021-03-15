#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Checks if the user has only given a single string as input.
    if (argc == 2)
    {
        //Checks if the cipher has proper length.
        if (strlen(argv[1]) == 26)
        {
            //Checks if the given cipher consists of only alphabetic characters.
            for (int i = 0; i < 26; i++)
            {
                if ((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z'))
                {
                    //Nothing needs to be done unless the conditions are not met.
                }
                else
                {
                    printf("Key must only contain alphabetic characters.\n");
                    return 1;
                }
            }
            //Checks if the given cipher doesn't have repeated characters.
            //The sum of all the uppercase ASCII equivalent values of the cipher has to be 2015.
            int test = 0;
            for (int i = 0; i < 26; i++)
            {
                test += (int) toupper(argv[1][i]);
            }
            //Continues the cipher or returns that the program needs only unique characters.
            if (test == 2015)
            {
                //Doing the convertion
                string plaintext = get_string("plaintext: ");
                printf("ciphertext: ");
                //Gets the length of the plaintext given by the user.
                int pt_length = strlen(plaintext);
                for (int i = 0; i < pt_length; i++)
                {
                    //If it's a lowercase letter, it subtracts -97 due to its ASCII value and then
                    //uses that to give the correct position in the cipher, while also converting it
                    //to the proper case format.
                    if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
                    {
                        int convertion = (int) plaintext[i];
                        convertion -= 97;
                        printf("%c", tolower(argv[1][convertion]));
                    }
                    //If it's a lowercase letter, it subtracts -65 due to its ASCII value and then
                    //uses that to give the correct position in the cipher, while also converting it
                    //to the proper case format.
                    else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
                    {
                        int convertion = (int) plaintext[i];
                        convertion -= 65;
                        printf("%c", toupper(argv[1][convertion]));
                    }
                    //If it isn't a letter, it just return the char.
                    else
                    {
                        printf("%c", plaintext[i]);
                    }
                }
                printf("\n");
                return 0;
            }
            //Asks that the user input only unique characters.
            else
            {
                printf("Key must not contain repeated characters.");
                return 1;
            }
        }
        //Asks that the user input a key with 26 characters.
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    //Shows the user the proper way to use the program.
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}