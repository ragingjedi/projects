#include "list-a.h"
// overloading >> to take list as input
istream &operator>>(istream &sin, List &lst)
{
    Node *tmp; // to store the node 
    string id;
    sin >> id; // take node data as input
    while (sin)
    {
        tmp = new Node(id, lst.head);
        lst.head = tmp;
        sin >> id;
    }
    // return istream object reference
    return sin;
}
// overloading << to print the list
ostream &operator<<(ostream &sout, List &lst)
{
    string list_str = "["; // print the bracket
    Node *curr = lst.head;
    // print the elements
    while ((curr != nullptr) && (curr->next != nullptr))
    {
        list_str += (curr->id + ", ");
        curr = curr->next;
    }
    // add the last node if (curr)
    list_str += curr->id;
    list_str += "]";
    sout << list_str << endl; // return the stream object
    return sout;
}
// method to add a node to the front
void List::prepend(string id)
{
    Node *newNode = new Node(id); // create a new Node
    newNode->next = head;         // set the links
    head = newNode;               // set the head
}
// method to add a node to the end
void List::append(string id)
{
    Node *newNode = new Node(id); // if list is empty
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    // add the node to the end of the list
    Node *curr = head;
    // go to the last node
    while (curr->next)
        curr = curr->next; // change the links
    curr->next = newNode;
}