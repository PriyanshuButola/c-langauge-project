#include <stdio.h>
#include "contact.h"

int main() {
    int choice, id;

    do {
        printf("\n==== Contact Manager ====\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchContact(id);
                break;
            case 4:
                printf("Enter ID to update: ");
       scanf("%d", &id);
                updateContact(id);
                break;
            case 5:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteContact(id);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 6);

    return 0;
}