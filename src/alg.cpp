// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include "tstack.h"

int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;
    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        if (c == ' ') {
            continue;
        }
        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                result += stack.pop();
                result += ' ';
            }
            if (!stack.empty() && stack.top() == '(') {
                stack.pop();
            }
        } else if (isOperator(c)) {
            while (!stack.empty() && stack.top() != '(' &&
                   getPriority(stack.top()) >= getPriority(c)) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(c);
        }
    }
    while (!stack.empty()) {
        result += stack.pop();
        result += ' ';
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}
int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::stringstream ss(post);
    std::string token;
    while (ss >> token) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            stack.push(std::stoi(token));
        } else if (token.length() == 1 && isOperator(token[0])) {
            int b = stack.pop();
            int a = stack.pop();
            int result = 0;
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }
            stack.push(result);
        }
    }
    return stack.pop();
}
