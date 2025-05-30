#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct clientData {
    int acctNum;
    char lastName[15];
    char firstName[10];
    float balance;
};

// Function prototypes
void createAccount();
void updateAccount();
void deleteAccount();
void displayAccounts();
int menu();

int main() {
    int choice;

    while ((choice = menu()) != 5) {
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                updateAccount();
                break;
            case 3:
                deleteAccount();
                break;
            case 4:
                displayAccounts();
                break;
            default:
                printf("Invalid choice.\n");
        }
    }

    printf("Program exited.\n");
    return 0;
}

int menu() {
    int ch;
    printf("\nBANK ACCOUNT MENU:\n");
    printf("1. Create new account\n");
    printf("2. Update existing account\n");
    printf("3. Delete an account\n");
    printf("4. Display all accounts\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);
    return ch;
}

void createAccount() {
    struct clientData client;
    FILE *fp = fopen("accounts.txt", "a");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &client.acctNum);
    printf("Enter last name: ");
    scanf("%s", client.lastName);
    printf("Enter first name: ");
    scanf("%s", client.firstName);
    printf("Enter balance: ");
    scanf("%f", &client.balance);

    fprintf(fp, "%d %s %s %.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
    fclose(fp);
    printf("Account created successfully.\n");
}

void updateAccount() {
    int acct, found = 0;
    struct clientData client;
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        perror("File error");
        return;
    }

    printf("Enter account number to update: ");
    scanf("%d", &acct);

    while (fscanf(fp, "%d %s %s %f", &client.acctNum, client.lastName, client.firstName, &client.balance) == 4) {
        if (client.acctNum == acct) {
            found = 1;
            printf("Current balance: %.2f\n", client.balance);
            float transaction;
            printf("Enter transaction amount (positive for deposit, negative for withdrawal): ");
            scanf("%f", &transaction);
            client.balance += transaction;
            printf("New balance: %.2f\n", client.balance);
        }
        fprintf(temp, "%d %s %s %.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
    }

    fclose(fp);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        printf("Account updated successfully.\n");
    else
        printf("Account not found.\n");
}

void deleteAccount() {
    int acct, found = 0;
    struct clientData client;
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        perror("File error");
        return;
    }

    printf("Enter account number to delete: ");
    scanf("%d", &acct);

    while (fscanf(fp, "%d %s %s %f", &client.acctNum, client.lastName, client.firstName, &client.balance) == 4) {
        if (client.acctNum == acct) {
            found = 1;
            continue;  // skip writing this record
        }
        fprintf(temp, "%d %s %s %.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
    }

    fclose(fp);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        printf("Account deleted successfully.\n");
    else
        printf("Account not found.\n");
}

void displayAccounts() {
    struct clientData client;
    FILE *fp = fopen("accounts.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\n%-10s%-15s%-15s%-10s\n", "Account", "Last Name", "First Name", "Balance");
    printf("-----------------------------------------------------\n");

    while (fscanf(fp, "%d %s %s %f", &client.acctNum, client.lastName, client.firstName, &client.balance) == 4) {
        printf("%-10d%-15s%-15s%-10.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
    }

    fclose(fp);
}
