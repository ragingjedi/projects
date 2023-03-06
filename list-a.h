#ifndef LIST_A_H
#define LIST_A_H
#include <iostream>
#include <string>

using namespace std;

class Node {
  public:
    std::string     id ;
    Node            *next ;
    Node ( std::string id , Node *next=nullptr ) {
        this->id = id ;
        this->next = next ;
    }
} ;

class List {
  public:
    Node    *head ;
    List() { head = nullptr ; }
    Node    *first() { return head ; }
    friend std::istream& operator>> ( std::istream& sin, List &lst ) ;
    friend std::ostream& operator<< (std::ostream& sout, List& lst); 
    void prepend(string id);
    void append(string id);
};

#endif
