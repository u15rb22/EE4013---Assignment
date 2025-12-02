// EE4013 - Assignment 1
// Release 1 integer_itemWithLimits 
// by Dawid Drewicz 
//
// R1_DD.h

#ifndef R1_DD_H 
#define R1_DD_H

//#include "generalArraywithTemplate_v2.h"
#include "../generalArraywithTemplate_v2.h"
#include <limits>


class integer_itemWithLimits : public integer_item{
    protected: 
        int min_val, max_val; 
        bool Lims_Set; 

        int PassMax(int val1, int val2) // unused 
        {
            if(val1 >= val2)
                return val1; 
            else 
                return val2;
        }

        int PassMin(int val1, int val2)  // unused
        {
            if(val1 <= val2)
                return val1; 
            else 
                return val2;
        }

        bool inLimits(int inVal) const
        {
            if((inVal<=max_val)&&(inVal>=min_val))
                return true;
            else
                return false;
        }

        bool itemInRange(int Lower, int Upper)
        {
            if((item_value<=Lower)&&(item_value>=Upper))
                return true;
            else
                return false;

        }

        void setLimits(int Lower, int Upper )
        {
            min_val = Lower;
            max_val = Upper; 
            Lims_Set = true; 
        }


    private:
    // privitising "generateRandomItemWithinlimits()" to prevent setting int val outisde limits
        using integer_item::generateRandomItemWithinLimits;

    public: 
        integer_itemWithLimits()
        {
            itemTypeName = "integer_itemWithLimits";
            min_val = -50; //  assumed defult vals
            max_val = 50; 
            Lims_Set = false; // is false while vals defult 

            // incrementincludedBy();
        }

        ~integer_itemWithLimits()
        {
           // decrementincludedBy();
           ;
        }
        bool isLims_Set() const {return Lims_Set;}

        int GetMinVal() const
        {
            if(!isLims_Set())
			    cout << "*Note: Limits are there defult values" << endl; 
		    return min_val;
        }

        int GetMaxVal() const
        {
            if(!isLims_Set())
			    cout << "*Note: Limits are there defult values" << endl; 
		    return max_val;
        }

        // * like this ? or keep "item" as refering to int val ...  *
        // and disp Limits sepretly ? *
        virtual void printItemOnScreen() const
        {
            if(isEmpty())
			    cout << "Item is empty." << endl;
		    else
			    cout << "Item value is " << item_value << " . " << endl;
                
            if(isLims_Set())
            {
                cout << "Lower limit is " << min_val << "." << endl;
                cout << "Upper limit is " << max_val << "." << endl;
            }
            else
                cout << "Limits are set to defult Values" << endl; 
        }

        virtual void enterValueFromKeyboard()
        {
            if(isLocked())
                cout << "Error in enterValueFromKeyboard: Item is locked" << endl;
            else
            {
                bool Valid_int = false;
                while(!Valid_int)
                {
		            cout << "Insert integer element then hit enter." << endl;
			        cin >> item_value;
                    if(cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "* Warning: Input must be an integer." << endl; 
                        cout << endl;
                    }
                    else
                    {
                        if(inLimits(item_value))
                            Valid_int = true; 
                        else
                            cout << "*Warning*: integer must fall within set limits" << endl << endl;  
                    } 
                }
                    empty = false;
                
            }
        }

        virtual bool enterLimitsFromKeyboard() // retruns True if it also set Int Value
        {
            if(isLocked())
                cout << "Error in enterLimitsFromKeyboard: Item is locked" << endl;
            else
            {
                bool valid_lim = false, OkInput = false, ForceNewItem = false; 
                int tempL, tempU ; 
                char yesNo_in;
                    

                while(!valid_lim)
                {
                    while (!OkInput)
                    {
                        cout << "Insert Lower Limit Value then hit enter."<< endl;
                        cin >> tempL;
                        if(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            cout << "* Warning: Input must be an integer." << endl;
                            cout << endl; 
                        }
                        else
                            OkInput = true; 
                    }

                    OkInput  = false;
                    while(!OkInput)
                    {
                        cout << "Insert Upper Limit Value then hit enter."<< endl;
                        cin >> tempU;
                        if(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "* Warning: Input must be an integer." << endl; 
                            cout << endl;
                        }
                        else
                            OkInput= true; 
                            
                             
                    }
                    
                    if(tempL != tempU)
                    {
                        if (tempL > tempU)  // make sure limits are correct way round
    			        {
                            cout << "Notice: Limits where entered wrong way round, This has been corrected internaly." << endl; 
		    		        int temp = tempL;
			    	        tempL = tempU;
				            tempU = temp;
			            }
                        if((isEmpty()) || itemInRange(tempL,tempU))
                            valid_lim = true; // exits while loop 
                        else
                        {
                            cout << "* Notice: Current Item dosn't fall within passed Limits *" << endl;
                            cout << "Do you want to continue with Passed Limits & change item. Enter 'Y' to cont." << endl;
                            cin >> yesNo_in; 

                            if((yesNo_in=='Y')||(yesNo_in=='y'))
                            {
                                valid_lim = true; 
                                ForceNewItem = true;
                            }
                            else
                                valid_lim = false;

                        }
                            
                    }
                    else
                    {
                        cout << "*Warning*: Limits cannot be the same Value." << endl; 
                    }
                }
                setLimits(tempL, tempU);  
                if(ForceNewItem)
                {
                    enterValueFromKeyboard();
                }
                return ForceNewItem; 
            }
        }

        virtual void enterItemFromKeyboard()
	    {
		    if(isLocked())
			    cout << "Error in enterItemFromKeyboard: Item is locked" << endl;
		    else
		    {
                bool intSet = false, newLims = false; 
                char yesNo_in; 

                // check if Limits need change 
                cout << "Do you want to Enter New limits ? type Y if yes then hit enter" << endl; 
                cin >> yesNo_in; 

                if((yesNo_in=='Y')||(yesNo_in=='y'))
                {
                    intSet = enterLimitsFromKeyboard(); // if true dont ask to change int again 
                    newLims = true; 
                }
                yesNo_in = 'N'; // "restet" slection to reuse var  

                if(!intSet) // run only if new lims set w this call, Assume Min 1 must update .: if lims !set int must be & Q is redundant 
                {
                    cout << "Do you want to Enter New Integer ? type Y if yes then hit enter" << endl; 
                    cin >> yesNo_in; 
                }
                
                if((yesNo_in=='Y')||(yesNo_in=='y')||(!newLims))
                {
                    enterValueFromKeyboard(); 
                }
                
                
		    }		
	    } 

        virtual void generateRandomItem()
        {
            if(isLocked())
                cout << "Error in generateRandomItem: Item is locked" << endl;
            else
                generateRandomItemWithinLimits(min_val, max_val); 
        }

        //void generateRandomLimi








};

#endif 