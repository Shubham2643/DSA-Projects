#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Base Class: BankAccount
class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

protected:
    void setBalance(double newBalance) {
        balance = newBalance;
    }

public:
    BankAccount(string accNo, string holderName, double initialBalance = 0.0) 
        : accountNumber(accNo), accountHolderName(holderName), balance(initialBalance) {}

    // Encapsulation: Public methods to access private attributes
    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    
    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << fixed << setprecision(2) << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << fixed << setprecision(2) << amount << endl;
        } else {
            cout << "Insufficient balance or invalid amount!" << endl;
        }
    }

    double getBalance() const { return balance; }

    virtual void displayAccountInfo() const {
        cout << "\n=== Account Information ===" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    virtual void calculateInterest() const {
        cout << "Base account has no interest calculation." << endl;
    }

    virtual ~BankAccount() {}
};

// Derived Class: SavingsAccount
class SavingsAccount : public BankAccount {
private:
    double interestRate; // in percentage

public:
    SavingsAccount(string accNo, string holderName, double initialBalance, double rate)
        : BankAccount(accNo, holderName, initialBalance), interestRate(rate) {}

    void calculateInterest() const override {
        double interest = getBalance() * (interestRate / 100);
        cout << "Savings Account Interest: $" << fixed << setprecision(2) << interest 
             << " (Rate: " << interestRate << "%)" << endl;
    }

    void deposit(double amount) override {
        BankAccount::deposit(amount);
        cout << "Note: Interest will be calculated on this deposit." << endl;
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Savings Account" << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

// Derived Class: CheckingAccount
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNo, string holderName, double initialBalance, double overdraft)
        : BankAccount(accNo, holderName, initialBalance), overdraftLimit(overdraft) {}

    bool checkOverdraft(double amount) const {
        return amount <= (getBalance() + overdraftLimit);
    }

    void withdraw(double amount) override {
        if (amount > 0 && checkOverdraft(amount)) {
            double newBalance = getBalance() - amount;
            if (newBalance < 0) {
                cout << "Warning: Overdraft used! Amount: $" << fixed << setprecision(2) << -newBalance << " overdrawn." << endl;
            }
            // Use protected setBalance method from base class
            setBalance(newBalance);
            cout << "Withdrawn: $" << fixed << setprecision(2) << amount << endl;
        } else {
            cout << "Withdrawal denied! Exceeds overdraft limit or invalid amount." << endl;
        }
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Checking Account" << endl;
        cout << "Overdraft Limit: $" << fixed << setprecision(2) << overdraftLimit << endl;
        cout << "Available with Overdraft: $" << fixed << setprecision(2) << (getBalance() + overdraftLimit) << endl;
    }

    void calculateInterest() const override {
        cout << "Checking accounts do not earn interest." << endl;
    }
};

// Derived Class: FixedDepositAccount
class FixedDepositAccount : public BankAccount {
private:
    int term; // duration in months
    double fixedInterestRate; // Fixed deposit interest rate

public:
    FixedDepositAccount(string accNo, string holderName, double initialBalance, int termMonths, double rate)
        : BankAccount(accNo, holderName, initialBalance), term(termMonths), fixedInterestRate(rate) {}

    void calculateInterest() const override {
        double interest = getBalance() * (fixedInterestRate / 100) * (term / 12.0);
        cout << "Fixed Deposit Interest: $" << fixed << setprecision(2) << interest 
             << " (Rate: " << fixedInterestRate << "%, Term: " << term << " months)" << endl;
    }

    void withdraw(double amount) override {
        cout << "Early withdrawal from Fixed Deposit may incur penalties!" << endl;
        char choice;
        cout << "Are you sure you want to withdraw? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            double penalty = amount * 0.05; // 5% penalty for early withdrawal
            if (amount + penalty <= getBalance()) {
                setBalance(getBalance() - amount - penalty);
                cout << "Withdrawn: $" << fixed << setprecision(2) << amount << endl;
                cout << "Penalty applied: $" << fixed << setprecision(2) << penalty << endl;
            } else {
                cout << "Insufficient balance including penalty!" << endl;
            }
        } else {
            cout << "Withdrawal cancelled." << endl;
        }
    }

    void displayAccountInfo() const override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Fixed Deposit Account" << endl;
        cout << "Term: " << term << " months" << endl;
        cout << "Fixed Interest Rate: " << fixedInterestRate << "%" << endl;
    }
};

