/*
Title       : Address Book Management System
Name        : Deepak Balappa Badiger
Date        : 12/04/2026
ID          : 26001_127
Description : This project is a console-based Address Book application developed in C.
              It allows users to manage contact details efficiently using fundamental
              programming concepts such as structures, arrays, pointers, file handling,
              and string manipulation.

              The Address Book stores multiple contacts, where each contact consists of
              a name, phone number, and email address. The application provides a
              user-friendly menu-driven interface to perform various operations.
              This addressBook allows us to:
                  1. Create contact
                  2. Search contact
                  3. Edit contact
                  4. Delete contact
                  5. List all contacts
                  6. Save and Exi
*/
#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

int main()
{
    int option;
    AddressBook addressBook;
    initialize(&addressBook);

    while (1)
    {
        printf("\n=============================================================\n");
        printf("                       ADDRESS BOOK MENU                \n");
        printf("=============================================================\n");
        printf(" 1. Add Contact\n");
        printf(" 2. Search Contact\n");
        printf(" 3. Edit Contact\n");
        printf(" 4. Delete Contact\n");
        printf(" 5. List All Contacts\n");
        printf(" 6. Save And Exit \n");
        printf("\n=============================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            add_contact(&addressBook);
            break;
        case 2:
            search_contact(&addressBook);

            break;
        case 3:
            edit_contact(&addressBook);
            break;
        case 4:
            delete_contact(&addressBook);

            break;
        case 5:
            list_contacts(&addressBook);

            break;
        case 6:
            saveContactsToFile(&addressBook);
            printf(" Contact Saved successfully... \n");
            exit(1);
            break;

        default:
            printf("Enter the valid Choice\n");
            break;
        }
    }

    return 0;
}