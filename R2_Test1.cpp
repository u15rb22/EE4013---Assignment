// testing Releease 2 

#include "Release2.h"

void test1()
{
    group1_item Item1;

    Item1.printItemOnScreen();
    Item1.generateRandomItem();
    Item1.printItemOnScreen(); 
}

void test2()
{
    group1_item Item1;

    Item1.printItemOnScreen();
    Item1.enterItemFromKeyboard();
    Item1.printItemOnScreen(); 
}

int main()
{
    test1();
    test2();

    //test1();
    //test1();
    //test1();


    return 0; 
}