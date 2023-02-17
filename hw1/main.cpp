#include <iostream>
#include <string>
#include "function.h"

using namespace std;

int main()
{

    int W, H, M;
    int col;
    string command;
    cin >> W >> H;
    cin >> M;
    
    InitialzeStage(W, H);

    for (int i=0; i<M; i++){
        cin >> command;
        if(command == "SHOOT"){
            cin >> col;
            ShootNormal(col, W);
        }
        else if(command == "SPECIAL"){
            cin >> col;
            ShootSpecial(col, W);
        }
        else if(command == "FRONT_ROW"){
            FrontRow(W);
        }
    }
    ShowResult(W);
    deleteStage();
    
    return 0;
}
