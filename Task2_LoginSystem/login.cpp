#include <iostream>
#include <fstream>
#include <functional> // header for password scrambling
#include <string>

using namespace std;

// function to collect password and give it back as scrambled text
string hashPassword(string pw)
{
    return to_string(hash<string>{}(pw));
}

int main()
{
    int choice;
    do // keep showing the Menu until user chooses Exit.
    {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
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


        if (choice == 1)
        {
            string username, password;
            cout << "Enter a username: ";
            cin >> username;
            cout << "Enter a password: ";
            cin >> password;

            // making sure the USERNAME & PASSWORD are long enough.
            if (username.length() < 3 || password.length() < 4)
            {
                cout << "Username must be at least 3 characters and password at least 4." << endl;
                continue; // skips saviing and returns to the menu.
            }

            ifstream check("users.txt");
            string savedUser, savedPass;
            bool taken = false;

            // looking through the saved users to see if this USERNAME already exists. 
            while (check >> savedUser >> savedPass)
            {
                if (savedUser == username)
                {
                    taken = true;
                }
            }
            check.close();

            if (taken)
            {
                cout << "That username is already taken." << endl;
            }
            else
            {
                ofstream file("users.txt", ios::app);
                file << username << " " << hashPassword(password) << endl;
                file.close();

                cout << "Registration successful!" << endl;
            }
        }

        else if (choice == 2)
        {
            string username, password;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            ifstream file("users.txt");
            string savedUser, savedPass;
            bool found = false;

            // check to confirm if username and password is correct.
            while (file >> savedUser >> savedPass)
            {
                if (savedUser == username && savedPass == hashPassword(password))
                {
                    found = true;
                }
            }
            file.close();

            if (found)
            {
                cout << "Login successful!" << endl;
            }
            else
            {
                cout << "Invalid username or password." << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Goodbye!" << endl;
        }
        else
        {
            cout << "Invalid option." << endl;
        }

    } while (choice != 3);

    return 0;
}