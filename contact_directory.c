
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LEN 100
#define PHONE_LEN 25
#define EMAIL_LEN 100

// Structure for each contact node
typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    struct Contact *next;
} Contact;

Contact *head = NULL;

// ---------- INPUT HELPER FUNCTIONS ----------

void readLine(const char *prompt, char *buffer, int size) {
    int ch;
    size_t len;

    printf("%s", prompt);

    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        while ((ch = getchar()) != '\n' && ch != EOF) {
            // Clear excess input
        }
    }
}

int readInt(const char *prompt) {
    char buffer[100];
    char extra;
    int value;

    while (1) {
        readLine(prompt, buffer, sizeof(buffer));

        if (sscanf(buffer, "%d %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid input! Enter a whole number.\n");
    }
}

// Case-insensitive string comparison
int compareIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);

        if (ca != cb)
            return ca - cb;

        a++;
        b++;
    }

    return tolower((unsigned char)*a) -
           tolower((unsigned char)*b);
}

// Case-insensitive partial search
int containsIgnoreCase(const char *text, const char *pattern) {
    size_t i, j;

    if (pattern[0] == '\0')
        return 0;

    for (i = 0; text[i] != '\0'; i++) {
        for (j = 0;
             pattern[j] != '\0' &&
             text[i + j] != '\0' &&
             tolower((unsigned char)text[i + j]) ==
             tolower((unsigned char)pattern[j]);
             j++) {
        }

        if (pattern[j] == '\0')
            return 1;
    }

    return 0;
}

// ---------- MODULE 1: ADD AND INSERT CONTACT ----------

// Create a new contact node
Contact *createContact(void) {
    Contact *newNode =
        (Contact *)malloc(sizeof(Contact));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    readLine("Enter name: ",
             newNode->name, NAME_LEN);

    readLine("Enter phone number: ",
             newNode->phone, PHONE_LEN);

    readLine("Enter email address: ",
             newNode->email, EMAIL_LEN);

    newNode->next = NULL;

    return newNode;
}

// Insert at the beginning
void insertBeginning(void) {
    Contact *newNode = createContact();

    if (newNode == NULL)
        return;

    newNode->next = head;
    head = newNode;

    printf("Contact added at the beginning!\n");
}

// Insert at the end
void insertEnd(void) {
    Contact *newNode = createContact();
    Contact *temp;

    if (newNode == NULL)
        return;

    if (head == NULL) {
        head = newNode;
    } else {
        temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    printf("Contact added at the end!\n");
}

// Insert at a specified 1-based position
void insertAtPosition(void) {
    int position, i;
    Contact *temp;
    Contact *newNode;

    position = readInt(
        "Enter position (1 = beginning): ");

    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }

    if (position == 1) {
        insertBeginning();
        return;
    }

    temp = head;

    for (i = 1;
         temp != NULL && i < position - 1;
         i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }

    newNode = createContact();

    if (newNode == NULL)
        return;

    newNode->next = temp->next;
    temp->next = newNode;

    printf("Contact inserted at position %d!\n",
           position);
}

// ---------- MODULE 2: DELETE AND UPDATE ----------

// Delete by name or phone number
void deleteContact(void) {
    int choice;
    Contact *temp = head;
    Contact *previous = NULL;
    char key[NAME_LEN];
    int found = 0;

    if (head == NULL) {
        printf("Directory is empty!\n");
        return;
    }

    printf("\n1. Delete by name\n");
    printf("2. Delete by phone number\n");

    choice = readInt("Enter choice: ");

    if (choice == 1) {
        readLine("Enter exact name: ",
                 key, sizeof(key));
    } else if (choice == 2) {
        readLine("Enter exact phone number: ",
                 key, sizeof(key));
    } else {
        printf("Invalid choice!\n");
        return;
    }

    while (temp != NULL) {
        if ((choice == 1 &&
             compareIgnoreCase(temp->name, key) == 0) ||
            (choice == 2 &&
             strcmp(temp->phone, key) == 0)) {
            found = 1;
            break;
        }

        previous = temp;
        temp = temp->next;
    }

    if (!found) {
        printf("Contact not found!\n");
        return;
    }

    if (previous == NULL) {
        head = temp->next;
    } else {
        previous->next = temp->next;
    }

    free(temp);

    printf("Contact deleted successfully!\n");
}

