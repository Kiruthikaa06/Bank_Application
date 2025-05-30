# Bank Account Management System

## 📌 Overview

This is a simple **Bank Account Management System** written in **C**. It allows users to:
- Create new bank accounts
- Update existing accounts (deposit or withdraw)
- Delete accounts
- Display all stored accounts

All account data is stored persistently in a plain text file named `accounts.txt`.

---

## 💡 Features

- ✅ Create a new bank account  
- ✏️ Update an existing account (deposit/withdraw)  
- ❌ Delete an account  
- 📄 Display all accounts  
- 💾 Data is saved to `accounts.txt`

---

## 🗂️ File Format

Each account is stored in a line of the `accounts.txt` file in the format:


**Example:**
101 Smith John 2500.75
102 Doe Jane 1200.50


Each line represents one client account.

---

## 📋 Menu Options

When the program runs, it displays the following menu:

Create new account

Update existing account

Delete an account

Display all accounts

Exit


---

## 🛠️ Function Descriptions

### 1. `createAccount()`
- Prompts the user to input:
  - Account Number
  - Last Name
  - First Name
  - Initial Balance
- Appends the new account to `accounts.txt`.

---

### 2. `updateAccount()`
- Asks the user for the account number to update.
- If found:
  - Displays the current balance.
  - Prompts for a deposit or withdrawal amount.
  - Updates the balance.
- Writes changes to a temporary file, then replaces the original file.

---

### 3. `deleteAccount()`
- Asks for the account number to delete.
- If found:
  - Removes that record from the file.
- Uses a temporary file to safely modify records.

---

### 4. `displayAccounts()`
- Opens `accounts.txt` and displays all stored accounts in a tabular format:
  - Account Number
  - Last Name
  - First Name
  - Balance

---

## 💾 File Handling

The program uses standard file I/O operations in C:
- `fopen()`, `fscanf()`, `fprintf()`, `fclose()` for reading/writing
- `remove()` and `rename()` for safe updates and deletions using a temporary file
- Appends new data and safely rewrites existing data as needed

---

## 🧪 Compilation & Execution

To compile the program:

```bash
gcc -o bank bank.c

⚠️ Limitations
❌ No check for duplicate account numbers

❌ No authentication or login system

⚠️ Floating-point precision may affect balance accuracy

⚠️ Not suitable for large datasets or concurrent use

🚀 Suggested Improvements
✅ Add duplicate account number check before creation

🔐 Implement a basic login system or PIN verification

📁 Use binary files for more efficient and reliable storage

📊 Add sorting or filtering features in the display menu

🧪 Improve user input validation and error handling

💰 Store balance in integer cents for precision

🧑‍💻 Author
Developed as a learning project to demonstrate:

File handling in C

Use of structs

Menu-driven programs

Simple data persistence

📄 License
This project is open-source and free to use for educational or learning purposes.


