#include <iostream>
#include <string.h>
#include "ToDoList.h"

using namespace std;

//--------------------------------------------
// Function: ToDoList()
// Purpose: Class constructor
// Returns: N/A
//--------------------------------------------
ToDoList::ToDoList()
{
    head = NULL;
}

//--------------------------------------------
// Function: ToDoList()
// Purpose: Class constructor. Initialize list
//        and add first item.
// Returns: N/A
//--------------------------------------------
ToDoList::ToDoList( const char *task, int priority)
{
    ToDoItem    *newNode;

    head = NULL; // Initialize head to null
    // Create a new ToDoItem structure
    newNode = new ToDoItem();
    // Insert data
    newNode->priority = priority;
    strcpy(newNode->theTask, task);
    newNode->next = NULL;
    // Call one of the Insert functions to insert it
    Insert(newNode);

}

//--------------------------------------------
// Function: ~ToDoList()
// Purpose: Class destructor
// Returns: N/A
//--------------------------------------------
ToDoList::~ToDoList()
{
    ClearList();  // Delete all items currently in the list
}


//--------------------------------------------
// Function: ClearList()
// Purpose: Remove all items from the list
// Returns: void
//--------------------------------------------
void ToDoList::ClearList()
{
    ToDoItem *temp;
    // Run down the list and delete all items in the
    //    list to prevent any memory leaks.
    temp = head;
    while(temp != NULL)
    {
        head = head->next; // Advance head
        delete temp;    // Free node temp points to
        temp = head;    // Set temp to current head
    }
}

//--------------------------------------------
// Function: Insert()
// Purpose: Insert a task into the list in
//        the correct order.
// Args: The task to insert and its priority
// Returns: void
//--------------------------------------------
void ToDoList::Insert(string *task, int priority)
{
    ToDoItem *newNode;

    // Create a new ToDoItem structure
    newNode = new ToDoItem();
    // Insert data
    newNode->priority = priority;
    strcpy(newNode->theTask, task);
    newNode->next = NULL;

    // Take the easy way out and call the other Insert()
    //  function to insert this node
    Insert(newNode);
}

//--------------------------------------------
// Function: Insert()
// Purpose: Insert a task into the list in
//        the correct order.
// Args: Pointer to the node to insert
// Returns: void
//--------------------------------------------
void ToDoList::Insert(ToDoItem *newNode)
{
    ToDoItem *back, *temp;


    // Check for inserting new task as first in empty list
    if(head == NULL)
    {
        head = newNode;
        return;
    }

    // Search for place to insert the new task
    back = NULL;
    temp = head;
    while((temp != NULL) && (temp->priority < newNode->priority))
    {
        back = temp;
        temp = temp->next;
    }

    // Check for inserting at first of an existing list
    if(back == NULL)
    {
        newNode->next = head;
        head = newNode;
        return;
    }
    else // Insert in middle or at end of list
    {
        newNode->next = temp;
        back->next = newNode;
    }
}

//--------------------------------------------
// Function: Delete()
// Purpose: Delete a task from the list given
//    its priority.  Assumes priority is unique.
// Returns: void
//--------------------------------------------
void ToDoList::Delete(int priority)
{
    ToDoItem *back, *temp;

    if(isEmpty()) return; // nothing to delete

    // Search for the item to delete
    back = NULL;
    temp = head;

    while((temp != NULL) && (temp->priority != priority))
    {
        back = temp;
        temp = temp->next;
    }

    if(back == NULL)    // Delete the first item in the list
    {
        head = temp->next;
        delete temp;
    }
    else if(temp != NULL)  // Delete from middle or end of list
    {
        back->next = temp->next;
        delete temp;
    }
    else
    {
        return;    // Didn't find the item to delete
    }

}

//--------------------------------------------
// Function: Delete()
// Purpose: Delete a task from the list given
//        the task string.  Not the usual way to
//        do this.
// Arg: The task to delete
// Returns: void
//--------------------------------------------
void ToDoList::Delete( const char *task)
{
    ToDoItem *back, *temp;

    if(isEmpty()) return; // nothing to delete

    // Search for the item to delete
    back = NULL;
    temp = head;

    // Search for the node containing the task string to delete
    while((temp != NULL) && (strcmp(temp->theTask, task) != 0))
    {
        back = temp;
        temp = temp->next;
    }

    if(back == NULL)    // Delete the first item in the list
    {
        head = temp->next;
        delete temp;
    }
    else if(temp != NULL)  // Delete from middle or end of list
    {
        back->next = temp->next;
        delete temp;
    }
    else
    {
        return;    // Didn't find the item to delete
    }
}


