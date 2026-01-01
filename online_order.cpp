#include "online_order.h"
#include "menu.h" // Include menu to access updateStock
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// void takeOnlineOrder() {
//     cout << "\n--- Online Order ---\n";
//     viewMenuOnly(); // Show menu
    
//     int id;
//     string name, phone, item;
//     int qty, price;

//     cout << "Order ID: "; cin >> id;
//     cin.ignore(); // Clears the newline character from the buffer
//     cout << "Customer Name: "; //cin >> name;
//     getline(cin, name); // Allows names with spaces (e.g., "Amin Afridi")
//     cout << "Phone: "; cin >> phone;
//     cout << "Item Name: "; cin >> item;
    
    
//     price = getItemPrice(item);
//     if(price == -1) {
//         cout << "Item not found.\n";
//         return;
//     }

//     cout << "Quantity: "; cin >> qty;

//     // Check Stock
//     if(updateStock(item, qty)) {
//         ofstream f("online_order.csv", ios::app);
//         f << id << "," << name << "," << phone << "," << item << "," << qty << "," << price << endl;
//         f.close();
//         cout << "Online order saved and stock updated.\n";
//     } else {
//         cout << "Order failed: Not enough stock.\n";
//     }
// }

// ------------------------------------------------------

void takeOnlineOrder() {
    cout << "\n--- Online Order ---\n";
    viewMenuOnly(); 
    
    int id;
    string name, phone, item;
    int qty, price;

    cout << "Order ID: "; 
    while (!(cin >> id) || id <= 0) {
        cout << "Invalid Order ID. Please enter a positive integer: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // 1. CLEAR THE BUFFER
    // This removes the 'Enter' key left behind by 'cin >> id'
    cin.ignore(1000, '\n'); 

    cout << "Customer Name: "; 
    // 2. USE GETLINE
    // This reads the whole line, including spaces (e.g., "Jan Khan")
    getline(cin, name); 
    while (name.empty()) {
        cout << "Customer Name cannot be empty. Please enter again: ";
        getline(cin, name);
    }

    cout << "Phone: "; 
    cin >> phone;
    // Basic phone validation (assuming 10-15 digits, adjustable)
    while (phone.length() < 10 || phone.length() > 15 || phone.find_first_not_of("0123456789") != string::npos) {
        cout << "Invalid phone number. Please enter 10-15 digits: ";
        cin >> phone;
    }

    cout << "Item Name: "; 
    cin >> item;
    
    price = getItemPrice(item);
    if(price == -1) {
        cout << "Item not found.\n";
        return;
    }

    cout << "Quantity: "; 
    while (!(cin >> qty) || qty <= 0) {
        cout << "Invalid quantity. Please enter a positive integer: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if(updateStock(item, qty)) {
        ofstream f("online_order.csv", ios::app);
        if (!f) {
            cout << "Error opening file for saving order.\n";
            return;
        }
        // This will now correctly save "Jan Khan" or just "Jan"
        f << id << "," << name << "," << phone << "," << item << "," << qty << "," << price << endl;
        f.close();
        cout << "Online order saved and stock updated.\n";
    } else {
        cout << "Order failed: Not enough stock.\n";
    }
}