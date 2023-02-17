#include <iostream>
#include <cstring>
using namespace std;

int main(){
    char str[1000];
    cin.getline(str,1000);

    char *pointer;
    pointer = strtok(str, " ");
    
    while(pointer != NULL){
        cout << pointer << "\n";
        pointer = strtok(NULL, " ");
    }

    return 0;
}