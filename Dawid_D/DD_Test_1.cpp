// EE4013 - Assignment 1
// Release 1 - Test file 1 
// by Dawid Drewicz 
//
// DD_Test_1.cpp

#include "R1_DD.h"

void test2() // Test if able to set limits that don't include Previously set Item 
{               // Fix : force item change if not within Limi
    integer_itemWithLimits my_item1;

    my_item1.enterItemFromKeyboard();
    my_item1.printItemOnScreen();

    my_item1.enterItemFromKeyboard();
    my_item1.printItemOnScreen();


}


int main()
{
    //test1(); 
    test2();

    

    return 0; 
}

void test1()
{
    integer_item base_item; 

    base_item.generateRandomItem(); 
    base_item.printItemTypeName();
    base_item.printItemOnScreen(); 

    integer_itemWithLimits my_item1; 

    int A = my_item1.GetMinVal();

    cout << "GetMinVal() returned Value is: " << A << endl; //check for error message

    //my_item.generateRandomItem(); 
    my_item1.enterItemFromKeyboard(); 
    my_item1.printItemTypeName();
    my_item1.printItemOnScreen();

    int B = my_item1.GetMaxVal();

    cout << "GetMaxVal() returned Value is: " << B << endl;


    integer_itemWithLimits my_item2;
    
    my_item2.generateRandomItem(); 
    my_item2.printItemOnScreen(); 

    integer_itemWithLimits my_item3;
    my_item3.enterItemFromKeyboard(); 
    //my_item3.generateRandomItemWithinLimits(10,20); // check if it possible to store item that's not within limit's.
    my_item3.printItemOnScreen(); 

}

