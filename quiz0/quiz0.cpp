#include <iostream>
using namespace std;

int main(){
    int x, y, z;
    cin >> x >> y >> z;

    int jay, jolin, jj;
    jay = (x+z-y)/2;
    jolin = (y-z+x)/2;
    jj = (y+z-x)/2;

    cout << jay << " ";
    cout << jolin << " ";
    cout << jj;

    return 0;
}