#include "main.h"

int main(){
    //input_medicine_information();
    //input_random_number_table();

    return 0;
}

void input_medicine_information(){
    freopen("medicine_input.txt", "r", stdin); //set a input.xt as the stdin
    cin >> medicine_num;                       //read medicine number

    for(int i=0; i<medicine_num; ++i){
        Task task;
        cin >> task.ID;

        cin >> task.short_turn_time;
        task.short_turn_time *= 60;     //change hour to minute

        cin >> task.long_turn_time;
        task.long_turn_time *= 60;      //change hour to minute

        task.turn_time = task.long_turn_time - task.short_turn_time;

        Task_vector.push_back(task);
    }
}

void input_random_number_table(){
    freopen("medicine_input.txt", "r", stdin); //set a input.xt as the stdin

    int random_number;
    while(cin >> random_number){               //read random table until eof
        Random_table_vector.push_back(random_number);
    }

}
