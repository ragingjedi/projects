#include "iostream"
#include "vector"
using namespace std;


void mergeVectors()
{
        int totalElements = 0;
        int numVectors;
        int ele;
        vector<vector<int>> vectors;  //vector of vector to store vectors;
        vector<int> mergedVector;     //mergedVector will be created after merging all the vectors
        while (1)
        {
                cout << " Enter number of vectors :: ";
                cin >> numVectors;
                if (numVectors > 0)            /* check if numVectors entered by user is valid or not. greater than 0 is considered as valid input*/
                        break;
        }

        for (int i = 0; i < numVectors; i++)   /* traverse to ask for elements for every vector*/
        {
                vector<int> temp;
                cout << "\nEnter elements for vector " << i+1 << " :: ";
                while (1)
                {
                        cin >> ele;
                        if (ele < 0)           /* if element is less than 0 then there is a end for that vector*/
                                break;
                        temp.push_back(ele);   /* push element in vector*/
                        totalElements++;       /* increment totalelements by 1, it maintain total number of elements in all the vectors*/
                }
                vectors.push_back(temp);       /* push vector in vector of vectors*/
                temp.clear();
        }

        int j = 0;
        int count = 0;
        int elementInserted = 0;
        while (1)
        {
                for (int i = 0; i < numVectors; i++)     /* traverse for all vectors*/
                {
                        if (j < (vectors[i].size()))     /* if j is less than ith vector size then only insert element in merged vector*/       
                        {
                                elementInserted++;
                                mergedVector.push_back(vectors[i][j]);
                        }
                }
                j++;
                if (totalElements == elementInserted)    /* if number of elements inserted in merged vector is equal to total number of vectors then come out of loop*/
                        break;
        }
        
        cout << "\n The merged vector is :: ";
        for (auto it = mergedVector.begin(); it != mergedVector.end(); it++)  /* traverse and print merged vector*/
        {
                cout << *it << " ";
        }
}
int main()
{
        mergeVectors();
        return 0;
}