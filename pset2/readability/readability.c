#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

//declare functions which generate inputs for Coleman-Liau formula
int get_letters(string s);
int get_words(string s);
int get_sentences(string s);

int coleman_liau(int a, int b, int c);

int main(void)
{
    //generates the information req
    uired to calculate reading age
    string text = get_string("Text: ");
    int letters = get_letters(text);
    int words = get_words(text);
    int sentences = get_sentences(text);
    int grade = coleman_liau(letters, words, sentences);
    
    //test filters to bracket the reading ages as required
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

//increments a counter for each valid alphabetical letter in a string
int get_letters(string s)
{
    int letters = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 65 && s[i] <= 122)
        {
            letters++;
        }
        else
        {
            
        }
    }
    return letters;
}

//increments a counter for each non-space character following a space
int get_words(string s)
{
    int words = 0;
    
    //bool to tell if the program is "in the process" of counting one word
    bool count = false;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] != ' ' && count == false)
        {
            words++;
            count = true;
        }
        //resets the count bool
        else if (s[i] == ' ')
        {
            count = false;
        }
        //catch-all for other non space characters
        else
        {
            
        }
    }
    return words;
}

//increments a counter each time a '.', '!' or '?' is detected
int get_sentences(string s)
{
    int sentences = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
        else
        {
            
        }
    }
    return sentences;
}

//coleman liau index calculator uses floats to calculate accurately, then rounds to produce an int.
int coleman_liau(int a, int b, int c)
{
    float l = (float) a / (float) b * 100;
    float s = (float) c / (float) b * 100;
    int cl = roundf(0.0588 * l - 0.296 * s - 15.8);
    return cl;
}