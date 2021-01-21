#pragma once
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <stack>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cassert>


struct Node {
//  dir
//   1
//2     3
//   4
    Node(std::string s_, int dir_) : dir(dir_), s(s_) {}
    int dir;
    std::string s;
};



class HRD
{
public:
    HRD();
    void print();
//private:
    void initBoard();
    int InversPair();
    int BFS();
private:
    int row;
    int col;
    std::vector<int> board;
    Node fin;
    std::map<std::string, int> visited;
};


