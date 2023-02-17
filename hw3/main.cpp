#include <iostream>
#include <string>
#include "function.h"

using namespace std;

int main(){
    Manager<Node> taskManager = Manager<Node>();
    int cmdCnt = 0;
    string command;
    cin >> cmdCnt;
    for(int j=0;j<cmdCnt;j++){
        cin >> command;
        if(command == "SET_ENDTIME"){
            u32 endTime;
            cin >> endTime;
            taskManager.cmd_set_endTime(endTime);
        }
        else if(command == "ADD_TA"){
            std::string id;
            u32 begin;
            cin >> id >> begin;
            taskManager.cmd_add_ta(id,begin);
        }
        else if(command == "ADD_TASK"){
            std::string taskName;
            u32 costTime;
            cin >> taskName >> costTime;
            taskManager.cmd_add_task(taskName,costTime);
        }
        else if(command == "CHECK_SCHEDULE"){
            u32 costTime, endTime;
            cin >> costTime >> endTime;
            taskManager.cmd_check_schedule(costTime,endTime);
        }
    }
    taskManager.result();
    return 0;
}