/*
* Name: Joshua Zamora, NSHE: 5006270225, ASSIGNMENT 8
* Description: Create a 2D linked list. The linked
  list will contain a string in the data component that will
  contain a 3 character string. 
* Input: Main file
* Output: expected output of the program by codegrade
*/
// libraries used
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std; // using namespace standard
// Node class definition
class Node
{
public:
    string data;
    Node *left, *right, *up, *down;
    Node (string data) { // Node constructor
        this->data = data; // sets the param to class variable
        // declaring the left, up, right, down ptrs to nullptr
        left = nullptr;
        right = nullptr;
        up = nullptr;
        down = nullptr;
    }
};
// LinkedList class definition
class LinkedList
{
    Node *head;
    // RNG string function that is static and returns a 3 letter string
    static string RNGString() {
        string str;
        int i;
        for (i = 0; i < 3; i++) { // grab the 3 strings
            char c = 'a' + rand() % 26;
            str += c; // store into str variable
        }
        return str; // return 3 letter string to function
    }

public:
    // Constructor to create and link nodes
    LinkedList(int length, int width) {
        // condition to check if the arguments are 0, 
        // if so return nullptr to head
        if (length == 0 || width == 0) {
            head = nullptr;
            return;
        }

        // generate random position for "neo"
        int neoRow = rand() % length;
        int neoCol = rand() % width;

        // generate 2D linked list
        Node *curr = new Node(RNGString());
        head = curr; // set the head as the current
        for (int i = 0; i < width - 1; i++) { // creating the first row
            Node *newNode = new Node(RNGString()); // create new node
            curr->right = newNode; // linking the curr right as new node
            newNode->left = curr; // linking new node left as curr
            curr = newNode; // setting curr as new node
        }
        // creates the next rows depending on the
        // length argument linking them up and down
        Node *rowStart = head; // set row start to head to keep track
        for (int i = 1; i < length; i++) {
            curr = new Node(RNGString()); // create a new node
            Node *prevRow = rowStart; // set prevRow as rowStart
            rowStart->down = curr; // link new row to curr
            curr->up = rowStart; // link curr up to rowStart
            for (int j = 0; j < width - 1; j++) { // create left to right
                Node* newNode = new Node(RNGString());
                curr->right = newNode; // link curr right to new node
                newNode->left = curr; // link new node left to curr
                //link new node up to prevRow right
                newNode->up = prevRow->right;
                // link prevRow right and down to new node
                prevRow->right->down = newNode;
                // set the prevRow right to prevRow
                prevRow = prevRow->right;
                curr = curr->right; // go next curr
            }
            rowStart = rowStart->down; // go down and set as rowStart
        }
        // Replace the data with the RNG neo location made earlier
        Node* neoCurr = head; // setting curr as head
        if (neoRow >= 1) {
            for (int i = 0; i < neoRow; i++) {
                if (neoCurr != nullptr) {
                    neoCurr = neoCurr->down; // go down
                }
            }
        }
        if (neoCol >= 1) {
            for (int i = 0; i < neoCol; i++) {
                if (neoCurr != nullptr) {
                    neoCurr = neoCurr->right; // go right
                }
            }
        }
        // replace current neoCurr data as "neo"
        if (neoCurr != nullptr) {
            neoCurr->data = "neo";
        }
    }
    // destructor for linked list
    ~LinkedList() {
        Node* curr = head; // start at head and delete from there
        Node* tempR = head;
        while (curr) { // while curr is not a null pointer
            Node* temp = curr->right; // create a temp for right of curr
            tempR = tempR->down;
            while (curr) { // while curr is not a null pointer
                delete curr; // delete that curr
                curr = temp; // set the next curr on right as temp
                if (temp) { // if temp is not a null pointer
                    temp = temp->right; // set temp as temp to the right
                }
            }
            curr = tempR; // setting curr as temp
        }
    }
    // print function to print the 2D linked list
    void print() {
        Node* currRow = head; // setting the curr Row as the head
        while (currRow) { // while curr row is not a null pointer
            Node* currCol = currRow; // set curr column as curr row
            while (currCol) { // while curr column is not a null pointer
                cout << currCol->data << " "; // display node string
                currCol = currCol->right; // move to the next column
            }
            cout << endl; // new line
            currRow = currRow->down; // go to next row down of "head"
        }
    }
    // traceTheCall void function used to find where neo is
    void traceTheCall (int mode) {
        if (mode != 0 && mode != 1) { // if mode != 1/0 return error
            cout << mode << ": Unknown Trace mode.\n";
            return;
        }
        if (mode == 0) { // if mode is 0 find the hacker by traverse
            int row = 0, col = 0, compares = 0;
            Node *curr = head; // start at the head
            Node *temp = curr; // setting curr to temp variable
            while (curr) { // while current is not a null pointer
                compares++; // increment compares it took to find hacker
                // if hacker found return success message
                if (curr->data == "neo") {
                    cout << "0: Trace Successful at Coordinates ("
                         << row << ", " << col << ") by "
                         << compares << " Compares...\n";
                    return;
                }
                col++;
                if (curr->right == nullptr) {
                    col = 0;
                    row++;
                    curr = temp = temp->down;
                } else {
                    curr = curr->right;
                }
            }
            cout << "0: Trace Failed.\n"; // print if curr is null ptr
        } else if (mode == 1) { // if mode is 1, RNG find the hacker
            int compares = 0;
            Node* curr = head; // starting at the head
            while (compares < 10000 && curr != nullptr) {
                compares++;
                // if hacker found return success message
                if (curr->data == "neo") {
                    cout << "\n1: Trace Successful by " 
                         << compares << " Compares...\n";
                    return;
                }
                curr = RNGdirection(curr); // call RNG direction function
            }
            cout << "\n1: Trace Failed.\n";
        }
    }
    // RNG direction function is a randomly
    // generated move to find a way to "neo"
    Node* RNGdirection (Node *curr) {
        Node* newCurr = nullptr;
        // print out which one RNG took and we can see it
        int direction = rand() % 4; //0,1,2,3 (up,down,left,right)
        switch (direction) {
            case 0: cout << "u,"; //up
            newCurr = curr->up;
            break;
            case 1: cout << "d,"; //down
            newCurr = curr->down;
            break;
            case 2: cout << "l,"; //left
            newCurr = curr->left;
            break;
            case 3: cout << "r,"; //right
            newCurr = curr->right;
            break;
        }
        if(!newCurr) return RNGdirection(curr);
        return newCurr;
    }
};