//--------------------------------------------
// Function: Search()
// Purpose: Search for a task by priority and
//    return a copy of the task string.
// 
// Returns: Char pointer pointing to a new
//    string 
//--------------------------------------------
char *ToDoList::Search(int priority)
{
    ToDoItem *temp;
    char     *retVal;

    temp = head;
    while((temp != NULL) && (temp->priority != priority))
    {
        temp = temp->next;
    }
    // At this point temp will point to the item or NULL
    if(temp == NULL)
        return (char *)NULL;    // Return NULL pointer to char
    else
    {
        // Allocate memory for a new character array
        retVal = new char[strlen(temp->theTask) + 1];
        

        // Copy the task string into the new array
        strcpy(retVal, temp->theTask);
        return retVal;
    }
}

//--------------------------------------------
// Function: ListLength()
// Purpose: Return the number of items in the 
//        list.
// Returns: Number of items in list
//--------------------------------------------
int ToDoList::ListLength()
{
    ToDoItem *temp;
    int      count = 0;
    
    // Count the items
    temp = head;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

//--------------------------------------------
// Function: isEmpty()
// Purpose: Return true if the list is empty
// Returns: True if empty, otherwise false
//--------------------------------------------
bool ToDoList::isEmpty()
{
    return (head == NULL);
}


//--------------------------------------------
// Function: GetNextTask()
// Purpose: Return the task string of the task
//    at the head of the list.  The task is 
//    automatically removed from the list.
//  Note the dynamic creation of a string.
// Returns: Char pointer pointing to a new
//    string containing a copy of the task.
//--------------------------------------------
char *ToDoList::GetNextTask()
{
    char *returnStr;

    // Copy the task
    if(isEmpty())
    {
        return NULL;
    }
    else
    {
        returnStr = new char[strlen(head->theTask) + 1];
        strcpy(returnStr, head->theTask);
        // Delete the item at the head
        Delete(head->priority);
        return returnStr;
    }
}

//--------------------------------------------
// Function: PrintList()
// Purpose: Print all tasks in the list with
//    their priority.
// Returns: void
//--------------------------------------------
void ToDoList::PrintList()
{
    ToDoItem *temp;

    cout << "\n\nTasks in the List\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Priority\t\tTask\n";
    cout << "-----------------------------------------------------------\n";

    temp = head;
    while(temp != NULL)
    {
        cout << temp->priority << "\t\t" << temp->theTask << "\n";
        temp = temp->next;
    }
    cout << "-----------------------------------------------------------\n\n";
}



int main()
{
    ToDoList *theList;

    cout << "Simple List Demonstration\n";
 string *task;
int priority;
string mytask;
    theList = new ToDoList();
    cout<<"\nenter a task and p";
    cin>>mytask;
    cin>>priority;
    task=&mytask;
    
    
theList->Insert(task,priority);
    theList->Insert("This is task 1", 5);
    theList->Insert("This is task 2", 1);
    theList->Insert("This is task 3", 3);
    
    // Show what is in the list
    theList->PrintList();

    // Test the list length function
    int m=theList->ListLength();
    cout << "\nList now contains " << m << " items.\n\n";

    // Test delete function 1
    cout << "Testing delete function 1(using task name).\n";
    theList->Delete("This is task 3");
    theList->PrintList();
    // Test delete function 2
    cout << "Testing delete function 2(using priority).\n";
    theList->Delete(5);
    theList->PrintList();

   
    // Test search
    cout << "Testing Search function\n"<<"\n Searching for priority 1\n\n";
    cout << "Search result: " << theList->Search(1) << "\n\n";

    // Testing get next task
    cout << theList->GetNextTask();
    cout << "\n";
    
    cout << "\n\nEnd list demonstration...";

    return 0;
}

