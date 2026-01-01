#include "login.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// 1. Simple Header Check
void usersheader()
{
    ifstream fCheck("users.csv");
    if(!fCheck) { // If file does not exist
        fCheck.close();
        ofstream fCreate("users.csv");
        fCreate << "username,password,role" << endl; // Create Header
        fCreate.close();
    } else {
        fCheck.close();
    }
}

string login()
{
    usersheader(); // Ensure file exists
    string u, p;
    cout << "Enter username: ";
    cin >> u;
    cout << "Enter password: ";
    cin >> p;

    ifstream f("users.csv");
    string line, dummy;
    
    // Skip the Header line
    getline(f, dummy); 

    while(getline(f, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string user, pass, role;

        // Read up to comma
        getline(ss, user, ',');
        getline(ss, pass, ',');
        
        // CRITICAL FIX: Read the rest of the line for Role (No comma after role)
        getline(ss, role); 

        if(u == user && p == pass)
        {
            // Remove any accidental spaces from role (Optional cleanup)
            if(role == "admin" || role == "Admin") role = "admin";
            if(role == "worker" || role == "Worker") role = "worker";

            writeLog("Login success: " + u);
            writeloginlog(u + " logged in successfully \t Role: " + role);
            return role; // Returns "admin" or "worker"
        }
    }

    writeLog("Login failed: " + u);
    writeloginlog(u + " login failed");
    return ""; // Return empty if not found
}

void signup()
{
    usersheader();
    string u, p, role;
    int roleChoice;
    
    cout << "Enter new username: ";
    cin >> u;

    ifstream f("users.csv");
    string line, dummy;
    
    getline(f, dummy); // Skip Header

    while(getline(f, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string user;
        getline(ss, user, ',');
        if(user == u) {
            cout << "Username already exists.\n";
            return;
        }
    }
    f.close();

    cout << "Enter password: ";
    cin >> p;
    
    cout << "Select Role:\n1. Admin (Manager)\n2. Worker (Staff/Waiter)\nChoose: ";
    cin >> roleChoice;
    
    // Force lowercase to ensure matching works later
    if(roleChoice == 1) role = "admin";
    else role = "worker";

    ofstream out("users.csv", ios::app);
    // Write format: user,pass,role
    out << u << "," << p << "," << role << endl;
    out.close();

    writeLog("Signup: " + u);
    writeloginlog(u + " signed up successfully \t Role: " + role);
    cout << "Signup successful! You are registered as " << role << ".\n";
}

void forgotPassword()
{
    usersheader();
    string u;
    cout << "Enter username: ";
    cin >> u;

    ifstream f("users.csv");
    string line, dummy;
    getline(f, dummy); // Skip Header

    while(getline(f, line))
    {
        if(line.empty()) continue;
        stringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
        getline(ss, pass, ',');

        if(user == u) {
            cout << "Your password is: " << pass << endl;
            return;
        }
    }
    cout << "Username not found.\n";
}