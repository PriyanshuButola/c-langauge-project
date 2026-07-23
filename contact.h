#ifndef CONTACT_H
#define CONTACT_H

#define NAME_LEN 50
#define PHONE_LEN 15
#define EMAIL_LEN 50
#define FILENAME "contacts.dat"

typedef struct {
    int id;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

void addContact();
void viewContacts();
void searchContact(int id);
void updateContact(int id);
void deleteContact(int id);

#endif