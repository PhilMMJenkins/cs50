#include <stdio.h>
#include <cs50.h>
#include <string.h>

//Functions defined:
bool validate(int a, string b);
string encipher(string a, string b);
int check_repeats(char a, string b);

//Main string validates then runs the encipher function if valid.
int main(int argc, string argv[])
{
    bool valid = validate(argc, argv[1]);
    if (valid == true)
    {
        string plain = get_string("plaintext: ");
        string cipher = encipher(plain, argv[1]);
        printf("ciphertext: %s\n", cipher);
        return 0;
    }
    else
    {
        return 1;
    }
}

//Function validates the input string by a series of nested 'if' statements
//returns false if statement not met.
bool validate(int a, string b)
{
    //first test validates that there is only one argument at the command line.
    if (a == 2)
    {
        int n = strlen(b);
        //Second test confirms that there are 26 characters.
        if (n == 26)
        {
            //'al' is the number of alphabetic characters in a string
            int al = 0;
            //'re' is the number of repeats in a string
            int re = 0;
            for (int i = 0; i < n; i++)
            {
                //upper case
                if (b[i] >= 65 && b[i] <= 90)
                {
                    al++;
                    re += check_repeats(b[i], b);
                }
                //lower case
                else if (b[i] >= 97 && b[i] <= 122)
                {
                    al++;
                    re += check_repeats(b[i], b);
                    //this normalises the string to all capital letters to make enciphering easier
                    b[i] -= 32;
                }
            }
            if (al == 26)
            {
                if (re == 26)
                {
                    return true;
                }
                else
                {
                    printf("Key must not contain repeated characters!\n");
                    return false;
                }
            }
            else
            {
                printf("Key must contain only alphabetic characters!\n");
                return false;
            }
        }
        else
        {
            printf("Key must contain 26 characters!\n");
            return false;
        }
    }
    else
    {
        printf("Usage: ./substitution KEY\n");
        return false;
    }
}

//takes the plaintext and the key. For each letter in plaintext, the program grabs the corresponding letter from the key
//the program then saves the letter from the key in the place of the original letter from in a copy of plaintext called cipher
//because the key is normalised to all caps in the validation step, only the case of the plaintext needs to be adjusted for.
string encipher(string a, string b)
{
    string cipher = a;
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        //upper case
        if (a[i] >= 65 && a[i] <= 90)
        {
            cipher[i] = (char) b[(int) a[i] - 65];
        }
        //lower case
        else if (a[i] >= 97 && a[i] <= 122)
        {
            cipher[i] = (char) b[(int) a[i] - 97];
            cipher[i] += 32;
        }
    }
    return cipher;
}

//checks the current character against all characters in the string
//adds 1 for each repeat
int check_repeats(char a, string b)
{
    int lc = 0;
    int uc = 0;
    int repeats = 0;
    for (int i = 0, n = strlen(b); i < n; i++)
    {
        //upper case
        if (a >= 65 && a <= 90)
        {
            uc = a;
            lc = a + 32;
        }
        //lower case
        else if (a >= 97 && a <= 122)
        {
            uc = a - 32;
            lc = a;
        }
        if (uc == b[i] || lc == b[i])
        {
            repeats++;
        }
    }
    return repeats;
}