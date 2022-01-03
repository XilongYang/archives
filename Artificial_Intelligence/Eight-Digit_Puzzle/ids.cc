/*===================================
//IDS求解八数码问题
//作者:Vincent Jan
//==================================*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// 设置区域大小为n * n
const int area_size = 3;

// 传入一个string和两个下标，交换对应元素的位置，返回处理后的string
// 不改变原string的值
string swap_elem(const string& origin, int pos1, int pos2);
void print_str(const string& str);

void DFS(const string& current_state, const string& target_state
    , map<string, bool>& is_arrived, bool& is_found, int depth
    , const int& max_depth);

int main()
{
    cout << "Input origin state:" << endl;
    string origin_state;
    cin >> origin_state;
    cout << "Input target state:" << endl;
    string target_state;
    cin >> target_state;

    // 逆序输出， 交换位置
    swap(target_state, origin_state);

    // 定义两个map保存搜索过程中的信息
    // is_arrived保存当前状态是否路过过
    // step_left表示当前状态距离终点的步数，提前定义非法走法的步数是无限
    map<string, bool> is_arrived;
    bool is_found = false;
    int max_depth = 0;

    while(!is_found)
    {
        DFS(origin_state, target_state, is_arrived, is_found
            , 1, max_depth);
        ++max_depth;
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

void DFS(const string& current_state, const string& target_state
    , map<string, bool>& is_arrived, bool& is_found, int depth
    , const int& max_depth)
{

    if(current_state == target_state)
    {
        is_found = true;
        print_str(target_state);
        return;
    }

    if(depth > max_depth) return;
    is_arrived[current_state] = true;

    // 查找0的位置
    int zero_pos = current_state.find('0');

    // 在四个方向上求最优解
    int phase[4] = {area_size * -1, -1, 1, area_size};
    for(int i = 0; i < 4; ++i)
    {
        string possible_state = swap_elem(current_state, zero_pos, zero_pos + phase[i]);

        if(possible_state == "error" || is_arrived[possible_state])
        {
            continue;
        }

        if(!is_found) 
        {
            DFS(possible_state, target_state, is_arrived, is_found
                , depth + 1, max_depth);
        }
    } //for(i)

    if(is_found)
    {
        print_str(current_state);
    }

    // DFS的原理，退出当前状态时要将当前状态设为未访问
    is_arrived[current_state] = false;
}