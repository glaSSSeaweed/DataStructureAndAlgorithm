#include "calc.h"
#include <cmath>
#include <climits>
#include <cstdlib>
#include <iostream>
using namespace std;
Calc::Calc(string& f)
{
    stack<char> operatorStack;
    operatorStack.push('#');
    char ch[] = {0, 0};
    char op[] = {0, 0};
    size_t pos = 0;
    while (!operatorStack.empty() && pos < f.length())
    {
        if ((f[pos] == '.') || (f[pos] - '0' >= 0 && f[pos] - '0' <= 9))
        {
            string tmp("");
            while ( ( (f[pos] == '.') || (f[pos] - '0' >= 0 && f[pos] - '0' <= 9) )  && pos < f.length())
            {
                ch[0] = f[pos];
                tmp += string(ch);
                ++pos;
            }
            pos -= 1;
            pf.push(tmp);
            pos++;
        }
        else
        {
            ch[0] = operatorStack.top();
            if (isp(ch[0]) < icp(f[pos]))
            {
                operatorStack.push(f[pos]);
                pos++;
            }
            else if (isp(ch[0]) > icp(f[pos]))
            {
                op[0] = operatorStack.top();
                operatorStack.pop();
                pf.push(string(op));
            }
            else
            {
                op[0] = operatorStack.top();
                operatorStack.pop();
                if (op[0] == '(')
                    pos++;
            }
        }
    }
//     while(!pf.empty())
//     {
//        cout << pf.front() <<" ";
//        pf.pop();
//     }
}

double Calc::ans()
{
    //double res;
            double num;
            double calc;
            string current;
            stack<double> ansStack;

            if(pf.empty()){
                return 0;
            }
            if(!pf.empty()){
                ansStack.push(atof(pf.front().c_str()));
                pf.pop();
            }
            if(pf.empty()){
                return ansStack.top();
            }
            if (!pf.empty()){
                ansStack.push(atof(pf.front().c_str()));
                pf.pop();
            }

            while(!pf.empty())
            {

                current = pf.front();
                pf.pop();
                num = atof(current.c_str());
                //cout << current.c_str() << endl;
                //cout << num << endl;
                if(num != 0){
                    ansStack.push(num);
                    //cout << num << endl;
                }
                else
                {

                    switch (current.c_str()[0])
                    {
                    case '+':
                        calc = ansStack.top();
                        ansStack.pop();
                        calc += ansStack.top();
                        ansStack.pop();
                        ansStack.push(calc);
                        break;
                    case '-':
                        calc = ansStack.top();
                        ansStack.pop();
                        calc = ansStack.top() - calc;
                        ansStack.pop();
                        ansStack.push(calc);
                        break;
                    case '*':
                        calc = ansStack.top();
                        ansStack.pop();
                        calc *= ansStack.top();
                        ansStack.pop();
                        ansStack.push(calc);
                        break;
                    case '/':
                        calc = ansStack.top();
                        if(calc == 0){
                            calc = INT_MAX;
                            cerr << "0 is divided" << endl;
                        }
                        ansStack.pop();
                        calc = ansStack.top() /calc;
                        ansStack.pop();
                        ansStack.push(calc);
                        break;
                    default:
                        ansStack.push(num);
                        break;
                    }
                }

            }
            return ansStack.top();
}

int Calc::isp(char c)
{
    if (c == '#') return 0;
    if (c == '(') return 1;
    if (c == '*' || c == '/') return 5;
    if (c == '+' || c == '-') return 3;
    if (c == ')') return 6;
    return -1;
}

int Calc::icp(char c)
{
    if (c == '#') return 0;
    if (c == '(') return 6;
    if (c == '*' || c == '/') return 4;
    if (c == '+' || c == '-') return 2;
    if (c == ')') return 1;
    return -1;
}


void Calc::decodeFormula(string& f){

    string df("");
    size_t pos = 0;
    while(pos < f.length())
    {
        //因为考虑输入表达式一定正确，其实部分if没有必要判断pos越界问题;
        if(f[pos]>='a' && f[pos]<='z'){
            string token;
            stack<char> brackets;
            while(f[pos] != '('){
                token.push_back(f[pos]);
                ++pos;
            }
            size_t i = pos;
            ++pos;
            brackets.push('(');

            while(!brackets.empty()){
                if(f[pos] == '(')
                    brackets.push('(');
                if(f[pos] ==')')
                    brackets.pop();
                ++pos;
            }
            string tmp = f.substr(i, pos - i);
            decodeFormula(tmp);
            tmp.append("#");
            Calc *CalcPtr;
            double value;
            if(token == "sin"){

                CalcPtr = new Calc(tmp);
                value = sin(CalcPtr->ans());
            }
            else if(token == "cos"){
                CalcPtr = new Calc(tmp);
                value = cos(CalcPtr->ans());

            }
            else if(token == "tan"){
                CalcPtr = new Calc(tmp);
                value = tan(CalcPtr->ans());
            }
            else{
                value = INT_MAX;
                cerr << "unkown token" << endl;

            }


            if(value>=0){
                df.append("(0+");
                df.append(to_string(value));
            }
            else{
                df.append("(0");
                df.append(to_string(value));
            }
            df.push_back(')');
            delete CalcPtr;

        }
        else if(f[pos] == '('){
            // || f[pos+1] == '*' || f[pos+1] == '/'
            if(f[pos+1] == '+' || f[pos+1] == '-'){
                df.append("(0");
                df.push_back(f[pos+1]);
                pos += 2;
                while ( (f[pos] == '.') || (f[pos] - '0' >= 0 && f[pos] - '0' <= 9) )
                {
                    df.push_back(f[pos]);
                    ++pos;
                }
                df.push_back(')');
                if(f[pos] == ')')
                    ++pos;
            }
            else{
                df.push_back(f[pos]);
                ++pos;
            }

        }// || f[pos] == '*' || f[pos] == '/'
        else if( f[pos] == '+' || f[pos] == '-'){
            //实际上不用考虑（或者说存在即是错误）* / ;因为不存在 +/ +* -/ -* // /* */ **
             //|| f[pos+1] == '*' || f[pos+1] == '/'
            if(pos+1 < f.length() && (f[pos+1] == '+' || f[pos+1] == '-')){
                df.push_back(f[pos]);
                df.append("(0");
                df.push_back(f[pos+1]);
                pos += 2;
            }
            else if(pos == 0){
                df.append("(0");
                df.push_back(f[pos]);
                ++pos;
            }
            else{
                df.push_back(f[pos]);
                ++pos;
                continue;
            }
            while ( ( (f[pos] == '.') || (f[pos] - '0' >= 0 && f[pos] - '0' <= 9) )  && pos < f.length())
            {
                df.push_back(f[pos]);
                ++pos;
            }
            df.push_back(')');
        }
        else{
            df.push_back(f[pos]);
            ++pos;
        }
    }
    // cout << f << endl;
    //cout << df << endl;
    f = df;


}

