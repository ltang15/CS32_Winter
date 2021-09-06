#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int precedent(char ch);
bool checkInfix(const string& infix);
bool infixToPostfix(string input_infix, string& postfix);




int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    // Evaluates a boolean expression
        //   If infix is a syntactically valid infix boolean expression,
        //   then set postfix to the postfix form of that expression, set
        //   result to the value of the expression (where in that expression,
        //   each digit k represents element k of the values array), and
        //   return zero.  If infix is not a syntactically valid expression,
        //   return 1.  (In that case, postfix may or may not be changed, but
        //   result must be unchanged.)
    

    // can't convert infix to postfix
    if (!infixToPostfix(infix, postfix))
        return 1;


    stack <bool> operand;
    for (int j = 0; j < postfix.size(); j++)
    {
        char ch = postfix[j];

        if (isdigit(ch))
        {
            int num = ch - '0';
            if (values[num] == true)
                operand.push(true);
            else
                operand.push(false);
        }
        else if (ch == '!')
        {
            bool op = operand.top();
            operand.pop();
            if (op == true)
                operand.push(false);
            else
                operand.push(true);
        }
        else if (ch == '|' || ch == '&')
        {

            bool op1 = operand.top();
            operand.pop();
            bool op2 = operand.top();
            operand.pop();

            if (ch == '|')
            {

                if (op1 == true || op2 == true)
                    operand.push(true);
                else
                    operand.push(false);
            }
            if (ch == '&')
            {

                if (op1 == true && op2 == true)
                    operand.push(true);
                else
                    operand.push(false);
            }


        }
        else
            return 1;
     
    }

    
    // if the stack is empty
    if (operand.empty())
            return 1;

    bool value = operand.top();
    operand.pop();

    // stack should be empty after popping off the stack
    if (!operand.empty())
        return 1;

    // Set up value
    if (value == true)
        result = 1;
    else
        result = 0;
    
    return 0;
}


int precedent(char ch)
{
    // calculate the precedence of operators
    // ! > & > |
    if (ch == '|')
        return 1;
    else if (ch == '&')
        return 2;
    else if (ch == '!')
        return 3;
    else
        return -1;
}



bool checkInfix(const string& infix)
{

    // check the validity olf the infix

    for (int k = 0; k < infix.size(); k++)
    {
        char ch = infix[k];

        if (isdigit(ch))
        {
            if (k > 0)
                if (isdigit(infix[k + 1]))
                    return false;

        }

        if (ch == '(' && infix[k + 1] == ')')
            return false;


        if (ch == '|' || ch == '&')
        {
            if (k == infix.size() - 1 || k == 0)
                return false;

            if (k <= infix.size() - 1)
                if (infix[k + 1] == ')' || infix[k + 1] == '|' || infix[k + 1] == '&')
                    return false;

            if (k >= 0)
                if (infix[k - 1] == '!' || infix[k - 1] == '|' || infix[k - 1] == '&' || infix[k - 1] == '(')
                    return false;


        }

       

    }
    return true;
}


bool infixToPostfix(string input_infix, string& postfix)
{
    // erase the space in the string
    string infix = "";
    for (int i = 0; i < input_infix.size(); i++)
    {
        char ch = input_infix[i];
        if (ch != ' ')
            infix += ch;
    }


    // check the validity of the infix
    if (!checkInfix(infix))
        return false;




    int parenth = 0;
    postfix = "";
    stack <char> operatorStack;
    for (int i = 0; i < infix.size(); i++)
    {
        char ch = infix[i];
        switch (ch)
        {
        case ' ':
            continue;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            postfix += infix[i];
            break;
        case '(':
            parenth++; // increment with the open parenth
            operatorStack.push(ch);
            break;
        case ')':
            parenth--; // decrement with the close parenth
            while (operatorStack.top() != '(')
            {
                postfix += operatorStack.top();
                operatorStack.pop();
            }

            operatorStack.pop();// remove the '('
            break;
        case '!':
        case '|':
        case '&':
            while (!operatorStack.empty() && operatorStack.top() != '(' && precedent(ch) <= precedent(operatorStack.top()))
            {
                postfix += operatorStack.top();
                operatorStack.pop();
            }

            operatorStack.push(ch);
            break;
        default:
            return false;

        }
    }

    // check the error of parenth
    if (parenth != 0)
        return false;

    // Adding remaining items from stacks to postfix

    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();

    }
    return true;
}
//int main()
//{
//    bool ba[10] = {
//        //  0      1      2      3      4      5      6      7      8      9
//          true,  true,  true,  false, false, false, true,  false, true,  false
//    };
//    string pf;
//    bool answer;
//    assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" && answer);
//    assert(evaluate("8|", ba, pf, answer) == 1);
//    assert(evaluate(" &6", ba, pf, answer) == 1);
//    assert(evaluate("4 5", ba, pf, answer) == 1);
//    assert(evaluate("01", ba, pf, answer) == 1);
//    assert(evaluate("()", ba, pf, answer) == 1);
//    assert(evaluate("()4", ba, pf, answer) == 1);
//    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
//    assert(evaluate("2(&8)", ba, pf, answer) == 1);
//    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
//    assert(evaluate("x+5", ba, pf, answer) == 1);
//    assert(evaluate("", ba, pf, answer) == 1);
//    assert(evaluate("2|3|4", ba, pf, answer) == 0
//        && pf == "23|4|" && answer);
//    assert(evaluate("2|(3|4)", ba, pf, answer) == 0
//        && pf == "234||" && answer);
//    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
//        && pf == "43!03&&|" && !answer);
//    assert(evaluate(" 9  ", ba, pf, answer) == 0 && pf == "9" && !answer);
//    ba[2] = false;
//    ba[9] = true;
//    assert(evaluate("((9))", ba, pf, answer) == 0 && pf == "9" && answer);
//    assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" && !answer);
//    cout << "Passed all tests" << endl;
//}

