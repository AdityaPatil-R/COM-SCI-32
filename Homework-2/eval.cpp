#include <iostream>
#include <string>
#include <stack>
#include <cassert>

using namespace std;

// ! has higher precedence than &, which has higher precedence than |
int precedence(char ch) {
    switch (ch) {
        case '!':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            return 0;
    }
}

bool isValid(string& infix) {
    // Remove spaces
    string infixWithoutSpaces = "";

    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] != ' ') {
            infixWithoutSpaces += infix[i];
        }
    }

    infix = infixWithoutSpaces;

    // Check beginning and end
    if (infix == "" || infix[0] == '&' || infix[0] == '|' || infix[0] == ')' 
    || infix[infix.size() - 1] == '&' || infix[infix.size() - 1] == '|' 
    || infix[infix.size() - 1] == '!' || infix[infix.size() - 1] == '(') {
        return false;
    }
    
    // Loop through each character and check if them, the ones directly before, and the ones after are valid
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];

        if (ch == 'T' || ch == 'F') {
            if (i > 0) {
                if (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')') {
                    return false;
                }
            }

            if (i < infix.size() - 1) {
                if (infix[i + 1] == 'T' || infix[i + 1] == 'F' || infix[i + 1] == '(' || infix[i + 1] == '!') {
                    return false;
                }
            }
        } else if (ch == '(' || ch == '!') {
            if (i > 0) {
                if (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')') {
                    return false;
                }
            }

            if (i < infix.size() - 1) {
                if (infix[i + 1] == ')' || infix[i + 1] == '&' || infix[i + 1] == '|') {
                    return false;
                }
            }
        } else if (ch == ')') {
            if (i > 0) {
                if (infix[i - 1] == '(' || infix[i - 1] == '!' || infix[i - 1] == '&' || infix[i - 1] == '|') {
                    return false;
                }
            }

            if (i < infix.size() - 1) {
                if (infix[i + 1] == 'T' || infix[i + 1] == 'F' || infix[i + 1] == '(' || infix[i + 1] == '!') {
                    return false;
                } 
            }
        } else if (ch == '&' || ch == '|') {
            if (i > 0) {
                if (infix[i - 1] == '(' || infix[i - 1] == '!' || infix[i - 1] == '&' || infix[i - 1] == '|') {
                    return false;
                }
            }

            if (i < infix.size() - 1) {
                if (infix[i + 1] == '&' || infix[i + 1] == '|' || infix[i + 1] == ')') {
                    return false;
                }
            }
        } else {
            return false;
        }
    }

    return true;
}

bool infixToPostfix(string infix, string& postfix) {
    // Verify validity
    if (!isValid(infix)) {
        return false;
    }

    // Initialize postfix to empty
    postfix = "";
    // Initialize the operator stack to empty
    stack<char> operatorStack;
    
    // For each character ch in the infix string
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];

        // Switch (ch)
        switch (ch) {
            // case operand:
            case 'T':
            case 'F':
                // append ch to end of postfix
                postfix += ch;
                // break
                break;
            // case '(':
            case '(':
            case '!':
                // push ch onto the operator stack
                operatorStack.push(ch);
                // break
                break;
            // case ')':
            case ')':
                // While stack top is not '('
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    // append the stack top to postfix
                    postfix += operatorStack.top();
                    // pop the stack
                    operatorStack.pop();
                }

                if (operatorStack.empty()) {
                    return false;
                }

                // pop the stack
                operatorStack.pop();
                // break
                break;
            // case operator:
            case '&':
            case '|':
                // While the stack is not empty and stack top is not '(' and precedence of ch <= precedence of stack top
                while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(ch) <= precedence(operatorStack.top())) {
                    // append the stack top to postfix
                    postfix += operatorStack.top();
                    // pop the stack
                    operatorStack.pop();
                }

                // push ch onto the stack
                operatorStack.push(ch);
                // break
                break;
            default:
                return false;
        }
    }

    // While the stack is not empty
    while (!operatorStack.empty()) {
        if (operatorStack.top() == '(' || operatorStack.top() == ')') {
            return false;
        }

        // append the stack top to postfix
        postfix += operatorStack.top();
        // pop the stack
        operatorStack.pop();
    }

    return true;
}

bool evaluatePostfix(string postfix) {
    // Initialize the operand stack to empty
    stack<bool> operandStack;

    // For each character ch in the postfix string
    for (int i = 0; i < postfix.size(); i++) {
        char ch = postfix[i];

        // if ch is an operand
        if (ch == 'T' || ch == 'F') {
            // push the value that ch represents onto the operand stack
            operandStack.push(ch == 'T');
        // else // ch is a binary operator
        } else if (ch == '&' || ch == '|') {
            // set operand2 to the top of the operand stack
            bool operand2 = operandStack.top();
            // pop the stack
            operandStack.pop();

            // set operand1 to the top of the operand stack
            bool operand1 = operandStack.top();
            // pop the stack
            operandStack.pop();

            // apply the operation that ch represents to operand1 and operand2, and push the result onto the stack
            operandStack.push(ch == '&' ? operand1 && operand2 : operand1 || operand2);
        } else if (ch == '!') {
            bool operatorStackTop = operandStack.top();
            operandStack.pop();
            operandStack.push(!operatorStackTop);
        }
    }

    // When the loop is finished, the operand stack will contain one item, the result of evaluating the expression
    return operandStack.top();
}

int evaluate(string infix, string& postfix, bool& result) {
    if (!infixToPostfix(infix, postfix)) {
        return 1;
    }

    result = evaluatePostfix(postfix);
    return 0;
}