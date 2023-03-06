#include <iostream>
#include <string>
#include "list-a.h"

int main(){
    List a_list; //this inputs the list from the user 
    cin >> a_list;
    a_list.prepend("HEAD");
    a_list.append("TAIL");

//this output the resultant list
cout << a_list << endl;
return 0;
}