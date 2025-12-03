#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define INITIAL_CAPACITY 10
#define MAX_LINE_LENGTH 2048

void initEditor(char ***lines, int *numLines, int *capacity);
void insertLine(char ***lines, int *numLines, int *capacity, int index, const char *text);
void deleteLine(char ***lines, int *numLines, int index);
void printAllLines(char **lines, int numLines);
void freeAll(char ***lines, int numLines);
void shrinkToFit(char ***lines, int *capacity, int numLines);
void saveToFile(char **lines, int numLines, const char *filename);
void loadFromFile(char ***lines, int *numLines, int *capacity, const char *filename);
void displayMenu();
char* readLine();

void initEditor(char ***lines, int *numLines, int *capacity) {
    *capacity = INITIAL_CAPACITY;
    *numLines = 0;

    *lines = (char **)malloc((*capacity) * sizeof(char *));
    if (*lines == NULL) {
        error(1, errno, "Memory allocation failed during initialization");
    }

    printf("Editor initialized with capacity: %d lines\n", *capacity);
}

void insertLine(char ***lines, int *numLines, int *capacity, int index, const char *text) {
    if (index < 0 || index > *numLines) {
        fprintf(stderr, "Invalid index %d. Valid range is 0-%d\n", index, *numLines);
        return;
    }

    if (*numLines >= *capacity) {
        int newCapacity = (*capacity) * 2;
        char **temp = (char **)realloc(*lines, newCapacity * sizeof(char *));
        if (temp == NULL) {
            error(0, errno, "Failed to expand array capacity");
            return;
        }

        *lines = temp;
        *capacity = newCapacity;
        printf("Array capacity expanded to %d lines\n", newCapacity);
    }

    size_t textLen = strlen(text);
    char *newLine = (char *)malloc((textLen + 1) * sizeof(char));
    if (newLine == NULL) {
        error(0, errno, "Failed to allocate memory for new line");
        return;
    }

    strcpy(newLine, text);

    if (index < *numLines) {
        memmove(&(*lines)[index + 1], &(*lines)[index],
                (*numLines - index) * sizeof(char *));
    }

    (*lines)[index] = newLine;
    (*numLines)++;

    printf("Line inserted at index %d\n", index);
}

void deleteLine(char ***lines, int *numLines, int index) {
    if (index < 0 || index >= *numLines) {
        fprintf(stderr, "Invalid index %d. Valid range is 0-%d\n", index, *numLines - 1);
        return;
    }

    free((*lines)[index]);

    if (index < *numLines - 1) {
        memmove(&(*lines)[index], &(*lines)[index + 1],
                (*numLines - index - 1) * sizeof(char *));
    }

    (*numLines)--;
    printf("Line at index %d deleted successfully\n", index);
}

void printAllLines(char **lines, int numLines) {
    if (numLines == 0) {
        printf("Editor is empty.\n");
        return;
    }

    printf("\n========== Editor Contents (%d lines) ==========\n", numLines);
    for (int i = 0; i < numLines; i++) {
        printf("%4d: %s\n", i, lines[i]);
    }
    printf("================================================\n\n");
}

void freeAll(char ***lines, int numLines) {
    if (*lines == NULL) {
        return;
    }

    for (int i = 0; i < numLines; i++) {
        free((*lines)[i]);
    }

    free(*lines);
    *lines = NULL;

    printf("All memory freed successfully\n");
}

void shrinkToFit(char ***lines, int *capacity, int numLines) {
    if (numLines == 0) {
        fprintf(stderr, "Cannot shrink: editor is empty\n");
        return;
    }

    if (*capacity == numLines) {
        printf("Already at optimal size\n");
        return;
    }

    char **temp = (char **)realloc(*lines, numLines * sizeof(char *));
    if (temp == NULL) {
        error(0, errno, "Shrink operation failed");
        return;
    }

    *lines = temp;
    int oldCapacity = *capacity;
    *capacity = numLines;

    printf("Capacity reduced from %d to %d (freed %d pointer slots)\n",
           oldCapacity, numLines, oldCapacity - numLines);
}

void saveToFile(char **lines, int numLines, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        error(0, errno, "Cannot open file '%s' for writing", filename);
        return;
    }

    for (int i = 0; i < numLines; i++) {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);
    printf("Successfully saved %d lines to '%s'\n", numLines, filename);
}

