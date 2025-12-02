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

class year_of_enrolment : public integer_item{
protected:
    bool limits_initFlag;
    static int min_year, max_year;
public:
    year_of_enrolment(){itemTypeName = "year_of_enrolment";}

    void setLimits()
    {
        if(!limits_initFlag)
        {
            // CHECKING WHETHER TO USE DEFAULT LIMITS OR NOT
            char limit_options;
            cout << "Add limits or use default limits? Y TO ADD, N FOR DEFAULT: ";
            cin >> limit_options;
            if(limit_options=='Y' || limit_options=='y')
            {
                cout << "Input the upper limit for the year: " << endl;
                cin >> max_year;   // Directly input into the max_year

                cout << "Input the lower limit for the year: " << endl;
                cin >> min_year;   // Directly input into the minIntVal

                // Below is checking whether the minIntVal is less than the max_year. If not, it swaps them
                if (min_year > max_year)
                {
                    cout << "Error in setLimits(): min_year is greater than max_year. They will be swapped." << endl;
                    int temp = min_year;
                    min_year = max_year;
                    max_year = temp;
                }

                if(min_year<0 || max_year<0)
                    cout << "Error in setLimits(): Limit is a negative year. Input not set." << endl;
                limits_initFlag = true; // Set the flag to true
            }
            else
            {
                cout<<"Using default years [1980,2005]"<<endl;
                min_year = 1980;
                max_year = 2005;
                limits_initFlag = true;
            }
        }
        else
            cout << "Error in setLimits(): Limits have already been set." << endl;
    }

    virtual void enterItemFromKeyboard()
    {
        char limit_check;
        cout<<"Carry on limits or set new limits? Y TO SET NEW, N OTHERWISE: ";
        cin>>limit_check;

        if(limit_check == 'Y'||limit_check == 'y')
        {year_of_enrolment::setLimits();}
            

        cout << "Enter the value of the integer item within the set limits [" << min_year << ", " << max_year << "] :" << endl;
        integer_item::enterItemFromKeyboard();
        // Check if the input is within limits
        if(item_value < min_year || item_value > max_year)
        {
            cout << "Error in enterItemFromKeyboard(): Input year is out of limits." << endl;
            empty = true;               // Reset the item to empty if out of limits
            enterItemFromKeyboard();    // Prompt user to enter again
        }
        else 
            return;
    }
};

class group1_item : public basic_item{
    protected: 
        string_item first_Name;
        string_item last_Name;
        year_of_enrolment yearOfEnrolement;
        //Add the other items when you can
    public:
        group1_item(){
            string the_name = "Group1_item - comprising: ";
		    the_name += first_Name.getName();
		    the_name += "; ";
		    the_name += last_Name.getName();
		    the_name += ";";
            the_name += yearOfEnrolement.getName();
            the_name += ".";
            //Add other fields when you can
		    itemTypeName = the_name;
        }

        ~group1_item(){;}

        virtual void printItemOnScreen() const{
            if(isEmpty()){
                cout << "Item is empty." << endl;
            }
            else{
                cout << "First Name: " << endl;
                first_Name.printItemOnScreen(); 
                cout<< endl;
                cout << "Last Name:" << endl;
                last_Name.printItemOnScreen();
                cout << endl;
                cout << "Year of enrolement: " << endl;
                yearOfEnrolement.printItemOnScreen();
                cout << endl;
                //Add the other data when you can
            }
        }

        virtual void enterItemFromKeyboard(){
            if(isLocked()){
                cout << "Error in enterItemFromKeyboard: Item is locked" << endl;
            }
            else{
                cout << "Enter first name: " << endl;
                first_Name.enterItemFromKeyboard();
                cout << endl;
                cout << "Enter last name: " << endl;
                last_Name.enterItemFromKeyboard();
                cout << endl;
                cout << "Enter year of enrolement: " << endl;
                yearOfEnrolement.enterItemFromKeyboard();
                //Add other fields when you can
                empty = false;
            }
        }

        virtual void generateRandomItem()
	    {
		    if (isLocked()){
                cout << "Error in generateRandomItem: Item is locked" << endl;
            }
		    else
		    {
		    	first_Name.generateRandomItem();
			    last_Name.generateRandomItem();
                yearOfEnrolement.generateRandomItem();
			    //Add other fields when you can
			    empty = false;
		    }
	    }

        //Have not finished yet
        virtual bool compatibilityCheck(const basic_item* other_item) const{
            return false;
        }
	    virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            return false;
        }	
	    virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const{
            return false;
        }
};

int year_of_enrolment::min_year = 1980;
int year_of_enrolment::max_year = 2005;

#endif