// Update contact details
void updateContact(void) {
    int choice;
    Contact *temp = head;
    char key[NAME_LEN];
    int found = 0;
    char buffer[EMAIL_LEN];

    if (head == NULL) {
        printf("Directory is empty!\n");
        return;
    }

    printf("\n1. Find by name\n");
    printf("2. Find by phone number\n");

    choice = readInt("Enter choice: ");

    if (choice == 1) {
        readLine("Enter exact name: ",
                 key, sizeof(key));
    } else if (choice == 2) {
        readLine("Enter exact phone number: ",
                 key, sizeof(key));
    } else {
        printf("Invalid choice!\n");
        return;
    }

    while (temp != NULL) {
        if ((choice == 1 &&
             compareIgnoreCase(temp->name, key) == 0) ||
            (choice == 2 &&
             strcmp(temp->phone, key) == 0)) {
            found = 1;
            break;
        }

        temp = temp->next;
    }

    if (!found) {
        printf("Contact not found!\n");
        return;
    }

    printf("\nPress Enter to keep the existing value.\n");

    readLine("New name: ", buffer, sizeof(buffer));
    if (buffer[0] != '\0') {
        snprintf(temp->name, NAME_LEN, "%s", buffer);
    }

    readLine("New phone number: ",
             buffer, sizeof(buffer));
    if (buffer[0] != '\0') {
        snprintf(temp->phone, PHONE_LEN, "%s", buffer);
    }

    readLine("New email address: ",
             buffer, sizeof(buffer));
    if (buffer[0] != '\0') {
        snprintf(temp->email, EMAIL_LEN, "%s", buffer);
    }

    printf("Contact updated successfully!\n");
}

// ---------- MODULE 3: SEARCH CONTACT ----------

