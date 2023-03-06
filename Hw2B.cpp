#include <iostream> 
#include "list-a.h"

int main() {
    List the_list;
    cout << "Input: " << endl;
    // inputs the list from the user
    cin >> the_list;
    cout << endl;
    cout << "Output : " << endl;
    // output the resultant list to the console
    cout << the_list << endl;
    the_list.reverse();
    // output the resultant list to the console
    cout << the_list << endl;
    return 0;

    cout << "has_id (14)" << endl;
    if (the_list.has_id("14"))
    {
        cout << " 14 is found in the list ";
    }
    else
    {
        cout << " 14 is not found in the list ";
    }
    return 0 ;
}
