#include "main.h"
#include <fstream>

int main()
{
    input_medicine_information();
    input_random_number_table();
    while (Task_vector.size() > 0)
    {
        set_group(collect_groupnum_time());
    }

    for (int i = 0; i < Medicine_groups.size(); ++i)
    {
        /*
        for (int j = 0; j < (Medicine_groups[i].medicine_group).size(); ++j)
        {
            //cout << Medicine_groups[i].medicine_group[j].ID << endl;
        }
        printf("%d %d\n", Medicine_groups[i].drink_time, (Medicine_groups[i].medicine_group).size());
        */
        hyper_period = LCM(hyper_period, Medicine_groups[i].drink_time);
    }
    //printf("hyper_period %d\n", hyper_period);

    start_schedule();

    return 0;
}

void input_medicine_information()
{
    freopen("medicine_input.txt", "r", stdin); //set a input.txt as the stdin
    cin >> medicine_num;                       //read medicine number

    for (int i = 0; i < medicine_num; ++i)
    {
        Task task;
        cin >> task.ID;
        //cout << task.ID << endl;

        cin >> task.short_turn_time;
        task.short_turn_time *= 60; //change hour to minute

        cin >> task.long_turn_time;
        task.long_turn_time *= 60; //change hour to minute
        longest_turn_time = (longest_turn_time < task.long_turn_time) ? task.long_turn_time : longest_turn_time;

        task.time_interval = task.long_turn_time - task.short_turn_time;
        task.turn_time = task.short_turn_time;

        Task_vector.push_back(task);
    }
}

void input_random_number_table()
{
    //freopen("random_input.txt", "r", stdin); //set a input.txt as the stdin
    ifstream iFile("random_input.txt"); //read input file

    while (true)
    {
        int random_number;
        iFile >> random_number;
        if (iFile.eof())
            break;
        Random_table_vector.push_back(random_number);
    }
    //cout << "size of random" << Random_table_vector.size() << endl;
}

int collect_groupnum_time()
{
    int time_interval_start = -1;
    int time_interval_end = -1;
    int time_interval_end_flag = 0;
    max_group_num = -1;

    for (int i = 0; i <= longest_turn_time; ++i)
    {
        int num_of_group_contain_tasks_in_a_time = 0;
        for (int j = 0; j < Task_vector.size(); ++j)
        {
            if (i >= Task_vector[j].short_turn_time && i <= Task_vector[j].long_turn_time)
                ++num_of_group_contain_tasks_in_a_time;
        }
        if (max_group_num < num_of_group_contain_tasks_in_a_time)
        {
            max_group_num = num_of_group_contain_tasks_in_a_time;
            time_interval_start = i;
            time_interval_end_flag = 1;
        }
        if (max_group_num > num_of_group_contain_tasks_in_a_time && time_interval_end_flag)
        {
            time_interval_end = i;
            time_interval_end_flag = 0;
        }
    }

    if (time_interval_end_flag)
    {
        time_interval_end = longest_turn_time;
        time_interval_end_flag = 0;
    }

    return (time_interval_start + time_interval_end) / 2;
}

void set_group(int time)
{
    Medicine_group new_group;
    new_group.drink_time = time;
    new_group.drink_duration = time;
    //cout << time << endl;

    for (int i = 0; i < Task_vector.size(); ++i)
    {
        //cout << i << Task_vector[i].ID << endl;
        if (time >= Task_vector[i].short_turn_time && time <= Task_vector[i].long_turn_time)
        {
            (new_group.medicine_group).push_back(Task_vector[i]);
            Task_vector.erase(Task_vector.begin() + i);
            i = -1;
        }
    }

    Medicine_groups.push_back(new_group);
}

void start_schedule()
{
    int max_idle_time = 0;
    int before_medicine_time = 0;
    int hit_time = 0;
    int miss_time = 0;
    int take_medicine_time = 0;
    int take_medicine_flag = 0;

    for (int i = 0; i <= hyper_period; ++i)
    {
        for (int j = 0; j < Medicine_groups.size(); ++j)
        {
            if (Medicine_groups[j].drink_time == i)
            {

                max_idle_time = (max_idle_time < i - before_medicine_time) ? i - before_medicine_time : max_idle_time;

                Medicine_groups[j].drink_time += Medicine_groups[j].drink_duration;
                for (int k = 0; k < Medicine_groups[j].medicine_group.size(); ++k)
                {
                    cout << i / 60 << ":" << i % 60 << " task medicine " << Medicine_groups[j].medicine_group[k].ID << " before " << Medicine_groups[j].medicine_group[k].short_turn_time << " after " << Medicine_groups[j].medicine_group[k].long_turn_time;

                    if (i + Random_table_vector[take_medicine_time] < Medicine_groups[j].medicine_group[k].short_turn_time || i + Random_table_vector[take_medicine_time] > Medicine_groups[j].medicine_group[k].long_turn_time)
                    {
                        ++miss_time;
                        cout << " miss at: " << i + Random_table_vector[take_medicine_time] << endl;
                    }
                    else
                    {
                        ++hit_time;
                        cout << " hit at: " << i + Random_table_vector[take_medicine_time] << endl;
                    }

                    Medicine_groups[j].medicine_group[k].short_turn_time = i + Medicine_groups[j].medicine_group[k].turn_time;
                    Medicine_groups[j].medicine_group[k].long_turn_time = i + Medicine_groups[j].medicine_group[k].turn_time + Medicine_groups[j].medicine_group[k].time_interval;
                }

                take_medicine_flag = 1;
                before_medicine_time = i;
            }
        }
        if (take_medicine_flag)
        {
            ++take_medicine_time;
            take_medicine_flag = 0;
        }
    }
    cout << "Average frequency of medicine-taking per day: " << (float)take_medicine_time * 1440 / (float)hyper_period << " time/day" << endl;
    cout << "Hit rate: " << (float)hit_time / (float)(miss_time + hit_time) << endl;
    cout << "max_idle_time: " << max_idle_time << endl;
}