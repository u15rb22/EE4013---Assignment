// EE4013 - Assignment 1
// Release 1 integer_itemWithLimits 
// by Dawid Drewicz 
//
// R1_DD.h

#ifndef R1_DD_H 
#define R1_DD_H

//#include "generalArraywithTemplate_v2.h"
#include "../generalArraywithTemplate_v2.h"

class integer_itemWithLimits : public integer_item{
    protected: 
        int min_val, max_val; 

    private:
    // privitising "generateRandomItemWithinlimits()" to prevent setting int val outisde limits
        using integer_item::generateRandomItemWithinLimits;

    public: 
        integer_itemWithLimits()
        {
            itemTypeName = "integer_itemWithLimits";
            min_val = -50; //  assumed defult vals
            max_val = 50; 
        }
        ~integer_itemWithLimits(){;}

        int GetMinVal()
        {
            if(isEmpty())
			cout << "*Warning*: GetMinVal() called on an empty object" << endl; 
		    return min_val;
        }

        int GetMaxVal()
        {
            if(isEmpty())
			cout << "*Warning*: GetMaxVal() called on an empty object" << endl; 
		    return max_val;
        }

        // * like this ? or keep "item" as refering to int val ...  *
        // and disp Limits sepretly ? *
        virtual void printItemOnScreen() const
        {
            if(isEmpty())
			    cout << "Item is empty." << endl;
		    else
            {
			    cout << "Item value is " << item_value << " . " << endl;
                cout << "Lower limit is " << min_val << "." << endl;
                cout << "Upper limit is " << max_val << "." << endl;
            }
        }

        // * Again like above or sepreate or mix have this but also 
        // option to do 1 by 1 ? *
        virtual void enterItemFromKeyboard()
	    {
		    if(isLocked())
			    cout << "Error in enterItemFromKeyboard: Item is locked" << endl;
		    else
		    {
                bool Valid_int = false; 
                char yesNo_in; 

                // check if Limits need change 
                cout << "Do you want to Enter New limits ? type Y if yes then hit enter" << endl; 
                cin >> yesNo_in; 

                if((yesNo_in=='Y')||(yesNo_in=='y'))
                {
                    bool valid_lim = false; 

                    int tempL, tempU ; 
                    while(!valid_lim)
                    {
                    cout << "Insert Lower Limit Value then hit enter."<< endl;
                    cin >> tempL;
                    cout << endl;
                    cout << "Insert Upper Limit Value then hit enter."<< endl;
                    cin >> tempU;
                    cout << endl;
                    
                    if(tempL != tempU)
                        valid_lim = true; 
                    else
                        cout << "*Warning*: Limits cannot be the same Value." << endl; 
                    }

                    if (tempL > tempU)  // make sure limits are correct way round
			        {
                        cout << "Notice: Limits where entered wrong way round, This has been corrected internaly." << endl; 
				        int temp = tempL;
				        tempL = tempU;
				        tempU = temp;
			        }
                    max_val = tempU; 
                    min_val = tempL; 
                }

                while(!Valid_int)
                {
			        cout << "Insert integer element then hit enter." << endl;
			        cin >> item_value;
			        cout << endl;
			        
                    if((item_value<=max_val)&&(item_value>=min_val))
                        Valid_int = true; 
                    else
                        cout << "*Warning*: integer must fall within set limits" << endl << endl;    
                }
                empty = false;
		    }		
	    } 

        virtual void generateRandomItem()
        {
            generateRandomItemWithinLimits(min_val, max_val); 
        }








};

#endif 