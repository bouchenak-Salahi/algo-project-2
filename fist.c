#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEMESTERS_LICENSE 6
#define MAX_SEMESTERS_MASTER 4
#define MAX_SUBJECTS 10

struct Subject {
    char name[50];
    float coefficient;
    float grade;};

struct Semester {
    struct Subject subjects[MAX_SUBJECTS];
    int numSubjects;};

struct Student {
    char name[50];
    int universityNumber;
    char dateOfBirth[20];
    char registrationDate[20];
    char academicLevel[10];
    struct Semester semesters[MAX_SEMESTERS_LICENSE + MAX_SEMESTERS_MASTER];
    int numSemesters;};

float calculateSemesterAverage(struct Semester* semester) {
    float totalCoefficient = 0.0;
    float weightedSum = 0.0;

    for (int i = 0; i < semester->numSubjects; i++) {
        totalCoefficient += semester->subjects[i].coefficient;
        weightedSum += semester->subjects[i].grade * semester->subjects[i].coefficient;}

    if (totalCoefficient == 0.0) {
        return 0.0;
    }
    float semesterAverage = weightedSum / totalCoefficient;
    return semesterAverage;
}
float calculateYearAverage(struct Student* student) {
    float totalSemesterAverage = 0.0;
    int numSemesters = student->numSemesters;
    for (int i = 0; i < numSemesters; i++) {
        struct Semester* semester = &(student->semesters[i]);
        float semesterAverage = calculateSemesterAverage(semester);
        totalSemesterAverage += semesterAverage;
    }
    if (numSemesters == 0) {
        return 0.0;
    }
    float yearAverage = totalSemesterAverage / numSemesters;
    return yearAverage;
}
void displayStudentInformation(struct Student* student) {
    printf("Name: %s\n", student->name);
    printf("University Number: %d\n", student->universityNumber);
    printf("Date of Birth: %s\n", student->dateOfBirth);
    printf("Registration Date: %s\n", student->registrationDate);
    printf("Academic Level: %s\n", student->academicLevel);

    printf("Semester Results:\n");
    for (int i = 0; i < student->numSemesters; i++) {
        printf("Semester %d:\n", i + 1);
        struct Semester* semester = &(student->semesters[i]);
        for (int j = 0; j < semester->numSubjects; j++) {
            struct Subject* subject = &(semester->subjects[j]);
            printf("Subject Name: %s\n", subject->name);
            printf("Coefficient: %.2f\n", subject->coefficient);
            printf("Grade: %.2f\n", subject->grade);}
        float semesterAverage = calculateSemesterAverage(semester);
        printf("Semester Average: %.2f\n", semesterAverage);}
    float yearAverage = calculateYearAverage(student);
    printf("Year Average: %.2f\n", yearAverage);

    if (yearAverage >= 10.0) {
        printf("Result: Passed\n");
    } else {
        printf("Result: Deferred\n");}
    printf("--------------------\n");
}

int main() {
    int n;
    int numSubjects;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    struct Student students[n];
    for (int i = 0; i < n; i++) {
        struct Student* student = &(students[i]);
        printf("\nStudent %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]s", student->name);
        printf("University Number: ");
        scanf("%d", &student->universityNumber);
        printf("Date of Birth: ");
        scanf(" %[^\n]s", student->dateOfBirth);
        printf("Registration Date: ");
        scanf(" %[^\n]s", student->registrationDate);
        printf("Academic Level (License/Master): ");
        scanf(" %[^\n]s", student->academicLevel);
        if (strcmp(student->academicLevel, "License") == 0) {
            student->numSemesters = MAX_SEMESTERS_LICENSE;
        } else if (strcmp(student->academicLevel, "Master") == 0){
            student->numSemesters = MAX_SEMESTERS_MASTER;
        }else{
            printf("Invalid academic level!\n");
            return 0;}
        for (int j = 0; j < student->numSemesters; j++) {
            struct Semester* semester = &(student->semesters[j]);
            printf("\nSemester %d:\n", j + 1);
            printf("Enter the number of subjects: ");
            scanf("%d", &numSubjects);
            semester->numSubjects = numSubjects;
            for (int k = 0; k < numSubjects; k++) {
                struct Subject* subject = &(semester->subjects[k]);
                printf("\nSubject %d:\n", k + 1);

                printf("Subject Name: ");
                scanf(" %[^\n]s", subject->name);

                printf("Subject Coefficient: ");
                scanf("%f", &subject->coefficient);

                printf("Subject Grade: ");
                scanf("%f", &subject->grade);}}}
    int option;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Display university numbers for students with year average >= 10\n");
        printf("2. Display percentage of students with year average >= 10\n");
        printf("3. Display percentage of students with year average < 10\n");
        printf("4. Display student information based on university number\n");
        printf("5. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);
        switch (option) {
            case 1: {
                printf("\nUniversity Numbers with Year Average >= 10:\n");
                for (int i = 0; i < n; i++) {
                    struct Student* student = &(students[i]);
                    float yearAverage = calculateYearAverage(student);

                   
                    if (yearAverage >= 10.0) {
                        printf("%d\n", student->universityNumber);
                    }}
                break;}
            case 2: {
                int countPassed = 0;
                for (int i = 0; i < n; i++) {
                    struct Student* student = &(students[i]);
                    float yearAverage = calculateYearAverage(student);
                    if (yearAverage >= 10.0) {
                        countPassed++;
                    }}
                float percentagePassed = (float)countPassed / n * 100;
                printf("\nPercentage of Students with Year Average >= 10: %.2f%%\n", percentagePassed);
                break;}
            case 3: {
                int countDeferred = 0;
                for (int i = 0; i < n; i++) {
                    struct Student* student = &(students[i]);
                    float yearAverage = calculateYearAverage(student);

                    if (yearAverage < 10.0) {
                        countDeferred++;
                    }}
                float percentageDeferred = (float)countDeferred / n * 100;
                printf("\nPercentage of Students with Year Average < 10: %.2f%%\n", percentageDeferred);
                break;
            }
            case 4: {
                int universityNumber;
                printf("\nEnter the university number to search for: ");
                scanf("%d", &universityNumber);
                int found = 0;
                for (int i = 0; i < n; i++) {
                    struct Student* student = &(students[i]);
                    if (student->universityNumber == universityNumber) {
                        displayStudentInformation(student);
                        found = 1;
                        break;
                    }}
                if (!found) {
                    printf("\nStudent with university number %d not found.\n", universityNumber);
                }
                break;}
            case 5: {
                printf("\nExiting program.\n");
                break;}
            default: {
                printf("\nInvalid option. Please try again.\n");
                break;
            }}
    } while (option != 5);
    return 0;
}