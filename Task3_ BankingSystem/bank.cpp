#include <iostream>
#include <string>
#include <vector>
using namespace std;

// A record of money movement (a deposit, withdrawal or transfer)
class Transaction
{
public:
    string type;
    double amount;
};

// A bank account: it holds a balance and remembers every transaction
class Account
{
public:
    string accountNumber;
    double balance;
    vector<Transaction> history; // list of all transactions on this account

    // Add money to the account and record it in the history
    void deposit(double amount)
    {
        balance += amount;

        Transaction t;
        t.type = "Deposit";
        t.amount = amount;
        history.push_back(t);

        cout << "Deposited " << amount << ". New balance: " << balance << endl;
    }

    // Take money out, but only if the balance can cover it
    void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient funds. Balance: " << balance << endl;
        }
        else
        {
            balance -= amount;

            Transaction t;
            t.type = "Withdrawal";
            t.amount = amount;
            history.push_back(t);

            cout << "Withdrew " << amount << ". New balance: " << balance << endl;
        }
    }

    // Send money to another account (&to means we change the real account, not a copy)
    void transfer(Account &to, double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient funds. Balance: " << balance << endl;
        }
        else
        {
            // move the money from this account to the other one
            balance -= amount;
            to.balance += amount;

            // record the transfer in this account's history
            Transaction out;
            out.type = "Transfer to " + to.accountNumber;
            out.amount = amount;
            history.push_back(out);

            // record the same transfer in the receiving account's history
            Transaction in;
            in.type = "Transfer from " + accountNumber;
            in.amount = amount;
            to.history.push_back(in);

            cout << "Transferred " << amount << " to account " << to.accountNumber << "." << endl;
        }
    }

    // Print the account number and its current balance
    void showBalance()
    {
        cout << "Account " << accountNumber << ". balance: " << balance << endl;
    }

    // Print every transaction in order, with the balance as the last line
    void showHistory()
    {
        cout << "Transactions for account " << accountNumber << ":" << endl;
        for (size_t i = 0; i < history.size(); i++)
        {
            cout << i + 1 << ". " << history[i].type << ": " << history[i].amount << endl;
        }
        cout << history.size() + 1 << ". Balance: " << balance << endl;
    }
};

// A bank customer: a name and the account they own
class Customer
{
public:
    string name;
    Account account;

    // Print the customer's name and their account balance
    void showInfo()
    {
        cout << "Customer: " << name << endl;
        account.showBalance();
    }
};

// Look through the customers for an account number.
// Gives back the customer's position in the list, or -1 if nobody has it.
int findCustomer(vector<Customer> &list, string accountNumber)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        if (list[i].account.accountNumber == accountNumber)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    vector<Customer> customers; // every customer created while the program runs
    int choice;

    // keep showing the menu until the user chooses Exit
    do
    {
        cout << endl;
        cout << "1. Create customer and account" << endl;
        cout << "2. Show all customers" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Withdraw" << endl;
        cout << "5. Transfer" << endl;
        cout << "6. Transaction history" << endl;
        cout << "7. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        // if a letter was typed instead of a number, clear the error and ask again
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }

        // Option 1: create a new customer with an account
        if (choice == 1)
        {
            Customer c;
            cout << "Enter customer name: ";
            cin >> c.name;
            cout << "Enter account number: ";
            cin >> c.account.accountNumber;

            // refuse if the account number is already in use
            if (findCustomer(customers, c.account.accountNumber) != -1)
            {
                cout << "That account number already exists." << endl;
            }
            else
            {
                c.account.balance = 0; // new accounts start empty
                customers.push_back(c);
                cout << "Customer created." << endl;
            }
        }
        // Option 2: list every customer and their balance
        else if (choice == 2)
        {
            if (customers.empty())
            {
                cout << "No customers yet." << endl;
            }
            else
            {
                for (size_t i = 0; i < customers.size(); i++)
                {
                    customers[i].showInfo();
                }
            }
        }
        // Option 3: deposit money into an account
        else if (choice == 3)
        {
            string number;
            double amount;
            cout << "Enter account number: ";
            cin >> number;
            int index = findCustomer(customers, number);
            if (index == -1)
            {
                cout << "Account not found." << endl;
            }
            else
            {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                // refuse any deposit that is less than or equal to zero(0)
                if (amount <= 0)
                {
                    cout << "Amount must be more than zero(0)." << endl;
                }
                else
                {
                    customers[index].account.deposit(amount);
                }
            }
        }
        // Option 4: withdraw money from an account
        else if (choice == 4)
        {
            string number;
            double amount;
            cout << "Enter account number: ";
            cin >> number;
            int index = findCustomer(customers, number);
            if (index == -1)
            {
                cout << "Account not found." << endl;
            }
            else
            {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                if (amount <= 0)
                {
                    cout << "Amount must be more than zero(0)." << endl;
                }
                else
                {
                    customers[index].account.withdraw(amount);
                }
            }
        }
        // Option 5: transfer money from one account to another
        else if (choice == 5)
        {
            string fromNumber, toNumber;
            double amount;
            cout << "Enter your account number: ";
            cin >> fromNumber;
            cout << "Enter the account number to send to: ";
            cin >> toNumber;

            // find both customers in the list
            int fromIndex = findCustomer(customers, fromNumber);
            int toIndex = findCustomer(customers, toNumber);

            if (fromIndex == -1 || toIndex == -1)
            {
                cout << "Account not found." << endl;
            }
            else if (fromIndex == toIndex)
            {
                cout << "You can't transfer to the same account." << endl;
            }
            else
            {
                cout << "Enter amount to transfer: ";
                cin >> amount;
                if (amount <= 0)
                {
                    cout << "Amount must be more than zero(0)." << endl;
                }
                else
                {
                    customers[fromIndex].account.transfer(customers[toIndex].account, amount);
                }
            }
        }
        // Option 6: show all transactions for one account
        else if (choice == 6)
        {
            string number;
            cout << "Enter account number: ";
            cin >> number;
            int index = findCustomer(customers, number);

            if (index == -1)
            {
                cout << "Account not found." << endl;
            }
            else
            {
                customers[index].account.showHistory();
            }
        }
        // Option 7: leave the program
        else if (choice == 7)
        {
            cout << "Goodbye!" << endl;
        }
        // anything else is not on the menu
        else
        {
            cout << "Invalid option." << endl;
        }

    } while (choice != 7);

    return 0;
}