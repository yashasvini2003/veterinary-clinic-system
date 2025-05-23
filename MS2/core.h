/*
*****************************************************************************
                        Assignment 1 - Milestone 2
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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);






//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
// To get and validate int input from user
int inputInt(void);

// To get and validate positive integer input from user
int inputIntPositive(void);

//To validate the input value is within the range
int inputIntRange(const int lower, const int upper);

//To validate the entered char is in the received string
char inputCharOption(const char validationString[]);

// To validate the entered tring is within the specified range
void inputCString(char string[], int lower, int upper);

// to display formated phone number
// by validating the received phone number is exactely 10 char in length
// with only digits (0 - 9)
void displayFormattedPhone(const char string[]);

// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
