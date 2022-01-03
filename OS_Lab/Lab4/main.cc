#include <iostream>
#include <string>
#include <deque>
#include <regex>

using namespace std;


struct Page {
    unsigned pageNum;
    bool exist;
    unsigned addr;
    bool modify;
    unsigned storageNum;
    static const unsigned pageSize = 1024;
};

deque<Page> pageTable= {
    Page{0, true, 0, false, 0},
    Page{1, true, 1, false, 1},
    Page{2, true, 2, false, 2},
    Page{3, false, 0, false, 3},
    Page{4, false, 0, false, 4},
    Page{5, false, 0, false, 5},
    Page{6, false, 0, false, 6},
    Page{7, false, 0, false, 7}
};

deque<Page> pageQueue= {
    Page{0, true, 0, false, 0},
    Page{1, true, 1, false, 1},
    Page{2, true, 2, false, 2}
};

void Swap(unsigned n);

int main() {
    string input;
    getline(cin, input);
    while(input != "0") {
        if(!regex_match(input, regex("[0-9]+"))) {
            cout << "Input error!" << endl;
            cin.get();
            continue;
        }
        int pageNum = stoi(input) / Page::pageSize;
        int pageAddr = stoi(input) % Page::pageSize;
        if(!pageTable[pageNum].exist) {
            Swap(pageNum);
        }
        int addr = pageTable[pageNum].addr * Page::pageSize + pageAddr;
        cout << addr << endl;
        getline(cin, input);
    }
    return 0;
}

void Swap(unsigned n) {
    auto originPage = pageQueue[0];
    pageQueue.pop_front();
    for(auto& i : pageTable) {
        if(i.pageNum == originPage.pageNum) {
            i.exist = false;
        }
        if(i.pageNum == n) {
            i.exist = true;
            i.addr = originPage.addr;
            pageQueue.push_back(i);
        }
    }
}