// Search by name
void searchByName(void) {
    Contact *temp = head;
    char key[NAME_LEN];
    int found = 0;

    readLine("Enter name or part of name: ",
             key, sizeof(key));

    while (temp != NULL) {
        if (containsIgnoreCase(temp->name, key)) {
            printf("\nName : %s\n", temp->name);
            printf("Phone: %s\n", temp->phone);
            printf("Email: %s\n", temp->email);
            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("No matching contact found!\n");
}

// Search by phone number
void searchByPhone(void) {
    Contact *temp = head;
    char key[PHONE_LEN];
    int found = 0;

    readLine("Enter phone number or part of it: ",
             key, sizeof(key));

    while (temp != NULL) {
        if (key[0] != '\0' &&
            strstr(temp->phone, key) != NULL) {
            printf("\nName : %s\n", temp->name);
            printf("Phone: %s\n", temp->phone);
            printf("Email: %s\n", temp->email);
            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("No matching contact found!\n");
}

// Search by email
void searchByEmail(void) {
    Contact *temp = head;
    char key[EMAIL_LEN];
    int found = 0;

    readLine("Enter email or part of email: ",
             key, sizeof(key));

    while (temp != NULL) {
        if (containsIgnoreCase(temp->email, key)) {
            printf("\nName : %s\n", temp->name);
            printf("Phone: %s\n", temp->phone);
            printf("Email: %s\n", temp->email);
            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("No matching contact found!\n");
}

// ---------- MODULE 4: DISPLAY AND DUPLICATE CHECK ----------

// Display all contacts
void displayContacts(void) {
    Contact *temp = head;
    int count = 1;

    if (head == NULL) {
        printf("Directory is empty!\n");
        return;
    }

    printf("\n================ CONTACT DIRECTORY ================\n");

    printf("%-5s %-25s %-20s %-30s\n",
           "No.", "Name", "Phone", "Email");

    printf("----------------------------------------------------"
           "-----------------------------------\n");

    while (temp != NULL) {
        printf("%-5d %-25.25s %-20.20s %-30.30s\n",
               count++,
               temp->name,
               temp->phone,
               temp->email);

        temp = temp->next;
    }

    printf("====================================================\n");
}

// Count contacts
void countContacts(void) {
    Contact *temp = head;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    printf("Total contacts: %d\n", count);
}

// Detect duplicate names, phone numbers, and emails
void checkDuplicates(void) {
    Contact *first, *second;
    int found = 0;

    if (head == NULL) {
        printf("Directory is empty!\n");
        return;
    }

    for (first = head;
         first != NULL;
         first = first->next) {

        for (second = first->next;
             second != NULL;
             second = second->next) {

            if (first->name[0] != '\0' &&
                compareIgnoreCase(first->name,
                                  second->name) == 0) {
                printf("Duplicate name: %s\n",
                       first->name);
                found = 1;
            }

            if (first->phone[0] != '\0' &&
                strcmp(first->phone,
                       second->phone) == 0) {
                printf("Duplicate phone: %s\n",
                       first->phone);
                found = 1;
            }

            if (first->email[0] != '\0' &&
                compareIgnoreCase(first->email,
                                  second->email) == 0) {
                printf("Duplicate email: %s\n",
                       first->email);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No duplicate contacts found!\n");
    }
}

// Sort contacts alphabetically using bubble sort
void sortAlphabetically(void) {
    Contact *current, *nextNode;
    char tempName[NAME_LEN];
    char tempPhone[PHONE_LEN];
    char tempEmail[EMAIL_LEN];

    if (head == NULL || head->next == NULL) {
        printf("Not enough contacts to sort.\n");
        return;
    }

    for (current = head;
         current != NULL;
         current = current->next) {

        for (nextNode = current->next;
             nextNode != NULL;
             nextNode = nextNode->next) {

            if (compareIgnoreCase(current->name,
                                  nextNode->name) > 0) {

                // Swap complete contact data
                strcpy(tempName, current->name);
                strcpy(tempPhone, current->phone);
                strcpy(tempEmail, current->email);

                strcpy(current->name, nextNode->name);
                strcpy(current->phone, nextNode->phone);
                strcpy(current->email, nextNode->email);

                strcpy(nextNode->name, tempName);
                strcpy(nextNode->phone, tempPhone);
                strcpy(nextNode->email, tempEmail);
            }
        }
    }

    printf("Contacts sorted alphabetically!\n");
    displayContacts();
}

// ---------- MEMORY CLEANUP ----------

void freeAllContacts(void) {
    Contact *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// ---------- MAIN MENU ----------

int main(void) {
    int choice;

    do {
        printf("\n");
        printf("============================================\n");
        printf("      CONTACT DIRECTORY MANAGEMENT\n");
        printf("============================================\n");
        printf("1.  Add contact at beginning\n");
        printf("2.  Add contact at end\n");
        printf("3.  Insert contact at position\n");
        printf("4.  Delete contact\n");
        printf("5.  Update contact\n");
        printf("6.  Search by name\n");
        printf("7.  Search by phone\n");
        printf("8.  Search by email\n");
        printf("9.  Display all contacts\n");
        printf("10. Count total contacts\n");
        printf("11. Check duplicate contacts\n");
        printf("12. Sort contacts alphabetically\n");
        printf("0.  Exit\n");
        printf("============================================\n");

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                insertBeginning();
                break;

            case 2:
                insertEnd();
                break;

            case 3:
                insertAtPosition();
                break;

            case 4:
                deleteContact();
                break;

            case 5:
                updateContact();
                break;

            case 6:
                searchByName();
                break;

            case 7:
                searchByPhone();
                break;

            case 8:
                searchByEmail();
                break;

            case 9:
                displayContacts();
                break;

            case 10:
                countContacts();
                break;

            case 11:
                checkDuplicates();
                break;

            case 12:
                sortAlphabetically();
                break;

            case 0:
                printf("Exiting Contact Directory...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 0);

    freeAllContacts();

    return 0;
}
