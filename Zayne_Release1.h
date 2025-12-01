
#pragma once
#include "arrayItem_v3.h"
#include "generalArraywithTemplate_v2.h"

class integer_itemWithLimits_Zayne : public integer_item
{
protected:
    bool limits_initFlag;
    bool item_initFlag;
    int minIntVal, maxIntVal;

public:
    integer_itemWithLimits_Zayne()
    {
        itemTypeName = "integer_itemWithLimits_Zayne";
        // Below is the default initialization. If the user does not set the limits, these will be used
        limits_initFlag = false;
        item_initFlag = false;
        minIntVal = -50;
        maxIntVal = 50;
    }
    ~integer_itemWithLimits_Zayne() { ; } // without printout

    int getItemValue()
    {
        if(item_initFlag)
            return item_value;
        else
        {
            cout<<"Item value not set"<<endl;
            return 0;
        }
    }

    void setLimits()
    {
        // Only set the limits once
        if(!limits_initFlag)
        {
            cout << "Input the upper limit for the integer item: " << endl;
            cin >> maxIntVal;   // Directly input into the maxIntVal
            cout << "Input the lower limit for the integer item: " << endl;
            cin >> minIntVal;   // Directly input into the minIntVal

            // Below is checking whether the inputs are integers
            if(typeid(maxIntVal) != typeid(int) || typeid(minIntVal) != typeid(int))
            {
                cout << "Error in setLimits(): Non-integer value entered for limits." << endl;
                return;
            }

            // Below is checking whether the minIntVal is less than the maxIntVal. If not, it swaps them
            if (minIntVal > maxIntVal)
            {
                cout << "Error in setLimits(): minIntVal is greater than maxIntVal. They will be swapped." << endl;
                int temp = minIntVal;
                minIntVal = maxIntVal;
                maxIntVal = temp;
            }
            limits_initFlag = true; // Set the flag to true
        }
        else
            cout << "Error in setLimits(): Limits have already been set." << endl;
    }

    virtual void enterItemFromKeyboard()
    {
		integer_itemWithLimits_Zayne::setLimits();

        cout << "Enter the value of the integer item within the set limits [" << minIntVal << ", " << maxIntVal << "] :" << endl;
        integer_item::enterItemFromKeyboard();
        // Check if the input is within limits
        if(item_value < minIntVal || item_value > maxIntVal)
        {
            cout << "Error in enterItemFromKeyboard(): Input value is out of limits." << endl;
            empty = true;               // Reset the item to empty if out of limits
            enterItemFromKeyboard();    // Prompt user to enter again
        }
        else 
            return;
    }

};