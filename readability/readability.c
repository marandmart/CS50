#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Function calls.
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void return_CLi_level(int letters, int words, int sentences);

int main(void)
{
    //Asks the user for the text.
    string text = get_string("Text: ");
    //Counts the total of letters.
    int letters = count_letters(text);
    //Counts the total of words.
    int words = count_words(text);
    //Counts the total of sentences.
    int sentences = count_sentences(text);
    // Returns the Coleman-Liau Index.
    return_CLi_level(letters, words, sentences);
}

int count_letters(string text)
{
    //Starts the counter from 0.
    int letter_count = 0;
    //Gets the total length of the text array.
    int total_caracters = strlen(text);
    //Loops the string and adds +1 each time it identifies a caracter.
    for (int i = 0; i < total_caracters; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letter_count += 1;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    //Starts the counter from 1. The function counts the ammount of spaces which is equal to (ammount of words - 1).
    int word_count = 1;
    int total_caracters = strlen(text);
    for (int i = 0; i < total_caracters; i++)
    {
        if (isspace(text[i]) != 0)
        {
            word_count += 1;
        }
    }
    return word_count;
}

int count_sentences(string text)
{
    //Starts the counter from 0.
    int sentence_count = 0;
    int total_caracters = strlen(text);
    for (int i = 0; i < total_caracters; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentence_count += 1;
        }
    }
    return sentence_count;
}

//Return the CLi value and gives back the proper result.
void return_CLi_level(int letters, int words, int sentences)
{
    int cli = round(0.0588 * ((float) letters / (float) words * 100) - 0.296 * ((float) sentences / (float) words * 100) - 15.8);
    if (cli > 16)
    {
        printf("Grade 16+\n");
    }
    else if (cli < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", cli);
    }
}