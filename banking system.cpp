#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
public:
    int accountNumber;
    string name;
    double balance;

    void createAccount() {
        cout << "\n===== Create New Account =====\n";
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Deposit Amount: ";
        cin >> balance;
        cout << "\nAccount created successfully!\n";
    }

    void showAccount() {
        cout << "------------------------------------\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder: " << name << "\n";
        cout << "Balance: $" << balance << "\n";
        cout << "------------------------------------\n";
    }

    void deposit() {
        double amount;
        cout << "\nEnter amount to deposit: ";
        cin >> amount;
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully.\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw() {
        double amount;
        cout << "\nEnter amount to withdraw: ";
        cin >> amount;
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        } else {
            cout << "Invalid or insufficient balance!\n";
        }
    }
};

// Function prototypes
void writeAccount();
void displayAccount(int);
void depositWithdraw(int, int);

int main() {
    int choice, accNo;

    cout << "====================================\n";
    cout << "        Welcome to Banking System    \n";
    cout << "           Made By: Mishal Zahara    \n";
    cout << "====================================\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Create New Account\n";
        cout << "2. Display Account Details\n";
        cout << "3. Deposit Amount\n";
        cout << "4. Withdraw Amount\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            writeAccount();
            break;
        case 2:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            displayAccount(accNo);
            break;
        case 3:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            depositWithdraw(accNo, 1);
            break;
        case 4:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            depositWithdraw(accNo, 2);
            break;
        case 5:
            cout << "\nThank you for using the banking system. Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

        if (choice != 5) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 5);

    return 0;
}

void writeAccount() {
    BankAccount acc;
    acc.createAccount();

    ofstream outFile("accounts.txt", ios::app);
    outFile << acc.accountNumber << "\n" << acc.name << "\n" << acc.balance << "\n";
    outFile.close();
}

void displayAccount(int accNo) {
    ifstream inFile("accounts.txt");
    bool found = false;
    BankAccount acc;

    while (inFile >> acc.accountNumber) {
        inFile.ignore();
        getline(inFile, acc.name);
        inFile >> acc.balance;

        if (acc.accountNumber == accNo) {
            cout << "\nAccount Details:\n";
            acc.showAccount();
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found)
        cout << "\nAccount not found.\n";
}

void depositWithdraw(int accNo, int option) {
    ifstream inFile("accounts.txt");
    ofstream tempFile("temp.txt");
    bool found = false;
    BankAccount acc;

    while (inFile >> acc.accountNumber) {
        inFile.ignore();
        getline(inFile, acc.name);
        inFile >> acc.balance;

        if (acc.accountNumber == accNo) {
            found = true;
            if (option == 1) {
                acc.deposit();
            } else if (option == 2) {
                acc.withdraw();
            }
        }
        tempFile << acc.accountNumber << "\n" << acc.name << "\n" << acc.balance << "\n";
    }

    inFile.close();
    tempFile.close();

    if (!found) {
        cout << "\nAccount not found.\n";
        remove("temp.txt");
        return;
    }

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}
