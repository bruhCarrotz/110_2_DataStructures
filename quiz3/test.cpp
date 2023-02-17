#include <iostream>
#include <queue>
#include <string>
using namespace std;

priority_queue <int> pq;
vector<int> arr;

/*
void showpq(priority_queue<int> gq){
    while (!gq.empty()) {
        cout << gq.top() << ' ';
        gq.pop();
    }
    cout << '\n';
}
*/

int check_unreserved(priority_queue<int> gq, int room){
    for(int i=0 ; i<arr.size() ; i++){
        if(arr[i] == room) return 1;
        else return 0;
    }
}

void reserve(int room){
    if(room > pq.size()){
        cout << "RESERVE: no vacant rooms" << endl;
        return;
    }
    cout << "RESERVE: reserve room ";
    for(int i=0 ; i<room ; i++){
        int x = pq.top();
        arr.push_back(x);
        pq.pop();
        if(i != room-1){
            cout << x << ",";
        }
        else{
            cout << x;
        }
    }
    cout << endl;
}

void unreserve(int room1){
    if(check_unreserved(pq,room1) == 1){
        pq.push(room1);
        int x = pq.top();
        cout << "UNRESERVE: unreserved room " << room1 << endl;
    }
    else {
        cout << "UNRESERVE: " << room1 << " has not been reserved" << endl;
        return;
    }

}

int main(){
    string cmd;
    int n, m;
    cin >> n;
    for(int i=0 ; i<n ; i++){
        pq.push(i);
    }
    cin >> m;
    for(int i=0 ; i<m ; i++){
        cin >> cmd;
        if(cmd == "RESERVE"){
            int room;
            cin >> room;
            reserve(room);
        }
        else if(cmd == "UNRESERVE"){
            int rooms;
            cin >> rooms;
            unreserve(rooms);
        }
    }
    return 0;
}