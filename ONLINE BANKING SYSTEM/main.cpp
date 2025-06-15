#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;
    vector<string> transactions;

public:
    BankAccount() : accountNumber(""), balance(0.0) {}

    BankAccount(string accNumber, double initialBalance) {
        accountNumber = accNumber;
        balance = initialBalance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back("Deposit: " + to_string(amount));
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.push_back("Withdrawal: " + to_string(amount));
            return true;
        }
        return false;
    }

    double getBalance() const {
        return balance;
    }

    void printTransactions() const {
        cout << "Transaction History:" << endl;
        for (const auto& transaction : transactions) {
            cout << transaction << endl;
        }
        cout << "Current Balance: " << balance << endl;
    }
};

bool authenticateUser(const string& username, const string& password, const vector<pair<string, string>>& credentials) {
    for (const auto& user : credentials) {
        if (user.first == username && user.second == password) {
            return true;
        }
    }
    return false;
}

void createUserAccount(vector<BankAccount*>& userAccounts, vector<pair<string, string>>& userCredentials) {
    string username, password, sacno;
    double opening_balance;

    cout << "Create an account:" << endl;
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    userCredentials.push_back({ username, password });

    cout << "Account number: "; cin >> sacno;
    cout << "Opening balance: "; cin >> opening_balance;
    userAccounts.push_back(new BankAccount(sacno, opening_balance));

    cout << "Account created successfully." << endl;
}

void performTransactions(BankAccount* account) {
    double deposit_amt, withdrawal_amt;
    char choice;

    while (true) {
        cout << "Choose transaction:" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdrawal" << endl;
        cout << "3. View Transaction History and Current Balance" << endl;
        cout << "4. Log out" << endl;
        cout << "Enter choice: "; cin >> choice;

        if (choice == '1') {
            cout << "Deposit amount: "; cin >> deposit_amt;
            account->deposit(deposit_amt);
            cout << "Deposit successful. Current balance: " << account->getBalance() << endl;
        }
        else if (choice == '2') {
            cout << "Withdrawal amount: "; cin >> withdrawal_amt;
            if (account->withdraw(withdrawal_amt)) {
                cout << "Withdrawal successful. Current balance: " << account->getBalance() << endl;
            }
            else {
                cout << "Insufficient balance. Cannot withdraw." << endl;
            }
        }
        else if (choice == '3') {
            account->printTransactions();
        }
        else if (choice == '4') {
            cout << "Logging out..." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please enter again." << endl;
        }
    }
}

int main() {
    vector<BankAccount*> userAccounts;
    vector<pair<string, string>> userCredentials;
    string username, password;

    createUserAccount(userAccounts, userCredentials);

    cout << "Enter username: "; cin >> username;
    cout << "Enter password: "; cin >> password;

    if (authenticateUser(username, password, userCredentials)) {
        performTransactions(userAccounts[0]);
    }
    else {
        cout << "Authentication failed. Exiting..." << endl;
    }

    for (BankAccount* account : userAccounts) {
        delete account;
    }

    return 0;
}
