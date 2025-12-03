#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10
#define FILENAME "members.dat"

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char registrationDate[12];
    char dateOfBirth[12];
    char interest[20];
} Student;

typedef struct {
    Student *students;
    int count;
    int capacity;
} Database;

void initDatabase(Database *db);
void loadDatabase(Database *db, const char *filename);
void saveDatabase(Database *db, const char *filename);
void addStudent(Database *db, Student s, const char *filename);
void updateStudent(Database *db, int studentID, const char *filename);
void deleteStudent(Database *db, int studentID, const char *filename);
void displayAllStudents(Database *db);
void generateBatchReport(Database *db, const char *batch, const char *membershipType);
int findStudentIndex(Database *db, int studentID);
void expandCapacity(Database *db);
void freeDatabase(Database *db);
void displayMenu();
Student inputStudentData();

void initDatabase(Database *db) {
    db->capacity = INITIAL_CAPACITY;
    db->count = 0;
    db->students = (Student *)malloc(db->capacity * sizeof(Student));

    if (db->students == NULL) {
        fprintf(stderr, "Error: Failed to initialize database\n");
        exit(1);
    }
}

void loadDatabase(Database *db, const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }

    Student temp;
    while (fread(&temp, sizeof(Student), 1, file) == 1) {
        if (db->count >= db->capacity) {
            expandCapacity(db);
        }
        db->students[db->count++] = temp;
    }

    fclose(file);
    printf("Loaded %d records from database\n", db->count);
}

void saveDatabase(Database *db, const char *filename) {
    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        fprintf(stderr, "Error: Cannot save database to file\n");
        return;
    }

    fwrite(db->students, sizeof(Student), db->count, file);
    fclose(file);

    printf("Database saved successfully (%d records)\n", db->count);
}

void expandCapacity(Database *db) {
    int newCapacity = db->capacity * 2;
    Student *temp = (Student *)realloc(db->students, newCapacity * sizeof(Student));

    if (temp == NULL) {
        fprintf(stderr, "Error: Failed to expand database capacity\n");
        return;
    }

    db->students = temp;
    db->capacity = newCapacity;
    printf("Database capacity expanded to %d\n", newCapacity);
}

int findStudentIndex(Database *db, int studentID) {
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].studentID == studentID) {
            return i;
        }
    }
    return -1;
}

void addStudent(Database *db, Student s, const char *filename) {
    if (findStudentIndex(db, s.studentID) != -1) {
        printf("Error: Student ID %d already exists!\n", s.studentID);
        return;
    }

    if (db->count >= db->capacity) {
        expandCapacity(db);
    }

    db->students[db->count++] = s;
    saveDatabase(db, filename);

    printf("Student added successfully!\n");
}

void updateStudent(Database *db, int studentID, const char *filename) {
    int index = findStudentIndex(db, studentID);

    if (index == -1) {
        printf("Error: Student ID %d not found\n", studentID);
        return;
    }

    printf("\nCurrent Details:\n");
    printf("Name: %s\n", db->students[index].fullName);
    printf("Batch: %s\n", db->students[index].batch);
    printf("Membership: %s\n", db->students[index].membershipType);

    int choice;
    printf("\nWhat do you want to update?\n");
    printf("1. Batch\n");
    printf("2. Membership Type\n");
    printf("3. Both\n");
    printf("Choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1 || choice == 3) {
        printf("Enter new batch (CS/SE/Cyber Security/AI): ");
        fgets(db->students[index].batch, sizeof(db->students[index].batch), stdin);
        db->students[index].batch[strcspn(db->students[index].batch, "\n")] = 0;
    }

    if (choice == 2 || choice == 3) {
        printf("Enter new membership type (IEEE/ACM): ");
        fgets(db->students[index].membershipType, sizeof(db->students[index].membershipType), stdin);
        db->students[index].membershipType[strcspn(db->students[index].membershipType, "\n")] = 0;
    }

    saveDatabase(db, filename);
    printf("Student record updated successfully!\n");
}

void deleteStudent(Database *db, int studentID, const char *filename) {
    int index = findStudentIndex(db, studentID);

    if (index == -1) {
        printf("Error: Student ID %d not found\n", studentID);
        return;
    }

    printf("Deleting student: %s (ID: %d)\n", db->students[index].fullName, studentID);

    for (int i = index; i < db->count - 1; i++) {
        db->students[i] = db->students[i + 1];
    }

    db->count--;
    saveDatabase(db, filename);

    printf("Student deleted successfully!\n");
}

void displayAllStudents(Database *db) {
    if (db->count == 0) {
        printf("No students registered yet.\n");
        return;
    }

    printf("\n========== All Registered Students ==========\n");
    printf("%-8s %-25s %-15s %-10s %-12s %-12s %-15s\n",
           "ID", "Name", "Batch", "Type", "Reg Date", "DOB", "Interest");
    printf("====================================================================================\n");

    for (int i = 0; i < db->count; i++) {
        printf("%-8d %-25s %-15s %-10s %-12s %-12s %-15s\n",
               db->students[i].studentID,
               db->students[i].fullName,
               db->students[i].batch,
               db->students[i].membershipType,
               db->students[i].registrationDate,
               db->students[i].dateOfBirth,
               db->students[i].interest);
    }
    printf("====================================================================================\n");
    printf("Total students: %d\n\n", db->count);
}

