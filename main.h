#include <iostream>
#include <vector>
using namespace std;

//Medicine class
class Task{
    public:
        int ID; // 藥物ID
        int short_turn_time;    //下一次最短吃藥時間 單位：分鐘
        int long_turn_time;     //下一次最長吃藥時間 單位：分鐘
        int time_interval;      //可以吃藥的時間長度
        int turn_time;          //吃完等待時間 單位：分鐘
};

class Medicine_group{
    public:
        int drink_time;                 //下一次服藥時間
        int drink_duration;             //服藥間隔
        vector<Task> medicine_group;    //group of some medicine
};

//vecter
vector<Task> Task_vector;           //vector of all medicine
vector<int>  Random_table_vector;   //vector of random table
vector<Medicine_group> Medicine_groups; //vector of all group of medicine

//function
void input_medicine_information();              //input medicine information 單位：小時
void input_random_number_table();   //input random table 單位：分鐘
int collect_groupnum_time();
void set_group(int);
void start_schedule();

//variable
int medicine_num;           //number of medicine need to schedule
int longest_turn_time = -1; //longest [long_turn_time] of Task
int max_group_num = -1;
int hyper_period = 1;       //中止條件


//function to find greatest common divisor
template <typename T>
T GCD(T a, T b)
{
    if (b)
        while ((a %= b) && (b %= a))
            ;
    return a + b;
}
//function to find least common multiple
template <typename T>
T LCM(T a, T b)
{
    return a * b / GCD(a, b);
}



