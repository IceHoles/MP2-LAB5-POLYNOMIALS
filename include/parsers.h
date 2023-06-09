#pragma once
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <algorithm>
#include <vector>
#include <stack>
#include "polynomial.h"

int get_exp(const std::string s) {
    if (s == "") return 1;
    return std::stoi(s);
};

bool is_number(const std::string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

polynomial parse_polynomial(const std::string& s, std::map<std::string, polynomial>& polynomials, std::string& pname) {
    std::map<std::string, polynomial> result;
    std::regex pattern_equation("(\\w+)\\s*=\\s*(.*)");
    std::smatch match_eq;
    if (regex_search(s, match_eq, pattern_equation)) {
        std::string name = match_eq[1].str();
        std::string value = match_eq[2].str();
        std::vector<std::string> monomials;
        std::regex pattern_monomial("([+-]?[^-+]+)");
        std::sregex_iterator it(value.begin(), value.end(), pattern_monomial);
        std::sregex_iterator end;

        while (it != end) {
            monomials.push_back((*it).str());
            ++it;
        }
        polynomial p;
        for (auto mstr : monomials) {
            double coef = 1.0;
            int a, b, c;
            a = 0;
            b = 0;
            c = 0;
            std::smatch match;
            std::regex pattern("([+-]?)\\s*([\\d|\\.]*)?s*(x|y|z)?\\s*\\^*\\s*(\\d*)?\\s*(x|y|z)?\\s*\\^*\\s*(\\d*)?\\s*(x|y|z)?\\s*\\^*\\s*(\\d*)?");
            std::regex_search(mstr, match, pattern);  //s
            if (match[1].str() == "-") {
                if (match[2].str() == "") coef = -1;
                else coef = -(std::stod(match[2].str()));
            }
            else if (match[2].str() == "") { coef = 1; }
            else coef = std::stod(match[2].str());
            for (int i = 1; i < 4; i++) {
                if (match[2 * i + 1].str() == "x") a += get_exp(match[2 * i + 2].str());
                else if (match[2 * i + 1].str() == "y") b += get_exp(match[2 * i + 2].str());
                else if (match[2 * i + 1].str() == "z") c += get_exp(match[2 * i + 2].str());
            }
            p.add_monomial(monomial(coef, a, b, c));
        }
        polynomials[name] = p;
        pname = name;
        return p;
    }
    else throw std::invalid_argument("Invalid input");
}

int precedence(char op) {
    if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '+' || op == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

void apply_operation(std::stack<polynomial>& poly_stack, char op) {
    if (poly_stack.size() < 2) {
        throw std::invalid_argument("Invalid expression");
    }
    polynomial right = poly_stack.top();
    poly_stack.pop();
    polynomial left = poly_stack.top();
    poly_stack.pop();
    polynomial result;
    switch (op) {
    case '+':
        result = left + right;
        break;
    case '-':
        result = left - right;
        break;
    case '*':
        result = left * right;
        break;
    case '/':
        result = left / right;
        break;
    default:
        throw std::invalid_argument("Invalid operator");
    }
    poly_stack.push(result);
}

std::string remove_whitespace(const std::string& s) {
    std::string result;
    for (char c : s) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    return result;
}

polynomial parse_expression(const std::string& s, std::map<std::string, polynomial>& polynomials) {
    std::string expr = remove_whitespace(s);
    std::stack<polynomial> poly_stack;
    std::stack<char> op_stack;
    size_t pos = expr.find('=');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid expression: Missing equals sign '='");
    }

    std::string result_name = expr.substr(0, pos);
    if (result_name.empty()) {
        throw std::invalid_argument("Invalid expression: Missing result polynomial name");
    }
    pos++;
    while (pos < expr.length()) {
        char current = expr[pos];
        if (current == '(') {
            op_stack.push(current);
        }
        else if (current == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                apply_operation(poly_stack, op_stack.top());
                op_stack.pop();
            }
            if (op_stack.empty()) {
                throw std::invalid_argument("Invalid expression");
            }
            op_stack.pop();
        }
        else if (current == '+' || current == '-' || current == '*' || current == '/') {
            while (!op_stack.empty() && op_stack.top() != '(' && precedence(current) <= precedence(op_stack.top())) {
                apply_operation(poly_stack, op_stack.top());
                op_stack.pop();
            }
            op_stack.push(current);
        }
        else {
            size_t end_pos = expr.find_first_of("+-*/()", pos);
            std::string poly_name = expr.substr(pos, end_pos - pos);
            if (polynomials.find(poly_name) == polynomials.end()) {
                throw std::invalid_argument("Undefined polynomial: " + poly_name);
            }
            poly_stack.push(polynomials.at(poly_name));
            pos = end_pos - 1;
        }

        pos++;
    }

    while (!op_stack.empty()) {
        if (op_stack.top() == '(') {
            throw std::invalid_argument("Invalid expression");
        }
        apply_operation(poly_stack, op_stack.top());
        op_stack.pop();
    }

    if (poly_stack.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }
    polynomials[result_name] = poly_stack.top();
    return poly_stack.top();
}