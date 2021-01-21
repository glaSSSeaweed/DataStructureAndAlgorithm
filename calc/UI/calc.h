#ifndef CALC_H
#define CALC_H


#include <string>
#include <stack>
#include <queue>

class Calc
{
public:
    static void decodeFormula(std::string& f);
    Calc(std::string& f);
    double ans();
private:
    int isp(char c);
    int icp(char c);
    std::queue<std::string> pf;
};





#endif // CALC_H
