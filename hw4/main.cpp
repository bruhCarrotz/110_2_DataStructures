#include <iostream>
#include <bits/stdc++.h>
#include <climits>
#include <cmath>
using namespace std;

class Node{
    private:
        int id, ps, condition;
        string name;
    public: 
        Node(int _id, string _name, int _ps, int _condition){
            this->id = _id;
            this->ps = _ps;
            this->name = _name;
            this->condition = _condition; //0 = close ; 1 = open
        }
        int get_id(){
            return id;
        }
        string get_name(){
            return name;
        }
        int get_ps(){
            return ps;
        }
        int get_condition(){
            return condition;
        }

        void set_condition(int x){
            this->condition = x;
        }
};

vector<pair<Node, pair<int, double>>> matrix[100];
vector<Node> places;
//vector<string> to_close;
//vector<string> to_open;

int dis[100000];
bool vis[100000];
long long path[100010];

int start_point;

void reset(){
    for(int i=0 ; i<10000;i++){
        dis[i] = 2147483647;
        path[i] = 2147483647; 
        vis[i] = false;
    }
}

void create_origin(string target){
    bool flag = false;
    for(auto i : places){
        if(i.get_name() == target && i.get_condition() == 1){ // 1 meaning open
            start_point = i.get_id();
            flag = true;
            cout << i.get_name() << " is the new origin" << endl;
            return;
        }
    }
    if(flag == false)
        cout << "Fail to set the origin" << endl;
}

void dijsktra(string mode, string destination, int source){
    
    reset();

    queue<pair<int,int>> q;
    dis[source] = 0;

    q.push({dis[source], source});

    while(!q.empty()){
        // Pop least distance element from the queue
        pair<int,int> p = q.front();
        q.pop();

        // If it is always processed then continue;
        if(vis[p.second]) continue;

        // Mark it processed that means now it have minimum possible distance
        vis[p.second] = true;

        int distance = p.first;
        int y = p.second;

        if(mode == "FLOW"){
            for(int i=0 ; i<matrix[y].size() ; i++)
            {
                if(vis[matrix[y][i].first.get_id()]) continue;
                if(dis[matrix[y][i].first.get_id()] > distance + matrix[y][i].second.first){
                    dis[matrix[y][i].first.get_id()] = distance + matrix[y][i].second.first;
                    q.push({dis[matrix[y][i].first.get_id()], matrix[y][i].first.get_id()});
                    path[matrix[y][i].first.get_id()] = y;
                }
            }
        }
        if(mode == "TIME"){
            for(int i=0 ; i<matrix[y].size() ; i++)
            {
                if(vis[matrix[y][i].first.get_id()]) continue;
                if(dis[matrix[y][i].first.get_id()] > distance + abs(log2(matrix[y][i].second.second))){
                    dis[matrix[y][i].first.get_id()] = distance + abs(log2(matrix[y][i].second.second));
                    q.push({dis[matrix[y][i].first.get_id()], matrix[y][i].first.get_id()});
                    path[matrix[y][i].first.get_id()] = y;
                }
            }
        }
    }

    vector<int> ans;
    for(auto i : places){
        if(i.get_name() == destination){
            int n;
            n = i.get_id();
            while(n != source){
                ans.push_back(n);
                n = path[n];
            }
            break;
        }
    }

    ans.push_back(source);
    cout << "Optimal " << mode << " : ";
    for(int i=ans.size()-1 ; i>=0 ; i--){
        if(i==0){
            cout << places[ans[i]].get_name() << endl;
        }
        else cout << places[ans[i]].get_name() << " -> ";
    }
}

void mark_state(int cond, string place){
    for(auto i : places){
        if(i.get_name() == place){
            i.set_condition(cond);
        }
        if(i.get_id() == start_point){ // cannot close origin
            cout << "Fail to close " << place << endl;
        }
    }
    cout << "Fail to open " << place << endl;
}

void limited_path(){

}

int main(){
    int num;
    cin >> num;
    
    for(int i=0 ; i<num ; i++){
        int index, score;
        string place_name;
        cin >> index >> place_name >> score;

        Node vertex(index, place_name, score, 1); // 1 meaning open
        places.push_back(vertex);
    }

    for(int i=0 ; i<num ; i++){ //taking adjacency list
        for(int j=0 ; j<num ; j++){
            int weight;
            cin >> weight;
            if(weight != 0){
                matrix[i].push_back(make_pair(places[j], make_pair(weight, 0.0)));
            }
        }
    }

    cin.ignore();

    for(int i=0; i<num; i++){ //taking tourist preference score
        for(int j=0; j<num; j++){
            double weight;
            cin >> weight;
            matrix[i][j].second.second = weight;
        }
    } 
    
    string command;
    while(true){
        cin >> command;
        if(command == "SET_ORIGIN"){
            string place1;
            cin >> place1;
            create_origin(place1);
        }
        else if(command == "MARK_STATE"){
            string cond, place2;
            cin >> cond;
            for(int i=0 ; i!=num-1 ; i++){
                if(cond == "OPEN"){
                    cin >> place2;
                    mark_state(1, place2);
                }
                else if(cond == "CLOSE") {
                    mark_state(0, place2);
                }
            }

        }
        else if(command == "OPTIMAL_PATH"){
            string place3, cond1;
            cin >> place3 >> cond1;

            for(auto i : places){
                if(i.get_name() == place3 && cond1 == "TIME"){
                    dijsktra(cond1, place3, start_point);
                }
                else if(i.get_name() == place3 && cond1 == "FLOW"){
                    dijsktra(cond1, place3, start_point);
                }
            }
        }
        else if(command == "LIMITED_PATH"){
            string place4, consideration;
            int max;
            cin >> place4 >> consideration >> max;
            limited_path(); 
        }
        else if(command == "END_OF_INSTRUCTION"){
            cout << "Stop receiving instruction" << endl;
            break;
        }
    }
    return 0;
}