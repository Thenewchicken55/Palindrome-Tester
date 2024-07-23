// palindromei.cpp -- iterative palindrome tester
// c. 2015 A. Deeter

#include "PalindromeI.hpp"
#include <string.h>

class Stack
{
private:
    // StackNode is a node of a stack and holds data and a pointer to the next node in the stack
    struct StackNode
    {
        char value;
        StackNode *next;
    };

    int stackSize; // Number of elements in the stack
    StackNode *top_ptr; // Pointer to the top of the stack
public:
    // Constructor
    Stack() : stackSize(0), top_ptr(nullptr) {}

    // Copy constructor
    Stack(const Stack &obj)
    {
        // empty the stack so that you can copy information from obj into this stack
        while (!isEmpty())
        {
            pop();
        }
        // if the object is empty, then there is nothing to copy
        if (obj.top_ptr == nullptr)
            return;
        else
        {
            StackNode *temp = obj.top_ptr;
            StackNode *end = new StackNode;
            end->value = temp->value;
            top_ptr = end;
            // copy the rest of the stack by creating a new node and copying the data
            while (temp != nullptr)
            {
                end->next = new StackNode;
                end = end->next;
                end->value = temp->value;
                temp = temp->next;
            }
            end->next = nullptr;
            stackSize = obj.stackSize;
        }
    }

    // Destructor
    ~Stack()
    {
        StackNode *nodePtr;
        StackNode *nextNode;
        nodePtr = top_ptr;
        // iterate node by node deleting the nodes while using nextNode to store the next node to be able to access it
        while (nodePtr != nullptr) {
            nextNode = nodePtr->next;
            delete nodePtr;
            nodePtr = nextNode;
        }
    }

    // prepend operation
    void push(char value)
    {
        /*
        If the stack is empty, top_ptr will be null. So temp->next will also be set to null,
        and then top_ptr is updated to point to temp, which adds the first node.

        If the stack already has nodes, top_ptr will point to the existing top node.
        temp->next will be set to that existing top node, linking the new node in.
        Then top_ptr is updated to point to the new node temp, pushing it onto the top of the stack.
        */
        StackNode *temp = new StackNode;
        temp->value = value;
        temp->next = top_ptr;
        top_ptr = temp;
        stackSize++;
    }

    char pop()
    {
        if (isEmpty())
        {
            throw "Stack is empty\n";
        }
        char value = top_ptr->value;
        // you need a temp variable to be able to release the memory of the node you are popping
        StackNode *temp = top_ptr;
        top_ptr = top_ptr->next;
        delete temp;
        stackSize--;
        return value;
    }

    char top() const
    {
        if (isEmpty())
        {
            throw "Stack is empty\n";
        }
        return top_ptr->value;
    }

    bool isEmpty() const
    {
        return (top_ptr == nullptr);
    }
};

class Queue
{
public:
    char *queueArray;
    int queueSize;
    int frontIndex;
    int rearIndex;
    int numItems;

    // Constructor, note you need to set the indecies to 0 instead of
    // -1 because when you first use the queue, you will need to access the index 0.
    Queue(int size) : queueArray(new char[size]), queueSize(size),
        frontIndex(0), rearIndex(0), numItems(0) {}

    // Copy constructor
    Queue(const Queue &obj)
    {
        // Allocate the queue array.
        if (obj.queueSize > 0) {
            // temp is used to delete the old queue array.
            char *temp = queueArray;
            queueArray = new char[obj.queueSize];
            delete [] temp;
            temp = nullptr;
        }
        else // queue is empty, so queueArray is already null.
        {
            queueArray = nullptr;
            return;
        }
        // Copy the queue array.
        queueSize = obj.queueSize;
        for (int i = obj.frontIndex; i < obj.rearIndex; ++i)
        {
            enqueue(obj.queueArray[i]);
        }
    }

    // Destructor
    ~Queue()
    {
        while(!isEmpty())
            dequeue();

        delete[] queueArray;

        queueArray = nullptr;
    }

    void enqueue(char value)
    {
        if (numItems >= queueSize)
        {
            throw "Queue is full\n";
        }
        queueArray[rearIndex] = value;
        rearIndex = (rearIndex + 1) % queueSize; // wrap around if you reach the end of the queue
        ++numItems;
        }

    char dequeue()
    {
        if (isEmpty())
        {
            throw "Queue is empty\n";
        }
        char value = queueArray[frontIndex];
        frontIndex = (frontIndex + 1) % queueSize; // wrap around if you reach the end of the queue
        --numItems;
        return value;
    }

    char front() const
    {
        if (isEmpty())
        {
            throw "Queue is empty\n";
        }
        return queueArray[frontIndex];
    }

    bool isEmpty() const
    {
        return (numItems == 0);
    }

    int getSize() const
    {
        return numItems;
    }
};

// returns true if char c is a letter or a number; false otherwise
bool isAlphanumeric(char c) {
	std::string alphanumericCharacters = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return (alphanumericCharacters.find(c) != std::string::npos);
}

// returns -1 if the string is a palindrome; otherwise returns the
// number of matches before it begins to mismatch
int PalindromeI::test_string(const std::string &s)
{
    int countMatches = 0;
    Stack stack;
    Queue queue(s.length());
    for (int i = 0; i < s.length(); ++i) {
        if (isAlphanumeric(s[i])) {
            stack.push(toupper(s[i]));
            queue.enqueue(toupper(s[i]));
        }
    }
    while (!queue.isEmpty()) {
        if (stack.pop() == queue.dequeue()) {
            ++countMatches;
        }
        else {
            return countMatches;
        }
    }
    return -1;
}

