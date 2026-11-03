CONTACT DIRECTORY MANAGEMENT SYSTEM (C / DSA)
================================================

PROJECT MODULES
1. Add and Insert Contact
   - Create contact nodes (name, phone, email)
   - Insert at beginning, end, or a 1-based position
2. Delete and Update
   - Delete by exact name or phone number
   - Update name, phone, and email
   - Press Enter during an update to keep a field unchanged
3. Search
   - Search by full or partial name, phone, or email
4. Display and Duplicate Check
   - Display all contacts
   - Count contacts
   - Detect repeated names, phone numbers, and emails
   - Sort alphabetically by name

DSA CONCEPTS
- Structures
- Singly linked lists
- Dynamic memory allocation (malloc/free)
- Insertion and deletion
- Linked-list traversal
- Searching
- Duplicate detection
- Bubble sort on contact data

FILES
- contact.h                  Shared structure and declarations
- main.c                     Menu, input helpers, integration, cleanup
- module1_add_insert.c       Module 1
- module2_delete_update.c    Module 2
- module3_search.c           Module 3
- module4_display.c          Module 4

COMPILE WITH GCC
Open a terminal in this folder and run:

gcc -std=c11 -Wall -Wextra -pedantic main.c module1_add_insert.c module2_delete_update.c module3_search.c module4_display.c -o contact_directory

Run on Windows:
contact_directory.exe

Run on Linux/macOS:
./contact_directory

If using VS Code, make sure a C compiler such as GCC is installed and available in PATH.

NOTES
- This version keeps contacts in memory only. Contacts are cleared when you exit.
- Phone numbers are strings so leading zeroes and '+' country codes are preserved.
- Insert positions start at 1.
- Deleting or updating by name uses the first matching name. If multiple contacts share a name, use phone number where possible.
- Duplicate checking reports duplicates; it does not automatically delete them.
