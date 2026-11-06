#include <stdio.h>
// Function prototypes
float loadBalance(void);
int saveBalance(float balance);
void checkBalance(float balance);
void deposit(float *balance);
void withdraw(float *balance);
void transactionHistory(void);

int main(void)
{
    float balance;
    int choice;

    balance = loadBalance();

    do
    {
        printf("\n========== MINI BANKING SYSTEM ==========\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transaction History\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

            continue;
        }

        switch (choice)
        {
            case 1:
                checkBalance(balance);
                break;

            case 2:
                deposit(&balance);
                break;

            case 3:
                withdraw(&balance);
                break;

            case 4:
                transactionHistory();
                break;

            case 5:
                printf("\nThank you for using our banking system!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 5);

    return 0;
}

// Load balance from file
float loadBalance(void)
{
    float balance;
    FILE *fp;

    fp = fopen("balance.txt", "r");

    if (fp == NULL)
    {
        balance = 10000;

        if (saveBalance(balance) == 0)
            printf("Warning: Could not create balance file!\n");

        return balance;
    }

    if (fscanf(fp, "%f", &balance) != 1 || balance < 0)
    {
        printf("Invalid balance file! Starting with Rs. 10000.\n");
        balance = 10000;
    }

    fclose(fp);

    return balance;
}

// Save updated balance
int saveBalance(float balance)
{
    FILE *fp;

    fp = fopen("balance.txt", "w");

    if (fp == NULL)
        return 0;

    if (fprintf(fp, "%.2f", balance) < 0)
    {
        fclose(fp);
        return 0;
    }

    if (fclose(fp) != 0)
        return 0;

    return 1;
}

// Display balance
void checkBalance(float balance)
{
    printf("\nCurrent Balance: Rs. %.2f\n", balance);
}

// Deposit money
void deposit(float *balance)
{
    float amount;
    FILE *fp;

    printf("\nEnter amount to deposit: ");

    if (scanf("%f", &amount) != 1)
    {
        printf("Invalid input!\n");

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        return;
    }

    if (amount <= 0)
    {
        printf("Please enter a valid amount!\n");
        return;
    }

    *balance += amount;

    if (saveBalance(*balance) == 0)
    {
        *balance -= amount;
        printf("Deposit failed! Could not save balance.\n");
        return;
    }

    fp = fopen("transactions.txt", "a");

    if (fp == NULL)
    {
        *balance -= amount;
        saveBalance(*balance);

        printf("Deposit failed! Could not save transaction history.\n");
        return;
    }

    if (fprintf(fp, "Deposit: Rs. %.2f\n", amount) < 0 ||
        fclose(fp) != 0)
    {
        printf("Warning: Transaction history could not be saved completely.\n");
        return;
    }

    printf("\nDeposit successful!\n");
    printf("Updated Balance: Rs. %.2f\n", *balance);
}

// Withdraw money
void withdraw(float *balance)
{
    float amount;
    FILE *fp;

    printf("\nEnter amount to withdraw: ");

    if (scanf("%f", &amount) != 1)
    {
        printf("Invalid input!\n");

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        return;
    }

    if (amount <= 0)
    {
        printf("Please enter a valid amount!\n");
        return;
    }

    if (amount > *balance)
    {
        printf("Insufficient balance!\n");
        return;
    }

    *balance -= amount;

    if (saveBalance(*balance) == 0)
    {
        *balance += amount;
        printf("Withdrawal failed! Could not save balance.\n");
        return;
    }

    fp = fopen("transactions.txt", "a");

    if (fp == NULL)
    {
        *balance += amount;
        saveBalance(*balance);

        printf("Withdrawal failed! Could not save transaction history.\n");
        return;
    }

    if (fprintf(fp, "Withdrawal: Rs. %.2f\n", amount) < 0 ||
        fclose(fp) != 0)
    {
        printf("Warning: Transaction history could not be saved completely.\n");
        return;
    }

    printf("\nWithdrawal successful!\n");
    printf("Updated Balance: Rs. %.2f\n", *balance);
}

// Display permanent transaction history
void transactionHistory(void)
{
    char line[100];
    FILE *fp;

    fp = fopen("transactions.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo transaction history found!\n");
        return;
    }

    printf("\n========== TRANSACTION HISTORY ==========\n");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp);
}
