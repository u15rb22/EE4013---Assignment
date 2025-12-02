#ifndef Release2_h
#define Release2_h

#include "arrayItem_v3.h"
#include "generalArraywithTemplate_v2.h"

class string_item : public basic_item{
    protected:
        string item_value;
        bool stringSet;
    public:
        string_item(){
            stringSet = false;
            itemTypeName = "String";
        }
        ~string_item(){;}

        //Small function to get the string length
        int getStringLength() const {
            if(!stringSet){
                cout << "Warning: Empty item." << endl;
            }
            return item_value.length();
        }

        //Function to print the string value
        virtual void printItemOnScreen() const{
            if(stringSet){
                cout << "String value: " << item_value << endl;
            }
            else{
                cout << "Error: String has not been set." << endl;
            }
        }

        //Function to enter a string from keyboard
        virtual void enterItemFromKeyboard(){
            if(!isLocked()){

                if(!stringSet){
                    cout << "Enter string: " << endl;
                    cin >> item_value;
                    cout << endl;

                    //Item has been filled
                    empty = false;
                    stringSet = true;
                }
                else{
                    cout << "Error on enterItemFromKeyboard: String already set." << endl;
                }
            }
            //Cannot access item
            else{
                cout << "Error: Item is locked." << endl;
            }   
        }

        //Function to check the type of another item to the strings
        virtual bool compatibilityCheck(const basic_item* other_item) const{
            //True if the same, false if not
            bool result = false;

            //Check to see if the other item is allocated, if not skip
            if(other_item != NULL){

                //Type casting the other item to confirm its the same as the string
                const string_item* typecast_OtherItem = typecastItem(other_item, this);

                if(typecast_OtherItem != NULL){result = true;}
                else{
                    cout << "Check failed for Item type: " << itemTypeName << endl;
                }
            }

            return result;
        }
        
        virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            bool result = false;

            //Check if other item is not allocated, if not dont compare
            if(other_item == NULL){return false;}

            //Type cast the other item
            const string_item* typecast_OtherItem = typecastItem(other_item, this);

            //Check if the items are the same type
            if(typecast_OtherItem == NULL){
                cout << "Error: Other item is not of the same string type." << endl;
                return false;
            }
            
            //Check if the strings have been set or not
            if(!stringSet || !typecast_OtherItem->stringSet) {
                cout << "Error: Cannot compare, one or both strings are not set." << endl;
                return false;
            }

            //Return true if the current item is larger than the other item
            if(item_value > (typecast_OtherItem->item_value) ){
                result = true;
            }
            
            //check if there are sorting options to apply 
		    if(sort_criteria!=NULL)
		    {
			    //if sorting is in descending order the result is reversed 
			    if(!( sort_criteria->getAscending())){
                    result=!result;
                }
		    }
            return result;
        }

        virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            bool result = false;

            //Check if other item is not allocated, if not dont compare
            if(other_item == NULL){return false;}

            //Type cast the other item
            const string_item* typecast_OtherItem = typecastItem(other_item, this);

            //Check if the items are the same type
            if(typecast_OtherItem == NULL){
                cout << "Error: Other item is not of the same string type." << endl;
                return false;
            }
            
            //Check if the strings have been set or not
            if(!stringSet || !typecast_OtherItem->stringSet) {
                cout << "Error: Cannot compare, one or both strings are not set." << endl;
                return false;
            }

            //Return true if the current item is larger than the other item
            if(item_value == (typecast_OtherItem->item_value) ){
                result = true;
            }
            return result;
        }

        //Function to generate a random string
        virtual void generateRandomItem(){
            if(!isLocked()){
                if(!stringSet){
                    const char charSet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

                    //Random string length 1 - 10
                    int length = rand() % 10 + 1;

                    //Function to loop through the given length
                    //And append a random character from the character set 
                    //Into item_value
                    for(int i = 0; i < length; i++){
                        item_value += charSet[rand() % (sizeof(charSet) - 1)];
                    }

                    //Item is not empty and string has been set.
                    empty = false;
                    stringSet = true;
                }
                else{
                    cout << "Error in generateRandomItem: String is already set." << endl;
                }
            }
            else{
                cout << "Error: Item is locked." << endl;
            }
            
        }

        //Small function to clear the string item
        void clearString(){
            item_value.clear();
            stringSet = false;
            empty = true;
        }

        //Small function to return the string item value
        string returnString(){
            if(!stringSet){
                cout << "Error in returnString: String has not been set." << endl;
            }
            return item_value;
        }
};


class composite_item : public basic_item{
    protected: 
        string_item fName;
        string_item lName;
    public:
        
};

#endif