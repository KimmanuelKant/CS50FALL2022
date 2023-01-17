#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string count_input)
{
    int count = 0;
    for (int i = 0; i < strlen(count_input); i++)
    {

        if (isalpha(count_input[i]))
        {
            count += 1;
        }
    }
    return count;
}
int count_spaces(string count_input)
{
    int count = 0;
    for (int i = 0; i < strlen(count_input); i++)
    {

        if (isspace(count_input[i]))
        {
            count += 1;
        }
    }
    return count + 1;
}
int count_sentences(string count_input)
{
    int count = 0;
    for (int i = 0; i < strlen(count_input); i++)
    {

        if (count_input[i] == '?' || count_input[i] == '.' || count_input[i] == '!')
        {
            count += 1;
        }
    }
    return count;
}
int main(void)
{
    // ta imot inputtekst
    string inputtekst = get_string("Text: ");

    // telle antall bokstaver
    int letters = count_letters(inputtekst);
    //  printf("letters: %i\n", letters);
    // isLetter(inputtekst[])

    // telleantall ord
    int words = count_spaces(inputtekst);
    //  printf("words: %i\n", words);
    // telle antall " " + 1

    // telle antall setninger
    int sentences = count_sentences(inputtekst);
    // printf("sentences: %i\n", sentences);

    // finn L og S
    // L = gjennomsnittlig antall bokstaver per 100 ord
    // S = gjennomsnittlig antall setninger per 100 ord
    float L = (float)letters / (float)words * 100.0;
    float S = (float)sentences / (float)words * 100.0;
    //   printf("%f\n ", L);
    //  printf("%f\n ", S);

    // Coleman-Liau index
    double index = 0.0588 * L - 0.296 * S - 15.8;
    int index_rounded = round(index);
    if (index_rounded > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index_rounded < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index_rounded);
    }

   
}