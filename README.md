# 📒 Address Book Management System

A console-based **Address Book Management System developed in C** to efficiently manage contact information such as name, phone number, and email address.

## 🚀 Features

- ➕ Add Contact
- 🔍 Search Contact
- ✏️ Edit Contact
- 🗑️ Delete Contact
- 📋 Display All Contacts
- 💾 Save Contacts
- 📂 Load Existing Contacts
- ✅ Input Validation
- ⚠️ Duplicate Contact Checking
- 🖥️ Menu-Driven Interface

## 🖥️ Sample Output

```text
========== Address Book Menu ==========

1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List Contacts
6. Save And Exit

Enter your choice: 1

Enter the name: Deepak
Enter the phone number: 9876543210
Enter the email address: deepak@gmail.com

Contact added successfully!

🔍 Search Contact
Enter the name to search: Deepak


Contact Found!


Name  : Deepak
Phone : 9876543210
Email : deepak@gmail.com
✏️ Edit Contact
Enter the contact name to edit: Deepak


Contact Found.


Enter new phone number: 9876543211
Enter new email address: deepak123@gmail.com


Contact updated successfully!
🗑️ Delete Contact
Enter the contact name to delete: Deepak


Contact Found.
Are you sure you want to delete this contact? Y


Contact deleted successfully!
📋 List Contacts
============= Contact List =============


Name        Phone Number      Email
----------------------------------------------
Deepak      9876543210        deepak@gmail.com
Rahul       9876543212        rahul@gmail.com
Amit        9876543213        amit@gmail.com


===========================================
❌ Contact Not Found
Enter the name to search: Raj


Contact not found.
⚠️ Duplicate Contact
Enter phone number: 9876543210


Error: Phone number already exists!
Please enter a different phone number.
💾 Save and Exit
Saving contacts...


Contacts saved successfully!


Thank you for using Address Book Management System.
📂 Project Structure
AddressBook/
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── contacts.txt
├── contact.csv
├── makefile
└── README.md