void loadFromFile(char ***lines, int *numLines, int *capacity, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        error(0, errno, "Cannot open file '%s' for reading", filename);
        return;
    }

    freeAll(lines, *numLines);
    initEditor(lines, numLines, capacity);

    char buffer[MAX_LINE_LENGTH];
    int linesLoaded = 0;

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        insertLine(lines, numLines, capacity, *numLines, buffer);
        linesLoaded++;
    }

    fclose(file);
    printf("Successfully loaded %d lines from '%s'\n", linesLoaded, filename);
}

void displayMenu() {
    printf("\n============ Text Editor Menu ============\n");
    printf("1. Insert line at position\n");
    printf("2. Delete line at position\n");
    printf("3. Display all lines\n");
    printf("4. Save buffer to file\n");
    printf("5. Load buffer from file\n");
    printf("6. Shrink capacity to fit\n");
    printf("7. Display memory statistics\n");
    printf("8. Exit editor\n");
    printf("==========================================\n");
    printf("Enter your choice: ");
}

char* readLine() {
    char buffer[MAX_LINE_LENGTH];

    if (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        char *line = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (line == NULL) {
            error(0, errno, "Memory allocation failed while reading input");
            return NULL;
        }
        strcpy(line, buffer);
        return line;
    }

    return NULL;
}

int main() {
    char **lines = NULL;
    int numLines = 0;
    int capacity = 0;
    int choice, index;
    char filename[256];

    printf("\n========================================\n");
    printf("  FAST University Karachi\n");
    printf("  Minimal Line-Based Text Editor\n");
    printf("  Using Dynamic Memory Allocation\n");
    printf("========================================\n\n");

    initEditor(&lines, &numLines, &capacity);

    while (1) {
        displayMenu();

        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Enter index (0-%d): ", numLines);
                if (scanf("%d", &index) != 1) {
                    fprintf(stderr, "Invalid index input\n");
                    while (getchar() != '\n');
                    break;
                }
                getchar();

                printf("Enter line text: ");
                char *text = readLine();
                if (text != NULL) {
                    insertLine(&lines, &numLines, &capacity, index, text);
                    free(text);
                }
                break;

            case 2:
                printf("Enter index to delete (0-%d): ", numLines - 1);
                if (scanf("%d", &index) != 1) {
                    fprintf(stderr, "Invalid index input\n");
                    while (getchar() != '\n');
                    break;
                }
                getchar();
                deleteLine(&lines, &numLines, index);
                break;

            case 3:
                printAllLines(lines, numLines);
                break;

            case 4:
                printf("Enter filename to save: ");
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    size_t len = strlen(filename);
                    if (len > 0 && filename[len - 1] == '\n') {
                        filename[len - 1] = '\0';
                    }
                    saveToFile(lines, numLines, filename);
                }
                break;

            case 5:
                printf("Enter filename to load: ");
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    size_t len = strlen(filename);
                    if (len > 0 && filename[len - 1] == '\n') {
                        filename[len - 1] = '\0';
                    }
                    loadFromFile(&lines, &numLines, &capacity, filename);
                }
                break;

            case 6:
                shrinkToFit(&lines, &capacity, numLines);
                break;

            case 7: {
                printf("\n========== Memory Statistics ==========\n");
                printf("Number of lines stored: %d\n", numLines);
                printf("Current array capacity: %d\n", capacity);
                printf("Memory for pointer array: %d bytes\n",
                       capacity * (int)sizeof(char *));
                printf("Unused capacity: %d lines\n", capacity - numLines);

                int totalTextMemory = 0;
                for (int i = 0; i < numLines; i++) {
                    totalTextMemory += strlen(lines[i]) + 1;
                }
                printf("Memory for text data: %d bytes\n", totalTextMemory);
                printf("Total memory usage: %d bytes\n",
                       capacity * (int)sizeof(char *) + totalTextMemory);
                printf("========================================\n");
                break;
            }

            case 8:
                printf("\nExiting editor...\n");
                freeAll(&lines, numLines);
                printf("Thank you for using the text editor!\n");
                return 0;

            default:
                fprintf(stderr, "Invalid choice! Please select 1-8.\n");
        }
    }

    return 0;
}