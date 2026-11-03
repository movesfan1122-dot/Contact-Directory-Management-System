#ifndef CONTACT_H
#define CONTACT_H

#define NAME_LEN 100
#define PHONE_LEN 25
#define EMAIL_LEN 100

typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    struct Contact *next;
} Contact;

/* Module 1: Add and insert */
void addContactBeginning(Contact **head);
void addContactEnd(Contact **head);
void insertContactAtPosition(Contact **head);

/* Module 2: Delete and update */
void deleteContact(Contact **head);
void updateContact(Contact *head);

/* Module 3: Search */
void searchByName(Contact *head);
void searchByPhone(Contact *head);
void searchByEmail(Contact *head);

/* Module 4: Display, count, duplicate detection, sorting */
void displayContacts(const Contact *head);
int countContacts(const Contact *head);
void checkDuplicates(const Contact *head);
void sortContactsAlphabetically(Contact *head);

/* Shared input helpers implemented in main.c */
void readLine(const char *prompt, char *buffer, int size);
int readInt(const char *prompt);
void freeAllContacts(Contact **head);

#endif
