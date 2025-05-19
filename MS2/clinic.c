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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    struct Patient pt = {0};
    displayPatientTableHeader();
    if (patient->patientNumber != 0) {
        for (i = 0; (i < max); i++)
        {
            pt = patient[i];
            if (pt.patientNumber != 0)
            {
                displayPatientData(&pt, fmt);
            }
        }
    }
    else {
        printf("*** No records found ***\n");
    }
    putchar('\n');
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int i, flage = 0;
    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        i = inputIntRange(0, 2);

        if (i == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (i == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }
        else if (i == 0)
        {
            flage = 1;
        }    
    } while (flage == 0);
    putchar('\n');
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
   int i = 0, flage = 0, index = 0;

   do
   {
        if (patient[i].patientNumber == 0)
        {
            patient[i].patientNumber =  nextPatientNumber(patient, max);
            flage = 1;
            index = i;
        }
        i++;
   } while ((i < max) && (flage != 1));

   if (flage == 0)
   {
        printf("ERROR: Patient listing is FULL!\n");
   }
   else
    {
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n");
    }
   putchar('\n');
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNumber = 0;
    printf("Enter the patient number: ");
    patientNumber = inputInt();
    putchar('\n');
    patientNumber = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (patientNumber == -1)
    {
        printf("ERROR: Patient record not found!");
    }
    else
    {
        menuPatientEdit(&patient[patientNumber]);
    }

}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNumber = 0, index = 0;
    char answer = ' ';
    struct Patient pt = { 0 };
    printf("Enter the patient number: ");
    patientNumber = inputInt();
    index = findPatientIndexByPatientNum(patientNumber, patient, max);
    putchar('\n');
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        displayPatientData(&patient[index], 1);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        answer = inputCharOption("(y/n)");
        if (answer == 'y')
        {
            patient[index] = pt;
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
    }
    putchar('\n');
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber = 0;
    struct Patient pt = {0};
    printf("\nSearch by patient number: ");
    patientNumber = inputInt();
    patientNumber = findPatientIndexByPatientNum(patientNumber, patient, max);
    printf("\n");
    if (patientNumber != -1)
    {
        pt = patient[patientNumber];
        displayPatientData(&pt, 1);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    printf("\n");
    suspend();
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNumber[11] = {' '};
    int i = 0, flage = 0;
    struct Patient pt = { 0 };
    printf("\nSearch by phone number: ");
    inputCString(phoneNumber, 10, 10);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        pt = patient[i];
        if(strcmp (pt.phone.number, phoneNumber) == 0)
        {
            displayPatientData(&pt, 2);
            flage = 1;
        }
    }
    putchar('\n');
    if (flage == 0)
    {
        printf("*** No records found ***\n\n");
    }
    suspend();
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i = 0, num = 0;
    for (i = 0; (i < max); i++)
    {
        if (num < patient[i].patientNumber)
        {
            num = patient[i].patientNumber;
        }
    }
    num = num + 1;
    return num;
}



// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i = 0, flage = 0, iNumber = -1;
    struct Patient pt = { 0 };

    for (i = 0; (i < max)||(flage == 1); i++)
    {
        pt = patient[i];
        if (pt.patientNumber == patientNumber)
        {
            iNumber = i;
            flage = 1;
        }  
        else
        {
            flage = 0;
        }
    }
    return iNumber;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, 15);
    putchar('\n');
    inputPhoneData(&patient->phone);

}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone) 
{
    int selection;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    switch (selection)
    {
    case 1:
        printf("\nContact: CELL\n");
        strcpy(phone->description, "CELL");
        printf("\nNumber : ");
        inputCString(phone->number, 10, 10);
        putchar('\n');
        break;
    case 2:
        printf("\nContact: HOME");
        strcpy(phone->description, "HOME");
        printf("\nNumber : ");
        inputCString(phone->number, 10, 10);
        putchar('\n');
        break;
    case 3:
        printf("\nContact: WORK");
        strcpy(phone->description, "WORK");
        printf("\nNumber : ");
        inputCString(phone->number, 10, 10);
        putchar('\n');
        break;
    case 4:
        strcpy(phone->description, "TBD");
        putchar('\n');
        break;
    default:
        break;
    }
}