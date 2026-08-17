#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "contact.h"
#include <ctype.h>
#include "file.h"

// Initialize address book and load data from file
void initialize(AddressBook *addressBook)
{
    addressBook->contact_count = 0;
    loadContactsFromFile(addressBook);
}
// Check the name is valid or not
status validName(char *name)
{
    if (name[0] == '\0') // Name should not be empty
        return FAILURE;
    int i = 0;
    while (name[i] != '\0') // Name only contains alphabets
    {
        if (!((name[i] <= 'z' && name[i] >= 'a') || (name[i] <= 'Z' && name[i] >= 'A') || name[i] == ' ' || name[i] == '.'))
            return FAILURE; // other than alphabets return false
        i++;
    }
    return SUCCESS;
}

// Check for Phone validation
status validPhone(char *phone)
{
    if (strlen(phone) != 10) // Should contain 10 digits
        return FAILURE;

    for (int i = 0; phone[i]; i++)
    {
        if (!isdigit(phone[i])) // it should contain only digits
            return FAILURE;
    }
    return SUCCESS;
}
// Check Mail validation
status validMail(char *mail)
{
    int pos_a = -1, pos_d = -1, count = 0;
    for (int i = 0; mail[i] != '\0'; i++)
    {
        if (!((mail[i] >= 'a' && mail[i] <= 'z') || (mail[i] >= '0' && mail[i] <= '9') || mail[i] == '@' || mail[i] == '.'))
            return FAILURE;
        if (mail[i] == '@') // Check @ and store the index
        {
            pos_a = i;
            count++;
        }
        if (mail[i] == '.') // Check . and store the index
        {
            pos_d = i;
            count++;
        }
    }
    if (strcasestr(mail, ".com") == NULL) // check .com string is present or not
        return FAILURE;

    if (pos_a == 0 || pos_d == 0 || count != 2 || mail[pos_a + 1] == '.') // ckect . and @ are present only one time
        return FAILURE;

    for (int i = pos_a + 1; i < pos_d; i++)
    {
        if (!(mail[i] >= 'a' && mail[i] <= 'z')) // between the . and @ string should be present
            return FAILURE;
    }
    return SUCCESS;
}
// Check if the phone number is already present or not
int isDuplicate_phone(AddressBook *addressBook, char *phone)
{
    for (int i = 0; i < addressBook->contact_count; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            return SUCCESS; // If present
    }
    return FAILURE; // if not
}
// Check if the Mail is already present or not
int isDuplicate_mail(AddressBook *addressBook, char *mail)
{
    for (int i = 0; i < addressBook->contact_count; i++)
    {
        if (strcmp(mail, addressBook->contacts[i].mail) == 0)
            return SUCCESS; // if present
    }
    return FAILURE; // if not
}

void loading()
{
    for (int i = 0; i <= 100; i++)
    {
        printf("Processing... %d%%\r", i);
        fflush(stdout);
        usleep(10000);
    }
    printf("Completed...\n");
}

/**  LOGIC FOR  ADD CONTACT **/
void add_contact(AddressBook *addressBook)
{
    printf("\n=============================================================\n");
    printf("                       ADD NEW CONTACT                      \n");
    printf("=============================================================\n");

    while (1)
    {
        char str[30];
        printf(" Enter the name : "); // Read Name
        scanf(" %[^\n]", str);

        if (!validName(str)) // Check Validation
        {
            printf(" Invalid Name\n");
            continue;
        }
        strcpy(addressBook->contacts[addressBook->contact_count].name, str); // Store the Name
        break;
    }

    while (1)
    {
        char str[100];
        printf("Enter Phone number : "); // Read the Phone
        scanf(" %[^\n]", str);
        if (!validPhone(str)) // Check the validation of phone
        {
            printf("Invalid Number\n");
            continue;
        }
        if (isDuplicate_phone(addressBook, str)) // Check the Phone is already present or not
        {
            printf("Number already exists\n");
            continue;
        }
        strcpy(addressBook->contacts[addressBook->contact_count].phone, str); // Store the phone
        break;
    }

    while (1)
    {
        char str[100];
        printf("Enter gmail : ");
        scanf(" %[^\n]", str); // Read the mail
        if (!validMail(str))
        {
            printf("Invalid Gmail!\n"); // Ckeck the validation of mail
            continue;
        }
        if (isDuplicate_mail(addressBook, str))
        {
            printf(" Mail already exists\n"); // Ckeck the mail is already is present or not
            continue;
        }

        strcpy(addressBook->contacts[addressBook->contact_count].mail, str); // Store the mail
        addressBook->contact_count++;                                        // Increament the count to store the next contaccts in structure
        loading();
        printf("Contact Added Successfully!\n");
        break;
    }
}

