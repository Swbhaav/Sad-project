#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <conio.h>

using namespace std;

class FoodOrderSystem {
private:
    const string foodFile = "food.txt";
    const string ordersFile = "orders.txt";
    const string adminPassword = "abc";

public:
    void start() {
        for (int i = 10; i <= 100; i += 15) {
            if (i == 100) i = 99;
            cout << "\n\n\n\n\n\t\t\tLoading..." << i << "%";
            Sleep(1000);
            system("cls");
        }
        showMainMenu();
    }

private:
    void showMainMenu() {
        int choice;
        while (true) {
            system("cls");
            cout << "\n\n\t\t______________________________________________\n\n";
            cout << "\t\t\t   WELCOME TO FOOD ORDER SYSTEM\n";
            cout << "\t\t_______________________________________________\n";
            cout << "\t\t1. Place your Order\n";
            cout << "\t\t2. Admin Mode\n";
            cout << "\t\t3. Exit\n";
            cout << "\n\t\tEnter your choice from 1 to 3:\n\t\t";
            cin >> choice;

            switch (choice) {
            case 1: placeOrder(); break;
            case 2: adminPanel(); break;
            case 3: exitSystem(); return;
            default:
                cout << "\n\n\t\tEnter Valid Number from 1 to 3\n";
                system("pause");
            }
        }
    }

    void placeOrder() {
        while (true) {
            system("cls");
            displayMenu();

            string customerName;
            int itemNo, quantity, price, total;
            char foodName[30];

            cout << "\nPlease Enter Your Name: ";
            cin >> customerName;
            cout << "Please Enter Your Choice: ";
            cin >> itemNo;
            cout << "Please Enter The Quantity: ";
            cin >> quantity;

            if (quantity > 15) {
                cout << "\n\t\tOrder limit exceeded! Max 15 items allowed.";
                Sleep(2000);
                continue;
            }

            ifstream file(foodFile);
            bool found = false;

            while (file >> itemNo >> foodName >> price) {
                if (itemNo == itemNo) {
                    found = true;
                    total = price * quantity;
                    cout << "\n\t\tYour order is " << quantity << " " << foodName;
                    cout << "\n\t\tYour order has been placed!";
                    Sleep(1500);
                    system("cls");

                    cout << "\n\t\t-----------------------FOOD ORDER SYSTEM------------------";
                    cout << "\n\t\t----------------------------BILL--------------------------";
                    cout << "\n\t\tName: " << customerName;
                    cout << "\n\t\tFood: " << foodName;
                    cout << "\n\t\tQuantity: " << quantity;
                    cout << "\n\t\tTotal Price: " << total;
                    cout << "\n\t\t---------------------------------------------------------";

                    ofstream out(ordersFile, ios::app);
                    out << "Name: " << customerName << " Item: " << foodName
                        << " Quantity: " << quantity << " Total Price: " << total << "\n";
                    out.close();
                    break;
                }
            }

            file.close();
            if (!found) {
                cout << "\n\t\tInvalid item number!";
            }

            Sleep(3000);
            break;
        }
    }

    void adminPanel() {
        char ch, password[100];
        int index = 0;

        cout << "\n\n\t\tEnter Admin Password: ";
        while ((ch = _getch()) != 13) {
            if (ch == 8 && index > 0) {
                index--;
                cout << "\b \b";
            } else {
                password[index++] = ch;
                cout << "*";
            }
        }
        password[index] = '\0';

        system("cls");
        cout << "\n\n\n\t\tAuthenticating";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(500);
        }

        if (strcmp(password, adminPassword.c_str()) == 0) {
            adminMenu();
        } else {
            cout << "\n\n\t\tInvalid Password. Access Denied.";
            Sleep(2000);
        }
    }

    void adminMenu() {
        int choice;
        while (true) {
            system("cls");
            cout << "\n\n\t\t\tAdmin Panel";
            cout << "\n\t\t1. View Menu";
            cout << "\n\t\t2. Add Items";
            cout << "\n\t\t3. Delete Items";
            cout << "\n\t\t4. Count Items";
            cout << "\n\t\t5. View Customer Orders";
            cout << "\n\t\t0. Return to Main Menu";
            cout << "\n\t\tEnter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: displayMenu(); system("pause"); break;
            case 2: addItems(); break;
            case 3: deleteItem(); break;
            case 4: countItems(); break;
            case 5: viewOrders(); break;
            case 0: return;
            default: cout << "Invalid Choice"; break;
            }
        }
    }

    void displayMenu() {
        ifstream file(foodFile);
        int no, price;
        char name[30];

        cout << "\n\t------------------ MENU ------------------\n";
        cout << "\tNumber\t\tFood\t\tPrice\n";
        while (file >> no >> name >> price) {
            cout << "\t" << no << "\t\t" << name << "\t\t" << price << "\n";
        }
        cout << "\t------------------------------------------\n";
        file.close();
    }

    void addItems() {
        int num, no, price;
        char name[30];

        cout << "\n\t\tEnter number of items to add: ";
        cin >> num;

        ofstream file(foodFile, ios::app);
        for (int i = 0; i < num; i++) {
            cout << "\n\t\tEnter Food Number: ";
            cin >> no;
            cout << "\t\tEnter Food Name: ";
            cin >> name;
            cout << "\t\tEnter Price: ";
            cin >> price;
            file << no << "\t" << name << "\t" << price << "\n";
        }
        file.close();
        cout << "\n\t\tItems added successfully.";
        Sleep(2000);
    }

    void deleteItem() {
        int dno, no, price;
        char name[30];

        cout << "\n\t\tEnter Food Number to delete: ";
        cin >> dno;

        ifstream inFile(foodFile);
        ofstream tempFile("temp.txt");

        while (inFile >> no >> name >> price) {
            if (no != dno) {
                tempFile << no << "\t" << name << "\t" << price << "\n";
            }
        }

        inFile.close();
        tempFile.close();
        remove(foodFile.c_str());
        rename("temp.txt", foodFile.c_str());

        cout << "\n\t\tItem deleted successfully.";
        Sleep(2000);
    }

    void countItems() {
        int no, price, count = 0;
        char name[30];
        ifstream file(foodFile);

        while (file >> no >> name >> price) {
            count++;
        }
        file.close();

        cout << "\n\t\tTotal items: " << count;
        Sleep(2000);
    }

    void viewOrders() {
        ifstream file(ordersFile);
        string line;

        cout << "\n\t\tCustomer Orders:\n";
        while (getline(file, line)) {
            cout << "\t\t" << line << "\n";
        }
        file.close();
        system("pause");
    }

    void exitSystem() {
        system("cls");
        cout << "\n\n\n\t\tThank you for using our system!\n\t\tPlease visit again!";
        Sleep(2000);
    }
};

int main() {
    FoodOrderSystem system;
    system.start();
    return 0;
}

