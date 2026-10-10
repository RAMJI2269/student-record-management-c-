
#include <stdio.h>

#define MAX_STUDENTS 100

struct Student {
    int rollno;
    char name[50];
    float marks;
    float totalMarks;
    float percentage;
};

// Function declarations
char calculateGrade(float percentage);
void saveStudents(struct Student students[], int count);
void loadStudents(struct Student students[], int *count);
void addStudent(struct Student students[], int *count);
void displayStudents(struct Student students[], int count);
void searchStudent(struct Student students[], int count);
void updateStudent(struct Student students[], int count);
void deleteStudent(struct Student students[], int *count);

// Calculate grade using percentage
char calculateGrade(float percentage) {
    if (percentage >= 90)
        return 'S';
    else if (percentage >= 80)
        return 'A';
    else if (percentage >= 70)
        return 'B';
    else if (percentage >= 60)
        return 'C';
    else if (percentage >= 40)
        return 'D';
    else
        return 'F';
}

// Save student records to file
void saveStudents(struct Student students[], int count) {
    FILE *file = fopen("students.txt", "w");

    if (file == NULL) {
        printf("\nError: Could not save student records!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2f %.2f %.2f\n",
                students[i].rollno,
                students[i].name,
                students[i].marks,
                students[i].totalMarks,
                students[i].percentage);
    }

    fclose(file);
    printf("\nStudent records saved successfully!\n");
}

// Load student records from file
void loadStudents(struct Student students[], int *count) {
    FILE *file = fopen("students.txt", "r");

    if (file == NULL) {
        printf("No previous records found. Starting fresh.\n");
        return;
    }

    while (*count < MAX_STUDENTS) {
        int roll;
        char name[50];
        float marks, totalMarks, percentage;

        if (fscanf(file, "%d %49s %f %f %f",
                   &roll, name, &marks,
                   &totalMarks, &percentage) != 5) {
            break;
        }

        if (roll <= 0 ||
            marks < 0 ||
            totalMarks <= 0 ||
            marks > totalMarks ||
            percentage < 0 ||
            percentage > 100) {
            printf("Invalid record found. Skipping it.\n");
            continue;
        }

        // Check duplicate roll numbers
        int duplicate = 0;

        for (int i = 0; i < *count; i++) {
            if (students[i].rollno == roll) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            printf("Duplicate roll number %d skipped.\n", roll);
            continue;
        }

        students[*count].rollno = roll;

        snprintf(students[*count].name,
                 sizeof(students[*count].name), "%s", name);

        students[*count].marks = marks;
        students[*count].totalMarks = totalMarks;
        students[*count].percentage =
            (marks / totalMarks) * 100.0f;

        (*count)++;
    }

    fclose(file);

    printf("%d student record(s) loaded.\n", *count);
}

// Add a student
void addStudent(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("\nStudent limit reached!\n");
        return;
    }

    int roll;
    float marks, totalMarks;
    char name[50];

    printf("\nEnter roll number: ");

    if (scanf("%d", &roll) != 1 || roll <= 0) {
        printf("Invalid roll number!\n");
        return;
    }

    // Check duplicate roll number
    for (int i = 0; i < *count; i++) {
        if (students[i].rollno == roll) {
            printf("Roll number already exists!\n");
            return;
        }
    }

    printf("Enter name (without spaces): ");

    if (scanf("%49s", name) != 1) {
        printf("Invalid name!\n");
        return;
    }

    printf("Enter total marks: ");

    if (scanf("%f", &totalMarks) != 1 || totalMarks <= 0) {
        printf("Invalid total marks!\n");
        return;
    }

    printf("Enter obtained marks: ");

    if (scanf("%f", &marks) != 1 ||
        marks < 0 || marks > totalMarks) {
        printf("Invalid marks! Marks must be between 0 and total marks.\n");
        return;
    }

    students[*count].rollno = roll;

    snprintf(students[*count].name,
             sizeof(students[*count].name), "%s", name);

    students[*count].marks = marks;
    students[*count].totalMarks = totalMarks;
    students[*count].percentage =
        (marks / totalMarks) * 100.0f;

    (*count)++;

    printf("\nStudent added successfully!\n");

    saveStudents(students, *count);
}

