#ifndef Release4_h
#define Release4_h

#include "Release2&3.h"
#include "generalArraywithTemplate_v2.h"

#include <list>

using namespace std;

class linkedlist: public basic_item{
    private:
        //This creates a list of group1_items as container
        list<group1_item*> container;
    public:
        linkedlist(){
            itemTypeName = "Linked_List_of_group1_items.";
        }

        ~linkedlist(){
            for(auto item : container){delete item;}
            container.clear();
        }

        void insertAtHead(group1_item* inp){
            //Create a new node
            container.push_front(inp);
        }

        void insertAtTail(group1_item* inp){
            //Create a new node
            container.push_back(inp);
        }

        void removeFromHead(){
            if(!container.empty()){
                group1_item* Item = container.front();
                container.pop_front();
                //Deletes the node at the back and frees memory
                delete Item;  
            }
        }

        void removeFromTail(){
            if(!container.empty()){
                group1_item* Item = container.back();
                container.pop_back();
                //Deletes the node at the back and frees memory
                delete Item; 
            }
        }

        virtual void printItemOnScreen() const override {
            //Check for empty list
            if (container.empty()) {
                cout << "Error: List empty" << endl;
                return;
            }

            //Traverse the list
            //Const group1_item &item creates a read only reference 
            //To each of the group1_items in the container
            // : container will iterate through all the group1_items in the list
            for(const group1_item* item : container) {
                item->printItemOnScreen();
            }
        }

        virtual void enterItemFromKeyboard() override{
            int size;
            cout << "How many items to add to the list? " << endl;
            cout << "Enter a number: " << endl;
            cin >> size;

            for(int i = 0; i < size; i++){
                group1_item* newItem = new group1_item();
                cout << "Enter new item: " << endl;
                newItem->enterItemFromKeyboard();

                char choice;
                cout << "Insert at the head or tail of the list: "<< endl;
                cout << "Type H for head or T for tails:" << endl;
                cin >> choice;

                if(choice == 'H' || choice == 'h'){
                    insertAtHead(newItem);
                }
                else{
                    insertAtTail(newItem);
                }
            }
        }

        virtual void generateRandomItem() override {
            group1_item* newItem = new group1_item();
            newItem->generateRandomItem();

            char choice;
            cout << "Insert at the head or tail of the list: "<< endl;
            cout << "Type H for head or T for tails:" << endl;
            cin >> choice;

            if(choice == 'H' || choice == 'h'){
                insertAtHead(newItem);
            }
            else{
                insertAtTail(newItem);
            }
        }

        virtual bool compatibilityCheck(const basic_item* other_item) const override{
            return false;
        }

        virtual bool IsLargerThan(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const override{
            return false;
        }

        virtual bool IsEqualTo(const basic_item* other_item, const basic_sort_criteria* sort_criteria=NULL) const override{
            return false;
        }
};

#endif