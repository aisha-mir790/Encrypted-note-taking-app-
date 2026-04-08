#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT_KEY 4
#define XOR_KEY 6
#define FILE_NAME "notes.txt"


// Create the notes.txt file automatically if it doesn't exist
void ensureFileExists() {
    FILE *fp = fopen(FILE_NAME, "a+");
    if (!fp) {
        printf("Error creating file!\n");
        exit(1);
    }
    fclose(fp);
}



// Encryption Function
void encrypt(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] + SHIFT_KEY;   // Step 1: ASCII shift
        text[i] = text[i] ^ XOR_KEY;     // Step 2: XOR
    }
}




// Decryption Function
void decrypt(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] ^ XOR_KEY;     // Reverse XOR
        text[i] = text[i] - SHIFT_KEY;   // Reverse shift
    }
}




// Create Note
void createNote() {
    char note[500];
    getchar(); // clear buffer
    printf("Enter your note: ");
    fgets(note, sizeof(note), stdin);

    note[strcspn(note, "\n")] = '\0'; // removes newline

    encrypt(note);

    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) {
        printf("Error writing to file.\n");
        return;
    }
    fprintf(fp, "%s\n", note);
    fclose(fp);

    printf("Note saved successfully!\n");
}




void popFile() {
    // Opens the notes.txt in Windows Notepad
    system("notepad " FILE_NAME);
}




// For viewing notes.
void viewNotes() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }


    char line[500];
    int count = 1;

    printf("\nYour Saved Notes (Decrypted):\n");
    printf("---------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        decrypt(line);
        printf("%d. %s\n", count++, line);
    }
    fclose(fp);
    popFile();

}



// This is used to delete the notes.
void deleteNotes() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        printf("Error clearing notes.\n");
        return;
    }
    fclose(fp);
    printf("All notes deleted successfully!\n");
    popFile();
}


// MAIN MENU
int main() {
    ensureFileExists();  // Auto-create file here!

    int choice;

    while (1) {
        printf("\nENCRYPTED NOTE-TAKING APP\n");
        printf("----------------------------\n");
        printf("1. Create a New Note\n");
        printf("2. View Encrypted Notes\n");
        printf("3. Delete Notes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createNote(); break;
            case 2: viewNotes(); break;
            case 3: deleteNotes(); break;
            case 4: 
                printf("Exiting program...\n");
                exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
}