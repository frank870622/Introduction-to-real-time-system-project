#include <iostream>
#include <vector>
using namespace std;

//Medicine class
class Task{
    public:
        int ID; // 藥物ID
        int short_turn_time;    //最短吃藥間隔時間 單位：分鐘
        int long_turn_time;     //最長吃藥間隔時間 單位：分鐘
        int turn_time;          //間隔時間 單位：分鐘
};

//vecter
vector<Task> Task_vector;           //vector of all medicine
vector<int>  Random_table_vector;   //vector of random table

//function
void input_medicine_information();              //input medicine information 單位：小時
void input_random_number_table();   //input random table 單位：分鐘

//variable
int medicine_num;

