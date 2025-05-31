#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "accounts.dat"

struct clientData {
    int acctNum;
    char lastName[15];
    char firstName[10];
    float balance;
    int pin;
    char recoveryCode[20];
};

// Function prototypes
void createAccount();
void updateAccountInfo();
void deleteAccount();
void displayAccounts();
void deposit();
void withdraw();
void checkBalance();
void changePIN();
int menu();

int main() {
    int choice;

    while ((choice = menu()) != 9) {
        switch (choice) {
            case 1: createAccount(); break;
            case 2: updateAccountInfo(); break;
            case 3: deleteAccount(); break;
            case 4: displayAccounts(); break;
            case 5: deposit(); break;
            case 6: withdraw(); break;
            case 7: checkBalance(); break;
            case 8: changePIN(); break;
            default: printf("Invalid choice.\n");
        }
    }

    printf("Program exited.\n");
    return 0;
}

int menu() {
    int ch;
    printf("\nBANK ACCOUNT MENU:\n");
    printf("1. Create new account\n");
    printf("2. Update client information (name)\n");
    printf("3. Delete an account\n");
    printf("4. Display all accounts\n");
    printf("5. Deposit\n");
    printf("6. Withdraw\n");
    printf("7. Check balance\n");
    printf("8. Change PIN\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);
    getchar(); // consume newline
    return ch;
}

void createAccount() {
    struct clientData client;
    FILE *fp = fopen(FILENAME, "ab");
    if (!fp) {
        perror("File error");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &client.acctNum);
    printf("Enter last name: ");
    scanf("%14s", client.lastName);
    printf("Enter first name: ");
    scanf("%9s", client.firstName);
    printf("Enter initial balance: ");
    scanf("%f", &client.balance);
    printf("Set a 4-digit PIN: ");
    scanf("%d", &client.pin);
    printf("Set a recovery code (no spaces): ");
    scanf("%19s", client.recoveryCode);
    getchar(); // consume newline

    fwrite(&client, sizeof(struct clientData), 1, fp);
    fclose(fp);
    printf("Account created successfully.\n");
}

void updateAccountInfo() {
    int acct, found = 0;
    struct clientData client;

    printf("Enter account number to update info: ");
    scanf("%d", &acct);
    getchar();

    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) {
        perror("File error");
        return;
    }

    while (fread(&client, sizeof(client), 1, fp)) {
        if (client.acctNum == acct) {
            found = 1;
            printf("Current Last Name: %s\n", client.lastName);
            printf("Enter new last name: ");
            scanf("%14s", client.lastName);
            printf("Current First Name: %s\n", client.firstName);
            printf("Enter new first name: ");
            scanf("%9s", client.firstName);
            getchar();

            fseek(fp, -(long)sizeof(client), SEEK_CUR);
            fwrite(&client, sizeof(client), 1, fp);
            printf("Client information updated successfully.\n");
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}

void deleteAccount() {
    int acct;
    struct clientData client;
    FILE *fp = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int found = 0;

    if (!fp || !temp) {
        perror("File error");
        return;
    }

    printf("Enter account number to delete: ");
    scanf("%d", &acct);
    getchar();

    while (fread(&client, sizeof(client), 1, fp)) {
        if (client.acctNum != acct) {
            fwrite(&client, sizeof(client), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found)
        printf("Account deleted successfully.\n");
    else
        printf("Account not found.\n");
}

void displayAccounts() {
    struct clientData client;
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    printf("\n%-10s %-15s %-15s %-10s\n", "Account", "Last Name", "First Name", "Balance");
    printf("-----------------------------------------------------\n");

    while (fread(&client, sizeof(client), 1, fp)) {
        printf("%-10d %-15s %-15s %-10.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
    }

    fclose(fp);
}

void deposit() {
    int acct, found = 0;
    float amount;
    struct clientData client;
    char input[50];

    printf("Enter account number to deposit: ");
    scanf("%d", &acct);
    getchar();

    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) {
        perror("File error");
        return;
    }

    while (fread(&client, sizeof(client), 1, fp)) {
        if (client.acctNum == acct) {
            found = 1;
            printf("Enter amount to deposit: ");
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%f", &amount) != 1 || amount <= 0) {
                printf("Invalid amount. Deposit must be positive.\n");
                fclose(fp);
                return;
            }
            client.balance += amount;
            fseek(fp, -(long)sizeof(client), SEEK_CUR);
            fwrite(&client, sizeof(client), 1, fp);
            printf("Deposit successful. New balance: %.2f\n", client.balance);
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}

void withdraw() {
    int acct, found = 0;
    float amount;
    struct clientData client;
    char input[50];

    printf("Enter account number to withdraw from: ");
    scanf("%d", &acct);
    getchar();

    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) {
        perror("File error");
        return;
    }

    while (fread(&client, sizeof(client), 1, fp)) {
        if (client.acctNum == acct) {
            found = 1;
            printf("Enter amount to withdraw: ");
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%f", &amount) != 1 || amount <= 0) {
                printf("Invalid amount. Withdrawal must be positive.\n");
                fclose(fp);
                return;
            }
            if (client.balance < amount) {
                printf("Insufficient balance. Withdrawal failed.\n");
                fclose(fp);
                return;
            }
            client.balance -= amount;
            fseek(fp, -(long)sizeof(client), SEEK_CUR);
            fwrite(&client, sizeof(client), 1, fp);
            printf("Withdrawal successful. New balance: %.2f\n", client.balance);
            break;
        }
    }

    if (!found)
        printf("Account not found.\n");

    fclose(fp);
}

void checkBalance() {
    int acct, pin, found = 0;
    struct clientData client;

    printf("Enter account number: ");
    scanf("%d", &acct);
    printf("Enter PIN: ");
    scanf("%d", &pin);
    getchar();

    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("File error");
        return;
    }

    while (fread(&client, sizeof(client), 1, fp)) {
        if (client.acctNum == acct && client.pin == pin) {
            printf("Current balance: %.2f\n", client.balance);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found or incorrect PIN.\n");

    fclose(fp);
}

void changePIN() {
    int acct, found = 0;
    char recovery[20];
    struct clientData client;

    printf("Enter account number: ");
    scanf("%d", &acct);
    printf("Enter recovery code: ");
    scanf("%19s", recovery);
    getchar();

    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) {
        perror("File error");
        return;
    }

    while (fread(&client, sizeof(client), 1, fp)) {
        if (client.acctNum == acct && strcmp(client.recoveryCode, recovery) == 0) {
            printf("Enter new 4-digit PIN: ");
            scanf("%d", &client.pin);
            fseek(fp, -(long)sizeof(client), SEEK_CUR);
            fwrite(&client, sizeof(client), 1, fp);
            printf("PIN changed successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Invalid account number or recovery code.\n");

    fclose(fp);
}