// Function to demonstrate polymorphism
void demonstratePolymorphism(vector<unique_ptr<BankAccount>>& accounts) {
    cout << "\n=== Demonstrating Polymorphism ===" << endl;
    for (auto& account : accounts) {
        account->calculateInterest();
    }
}

// Menu-driven interface
void displayMenu() {
    cout << "\n===== BANKING SYSTEM MENU =====" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Display Account Information" << endl;
    cout << "6. Calculate Interest (Polymorphism Demo)" << endl;
    cout << "7. List All Accounts" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

void createAccount(vector<unique_ptr<BankAccount>>& accounts) {
    cout << "\n--- Create New Account ---" << endl;
    cout << "Select Account Type:" << endl;
    cout << "1. Savings Account" << endl;
    cout << "2. Checking Account" << endl;
    cout << "3. Fixed Deposit Account" << endl;
    cout << "Enter choice: ";
    
    int type;
    cin >> type;
    
    string accNo, holderName;
    double initialBalance;
    
    cout << "Enter Account Number: ";
    cin >> accNo;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, holderName);
    cout << "Enter Initial Balance: $";
    cin >> initialBalance;
    
    if (type == 1) {
        double rate;
        cout << "Enter Interest Rate (%): ";
        cin >> rate;
        accounts.push_back(make_unique<SavingsAccount>(accNo, holderName, initialBalance, rate));
        cout << "Savings Account created successfully!" << endl;
    } else if (type == 2) {
        double overdraft;
        cout << "Enter Overdraft Limit: $";
        cin >> overdraft;
        accounts.push_back(make_unique<CheckingAccount>(accNo, holderName, initialBalance, overdraft));
        cout << "Checking Account created successfully!" << endl;
    } else if (type == 3) {
        int term;
        double rate;
        cout << "Enter Term (in months): ";
        cin >> term;
        cout << "Enter Fixed Interest Rate (%): ";
        cin >> rate;
        accounts.push_back(make_unique<FixedDepositAccount>(accNo, holderName, initialBalance, term, rate));
        cout << "Fixed Deposit Account created successfully!" << endl;
    } else {
        cout << "Invalid account type!" << endl;
    }
}

BankAccount* findAccount(vector<unique_ptr<BankAccount>>& accounts, const string& accNo) {
    for (auto& account : accounts) {
        if (account->getAccountNumber() == accNo) {
            return account.get();
        }
    }
    return nullptr;
}

int main() {
    vector<unique_ptr<BankAccount>> accounts;
    int choice;
    
    cout << "Welcome to the Banking System!" << endl;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                createAccount(accounts);
                break;
                
            case 2: {
                string accNo;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNo;
                BankAccount* account = findAccount(accounts, accNo);
                if (account) {
                    cout << "Enter amount to deposit: $";
                    cin >> amount;
                    account->deposit(amount);
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }
            
            case 3: {
                string accNo;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNo;
                BankAccount* account = findAccount(accounts, accNo);
                if (account) {
                    cout << "Enter amount to withdraw: $";
                    cin >> amount;
                    account->withdraw(amount);
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }
            
            case 4: {
                string accNo;
                cout << "Enter Account Number: ";
                cin >> accNo;
                BankAccount* account = findAccount(accounts, accNo);
                if (account) {
                    cout << "Current Balance: $" << fixed << setprecision(2) << account->getBalance() << endl;
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }
            
            case 5: {
                string accNo;
                cout << "Enter Account Number: ";
                cin >> accNo;
                BankAccount* account = findAccount(accounts, accNo);
                if (account) {
                    account->displayAccountInfo();
                } else {
                    cout << "Account not found!" << endl;
                }
                break;
            }
            
            case 6:
                if (accounts.empty()) {
                    cout << "No accounts to demonstrate polymorphism. Please create an account first." << endl;
                } else {
                    demonstratePolymorphism(accounts);
                }
                break;
                
            case 7:
                if (accounts.empty()) {
                    cout << "No accounts in the system." << endl;
                } else {
                    cout << "\n=== All Accounts ===" << endl;
                    for (size_t i = 0; i < accounts.size(); i++) {
                        cout << "\nAccount " << (i + 1) << ":";
                        accounts[i]->displayAccountInfo();
                    }
                }
                break;
                
            case 8:
                cout << "Thank you for using the Banking System. Goodbye!" << endl;
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);
    
    return 0;
}