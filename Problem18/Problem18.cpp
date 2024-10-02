// Problem18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> // console output
#include <fstream>  // to input the number pyramid
#include <regex>    // to process the number pyramid
#include <string>
#include "Tree.h"   // the tree datastructure ( this file contains the actual solution, that is the sweep algorithm)

int main()
{
    //  first step: input and process the number pyramid
    std::ifstream ifs("bigPyramid.txt");
    if (!ifs.good())
    {
        std::cerr << "input file error";
        return 0;
    }

    std::string s;      // the txt file will be read to this string
    while (ifs.good())  // while ifs holds valid input
    {
        char c = ifs.get();
        s.push_back(c);
    }

    std::regex_iterator<std::string::iterator> itEmpty; // to compare "it" to, when there are no more matches left
    std::regex wordReg("\\b\\d+\\b");   // the regex for a number delimited to the right and left
    auto it = std::regex_iterator<std::string::iterator>(s.begin(), s.end(), wordReg);  // matches the wordReg pattern from begin to end of the string

    // convert the matches (figures in the string) to integers and add them to the list l
    list<int> l = list<int>();
    while (it != itEmpty)
    {
        l.push_back(std::stoi(it->str()));
        it++;
    }

    // construct the tree from the list of numbers
    Tree t(l);

    // perform the sweep algorithm to find each nodes predecessor
    t.sweep();
    
    auto groundRowList = t.groundRow();
    int highestCost = 0;    // holds the path cost of the most expensive path found
    int nodeValue;          // just to check the last node of the path in the bottom row

    // iterate through the bottom row and find the most expensive path
    for (Node* n : groundRowList)
    {
        if (n->cost > highestCost)  // there's a new most expensive path
        {
            highestCost = n->cost;
            nodeValue = n->value;
        }
    }

    // print the tree, just for debugging
    //std::cout << t << std::endl;

    std::cout << "The path with the highest cost ends at a node with value " << nodeValue << std::endl;
    std::cout << "The path cost is " << highestCost << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
