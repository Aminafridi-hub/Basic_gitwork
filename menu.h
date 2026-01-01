#ifndef MENU_H
#define MENU_H
#include <string>
using namespace std;

void manageMenu();    // For Admin (Add items with Quantity)
void viewMenuOnly();  // Shows Price AND Stock
int getItemPrice(string itemName); // Returns price
bool updateStock(string itemName, int qtyOrdered); // NEW: Deducts stock

#endif