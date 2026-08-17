#include<stdio.h>
#include"contact.h"
#include"file.h"
void saveContactsToFile(AddressBook *addressBook)
{
    loading();
    FILE *fp = fopen("contacts.txt", "w");

    if (fp == NULL)
    {
        printf("File not opened\n");
        return;
    }
    fprintf(fp, "#%d\n", addressBook->contact_count);
    for (int i = 0; i < addressBook->contact_count; i++)
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].mail);
    }

    fclose(fp);
}
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.txt", "r");
    char fline[20]; // To store the first line in the file
    fscanf(fptr, "%[^\n]\n", fline);
    while ((fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[addressBook->contact_count].name, addressBook->contacts[addressBook->contact_count].phone, addressBook->contacts[addressBook->contact_count].mail)) == 3)
    {
        addressBook->contact_count++;
    }
    fclose(fptr);
}