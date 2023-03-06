#include <iostream>

using namespace std;

//initializing a function called searchLength that is going to find the length of the tones where E-F-E is found
//will take parameters of the array of characters called tones which is specified when calling the function in the main function
int searchLength(char tones[]){

    int index1;
    int index2;
    int index3;
    for(int i = 0; i<(sizeof(tones) / sizeof(tones[0])); i++)
    {
        if(tones[i]== 'E')
        {
            index1 = i;
            for(int i2 = index1; i2<(sizeof(tones) / sizeof(tones[0])); i++){
                if(tones[i2] == 'F'){
                    index2 = i2;
                    for(int i3 = index2; i3<(sizeof(tones) / sizeof(tones[0])); i++){
                        if (tones[i3] == 'E'){
                            index3 = i3;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    int lengthtotal = index1 + index3;
    return lengthtotal;

}
//thought by doing a loop of it searching once it finds E then it goes to find F then it goes to find E again while taking note of the indexes for E and E and adding them together at the end


//Here i am trying to call the functon 
int main() {
    char tonesInput[] = {'A','E','A','F','A','E','A'};
    int totalLength = searchLength(tonesInput);
    if (totalLength >= 3){
        cout << "The length is: " << totalLength << endl;
    }
    else{
        cout << "999999" << endl;
    }
    return 0;
}