/*
*****************************************************************************
                        Assignment 1 - Milestone 1
Full Name  : Yashasvini Bhanuraj
Student ID#: 164581217
Email      : ybhanuraj@myseneca.ca
Section    : NBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include "core.h"



// As demonstrated in the course notes: 
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer 
// Clear the standard input buffer

void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer: 
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue void suspend(void)

void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

// To get and validate int input from user

int inputInt(void)
{
    int num = 0, flage = 0, valid;
    do {
        valid = scanf("%d", &num);
        if (valid == 0)
        {
            printf("Error! Input a whole number: ");
            flage = 0;
        }

        else
        {
            flage = 1;
        }
        clearInputBuffer();

    } while (flage == 0);

    return num;
}

// To get and validate positive integer input from user

int inputIntPositive(void)
{
    int i = 0;
    do
    {
        i = inputInt();
        if (i < 1)
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (i <= 0);

    return i;
}

//To validate the input value is within the range

int inputIntRange(const int lower, const int upper)
{
    int uInput = 0, flage = 0;

    do
    {
        uInput = inputInt();

        if ((uInput < lower) || (uInput > upper))
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lower, upper);
            flage = 0;
        }
        else
        {
            flage = 1;
        }

    } while (flage == 0);
    return uInput;
}

//To validate the entered char is in the received string

char inputCharOption(const char validationString[])
{
    char uCharInput = ' ';
    int i = 0, flage = 0, flage2 = 0;

    do
    {

        scanf("%c", &uCharInput);
        clearInputBuffer();
        for (i = 0; validationString[i] != '\0'; i++)
        {
            if (uCharInput == validationString[i])
            {
                flage = 1;
            }
        }
        if (flage == 1)
        {
            flage2 = 1;
        }
        else
        {
            printf("ERROR: Character must be one of [%s]: ", validationString);
            flage2 = 0;
        }
    } while (flage2 == 0);
    return uCharInput;
}

// To validate the entered tring is within the specified range
void inputCString(char string[], int lower, int upper)
{
    int i = 0, len = 0, flage = 0;
    char inputString[100];

    do
    {

        len = 0;
        scanf("%[^\n]", inputString);
        clearInputBuffer();
        for (i = 0; inputString[i] != '\0'; i++)
        {
            len++;
        }
        if (lower == upper)
        {
            if (len < lower)
            {
                printf("ERROR: String length must be exactly %d chars: ", lower);
                flage = 0;
            }
            else if (len > upper)
            {
                printf("ERROR: String length must be exactly %d chars: ", upper);
                flage = 0;
            }
            else
            {
                flage = 1;
            }

        }
        else
        {
            if (len < lower)
            {
                printf("ERROR: String length must be between %d and %d chars: ", lower, upper);
                flage = 0;
            }
            else if (len > upper)
            {
                printf("ERROR: String length must be no more than %d chars: ", upper);
                flage = 0;
            }
            else
            {
                flage = 1;
            }
        }

    } while (flage == 0);

    for (i = 0; inputString[i] != '\0'; i++)
    {
        string[i] = inputString[i];
    }

}

// to display formated phone number
// by validating the received phone number is exactely 10 char in length
// with only digits (0 - 9)
void displayFormattedPhone(char string[])
{
    int i = 0, j = 0;

    if (string == NULL || string[0] == '\0')
    {
        printf("(___)___-____");
    }
    else
    {
        for (i = 0; string[i] != '\0'; i++)
        {
            if (
                (string[i] == '0') ||
                (string[i] == '1') ||
                (string[i] == '2') ||
                (string[i] == '3') ||
                (string[i] == '4') ||
                (string[i] == '5') ||
                (string[i] == '6') ||
                (string[i] == '7') ||
                (string[i] == '8') ||
                (string[i] == '9')
                )
            {
                j++;
            }

        }

        if (j == 10)
        {
            printf("(%c%c%c)%c%c%c-%c%c%c%c", string[0], string[1], string[2],
                string[3], string[4], string[5], string[6], string[7], string[8], string[9]);
        }
        else
        {
            printf("(___)___-____");
        }
    }
}