// Display all students
void displayStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    for (int i = 0; i < count; i++) {
        printf("\nRoll Number: %d\n", students[i].rollno);
        printf("Name: %s\n", students[i].name);
        printf("Obtained Marks: %.2f\n", students[i].marks);
        printf("Total Marks: %.2f\n", students[i].totalMarks);
        printf("Percentage: %.2f%%\n", students[i].percentage);
        printf("Grade: %c\n",
               calculateGrade(students[i].percentage));

        if (students[i].percentage >= 40)
            printf("Result: Pass\n");
        else
            printf("Result: Fail\n");
    }

    printf("\n=====================================\n");
}

// Search for a student
void searchStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    int roll;

    printf("\nEnter roll number to search: ");

    if (scanf("%d", &roll) != 1) {
        printf("Invalid roll number!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (students[i].rollno == roll) {
            printf("\nStudent Found!\n");
            printf("Roll Number: %d\n", students[i].rollno);
            printf("Name: %s\n", students[i].name);
            printf("Obtained Marks: %.2f\n", students[i].marks);
            printf("Total Marks: %.2f\n", students[i].totalMarks);
            printf("Percentage: %.2f%%\n", students[i].percentage);
            printf("Grade: %c\n",
                   calculateGrade(students[i].percentage));

            if (students[i].percentage >= 40)
                printf("Result: Pass\n");
            else
                printf("Result: Fail\n");

            return;
        }
    }

    printf("\nStudent not found!\n");
}

// Update student marks
void updateStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    int roll;
    float newMarks;

    printf("\nEnter roll number to update: ");

    if (scanf("%d", &roll) != 1) {
        printf("Invalid roll number!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (students[i].rollno == roll) {
            printf("Student Name: %s\n", students[i].name);
            printf("Current Marks: %.2f / %.2f\n",
                   students[i].marks,
                   students[i].totalMarks);

            printf("Enter new obtained marks: ");

            if (scanf("%f", &newMarks) != 1 ||
                newMarks < 0 ||
                newMarks > students[i].totalMarks) {
                printf("Invalid marks! Enter marks within the allowed range.\n");
                return;
            }

            students[i].marks = newMarks;
            students[i].percentage =
                (newMarks / students[i].totalMarks) * 100.0f;

            printf("\nStudent marks updated successfully!\n");
            printf("New Percentage: %.2f%%\n",
                   students[i].percentage);

            saveStudents(students, count);
            return;
        }
    }

    printf("\nStudent not found!\n");
}

// Delete a student
void deleteStudent(struct Student students[], int *count) {
    if (*count == 0) {
        printf("\nNo student records available to delete.\n");
        return;
    }

    int roll;
    int position = -1;

    printf("\nEnter roll number to delete: ");

    if (scanf("%d", &roll) != 1) {
        printf("Invalid roll number!\n");
        return;
    }

    // Find the student's position
    for (int i = 0; i < *count; i++) {
        if (students[i].rollno == roll) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        printf("\nStudent not found!\n");
        return;
    }

    // Shift remaining records to the left
    for (int i = position; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }

    (*count)--;

    printf("\nStudent deleted successfully!\n");

    saveStudents(students, *count);
}

// Main function
int main(void) {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    loadStudents(students, &count);

    do {
        printf("\n====== STUDENT RECORD MANAGEMENT ======\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student Marks\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;

            case 2:
                displayStudents(students, count);
                break;

            case 3:
                searchStudent(students, count);
                break;

            case 4:
                updateStudent(students, count);
                break;

            case 5:
                deleteStudent(students, &count);
                break;

            case 6:
                printf("\nExiting program. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice! Select 1-6.\n");
        }

    } while (choice != 6);

    return 0;
}

