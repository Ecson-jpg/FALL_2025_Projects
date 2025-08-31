//
//  main.c
//  final project simplified
//
//      Name of Students:
//
//      Ecson Cervantes
//      Haoyu Chen
//      Frederick Elia
//      Jay Bautista
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_FACULTY 30
#define MAX_ATTEMPTS 3

//________________________________________
typedef struct {
    char fullName[150];
    float gpa;
    char id[9];
    int creditHours;
} student;

typedef struct {
    char *name;
    char *id;
    char *department;
    char *rank;
} faculty;
//________________________________________

//List of functions for program
//________________________________________
void toUpperCase(char *str);
void toLowerCase(char *str);
void capitalizeString(char *str);
void printfcomma (int n, char *str);

int menu(int *counter);

void addFaculty(faculty array[], faculty *f);
void addStudent(student students[], int *numStudents);

void tuitionInvoice(student students[], int numStudents);
void printFacultyByID(faculty array[], const char* id);

void SortFacByName(faculty fac[], int count);
void SortStuByName(student stu[], int count);
void PrintFinalReport( faculty fac[], student stu[]);
//________________________________________

// Main Function
//________________________________________
int main() {
    student students[MAX_STUDENTS] = {0};
    int numStudents = 0;
    faculty fac[MAX_FACULTY] = {0};
    faculty f;
    int selection = 1;

    int counter = 0;


    printf("\n\t\t\t\tWelcome to PerPro\n");

    while ((selection = menu(&counter)) != 5) {
        counter++;
        switch (selection) {
            case 1: // Add a faculty member
                addFaculty(fac, &f);
                break;
            case 2: // Add a new student
                addStudent(students, &numStudents);
                break;
            case 3: // Get tuition invoice
                tuitionInvoice(students, numStudents);
                break;
            case 4: // Print the Faculty info
                printf("\tEnter the faculty's ID: ");
                char id[9];
                scanf("%s", id);
                printFacultyByID(fac, id);
                break;
        }
    }
    char response = 'n';
    printf("Would you like to print the final report (Y/N): ");
    scanf("%c", &response);
    if (response == 'y' || response == 'Y'){
        PrintFinalReport( fac , students);
        printf("\n\n\nThank you for using PerPro, Good-Bye!\n");
        exit(1);
    }
    else{
        printf("\nExiting Program...\n");
        printf("\n\n\nThank you for using PerPro, Good-Bye!\n");
    }
    return 0;
}


//Sets it uppercase
void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}
//Sets it lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
//________________________________________

//Capitalizes a String
//________________________________________
void capitalizeString( char *str) {
    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] = str[0] - ('a' - 'A');
    }
}
//________________________________________

// Format the tuition so that it has commas for nums in thousands
//________________________________________
void printfcomma (int n, char *str){
    if (n < 1000) {
        sprintf(str + strlen(str), "%d", n);
        return;
    }
    printfcomma(n / 1000, str);
    sprintf(str + strlen(str), ",%03d", n % 1000);
}

// Menu Function
//________________________________________
int menu(int *counter) {
    int selection;
    int isValid;
    int tries = 0;
    int maxTries = 3;


    if (*counter == 1){
        printf("\n\n\nChoose one of the options:\n");
    }
    printf("\n1 - Add a new faculty member\n");
    printf("2 - Add a new student\n");
    printf("3 - Print tuition invoice for a student\n");
    printf("4 - Print information of a faculty\n");
    printf("5 - Exit Program\n");

    do {
        printf("\n\tEnter your selection: ");

        isValid = scanf("%d", &selection);

        // Clear the input buffer
        while (getchar() != '\n');

        if (isValid != 1 || selection < 1 || selection > 5) {
            printf("\n\tInvalid entry- please try again.\n");
            isValid = 0; // Invalid input, loop will repeat
            tries++;
        } else {
            isValid = 1; // Valid input, loop will end
        }

        if (tries >= maxTries) {
            printf("\nYou have tried too many times...Exiting program.\n");
            printf("\nThank you for using PerPro, Good-Bye\n");
            exit(1);
        }

    } while (!isValid);

    return selection;
}
//________________________________________