void generateBatchReport(Database *db, const char *batch, const char *membershipType) {
    int found = 0;

    printf("\n========== Batch Report ==========\n");
    printf("Batch: %s | Membership: %s\n", batch, membershipType);
    printf("%-8s %-25s %-15s %-15s\n", "ID", "Name", "Interest", "Reg Date");
    printf("================================================================\n");

    for (int i = 0; i < db->count; i++) {
        int batchMatch = (strcmp(batch, "ALL") == 0) || (strcmp(db->students[i].batch, batch) == 0);
        int typeMatch = (strcmp(membershipType, "ALL") == 0) ||
                       (strcmp(db->students[i].membershipType, membershipType) == 0) ||
                       (strcmp(db->students[i].interest, "Both") == 0);

        if (batchMatch && typeMatch) {
            printf("%-8d %-25s %-15s %-15s\n",
                   db->students[i].studentID,
                   db->students[i].fullName,
                   db->students[i].interest,
                   db->students[i].registrationDate);
            found++;
        }
    }

    if (found == 0) {
        printf("No students found matching the criteria.\n");
    }

    printf("================================================================\n");
    printf("Total matching students: %d\n\n", found);
}

Student inputStudentData() {
    Student s;

    printf("\nEnter Student ID: ");
    scanf("%d", &s.studentID);
    getchar();

    printf("Enter Full Name: ");
    fgets(s.fullName, sizeof(s.fullName), stdin);
    s.fullName[strcspn(s.fullName, "\n")] = 0;

    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    fgets(s.batch, sizeof(s.batch), stdin);
    s.batch[strcspn(s.batch, "\n")] = 0;

    printf("Enter Membership Type (IEEE/ACM): ");
    fgets(s.membershipType, sizeof(s.membershipType), stdin);
    s.membershipType[strcspn(s.membershipType, "\n")] = 0;

    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(s.registrationDate, sizeof(s.registrationDate), stdin);
    s.registrationDate[strcspn(s.registrationDate, "\n")] = 0;

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(s.dateOfBirth, sizeof(s.dateOfBirth), stdin);
    s.dateOfBirth[strcspn(s.dateOfBirth, "\n")] = 0;

    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(s.interest, sizeof(s.interest), stdin);
    s.interest[strcspn(s.interest, "\n")] = 0;

    return s;
}

void freeDatabase(Database *db) {
    if (db->students != NULL) {
        free(db->students);
        db->students = NULL;
    }
    printf("Database memory freed\n");
}

void displayMenu() {
    printf("\n========== IEEE/ACM Registration System ==========\n");
    printf("1. Register New Student\n");
    printf("2. Update Student Information\n");
    printf("3. Delete Student Registration\n");
    printf("4. View All Registrations\n");
    printf("5. Generate Batch-Wise Report\n");
    printf("6. Exit\n");
    printf("===================================================\n");
    printf("Enter your choice: ");
}

int main() {
    Database db;
    int choice, studentID;
    char batch[20], membershipType[10];

    printf("\n================================================\n");
    printf("  FAST University Karachi\n");
    printf("  IEEE/ACM Membership Registration Manager\n");
    printf("================================================\n\n");

    initDatabase(&db);
    loadDatabase(&db, FILENAME);

    while (1) {
        displayMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1: {
                Student newStudent = inputStudentData();
                addStudent(&db, newStudent, FILENAME);
                break;
            }

            case 2:
                printf("Enter Student ID to update: ");
                scanf("%d", &studentID);
                getchar();
                updateStudent(&db, studentID, FILENAME);
                break;

            case 3:
                printf("Enter Student ID to delete: ");
                scanf("%d", &studentID);
                getchar();
                deleteStudent(&db, studentID, FILENAME);
                break;

            case 4:
                displayAllStudents(&db);
                break;

            case 5:
                printf("Enter Batch (CS/SE/Cyber Security/AI/ALL): ");
                fgets(batch, sizeof(batch), stdin);
                batch[strcspn(batch, "\n")] = 0;

                printf("Enter Membership Type (IEEE/ACM/ALL): ");
                fgets(membershipType, sizeof(membershipType), stdin);
                membershipType[strcspn(membershipType, "\n")] = 0;

                generateBatchReport(&db, batch, membershipType);
                break;

            case 6:
                printf("\nSaving database and exiting...\n");
                saveDatabase(&db, FILENAME);
                freeDatabase(&db);
                printf("Thank you for using the registration system!\n");
                return 0;

            default:
                printf("Invalid choice! Please select 1-6.\n");
        }
    }

    return 0;
}