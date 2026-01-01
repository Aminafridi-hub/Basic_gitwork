#include "menu.h"

#include <iostream>

#include <fstream>

#include <string>

#include <sstream>

#include <vector>



using namespace std;



// Helper to convert int to string

string intToString(int v) {

    stringstream ss;

    ss << v;

    return ss.str();

}



// 1. HEADER CHECKER (Like we did for users.csv)

void menuheader() {

    ifstream fCheck("menu.csv");

    if(!fCheck) { // If file doesn't exist

        // fCheck.close();

        ofstream fCreate("menu.csv");

        fCreate << "ItemName,Price,Stock" << endl; // Write Header

        fCreate.close();

    } else {

        fCheck.close();

    }

}



void viewMenuOnly() {

    menuheader(); // Ensure file and header exist

    ifstream f("menu.csv");

    string line, dummy;

   

    cout << "\n========== FOOD MENU ==========\n";

    cout << "Item Name\tPrice\tStock\n";

    cout << "--------------------------------------\n";

   

    getline(f, dummy); // SKIP HEADER LINE



    while(getline(f, line)) {

        if(line.empty()) continue;

        stringstream ss(line);

        string name, price, qty;

       

        getline(ss, name, ',');

        getline(ss, price, ',');

        getline(ss, qty); // Read until end of line

       

        cout << name << "\t\t" << price << "\t" << qty << endl;

    }

    cout << "======================================\n";

    f.close();

}



void manageMenu() {

    menuheader(); // Ensure file exists before adding

    int opt;

    cout << "\n1. View Menu\n2. Add Item\nChoice: ";

    cin >> opt;



    if(opt == 1) {

        viewMenuOnly();

    }

    else if(opt == 2) {

        string name;

        int price, qty;

        cout << "Enter Item Name (use_underscores): ";

        cin >> name;

        cout << "Enter Price: ";

        cin >> price;

        cout << "Enter Stock Quantity: ";

        cin >> qty;



        ofstream f("menu.csv", ios::app);

        // We don't need to write header here, menuheader() already did it if needed

        f << name << "," << price << "," << qty << endl;

        f.close();

        cout << "Item added to menu.\n";

    }

}



int getItemPrice(string itemName) {

    menuheader();

    ifstream f("menu.csv");

    if(!f) return -1;



    string line, dummy;

    getline(f, dummy); // SKIP HEADER LINE



    while(getline(f, line)) {

        if(line.empty()) continue;

        stringstream ss(line);

        string name, priceStr, qtyStr;

       

        getline(ss, name, ',');

        getline(ss, priceStr, ',');

       

        // We only need the price, so we stop reading here

       

        if(name == itemName) return stoi(priceStr);

    }

    return -1;

}



bool updateStock(string itemName, int qtyOrdered) {

    menuheader();

    vector<string> lines;

    ifstream f("menu.csv");

    string line, header;

    bool found = false;

    bool success = false;



    // 1. Read and preserve the Header

    if(getline(f, header)) {

        lines.push_back(header);

    }



    // 2. Read the rest of the data

    while(getline(f, line)) {

        if(line.empty()) continue;

        stringstream ss(line);

        string name, priceStr, qtyStr;

       

        getline(ss, name, ',');

        getline(ss, priceStr, ',');

        getline(ss, qtyStr); // Read until end



        if(name == itemName) {

            int currentStock = stoi(qtyStr);

            if(currentStock >= qtyOrdered) {

                currentStock = currentStock - qtyOrdered;

                // Reconstruct the line

                string newLine = name + "," + priceStr + "," + intToString(currentStock);

                lines.push_back(newLine);

                success = true;

                found = true;

            } else {

                cout << "Error: Not enough stock! Available: " << currentStock << endl;

                return false;

            }

        } else {

            lines.push_back(line); // Keep other items unchanged

        }

    }

    f.close();



    // 3. Write everything back

    if(found && success) {

        ofstream out("menu.csv");

        for(size_t i = 0; i < lines.size(); i++) {

            out << lines[i] << endl;

        }

        out.close();

        return true;

    }

   

    if(!found) cout << "Error: Item not found in menu.\n";

    return false;
}