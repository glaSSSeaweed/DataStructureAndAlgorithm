#include "HRD.h"




HRD::HRD() : row(3), col(3), board(std::vector<int>{1,0,2,3,4,5,6,7,8}),
    fin(Node("",0)) ,visited(std::map<std::string, int>()) {
    assert(row >= 2 && col >= 2);
    initBoard();
}
std::stack<int>* HRD::path(){
    int step = BFS();
    std::stack<int>* p = new std::stack<int>();
    std::string tmp = fin.s;
    int dir_tmp = fin.dir;
    p->push(8);
    while (step > 0) {
        int idx = 0;
        for (; tmp[idx] != '0'; idx++)
            ;
        int pos = idx;

        switch (dir_tmp)
        {
        case 1:pos += 3;break;
        case 2:pos += 1;break;
        case 3:pos -= 1;break;
        case 4:pos -= 3;break;
        default:break;
        }
        p->push(pos);
        std::swap(tmp[pos], tmp[idx]);
        tmp = visited.find(tmp)->first;
        dir_tmp = visited.find(tmp)->second;
        step--;
    }
    return p;
}
void HRD::print() {
    int step = BFS();
    std::string tmp = fin.s;
    int dir_tmp = fin.dir;
    while (step >= 0) {
        std::cout << step << std::endl;
        std::cout << tmp[0] << " " << tmp[1] << " " << tmp[2] << std::endl;
        std::cout << tmp[3] << " " << tmp[4] << " " << tmp[5] << std::endl;
        std::cout << tmp[6] << " " << tmp[7] << " " << tmp[8] << std::endl;
        std::cout << std::endl;
        int idx = 0;
        for (; tmp[idx] != '0'; idx++)
            ;
        int pos = idx;
        switch (dir_tmp)
        {
        case 1:pos += 3;break;
        case 2:pos += 1;break;
        case 3:pos -= 1;break;
        case 4:pos -= 3;break;
        default:break;
        }
        std::swap(tmp[pos], tmp[idx]);
        tmp = visited.find(tmp)->first;
        dir_tmp = visited.find(tmp)->second;
        step--;
    }
}

int HRD::InversPair() {
    std::vector<int> tmp;
    int countIP = 0;
    for (int i = 0;i < col * row;i++) {
        int now = std::upper_bound(tmp.begin(), tmp.end(), board[i]) - tmp.begin();
        countIP = countIP + i - now;
        tmp.insert(tmp.begin() + now, board[i]);
    }
    return countIP;
}


void HRD::initBoard() {

    srand((unsigned int)time(0));
    while (board[1] == 0 || board[3] == 0 || board[5] == 0 || board[7] == 0)
    {
        std::random_shuffle(board.begin(), board.end());
        for (int i = 0; i < col * row; ++i)
            std::cout << board[i];
        std::cout << std::endl;
    }

    // row, col is odd
    if (row % 2 == 1) {
        //Number of InversePairs of Board;
        if (InversPair() % 2 != 0) {
            int swap = board[0];
            board[0] = board[1];
            board[1] = swap;
        }
    }
}

int HRD::BFS() {
    std::string target = "123456780";
    std::vector<std::vector<int>> neighbor = {
        { 1, 3 },
        { 0, 4, 2 },
        { 1, 5 },
        { 0, 4 , 6},
        { 3, 1, 5 ,7},
        { 4, 2, 8},
        {3, 7},
        {6, 4, 8},
        {7, 5}
    };
    std::string start = "";
    for (int i = 0; i < col*row; i++)
            start.push_back(board[i] + '0');
    //start = "312456780";
    //std::cout << start << std::endl;
    std::queue<Node> q;
    q.push(Node(start, 0));
    visited.insert(std::make_pair(start, 0));
    int step = 0;

    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            std::string cur = q.front().s;
            if (target == cur) {
                fin.s = q.front().s;
                fin.dir = q.front().dir;
                return step;
            }
            q.pop();
            int idx = 0;
            for (; cur[idx] != '0'; idx++)
                ;
            for (int adj : neighbor[idx]) {
                std::string new_board = cur;
                std::swap(new_board[adj], new_board[idx]);
                if (!visited.count(new_board)) {
                    int dir = 0;
                    if (idx - adj == 1) { dir = 2; }
                    else if (idx - adj == -1) { dir = 3; }
                    else if (idx - adj == 3) { dir = 1; }
                    else if (idx - adj == -3) { dir = 4; }
                    else { std::cout << "!!!!!!!" << std::endl; }
                    q.push(Node(new_board, dir));
                    visited.insert(std::make_pair(new_board, dir));
                }
            }
        }
        step++;
    }
    return -1;


}
