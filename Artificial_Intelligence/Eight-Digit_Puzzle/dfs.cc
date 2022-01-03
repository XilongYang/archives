/*===================================
//DFS求解八数码问题
//作者:Vincent Jan
//==================================*/

#include <iostream>
#include <string>
#include <map>

using namespace std;

// 设置区域大小为n * n
const int area_size = 3;

// 基于问题规模求解解空间大小
int Infinity(int depth)
{
    if(depth <= 0) return 1;
    return depth * Infinity(depth - 1);
}
const int infinity = Infinity(area_size * area_size);

//设置最大搜索层数防止无限递归
const int max_depth = 30;

// 传入一个string和两个下标，交换对应元素的位置，返回处理后的string
// 不改变原string的值
string swap_elem(const string& origin, int pos1, int pos2);
void print_str(const string& str);

void DFS(const string& current_state, const string& target_state
    , map<string, bool>& is_arrived, map<string, int>& step_left
    , int depth, map<string, int>& minest_depth);

int main()
{
    cout << "Input origin state:" << endl;
    string origin_state;
    cin >> origin_state;
    cout << "Input target state:" << endl;
    string target_state;
    cin >> target_state;

    // 定义两个map保存搜索过程中的信息
    // is_arrived保存当前状态是否路过过
    // step_left表示当前状态距离终点的步数，提前定义非法走法的步数是无限
    map<string, bool> is_arrived;
    map<string, int> step_left;
    step_left["error"] = infinity;
    map<string, int> minest_depth;

    DFS(origin_state, target_state, is_arrived, step_left
        , 0, minest_depth);

    // 若解存在则输出，否则提示无解
    if(step_left[origin_state] == infinity)
    {
        cout << "Impossible move to target state" << endl;
    }
    else
    {
        // 输出一个空行以与输入分隔
        cout << endl;

        // 循环判定当前状态所能到达的状态中距终点最近的状态，直到抵达终点
        string cur_state = origin_state;
        while(step_left[cur_state] != 0)
        {
            // 找出0的位置
            int zero_pos = 0;
            while(zero_pos < cur_state.size() && cur_state[zero_pos] != '0')
            {
                ++zero_pos;
            }

            // 遍历上下左右寻找最优次状态
            int phase[4] = {area_size * -1, -1, 1, area_size};
            string min_state = swap_elem(cur_state, zero_pos, zero_pos + phase[0]);
            for(int i = 1; i < 4; ++i)
            {
                string possible_state = swap_elem(cur_state, zero_pos, zero_pos + phase[i]);
                if(possible_state == "error")
                {
                    continue;
                }
                if(step_left[possible_state] < step_left[min_state])
                {
                    min_state = std::move(possible_state);
                }
            }
            // 输出当前状态并转移到最优次状态
            print_str(cur_state);
            cur_state = min_state;
        }
        print_str(target_state);
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
    , map<string, bool>& is_arrived, map<string, int> &step_left
    , int depth, map<string, int>& minest_depth)
{

    if(current_state == target_state)
    {
        step_left[current_state] = 0;
        return;
    }
    // 默认当前状态无解，并且当层数超过限制时停止
    step_left[current_state] = infinity;
    if(depth > max_depth) return;
    is_arrived[current_state] = true;

    if(minest_depth.find(current_state) == minest_depth.end()
    || minest_depth[current_state] > depth)
    {
        minest_depth[current_state] = depth;
    }

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

        if(minest_depth.find(possible_state) == minest_depth.end())
        {
            minest_depth[possible_state] = depth + 1;
        }
        if(step_left.find(possible_state) == step_left.end() ||
            minest_depth[possible_state] > depth)
        {
            DFS(possible_state, target_state, is_arrived, step_left
                 , depth + 1, minest_depth);
        }
        if(step_left[possible_state] + 1 < step_left[current_state])
        {
            step_left[current_state] = step_left[possible_state] + 1;
        }
    } //for(i)

    // DFS的原理，退出当前状态时要将当前状态设为未访问
    is_arrived[current_state] = false;
}