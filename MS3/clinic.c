/*
*****************************************************************************
                        Assignment 1 - Milestone 3
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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
 void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    struct Patient pt = { 0 };
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
             patient[i].patientNumber = nextPatientNumber(patient, max);
             flage = 1;
             index = i;
         }
         i++;
     } while ((i < max) && (flage != 1));

     if (flage == 0)
     {
         printf("ERROR: Patient listing is FULL!\n\n");
     }
     else
     {
         inputPatient(&patient[index]);
         printf("*** New patient record added ***\n\n");
         clearInputBuffer();
     }

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


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
 void viewAllAppointments(struct ClinicData* data)
 {
     int i = 0;
     int index = 0;
     int max = 0;
     struct ClinicData cData = *data;
     sortAppointmentArray(cData.appointments);
     max = numberOfAppointment(cData.appointments);
     sortAppointmentArray(cData.appointments);

     if (max != 0)
     {
         sortAppointmentArray(cData.appointments);
         displayScheduleTableHeader(&data->appointments->date, 1);
         for(i = 0; i < 50 ; i++)
         { 
             if (cData.appointments[i].patNumber != 0) {
                 index = findPatientIndexByPatientNum(cData.appointments[i].patNumber, cData.patients, 20);
                 displayScheduleData(&cData.patients[index], &cData.appointments[i], 1);
             }
         }
     }
     else
     {
         printf("No Records to Display");
     }
     putchar('\n');
 }


// View appointment schedule for the user input date
 void viewAppointmentSchedule(struct ClinicData* data)
 {
     int i = 0,index = 0;
     struct Date date; 
     struct ClinicData cData = *data;
     date = getDate();

     putchar('\n');

     sortAppointmentArray(cData.appointments);

    displayScheduleTableHeader(&date, 0);

     for (i = 0; i < 50; i++)
     {

         if (cData.appointments[i].date.year == date.year)

         {
             if (cData.appointments[i].date.month == date.month)
             {
                 if (cData.appointments[i].date.day == date.day)
                 {
                     index = findPatientIndexByPatientNum(cData.appointments[i].patNumber, cData.patients, 20);
                     displayScheduleData(&cData.patients[index], &cData.appointments[i], 0);
                 }
                 
             }
             
         }

         
     }

     //if (flage == 1)
     //{
     //    printf("No Appointment on this day!!!\n");
     //}

     putchar('\n');
     
 }


// Add an appointment record to the appointment array
 void addAppointment(struct Appointment* appointment, int maxappointment, struct Patient* patients, int maxPatient)
 {
     struct Date date;
     struct Time time;
     int patNum = 0;
     int flage = 1, flage2 = 0;
     int max = 0;
     int i = 0;
     struct Appointment newappt =  { 0 };
     

     do {
         printf("Patient Number: ");
         scanf("%d", &patNum);
         flage = findPatientIndexByPatientNum(patNum, patients, 20);
         if (flage == -1)
         {
             printf("ERROR: Patient record not found!\n");
         }
     } while (flage == -1);

     max = numberOfAppointment(appointment);

     do {
         
         date = getDate();
         time = getTime();
         flage2 = 0;
         for (i = 0; i < max; i++)
         {
             if (appointment[i].date.year == date.year)
             {
                 if (appointment[i].date.month == date.month)
                 {
                     if (appointment[i].date.day == date.day)
                     {
                         if (appointment[i].time.hour == time.hour)
                         {
                             if (appointment[i].time.min == time.min)
                             {
                                 printf("\nERROR: Appointment timeslot is not available!\n");
                                 flage2 = 1;
                                 putchar('\n');
                             }
                             
                         }
                         
                     }
                     
                 }
                 
             }

         }
         
     } while (flage2 == 1);

     if (flage2 == 0) {
         newappt.date = date;
         newappt.time = time;
         newappt.patNumber = patNum;
         appointment[max + 1] = newappt;
         printf("\n*** Appointment scheduled! ***\n");
         sortAppointmentArray(appointment);
     }

     putchar('\n');
     clearInputBuffer();
 }


// Remove an appointment record from the appointment array
 void removeAppointment(struct Appointment* appointment, int maxappointment, struct Patient* patients, int maxPatient)
 {
     int patNum = 0;
     int flage = 0,flage2 = 0, i = 0;
     struct Date date = { 0 };
     char ans = ' ';
     struct Appointment appt = { 0 };

         printf("Patient Number: ");
         scanf("%d", &patNum);
         flage = findPatientIndexByPatientNum(patNum, patients, 20);

         if (flage == -1)
         {
             printf("ERROR: Patient record not found!\n");
             putchar('\n');
             clearInputBuffer();
         }
         else
         {
             date = getDate();
             putchar('\n');
             i = 0;
             do
             {
           
                 if (appointment[i].date.year == date.year)
                 {
                     if (appointment[i].date.month == date.month)
                     {
                         if (appointment[i].date.day == date.day)
                         {
                             if (appointment[i].patNumber == patNum)
                             {
                                 displayPatientData(&patients[flage], 1);
                                 printf("Are you sure you want to remove this appointment (y,n): ");
                                 ans = inputCharOption("y|n");
                                 if (ans == 'y')
                                 {
                                     putchar('\n');
                                     printf("Appointment record has been removed!\n");
                                     appointment[i] = appt;
                                     flage2 = 1;
                                     putchar('\n');
                                 }
                             }
                         }
                     }
                 }
                 i++;

             } while (flage2 == 0);
             

         }

     
         


 }


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
 void searchPatientByPatientNumber(const struct Patient patient[], int max)
 {
     int patientNumber = 0;
     struct Patient pt = { 0 };
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
     char phoneNumber[11] = { ' ' };
     int i = 0, flage = 0;
     struct Patient pt = { 0 };
     printf("\nSearch by phone number: ");
     inputCString(phoneNumber, 10, 10);
     putchar('\n');
     displayPatientTableHeader();
     for (i = 0; i < max; i++)
     {
         pt = patient[i];
         if (strcmp(pt.phone.number, phoneNumber) == 0)
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

     for (i = 0; (i < max) || (flage == 1); i++)
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

 // Find Number of Appointments (returns -1 if there is no appointment)
 int numberOfAppointment(const struct Appointment appoint[])
 {
     int i = 0, noAppt = -1;

     for (i = 0; i < 50; i++)
     {
         if (appoint[i].patNumber != 0)
         {
             noAppt++;
         }
     }
     return noAppt;
 }

 // Sorting of appointment Array
 void sortAppointmentArray(struct Appointment appoint[])
 {
     int i = 0, j = 0;
     struct Appointment appt = { 0 };
     int max = 0;


     max = numberOfAppointment(appoint);
     for (i = max; i > 0; i--)
     {
         for (j = 0; j < i; j++)
         {
             if (appoint[i].date.year < appoint[j].date.year)

             {
                 appt = appoint[j];
                 appoint[j] = appoint[i];
                 appoint[i] = appt;
             }

         }
     }
     for (i = max; i > 0; i--)
     {
         for (j = 0; j < i; j++)
         {
             if (appoint[i].date.year == appoint[j].date.year)
             {
                 if (appoint[i].date.month < appoint[j].date.month)
                 {
                     appt = appoint[j];
                     appoint[j] = appoint[i];
                     appoint[i] = appt;
                 }
             }

         }
     }
     for (i = max; i > 0; i--)
     {
         for (j = 0; j < i; j++)
         {
             if (appoint[i].date.year == appoint[j].date.year) {
                 if (appoint[i].date.month == appoint[j].date.month)
                 {
                     if (appoint[i].date.day < appoint[j].date.day)
                     {
                         appt = appoint[j];
                         appoint[j] = appoint[i];
                         appoint[i] = appt;
                     }
                 }
             }
         }
     }
     for (i = max; i > 0; i--)
     {
         for (j = 0; j < i; j++)
         {
             if (appoint[i].date.year == appoint[j].date.year)
             {
                 if (appoint[i].date.month == appoint[j].date.month)
                 {
                     if (appoint[i].date.day == appoint[j].date.day)
                     {
                         if (appoint[i].time.hour < appoint[j].time.hour)
                         {
                             appt = appoint[j];
                             appoint[j] = appoint[i];
                             appoint[i] = appt;
                         }
                     }
                 }
             }
         }
     }
     for (i = max; i > 0; i--)
     {
         for (j = 0; j < i; j++)
         {
             if (appoint[i].date.year == appoint[j].date.year)
             {
                 if (appoint[i].date.month == appoint[j].date.month)
                 {
                     if (appoint[i].date.day == appoint[j].date.day)
                     {
                         if (appoint[i].time.hour == appoint[j].time.hour)
                         {
                             if (appoint[i].time.min < appoint[j].time.min)
                             {
                                 appt = appoint[j];
                                 appoint[j] = appoint[i];
                                 appoint[i] = appt;
                             }
                         }
                     }
                 }
             }
         }
     }
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
     int selection, flage = 0, len = 0;
     char phno[20] = { 0 };
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
         printf("Number : ");
         do {
             scanf("%s", phno);
             len = strlen(phno);
             if (len != 10)
             {
                 printf("Invalid 10-digit number! Number: ");
                 flage = 0;
             }
             else {
                 flage = 1;
             }
         } while (flage == 0);
         strcpy(phone->number, phno);
         putchar('\n');
         break;
     case 2:
         printf("\nContact: HOME\n");
         strcpy(phone->description, "HOME");
         printf("Number : ");
        do{ scanf("%s", phno);
             len = strlen(phno);
             if (len != 10)
             {
                 printf("Invalid 10-digit number! Number: ");
                 flage = 0;
             }
             else {
                 flage = 1;
             }
         } while (flage == 0);
         strcpy(phone->number, phno);
         putchar('\n');
         break;
     case 3:
         printf("\nContact: WORK\n");
         strcpy(phone->description, "WORK");
         printf("Number : ");
         do {
             scanf("%s", phno);
             len = strlen(phno);
             if (len != 10)
             {
                 printf("Invalid 10-digit number! Number: ");
                 flage = 0;
             }
             else {
                 flage = 1;
             }
         } while (flage == 0);
         strcpy(phone->number, phno);
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

 // Get user input for Date
 struct Date getDate()
 {
     struct Date date;
     int flage = 0;

     printf("Year        : ");
     date.year = inputIntPositive();
     printf("Month (1-12): ");
     date.month = inputIntRange(1, 12);

     if (date.year % 400 == 0) {
         flage = 1;
     }
     else if (date.year % 100 == 0) {
         flage = 0;
     }
     else if (date.year % 4 == 0) {
         flage = 1;
     }
     else {
         flage = 0;
     }

     if ((date.month == 1) || (date.month == 3) || (date.month == 5) || (date.month == 7)
         || (date.month == 8) || (date.month == 10) || (date.month == 12))
     {
         printf("Day (1-31)  : ");
         date.day = inputIntRange(1, 31);
     }
     else
     {
         if (date.month == 2)
         {
             if (flage == 1)
             {
                 printf("Day (1-29)  : ");
                 date.day = inputIntRange(1, 29);
             }
             else
             {
                 printf("Day (1-28)  : ");
                 date.day = inputIntRange(1, 28);
             }
         }
         else {
             printf("Day (1-30)  : ");
             date.day = inputIntRange(1, 30);
         }

     }
     return date;
 }

 // Get the input for Time
 struct Time getTime() 
 {
     struct Time time = { 0 };
     int flage = 0;
     do {
         printf("Hour (0-23)  : ");
         scanf("%d", &time.hour);
         printf("Minute (0-59): ");
         scanf("%d", &time.min);

         if ((time.hour < HOUR_START) || (time.hour > HOUR_END)||(time.min % 30 != 0)||(time.min > 59))
         {
             printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", HOUR_START, HOUR_END, APPT_INTERVAL);
             flage = 1;
         }
         else if ((time.hour == HOUR_END) && (time.min > 1))
         {
             printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", HOUR_START, HOUR_END, APPT_INTERVAL);
             flage = 1;
         }
         else {
             flage = 0;
         }
     } while (flage == 1);

         return time;

 }


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
 int importPatients(const char* datafile, struct Patient patients[], int max)
 {
     int totalPatient = 0;
     int i = 0;
     int val = 4;
     FILE *patientFile = NULL;
     


     patientFile = fopen(datafile, "r");
         
         if (patientFile != NULL)
         {
             while (i < max && val == 4)
             {
                 val = fscanf(patientFile, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number);
                 if (patients[i].phone.number[0] == '\0')
                 {
                     val = 4;
                 }
                 i++;
             }
             fclose(patientFile);
         }
         else
         {
             printf("ERROR! File cannot be opened!\n");
         }
         totalPatient = i;
     return totalPatient;
 }


// Import appointment data from file into an Appointment array (returns # of records read)
 int importAppointments(const char* datafile, struct Appointment appoints[], int max) 
 {
     int totalAppointments = 0;
     int i = 0;
     int val = 6;
     FILE* appFile = NULL;

     appFile = fopen(datafile, "r");

     if (appFile != NULL)
     {
         while (i < max && val == 6)
         {
             val = fscanf(appFile, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);
             i++;
         }
         fclose(appFile);
     }
     else
     {
         printf("ERROR! File cannot be opened!\n");
     }
     totalAppointments = i-1;
     return totalAppointments;
 }