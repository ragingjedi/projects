#include <iostream>
#include <cmath>
#include <cctype>

using namespace std;

class hex 
{
    private:
    struct digit
    
    {
    char value;
    digit* link;
    };
    
    digit* head; // start of the linked list i.e points to most significant digit
    int count; // number of digits
    public:
    hex();
    void addDigit(char value);
    int convertToDecimal();
};

hex::hex() : head(NULL), count(0) // default constructor to create an empty list
{}

void hex::addDigit(char value) // function to add value at the end of list
{

digit* node = new digit; // creates a new node to store value
node->value = value;
node->link = NULL;

if(head == NULL) // empty list, set head to node
head = node;
else
{
digit* curr = head;
// loop to get the last node of the list
while(curr->link != NULL)
curr = curr->link;
curr->link = node; // make node the last node
}

count++; // increment count
}

// function to convert hexadecimal number to decimal
int hex::convertToDecimal()
{
int decimal = 0; // set decimal to 0
int pos = count-1; // set pos to count-1
digit* curr = head; // set curr to head node

// loop over the list
while(curr != NULL)
{
// multiply the value with the weight of digit and add it to decimal
if(curr->value >= '0' && curr->value <= '9')
decimal += ((int)(curr->value - '0'))*pow(16, pos);
else if(curr->value == 'A')
decimal += (int)(10*pow(16, pos));
else if(curr->value == 'B')
decimal += (int)(11*pow(16, pos));
else if(curr->value == 'C')
decimal += (int)(12*pow(16, pos));
else if(curr->value == 'D')
decimal += (int)(13*pow(16, pos));
else if(curr->value == 'E')
decimal += (int)(14*pow(16, pos));
else
decimal += (int)(15*pow(16, pos));
curr = curr->link; // go to next node
pos--; // decrement pos
}

return decimal; // return decimal equivalent
}

int main()
{

// test the class
char value;
string input;
hex obj;

cout<<"Please enter the digits of the hexadecimal number one by one (-1 to end): "<<endl;
// loop to read digits of hexadecimal number and add to obj and end the loop when -1 is entered
do
{
cin>>input; // read the input
if(input.length() == 1) // if single character input is read
{
value = toupper(input[0]); // convert the first character to uppercase
// if value is valid, then add it to end of obj
if((value >= '0' && value <='9') || (value >= 'A' && value <='F'))
{
obj.addDigit(value);
}
}
}while(input != "-1");

cout<<"Decimal value: "<<obj.convertToDecimal()<<endl; // displays the decimal value of entered hexadecimal number

return 0;
}