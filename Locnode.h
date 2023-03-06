// locnode.h
#ifndef LOCNODE_H 
#define LOCNODE_H
#include "list-a.h" 
#include <sstream> 
#include <cmath>
// LocNode derived from Node
class LocNode : public Node
{
public:
    double x, y; // additional attributes
    // parameterized constructor to initialize the id, x, y and next fields
    LocNode(string id, double x, double y, Node *next = nullptr) : Node(id) // calls Node class constructor
    {
        // set x and y values
        this->x = x;
        this->y = y;
    }
    // overridden function to return string representation of LocNode
    virtual std::string to_string()
    {
        std::stringstream ss;
        // convert x and y to string
        ss << "x: " << x << " y: " << y;
        // use the string returned from Node's to_string function and return the string representation of LocNode
        class
            return "<" + Node::to_string() + " " + ss.str() + ">";
    }
    // function that returns true if this LocNode's distance from origin is less than rhs's distance from origin
    virtual bool lt(LocNode *rhs)
    {
        return distance() < rhs->distance();
    }

private:
    // helper function that returns the distance of this LocNode from origin
    double distance()
    {
        return sqrt(x * x + y * y);
    }
};
#endif

//for this to work i realized that I had to update the methods to take as input a Node* parameter which would attach to the node at the head and end.