// Add Faculty Function
//________________________________________
void addFaculty(faculty array[], faculty *f) {
    const char *validRanks[] = {"Professor", "Adjunct"};
    const char *validDepartments[] = {"math", "cs", "science"};

    printf("\nEnter the faculty's info: \n");

    printf("\t\tName of the faculty: ");

    f->name = malloc(50 * sizeof(char));
    fgets(f->name, 50, stdin);
    f->name[strcspn(f->name, "\n")] = 0;

    printf("\t\tID: ");
    f->id = malloc(10 * sizeof(int));
    fgets(f->id, 10, stdin);
    f->id[strcspn(f->id, "\n")] = 0;
    toLowerCase(f->id);

    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        printf("\t\tRank: ");
        f->rank = malloc(30 * sizeof(char));
        fgets(f->rank, 30, stdin);
        f->rank[strcspn(f->rank, "\n")] = 0;

        int valid = 0;
        for (int j = 0; j < 2; j++) {
            if (strcasecmp(f->rank, validRanks[j]) == 0) {
                valid = 1;
                break;
            }
        }
        if (valid) break;
        if (i == MAX_ATTEMPTS - 1) {
            printf("\n\nYou have tried too many times...\nThank you for using PerPro. Goodbye!");
            exit(1);
        }
        printf("\t\t\tSorry, entered rank (%s) is invalid. Try again.\n", f->rank);
        free(f->rank);
    }

    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        printf("\t\tDepartment: ");
        f->department = malloc(30 * sizeof(char));
        fgets(f->department, 30, stdin);
        f->department[strcspn(f->department, "\n")] = 0;

        int valid = 0;
        for (int j = 0; j < 3; j++) {
            if (strcasecmp(f->department, validDepartments[j]) == 0) {
                printf("\nThanks!\n");
                valid = 1;
                break;
            }
        }
        if (valid) break;
        if (i == MAX_ATTEMPTS - 1) {
            printf("\n\nYou have tried too many times...\nThank you for using PerPro. Goodbye!");
            exit(1);
        }
        printf("\t\t\tSorry, entered department (%s) is invalid. Try again.\n", f->department);
        free(f->department);

    }

    // Adding member to array
    int index;
    for (index = 0; index < MAX_FACULTY; index++) {
        if (array[index].id == NULL) {
            array[index] = *f;
            return;
        }
    }
}
//________________________________________

// Add Student Function
//________________________________________
void addStudent(student students[], int *numStudents) {
    if (*numStudents >= MAX_STUDENTS) {
        return;
    }

    student newStudent;
    int attempts = 0;

    while (1) {
        printf("\nEnter the student's info:\n");
        printf("\t\tName of Student: ");
        fgets(newStudent.fullName, sizeof(newStudent.fullName), stdin);
        newStudent.fullName[strcspn(newStudent.fullName, "\n")] = '\0';

        if (strlen(newStudent.fullName) > 0) {
            break;
        } else {
            printf("Invalid input. Please enter a valid name.\n");
            attempts++;
        }

        if (attempts >= MAX_ATTEMPTS) {
            printf("You have tried too many times...\nThank you for using PerPro. Goodbye!");
            exit(1);
        }
    }

    attempts = 0;
    while (1) {
        printf("\t\tID: ");
        fgets(newStudent.id, sizeof(newStudent.id), stdin);
        newStudent.id[strcspn(newStudent.id, "\n")] = '\0';
        toLowerCase(newStudent.id);

        if (strlen(newStudent.id) > 0) {
            break;
        } else {
            printf("Invalid input. Please enter a valid ID.\n");
            attempts++;
        }

        if (attempts >= MAX_ATTEMPTS) {
            printf("You have tried too many times...\nThank you for using PerPro. Goodbye!");
            exit(1);
        }
    }

    attempts = 0;
    while (1) {
        printf("\t\tGPA: ");
        if (scanf("%f", &newStudent.gpa) == 1) {
            break;
        } else {
            printf("Invalid input. Please enter a valid GPA.\n");
            attempts++;
            while (getchar() != '\n');
        }

        if (attempts >= MAX_ATTEMPTS) {
            printf("You have tried too many times...\nThank you for using PerPro. Goodbye!");
            exit(1);
        }
    }

    attempts = 0;
    while (1) {
        printf("\t\tCredit hours: ");
        if (scanf("%d", &newStudent.creditHours) == 1) {
            if (newStudent.creditHours >= 0) {
                break; // Valid input
            } else {
                printf("Invalid input. Please enter valid credit hours.\n");
                attempts++;
            }
        } else {
            printf("Invalid input. Please enter valid credit hours.\n");
            attempts++;
            // Clear invalid input
            while (getchar() != '\n');
        }

        if (attempts >= MAX_ATTEMPTS) {
            printf("You have tried too many times...\nThank you for using PerPro. Goodbye!");
            exit(1);
        }
    }

    students[*numStudents] = newStudent;
    (*numStudents)++;

    printf("Thanks!");
}
//________________________________________

