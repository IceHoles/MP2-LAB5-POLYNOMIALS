#include "list.h"
#include "polynomial.h"		  
#include "hash_list.h"
#include "ordered_table.h"
#include "parsers.h"
#include "tree_rb.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

int main() {
    std::map<std::string, polynomial> polynomials;
    TOrderedTab1e<std::string, polynomial> table;
    TSearchTreeTab1e<std::string, polynomial> tree;
    THashTab1e<std::string, polynomial> hash;

    while (true) {
        std::cout << "Enter a command (add, expression, integ, diff, value, print, exit): ";
        std::string command;
        std::getline(std::cin, command);

        if (command == "add") {
            std::cout << "Enter the polynomial as a string: ";
            std::string polynomialString;
            std::getline(std::cin, polynomialString);
            std::string name;

            polynomial p = parse_polynomial(polynomialString, polynomials, name);
            table.Insert(name, p);
            tree.Insert(name, p);
            hash.insert(name, p);
            std::cout << "Polynomial added." << std::endl;
        }
        else if (command == "expression") {
            std::cout << "Enter the expression as a string: ";
            std::string expression;
            std::getline(std::cin, expression);

            polynomial result = parse_expression(expression, polynomials);
            std::cout << "Result: " << result << std::endl;
        }
        else if (command == "integ") {
            std::cout << "Enter the name of the polynomial to integrate: ";
            std::string name;
            std::getline(std::cin, name);

            std::cout << "Enter the variable to integrate (h): ";
            char h;
            std::cin >> h;

            polynomial& p = polynomials[name];
            p = p.integ(h);
            std::cout << "Polynomial integrated." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (command == "diff") {
            std::cout << "Enter the name of the polynomial to differentiate: ";
            std::string name;
            std::getline(std::cin, name);

            std::cout << "Enter the variable to differentiate (h): ";
            char h;
            std::cin >> h;

            polynomial& p = polynomials[name];
            p = p.diff(h);
            std::cout << "Polynomial differentiated." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (command == "value") {
            std::cout << "Enter the name of the polynomial: ";
            std::string name;
            std::getline(std::cin, name);

            std::cout << "Enter the value of x: ";
            double x;
            std::cin >> x;

            std::cout << "Enter the value of y: ";
            double y;
            std::cin >> y;

            std::cout << "Enter the value of z: ";
            double z;
            std::cin >> z;

            const polynomial& p = polynomials[name];
            double result = p.value(x, y, z);
            std::cout << "Result: " << result << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (command == "print") {
            print_polynomials(polynomials);
            table.print();
            tree.print();
            hash.print();
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }

    return 0;
}