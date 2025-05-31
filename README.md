# 🏦 Bank Account Management System (C Language)

## 📘 Project Description

This **Bank Account Management System** is a console-based application written in the C programming language. It simulates a minimalistic banking environment where a user can:
- Create new bank accounts
- Update balances through deposits or withdrawals
- Delete accounts
- View all existing accounts

All account information is stored persistently in a text file (`accounts.txt`), making the system simple and portable without the need for a database.

---

## 🎯 Objectives

- Demonstrate usage of **file handling** in C
- Work with **structures (`struct`)**
- Practice **modular programming** by dividing logic into functions
- Apply **basic validation and user input handling**
- Understand simple **CRUD** (Create, Read, Update, Delete) operations

---

## 🗂 File Structure

The core file is:

- `bank.c` – Contains the full source code of the application.

When the program runs, it creates and uses:

- `accounts.txt` – The data file storing all account records in plain text.
- `temp.txt` – A temporary file used for safely updating or deleting account records.

---

## 🧰 Features and Functionality

### 1. **Create New Account**
- Prompts user for:
  - Account number
  - Last name
  - First name
  - Initial balance
- Appends the data to `accounts.txt`
- No duplicate check (can be added as an improvement)

### 2. **Update Account**
- Prompts for an account number
- Reads all accounts into a temporary file
- If account exists:
  - Displays current balance
  - Accepts a transaction amount
  - Updates balance accordingly
- Replaces the original file with the updated temporary file

### 3. **Delete Account**
- Prompts for an account number to delete
- Copies all accounts except the matching one into a temporary file
- Replaces `accounts.txt` with the new file (account effectively deleted)

### 4. **Display All Accounts**
- Opens `accounts.txt`
- Displays a formatted table of all accounts showing:
  - Account Number
  - Last Name
  - First Name
  - Balance

### 5. **Exit Program**
- Gracefully exits the application loop.

---

## 💾 File Format (accounts.txt)

Each account is stored on a new line with the following format:

<AccountNumber> <LastName> <FirstName> <Balance>
1001 Smith John 2500.50
1002 Doe Jane 1800.00


---

## 🧪 How to Compile and Run

### 🔧 Prerequisites
- GCC Compiler (or any C compiler)
- Terminal / Command Prompt

### ✅ Compilation

```bash


gcc -o bank bank.c
🧱 Code Architecture
Structure Definition
c
Copy
Edit
struct clientData {
    int acctNum;
    char lastName[15];
    char firstName[10];
    float balance;
};
Main Function Loop
Displays the menu

Executes the appropriate function based on user input

Loops until user selects "Exit"

Core Functions
Function Name	Purpose
createAccount()	Adds a new account to the file
updateAccount()	Modifies balance of an existing account
deleteAccount()	Deletes an account from the file
displayAccounts()	Lists all stored accounts
menu()	Displays menu and returns user choice

⚠️ Limitations
No check for duplicate account numbers on creation

No error recovery if file operations fail midway

No support for concurrent users (single-user, terminal-only)

Floating-point balance may suffer from rounding issues

Minimal input validation (user could crash app with invalid input)

🚀 Suggested Improvements
Feature	Description
Duplicate Check	Prevent creating accounts with existing numbers
Login System	Add basic authentication using PIN or passwords
Binary File Storage	Use .dat binary files for better performance and data accuracy
Currency Handling	Store balance in integer cents to avoid floating-point errors
Sorting and Searching	Add options to sort by name/balance or search accounts by name/number
GUI Interface	Build a front-end using C graphics libraries or migrate to another UI
Unit Testing	Add tests for each function to ensure stability

📸 Sample Output
text
Copy
Edit
BANK ACCOUNT MENU:
1. Create new account
2. Update existing account
3. Delete an account
4. Display all accounts
5. Exit
Enter your choice: 1
Enter account number: 1003
Enter last name: White
Enter first name: Alice
Enter balance: 3050.75
Account created successfully.

🧑‍💻 Author
Developed as a learning project to demonstrate core C programming concepts such as:

File handling

Structs

Modular design

Basic data persistence

📄 License
This project is free and open-source for educational purposes. You may use, modify, and distribute it with proper attribution.


