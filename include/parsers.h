#pragma once
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <algorithm>
#include <vector>
#include "polynomial.h"

int get_exp(const std::string s) {
    if (s == "") return 1;
    return std::stoi(s);
};

std::map<std::string, polynomial> parse_equation(const std::string& s) {
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
        if (value[0] != '+' && value[0] != '-') {    // not sure if that catches unsigned monomial case
            monomials.push_back((*it).str());
            ++it;
        }
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
            std::regex pattern("([+-]?)\\s*(\\d*)?s*(x|y|z)?\\s*\\^*\\s*(\\d*)?\\s*(x|y|z)?\\s*\\^*\\s*(\\d*)?\\s*(x|y|z)?\\s*\\^*\\s*(\\d*)?");
            std::regex_search(mstr, match, pattern);  //s

            if (match[1].str() == "-") {
                if (match[2].str() == "") coef = -1;
                else coef = -(std::stod(match[2].str()));
            }
            else if (match[2].str() == "") {coef = 1;} else coef = std::stod(match[2].str());

            for (int i = 1; i < 4; i++) {
                if (match[2 * i + 1].str() == "x") a += get_exp(match[2 * i + 2].str());
                else if (match[2 * i + 1].str() == "y") b += get_exp(match[2 * i + 2].str());
                else if (match[2 * i + 1].str() == "z") c += get_exp(match[2 * i + 2].str());
            }
            p.add_monomial(monomial(coef, a, b, c));
        }
        result[name] = p;
        return result;
     }
    
}