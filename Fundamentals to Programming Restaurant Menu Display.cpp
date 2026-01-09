#include <iostream>
#include <iomanip>
using namespace std;

//Menu Pages
void showMenu(string prodDes[], double ppu[], int s, int e)
{
    cout << "\n|*---------------------------MENU-----------------------------*|" << endl;
    cout << endl;
    
    for (int i = s; i <= e; i++)
    {
        cout << "(" << setw(2) << i+1 << ")  " << setw(25) << left << prodDes[i] << "RM " << setw(5) << right << setprecision (2) << fixed << ppu[i] << endl;
    }
    cout << endl;
}

//The function to show each page
void selectPage(string pDesc[], double p[])
{
    //declaring variables
    int category;
    
    //displaying the menu and the categories
    cout << "|*---------------------------MENU-----------------------------*|" << endl;
    cout << endl;
    cout << "(1)  Hot Beverage" << endl;
    cout << "(2)  Cold Beverage" << endl;
    cout << "(3)  Snacks" << endl;
    cout << "(4)  Cakes" << endl;
    cout << endl;
    
    cout << "Please select a category by typing the corresponding number: ";
    do
    {
        cin >> category;
        //displays the food within each category
        switch(category)
        {
            case 1:
            showMenu(pDesc, p, 0, 3);//Hot Bev
            break;
            
            case 2:
            showMenu(pDesc, p, 4, 7);//Cold Bev
            break;
            
            case 3:
            showMenu(pDesc, p, 8, 11);//Snacks
            break;
            
            case 4:
            showMenu(pDesc, p, 12, 15);//Cakes
            break;
            
            default: //ERROR HERE! INFINITE LOOP WHEN NON INTEGER INPUT!
            cout << "No such category, try again: ";
            cin.clear();
            cin.ignore(1000, '\n'); //these 2 lines solved the issue
            break;
        }
    } while(category < 1 || category > 4);
}

int main()
{
    //declaring variables
    char confirm = ' ';
    string pDesc[16] = {
        "Hot Coffee", "Hot Cocoa", "Hot Lemon Tea", "Hot Water", "Iced Coffee", "Iced Cocoa", "Iced Lemon Tea", "Iced Water",
        "Fries", "Nuggets", "Spring Rolls", "Garlic Bread", "Red Velvet Cake", "Chocolate Cake", "Cheese Cake", "Carrot Cake"
    };
    double p[16]{
        7.00, 9.00, 5.50, 0.90, 8.00, 10.00, 6.50, 1.00, 5.00, 10.00, 7.50, 3.00, 15.00, 10.00, 12.00, 8.50
    };
    
    //show menu
    do
    {
        selectPage(pDesc, p);
        cout << "Go to another page? (Type 'Y'/'y' to confirm or any key to start ordering): ";
        cin >> confirm;
    } while (confirm == 'y' || confirm == 'Y'); //any other key moves to third part
    
//part 3 goes here

    return 0;
}