// Tuition Invoice Function
//________________________________________
void tuitionInvoice(student students[], int numStudents) {
    char id[9];
    int found = 0;
    float creditHourCost = 236.45;
    int adminFee = 52;
    float totalPayment = 0;
    float discount = 0;
    char idtemp[9];
    char formattedTotalPayment[20] = "";

    printf("\tEnter the student's ID: ");
    scanf("%s", id);
    strcpy(idtemp, id);
    toLowerCase(id);

    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found = 1;

            printf("\nHere is the tuition for %s :\n", students[i].fullName);
            printf("\n---------------------------------------------------------------------------\n\n");

            totalPayment = students[i].creditHours * creditHourCost + adminFee;
            if (students[i].gpa >= 3.85) {
                discount = totalPayment * 0.25;
                totalPayment *= 0.75;
            }

            printfcomma((int)totalPayment, formattedTotalPayment);

            printf("\t%s \t\t %s\n\n\tCredit Hours: %d \t($236.45/Credit Hour)\n\n\tFees: $52\n\n\n\tTotal Payment: $%.2f \t\t($%.2f discount applied)\n",
                   students[i].fullName, idtemp, students[i].creditHours, totalPayment, discount);
            printf("\n---------------------------------------------------------------------------\n");

            break;
        }
    }

    if (!found) {
        printf("\n\tSorry-student not found!\n");
    }
}
//________________________________________

// Print Faculty by ID Function
//________________________________________
void printFacultyByID(faculty array[], const char* id) {
    char lowerID[10];
    strcpy(lowerID, id);
    toLowerCase(lowerID);
    for (int i = 0; i < MAX_FACULTY; i++) {
        if (array[i].id != NULL) {
            char lowerArrayID[10];
            strcpy(lowerArrayID, array[i].id);
            toLowerCase(lowerArrayID);
            if (strcmp(lowerArrayID, lowerID) == 0) {
                toUpperCase(array[i].department);
                capitalizeString(array[i].rank);
                printf("\nFaculty found:\n");
                printf("------------------------------------------------------------------------------------------------\n");
                printf("\t%s\n\n", array[i].name);
                printf("\t%s Department, %s\n", array[i].department, array[i].rank);
                printf("------------------------------------------------------------------------------------------------\n");
                return;
                }
            }
        }
    printf("\tSorry %s doesn't exist\n", id);
}
//________________________________________


// Following functions are for Final Report:
//____________________________________________
void SortFacByName(faculty fac[], int count){
    faculty temp;

    for (int i = 0; i < count-1; i++){
        for (int j = i + 1; j < count - 1; j++ ){
            if (strcmp(fac[j].name, fac[i].name) > 0){
                temp = fac[j];
                fac[j] = fac[i];
                fac[i] = temp;
            }
        }
    }
}
//________________________________________
void SortStuByName(student stu[], int count){
    student temp;

    for (int i = 0; i < count-1; i++){
        for (int j = i + 1; j < count - 1; j++ ){
            if (strcmp(stu[j].fullName, stu[i].fullName) > 0){
                temp = stu[j];
                stu[j] = stu[i];
                stu[i] = temp;
            }
        }
    }
}

// Print final report
//________________________________________
void PrintFinalReport( faculty fac[], student stu[]){
    char sort = 'n';

    printf("Sorted by name? (Y/N): ");
    getchar();
    scanf("%c", &sort);

    if ( sort == 'y' || sort == 'Y'){
        int facCount = 0;
        int stuCount = 0;

        for (int i = 0; i < MAX_FACULTY && fac[i].name != NULL; i++ ){
            facCount++;
        }
        for (int i = 0; i< MAX_STUDENTS && stu[i].fullName[0] != '\0'; i++){
            stuCount++;
        }
        SortFacByName(fac, facCount);
    }
    
    printf("\nHere is your report...\n");

    printf("\n\t------ L I S T  O F  F A C U L T Y -----\n");
        for (int i = 0; i < MAX_FACULTY && fac[i].name != NULL; i++) {
            capitalizeString(fac[i].department);
            printf("\t\t%s - %s\n", fac[i].name, fac[i].department);
        }

        printf("\n\t------ L I S T  O F  S T D U E N T S -----\n");
        for (int i = 0; i < MAX_STUDENTS && stu[i].fullName[0] != '\0'; i++) {
            printf("\t\t%s\n", stu[i].fullName);
        }

}
//________________________________________
