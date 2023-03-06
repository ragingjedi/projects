#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int func(string arr,int n)
{
multiset<int> myset; 
myset.insert(arr[0]); 

int count = 0; 

multiset<int>::iterator x;
for (int i=1; i<n; i++)
{
myset.insert(arr[i]);

x= myset.upper_bound(arr[i]); 


count += distance(x, myset.end());
}

return count;
}

int main() {
int t;
cin>>t;
vector<string>v;
while(t--)
{
string s;
cin>>s;
v.push_back(s);

}
for(int i=0;i<v.size();i++)
{
int n=v[i].length();
cout<<"The Sequence has "<<func(v[i],n)<<" inversions"<<endl;
}
return 0;
}