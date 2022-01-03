/*===================================
//A*求解八数码问题
//作者:Vincent Jan
//==================================*/

#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

// 设置区域大小为n * n
const int area_size = 3;

// 维护映射保存状态深度
map<string, int> depth;

// 传入一个string和两个下标，交换对应元素的位置，返回处理后的string
// 不改变原string的值
string swap_elem(const string& origin, int pos1, int pos2);

void print_str(const string& str);

int G(const string& cur);

int NotInPlace(const string&, const string&);
int DistanceSum(const string&, const string&);
int (*const H[2])(const string& cur, const string& target)
    = {NotInPlace, DistanceSum};

int main()
{
    cout << "Input origin state:" << endl;
    string origin_state;
    cin >> origin_state;
    cout << "Input target state:" << endl;
    string target_state;
    cin >> target_state;

    swap(origin_state, target_state);

    auto F = [target_state](const string& cur)
    {
        return G(cur) + H[1](cur, target_state);
    };

    auto compare = [F](const string& str1, const string& str2)
    {
        return F(str1) < F(str2);
    };

    multiset<string, decltype(compare)> open(compare);
    open.insert(origin_state);
    set<string> closed;

    map<string, string> pre_state;

    while(!open.empty())
    {
        string cur_state = *open.begin();
        open.erase(open.begin());
        closed.insert(cur_state);

        if(cur_state == target_state)
        {
            print_str(cur_state);
            while(cur_state != origin_state)
            {
                cur_state = pre_state[cur_state];
                print_str(cur_state);
            }
            break;
        }

        int zero_pos = cur_state.find('0');

        int phase[4] = {area_size * -1, -1, 1, area_size};
        for(int i = 0; i < 4; ++i)
        {
            string possible_state = swap_elem(cur_state
                , zero_pos, zero_pos + phase[i]);
            
            if(possible_state == "error" 
                || closed.find(possible_state) != closed.end())
            {
                continue;
            }

            depth[possible_state] = depth[cur_state] + 1;
            pre_state[possible_state] = cur_state;
            open.insert(possible_state);
        }
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

int G(const string& cur)
{
    return depth[cur];
}

int NotInPlace(const string& cur, const string& target)
{
    int result = 0;
    for(int i = 0; i < area_size * area_size; ++i)
    {
        if(cur[i] != target[i])
        {
            ++result;
        }
    }
    return result;
}

int DistanceSum(const string& cur, const string& target)
{
    const string nums("012345678");
    int result = 0;
    for(const auto &c : nums)
    {
        int pos_cur = cur.find(c);
        int pos_target = target.find(c);
        int row_diff = pos_cur / area_size - pos_target / area_size;
        int col_diff = pos_cur % area_size - pos_target % area_size;
        if(row_diff < 0)
        {
            row_diff *= -1;
        }
        if(col_diff < 0)
        {
            col_diff *= -1;
        }
        result += row_diff + col_diff;
    }
    return result;
}