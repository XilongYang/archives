/*===================================
//BFS求解八数码问题
//作者:Vincent Jan
//==================================*/

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>

using namespace std;

// 设置区域大小为n * n
const int area_size = 3;

// 传入一个string和两个下标，交换对应元素的位置，返回处理后的string
// 不改变原string的值
string swap_elem(const string& origin, int pos1, int pos2);
void print_str(const string& str);

int main()
{
    cout << "Input origin state:" << endl;
    string origin_state;
    cin >> origin_state;
    cout << "Input target state:" << endl;
    string target_state;
    cin >> target_state;

    //由于输出时是逆序输出， 交换两状态位置
    swap(origin_state, target_state);

    queue<string> state_queue;
    state_queue.push(origin_state);

    // 分别存储一个状态是否已到达过及其上一个状态
    map<string, bool> is_arrived;
    map<string, string> pre_state;

    bool no_answer = true;

    // BFS求解
    while(!state_queue.empty())
    {
        // 从队列中取出当前状态并标记为已到达
        string cur_state = state_queue.front();
        state_queue.pop();
        is_arrived[cur_state] = true;

        if(cur_state == target_state)
        {
            no_answer = false;

            print_str(cur_state);
            // 将可能状态回溯至初始状态，并逐步输出
            while(cur_state != origin_state)
            {
                print_str(pre_state[cur_state]);
                cur_state = pre_state[cur_state];
            }
            break;
        }

        // 找出当前状态中的空位
        int free_position = cur_state.find('0');

        // 对空位可能移到的4个方向分别讨论
        for(int i = 0; i < 4; ++i)
        {
            int phase[4] = {area_size * -1, -1, 1, area_size};
            string possible_state = swap_elem(cur_state, free_position
                , free_position + phase[i]);
            
            // 如果当前方向不可到达或已到达过，跳过判定
            if(possible_state == "error" || is_arrived[possible_state])
            {
                continue;
            }

            // 将当前状态记录为可能状态的上一个状态
            pre_state[possible_state] = cur_state;

            // 将可能状态压入待处理队列
            state_queue.push(possible_state);
        } //for(i)
    } //while(state_queue)

    if(no_answer)
    {
        cout << "There's no answer for the two states." << endl;
    }

    return 0;
}

string swap_elem(const string& origin, int pos1, int pos2)
{
    // 判定下标是否越界
    if(pos1 < 0 || pos2 < 0 || pos1 >= origin.length()
        || pos2 >= origin.length())
    {
        return move(string("error"));
    }
    // 判定下标是否符合移动规则
    if(pos1 / area_size != pos2 / area_size
        && pos1 % area_size != pos2 % area_size)
    {
        return move(string("error"));
    }
    string tmp = origin;
    swap(tmp[pos1], tmp[pos2]);
    return move(tmp);
}

void print_str(const string& str)
{
    static int num = 0;
    cout << num++ << endl;
    for(int i = 0; i < area_size * area_size; ++i)
    {
        cout << str[i] << ' ';
        if((i + 1) % area_size == 0 )
        {
            cout << endl;
        }
    }
    cout << endl;
}