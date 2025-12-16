#ifndef Release4_h
#define Release4_h

#include "Release2&3.h"
#include "generalArraywithTemplate_v2.h"

class Node{
    public: 
        group1_item data;
        Node *next;

        //Constructor
        Node(){
            next = NULL;
        }

        Node(group1_item inp){
            this->data = inp;
            this->next = NULL;
        }
};

class linkedlist: public basic_item{
    Node* head;

    public:
        linkedlist(){
            head = NULL;
            itemTypeName = "Linked_List_of_group1_items.";
        }

        ~linkedlist() {
            Node* current = head;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }

        void insertAtHead(group1_item inp){

            //Create a new node
            Node *newNode = new Node(inp);

            //Assign to the head of the list if empty
            if(head == NULL){
                head = newNode;
                return;
            }

            //Insert the new linked list at the head
            newNode->next = this->head;
            this->head = newNode;
        }

        void insertAtTail(group1_item inp){
            Node* newNode = new Node(inp);

            if(head == NULL){
                head = newNode;
                return;
            }

            Node* temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newNode;
        }

        void printItemOnScreen() const {
            Node *temp = head;

            //Check for empty list
            if (head == NULL) {
                cout << "Error: List empty" << endl;
                return;
            }

            //Traverse the list
            while (temp != NULL) {
                temp->data.printItemOnScreen();
                temp = temp->next;
            }
        }

        void enterItemFromKeyBoard(){
            group1_item newItem;
            cout << "Enter new item: " << endl;
            newItem.enterItemFromKeyboard();

            char choice;
            cout << "Insert at the head or tail of the list: "<< endl;
            cout << "Type H for head or T for tails." << endl;
            cin >> choice;

            if(choice == 'H' || choice == 'h'){
                insertAtHead(newItem);
            }
            else{
                insertAtTail(newItem);
            }

        }

};

#endif