#include <stdio.h>
#include <string.h>
#include "contact.h"

void addContact() {
    FILE *fp = fopen(FILENAME, "ab");   // append, binary
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Contact c;
    printf("Enter ID: ");
    scanf("%d", &c.id);
    printf("Enter Name: ");
    scanf("%s", c.name);
    printf("Enter Phone: ");
    scanf("%s", c.phone);
    printf("Enter Email: ");
    scanf("%s", c.email);

    fwrite(&c, sizeof(Contact), 1, fp);
    fclose(fp);
    printf("Contact added successfully!\n");
}

void viewContacts() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No contacts found yet.\n");
        return;
    }

    Contact c;
    printf("\n--- All Contacts ---\n");
    while (fread(&c, sizeof(Contact), 1, fp) == 1) {
        printf("ID: %d | Name: %s | Phone: %s | Email: %s\n",
               c.id, c.name, c.phone, c.email);
    }
    fclose(fp);
}

void searchContact(int id) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No contacts found yet.\n");
        return;
    }

    Contact c;
    int found = 0;
    while (fread(&c, sizeof(Contact), 1, fp) == 1) {
        if (c.id == id) {
            printf("Found -> Name: %s | Phone: %s | Email: %s\n",
                   c.name, c.phone, c.email);
            found = 1;
            break;
        }
    }
    if (!found) printf("Contact with ID %d not found.\n", id);
    fclose(fp);
}

void updateContact(int id) {
    FILE *fp = fopen(FILENAME, "rb+");   // read + write, binary
    if (fp == NULL) {
        printf("No contacts found yet.\n");
        return;
    }

    Contact c;
    int found = 0;
    while (fread(&c, sizeof(Contact), 1, fp) == 1) {
        if (c.id == id) {
            printf("Enter new phone: ");
            scanf("%s", c.phone);
            printf("Enter new email: ");
            scanf("%s", c.email);

            fseek(fp, -(long)sizeof(Contact), SEEK_CUR);  // move back one record
            fwrite(&c, sizeof(Contact), 1, fp);            // overwrite it
            found = 1;
            break;
        }
    }
    if (!found) printf("Contact with ID %d not found.\n", id);
    fclose(fp);
}

void deleteContact(int id) {
    FILE *fp = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Contact c;
    int found = 0;
    while (fread(&c, sizeof(Contact), 1, fp) == 1) {
        if (c.id == id) {
            found = 1;
            continue;   // skip writing this one -> effectively deletes it
        }
        fwrite(&c, sizeof(Contact), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove(FILENAME);          // delete old file
    rename("temp.dat", FILENAME);  // rename temp file to original name

    if (found)
        printf("Contact with ID %d deleted.\n", id);
    else
        printf("Contact with ID %d not found.\n", id);
}