/**   LOGIC TO LIST THE CONTACT   **/
void list_contacts(AddressBook *addressBook)
{
    if (addressBook->contact_count == 0) // Check the list is empty or not
    {
        printf(" NO CONTACTS AVAILABLE\n");
        return;
    }

    printf("\n=============================================================\n");
    printf("                    LIST OF ALL CONTACTS               \n");
    printf("=============================================================\n");

    /**     LOGIC TO SORT THE CONTACTS BEFORE LIST   **/
    for (int i = 0; i < addressBook->contact_count - 1; i++)
    {
        for (int j = 0; j < addressBook->contact_count - i - 1; j++)
        {
            // Name is  used here to sort the contacts
            if (strcasecmp(addressBook->contacts[j].name,
                           addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
    // List the contacts
    printf("%-4s %-15s %-15s %-20s\n", "S.no", "Name", "phone", "Email");

    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contact_count; i++)
    {

        printf("%-4d %-15s %-15s %-20s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].mail);
    }
    printf("-------------------------------------------------------------\n");
}

// search by Name logic
int search_byName(AddressBook *addressBook)
{

    while (1)
    {
        char str[30];
        printf("Enter the Name : "); // Read the name to search
        scanf(" %[^\n]", str);
        if (!validName(str)) // Validate the name
        {
            printf("Invalid Name\n");
            continue;
        }

        if (addressBook->contact_count == 0) // Check list is empty
        {
            printf("List is Empty\n");
            continue;
        }
        int s = 1, count = 0, ind[100];
        loading();
        // Display the matched contacts
        for (int i = 0; i < addressBook->contact_count; i++)
        {

            if (strcasestr(addressBook->contacts[i].name, str) != NULL)
            {
                if(count == 0){
                    printf("Contact Found\n");
                    printf("-------------------------------------------------------------\n");
                }
                printf("%-4d %-15s %-15s %-20s\n", s++, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].mail);
                ind[count++] = i;
            }
        }
        // If not any contact matched
        if (count == 0)
        {
            return -1;
        }
        // If only one contact Matched
        else if (count == 1)
        {
            return ind[0]; // Returning index of conatct
        }
        // If multiple contacts matched
        else
        {
            int choice;
            printf("---MULTIPLE CONTACTS FOUND---\n");
            printf("Enter the Serial number to select contact\n"); // Aske user to select one conatact by serial number
            scanf("%d", &choice);
            if (!(choice > 0 && choice <= count)) // Ckeck selected serial number is valid or not
            {
                printf("Invalid Choice!");
                continue;
            }
            int choose_ind = ind[choice - 1];
            printf("Selected Contact : \n"); // Display the selected contact
             printf("-------------------------------------------------------------\n");
            printf("%-4d %-15s %-15s %-20s\n", 1, addressBook->contacts[choose_ind].name, addressBook->contacts[choose_ind].phone, addressBook->contacts[choose_ind].mail);
            return choose_ind;
        }
    }
}
// Search by phone
int search_byPhone(AddressBook *addressBook)
{
    while (1)
    {
        char str[15];
        printf("Enter the Phone : "); // Read the phone to search
        scanf(" %[^\n]", str);
        if (!validPhone(str)) // validate the phone
        {
            printf("Invalid Number\n");
            continue;
        }

        if (addressBook->contact_count != 0) // If contact is not empty
        {
            for (int i = 0; i < addressBook->contact_count; i++)
            {
                if (strstr(addressBook->contacts[i].phone, str) != NULL) // If phone matched display the contact
                {
                    printf("Contact Found\n");
                    printf("%-4d %-15s %-15s %-20s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].mail);
                    return i;
                }
            }
            // if contact is not present
            return -1;
        }
        else
            printf("List is Empty\n");
        return -1;
    }
}
// Search by Mail
int search_byMail(AddressBook *addressBook)
{
    while (1)
    {

        char str[30];
        printf("Enter the Mail : "); // Read the mail to search
        scanf(" %[^\n]", str);
        if (!validMail(str)) // Validate the mail
        {
            printf("Invalid Gmail");
            continue;
        }

        if (addressBook->contact_count != 0) // if contact is not empty
        {
            for (int i = 0; i < addressBook->contact_count; i++)
            {
                if (strcasestr(addressBook->contacts[i].mail, str) != NULL) // if mail matched display the contact
                {
                    printf("Contact Found\n");
                    printf("%-4d %-15s %-15s %-20s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].mail);
                    return i;
                }
            } // if not present
            return -1;
        }
    }
}

/**       LOGIC FOR SEARCH CONTACTS           **/
void search_contact(AddressBook *addressBook)
{
    while (1)
    {
        printf("\n=============================================================\n");
        printf("                        SEARCH CONTACT                       \n");
        printf("=============================================================\n");
        int op;
        // Ask user to select serch by name phone or mail
        printf("Search By : \n1.Name\n2.Phone\n3.Mail\n4.Exit\nEnter the choice : ");
        scanf("%d", &op);
        switch (op)
        {
            char str[100];
        case 1:
            if (search_byName(addressBook) == -1) // case 1. for search by name
            {
                printf("Name is  not present\n");
                break;
            }
            else
                break;

        case 2:
            if (search_byPhone(addressBook) == -1) // case 2.for seach by phone
            {
                printf("Contact is  not present\n");
                break;
            }
            else
                break;

        case 3:
            if (search_byMail(addressBook) == -1) // case 3. for seach by mail
            {
                printf("Contact is  not present\n");
                break;
            }
            else
                break;
        case 4: // case 4. for exit
            return;
        default:
            printf("Invlid Choice!\n");
            break;
        }
        break;
    }
}

/**       LOGIC FOR EDIT THE CONTACS          **/
void edit_contact(AddressBook *addressBook)
{
    while (1)
    {
        int op;
        printf("\n=============================================================\n");
        printf("                       EDIT CONTACT        \n");
        printf("=============================================================\n");
        printf("EDIT BY :\n"); // Ask user to select edit by name phone and mail
        printf(" 1.  Name\n");
        printf(" 2.  Phone\n");
        printf(" 3.  Mail\n");
        printf(" 4.  Exit\n");
        printf("Enter choice: ");
        scanf("%d", &op);

        switch (op)
        {
            // Case 1. for edit by name
        case 1:
            int ret = search_byName(addressBook);
            if (ret == -1)
            {
                printf("Name is  not present\n");
                break;
            }
            else
            {
                int choice;
                printf("\n What do you want to edit?\n");
                printf("1. Name\n");  // 1. To edit Name
                printf("2. Phone\n"); // 2. To edit Phone
                printf("3. Mail\n");  // 3. To edit Mail
                printf("Enter choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    char name[30];
                    printf("Enter the New name : "); // Enter the new to edit
                    scanf(" %[^\n]", name);
                    if (!validName(name)) // Validate the new name
                    {
                        printf("Invalid Name!");
                        break;
                    }
                    strcpy(addressBook->contacts[ret].name, name); // Edit the name
                    printf("Contact Edited Successfully\n");
                    return;
                case 2:
                    char phone[30];
                    printf("Enter the New Phone : "); // Enter the new Phone number to edit
                    scanf(" %[^\n]", phone);
                    if (!validPhone(phone)) // Validate the name
                    {
                        printf("Invalid Number\n");
                        break;
                    }
                    if (isDuplicate_phone(addressBook, phone)) // Check phone is already present or not
                    {
                        printf("Number is already Exist\nPlease Enter different number\n");
                        break;
                    }
                    strcpy(addressBook->contacts[ret].phone, phone); // Edit the phone
                    printf("Contact Edited Successfully\n");
                    return;
                case 3:
                    char mail[30];
                    printf("Enter the New mail : "); // Enter the new mail to Edit
                    scanf(" %[^\n]", mail);
                    if (!validMail(mail)) // Validate the mail
                    {
                        printf("Invalid Gmail\n");
                        break;
                    }
                    if (isDuplicate_mail(addressBook, mail)) // check mail is alredy present or not
                    {
                        printf("Mail is already Exist\nPlease Enter different Mail\n");
                        break;
                    }

                    strcpy(addressBook->contacts[ret].mail, mail); // Edit the mail
                    printf("Contact Edited Successfully\n");
                    return;
                default:
                    printf("Invalid Choice!\n");
                    break;
                }
            }
            break;

        case 2:
            int ret1 = search_byPhone(addressBook);
            if (ret1 == -1)
            {
                printf("Contct is  not present\n");
                break;
            }
            else
            {
                int choice;
                printf("\n What do you want to edit?\n");
                printf("1. Name\n");  // 1. To edit Name
                printf("2. Phone\n"); // 2. To edit Phone
                printf("3. Mail\n");  // 3. To edit Mail
                printf("Enter choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    char name[30];
                    printf("Enter the New name : "); // Enter the new to edit
                    scanf(" %[^\n]", name);
                    if (!validName(name)) // Validate the new name
                    {
                        printf("Invalid Name!");
                        break;
                    }
                    strcpy(addressBook->contacts[ret1].name, name); // Edit the name
                    printf("Contact Edited Successfully\n");
                    return;
                case 2:
                    char phone[30];
                    printf("Enter the New Phone : "); // Enter the new Phone number to edit
                    scanf(" %[^\n]", phone);
                    if (!validPhone(phone)) // Validate the name
                    {
                        printf("Invalid Number\n");
                        break;
                    }
                    if (isDuplicate_phone(addressBook, phone)) // Check phone is already present or not
                    {
                        printf("Number is already Exist\nPlease Enter different number\n");
                        break;
                    }
                    strcpy(addressBook->contacts[ret1].phone, phone); // Edit the phone
                    printf("Contact Edited Successfully\n");
                    return;
                case 3:
                    char mail[30];
                    printf("Enter the New mail : "); // Enter the new mail to Edit
                    scanf(" %[^\n]", mail);
                    if (!validMail(mail)) // Validate the mail
                    {
                        printf("Invalid Gmail\n");
                        break;
                    }
                    if (isDuplicate_mail(addressBook, mail)) // check mail is alredy present or not
                    {
                        printf("Mail is already Exist\nPlease Enter different Mail\n");
                        break;
                    }

                    strcpy(addressBook->contacts[ret1].mail, mail); // Edit the mail
                    printf("Contact Edited Successfully\n");
                    return;
                default:
                    printf("Invalid Choice!\n");
                    break;
                }
            }
            break;

        case 3:
            int ret2 = search_byMail(addressBook);
            if (ret2 == -1)
            {
                printf("Contact is  not present\n");
                break;
            }
            else
            {
                int choice;
                printf("\n What do you want to edit?\n");
                printf("1.  Name\n");  // 1. To edit Name
                printf("2.  Phone\n"); // 2. To edit Phone
                printf("3.  Mail\n");  // 3. To edit Mail
                printf("Enter choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    char name[30];
                    printf("Enter the New name : "); // Enter the new to edit
                    scanf(" %[^\n]", name);
                    if (!validName(name)) // Validate the new name
                    {
                        printf("Invalid Name!");
                        break;
                    }
                    strcpy(addressBook->contacts[ret2].name, name); // Edit the name
                    printf("Contact Edited Successfully\n");
                    return;
                case 2:
                    char phone[30];
                    printf("Enter the New Phone : "); // Enter the new Phone number to edit
                    scanf(" %[^\n]", phone);
                    if (!validPhone(phone)) // Validate the name
                    {
                        printf("Invalid Number\n");
                        break;
                    }
                    if (isDuplicate_phone(addressBook, phone)) // Check phone is already present or not
                    {
                        printf("Number is already Exist\nPlease Enter different number\n");
                        break;
                    }
                    strcpy(addressBook->contacts[ret2].phone, phone); // Edit the phone
                    printf("Contact Edited Successfully\n");
                    return;
                case 3:
                    char mail[30];
                    printf("Enter the New mail : "); // Enter the new mail to Edit
                    scanf(" %[^\n]", mail);
                    if (!validMail(mail)) // Validate the mail
                    {
                        printf("Invalid Gmail\n");
                        break;
                    }
                    if (isDuplicate_mail(addressBook, mail)) // check mail is alredy present or not
                    {
                        printf("Mail is already Exist\nPlease Enter different Mail\n");
                        break;
                    }

                    strcpy(addressBook->contacts[ret2].mail, mail); // Edit the mail
                    printf("Contact Edited Successfully\n");
                    return;
                default:
                    printf("Invalid Choice!\n");
                    break;
                }
            }
            break;
        case 4:
            return;
        default:
            printf("Invalid Choice!\n");
            break;
        }
    }
}

/**        LOGIC TO DELETE THE CONTACT       **/
void delete_contact(AddressBook *addressBook)
{
    int op;
    printf("\n=============================================================\n");
    printf("                        DELETE CONTACT      \n");
    printf("=============================================================\n");
    printf("DELETE BY : \n");
    printf(" 1. Name\n");
    printf(" 2. Phone\n");
    printf(" 3. Mail\n");
    printf("Enter choice: "); // Ask user to select delete by name phone or mail
    scanf("%d", &op);
    int index;
    switch (op)
    {
    case 1:
        index = search_byName(addressBook); // Delete by Name
        break;

    case 2:
        index = search_byPhone(addressBook); // Delete by Phone

        break;

    case 3:
        index = search_byMail(addressBook); // Delete By Mail
        break;
    default:
        printf("Invalid Choice!\n");
        break;
    }
    if (index != -1)
    {
        char ch;
        printf("To Delete the Contact Press (y/Y) and (n/N)for not to delete  :"); // For conformation ask user to y/Y to delete and n/N to not delete
        scanf(" %c", &ch);
        // logic to delete the conntacts
        if (ch == 'y' || ch == 'Y') // If user entered y/Y Delete the contact
        {

            for (int j = index; j < addressBook->contact_count - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }

            printf("Contact Deleted Successfully\n");
            addressBook->contact_count--; // After delete decrement the count by 1
            return;
        }
        else if (ch == 'n' || ch == 'N') // If User entered n/N do not delete
        {
            printf("Contact Not Deleted");
            return;
        }
        else
        {
            printf("Invalid Input!"); // if user entered invalid input other than y/Y/n/N
            return;
        }
    }
}
