#include <iostream>
using namespace std;

struct Tree
{
    string key;
    struct Tree *left, *right;
};

// made a function that will create a new Node with key as an item and return the same temp
struct Tree *newNode(string item)
{
    struct Tree *temp = (struct Tree *)malloc(sizeof(struct Tree));
    temp->key = item;  //sets the key as the item 
    temp->left = temp->right = NULL;
    return temp;
}
void inorder(struct Tree *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
struct Tree *insert(struct Tree *tree, string key)
{
    if (tree == NULL)
        return newNode(key);
    if (key < tree->key)
        tree->left = insert(tree->left, key);
    else if (key > tree->key)
        tree->right = insert(tree->right, key);
    return tree;
}

bool find(struct Tree * tree, string key)
{
    if (tree == NULL)
        return false;
    // Otherwise, its going to recur down the tree
    if (key < tree->key)
        return find(tree->left, key);
    else if (key > tree->key)
        return find(tree->right, key);
    return tree;
}

void postorder(struct Tree *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }
    if (Tree == NULL)
return newNode(key);
}

int maint (){

    struct Tree *root = NULL;
    string keys;
    while (cin >> keys)
    {
        if (keys == "EOF")
            break;
        root = insert(root, keys);
    }
    return 0;
}