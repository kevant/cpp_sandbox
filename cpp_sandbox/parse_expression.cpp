/*
An easy way to think about parsing expression (for me)

Given expression "1+2+3;"
parse_exp
    1
    + means recursively call parse_exp
    parse_exp
        2
        + means recursively call parse_exp
        parse_exp
            3
            ; means return expression
            return 3
        return 2 + 3
    return 1 + (2 + 3)
*/

#include <iostream>

using namespace std;

int parse_exp(string exp)
{
    int value = exp[0] - '0';
    if (exp[1] == ';')
        return value;
    if (exp[1] == '+')
        return value + parse_exp(exp.substr(2));
}

int main()
{
    string exp = "1+2+3;";
    cout << parse_exp(exp);

    return 0;
}