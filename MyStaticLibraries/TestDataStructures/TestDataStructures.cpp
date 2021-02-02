// TestDataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"
using namespace std;

int main()
{
    // try to find all implementations leaks of LinkedList:

    datastructures::LinkedList<int> l;
    try { l.getFirst(); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.getAt(0); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.getAt(1); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.getLast(); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.getFirst(); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.eraseFirst(); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.erase(0); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.erase(1); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.eraseLast(); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.popFirst(); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.pop(0); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.pop(1); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try { l.popLast(); }
    catch (std::runtime_error e) { cout << "successfully catched error:" << endl << e.what() << endl; }

    try
    {
        l.addAt(0, 10);
        l.addAt(0, 11);
        l.addAt(2, 12);
        l.addFirst(9);
        l.addLast(13);
        l.remove(11);
        cout << "The size is " << l.Size() << " and should be 4" << endl;
        l.clear();

        cout << "The size is " << l.Size() << " and should be 0" << endl;
        datastructures::LinkedList<int> l2;
        for (int i = 0; i < 10; i++)
            l2.addLast(i + 10);

        l += l2;
        cout << "The size is " << l.Size() << " and should be 10" << endl;

        cout << l << endl << l2 << endl;


        l.erase(0);
        l.eraseFirst();
        l.eraseLast();
        l.erase(l.Size()-1);
        cout << l << endl;
        l.erase(3);
        cout << l <<  " with size = " << l.Size() << endl;

        datastructures::LinkedList<int> l3;
        l3 = l+l2;
        cout << l3 << endl;
    }
    catch(runtime_error e)
    {
        cout << e.what() << endl;
    }
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
