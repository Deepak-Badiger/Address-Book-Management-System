#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
{
    char name[50];
    char phone[15];
    char mail[50];
} Contact;

typedef struct{
    Contact contacts[MAX_CONTACTS];
    int contact_count;
}AddressBook;
typedef enum 
{
    FAILURE = 0,
    SUCCESS = 1
}status;

void initialize(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);
void add_contact(AddressBook *addressBook);
void delete_contact(AddressBook *addressBook);
void edit_contact(AddressBook *addressBook);
void search_contact(AddressBook *addressBook);
void list_contacts(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
void loading();


/* Validation functions */
status validName(char *name);
status validPhone(char *phone);
status validMail(char *email);
int isDuplicate_phone(AddressBook *addressBook,char *phone);
int isDuplicate_phone(AddressBook *addressBook,char *phone);

#endif
