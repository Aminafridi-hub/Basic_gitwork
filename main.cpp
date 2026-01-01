#include <iostream>
#include <cstdlib> 

#include "login.h"
#include "menu.h"
#include "dine_in_order.h"
#include "billing.h"
#include "tables.h" 
#include "online_order.h"
// online_orders included only for admin if needed, 
// but sticking to your physical request, we focus on dine-in.

using namespace std;

// ================= WORKER PANEL (Waiters) =================
// Only: Set Tables, Take Orders, Bills
void workerPanel() {
    int opt;
    do {
        system("cls"); // Clear screen (Windows)
        cout << "\n================================\n";
        cout << "       WORKER DASHBOARD         \n";
        cout << "================================\n";
        cout << "1. Manage Tables (Free/Busy)\n";
        cout << "2. Take New Order\n";
        cout << "3. Generate Bill\n";
        cout << "4. Logout\n";
        cout << "================================\n";
        cout << "Enter Choice: ";
        cin >> opt;

        switch (opt) {
            case 1:
                manageTables(); // From tables.cpp
                break;
            case 2:
                takeDineInOrder(); // From dine_in_order.cpp
                break;
            case 3:
                generateBill(); // From billing.cpp
                break;
            case 4:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
        if(opt != 4) system("pause");

    } while (opt != 4);
}

// ================= ADMIN PANEL (Owner) =================
// Has access to Menu, Online orders, Logs, etc.
void adminPanel() {
    int opt;
    do {
        system("cls");
        cout << "\n================================\n";
        cout << "        ADMIN DASHBOARD         \n";
        cout << "================================\n";
        cout << "1. Manage Food Menu (Add/Edit)\n";
        cout << "2. Manage Tables\n";
        cout << "3. Take Dine-In Order\n";
        cout << "4. Take Online/Phone Order\n";
        cout << "5. Generate Bill\n";
        cout << "6. Logout\n";
        cout << "================================\n";
        cout << "Enter Choice: ";
        cin >> opt;

        switch (opt) {
            case 1: manageMenu(); break;
            case 2: manageTables(); break;
            case 3: takeDineInOrder(); break;
            // case 4: cout<<"Coming soon......"; break;
            case 4: takeOnlineOrder(); break;
            case 5: generateBill(); break;
            case 6: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice!\n";
        }
        if(opt != 6) system("pause");

    } while (opt != 6);
}

int main() {
    // Load table data immediately when system starts
    loadTablesFromFile(); 

    int choice;
    do {
        system("cls");
        cout << "\n************************************\n";
        cout << "   RESTAURANT MANAGEMENT SYSTEM     \n";
        cout << "************************************\n";
        cout << "1. Login (Admin/Worker)\n";
        cout << "2. Register New Staff\n";
        cout << "3. Recover Password\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string role = login(); 

            if (role == "admin") {
                adminPanel(); // Full Access
            } 
            else if (role == "worker") {
                workerPanel(); // Restricted Access
            } 
        } 
        else if (choice == 2) {
            signup(); 
            system("pause");
        } 
        else if (choice == 3) {
            forgotPassword(); 
            system("pause");
        }

    } while (choice != 4);

    cout << "\nSystem Shutdown.\n";
    return 0;
}