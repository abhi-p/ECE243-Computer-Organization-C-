/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Abhishek Paul
 *
 * Created on September 30, 2016, 8:04 AM
 */

// hello.cpp -- "Hello, world" C++ program

#include <iostream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#define MaxNodeNumber 5000
using namespace std;

int invalidArgument(string command) {
    cout << "Error: invalid argument";
    return (0);
}

int errorTest(string command, string name, double resistance, int nodeOne, int nodeTwo) {
    if (nodeOne > MaxNodeNumber || nodeOne < 0) {
        cout << "Error: node " << nodeOne << " is out of permitted range 0-5000";
        return (1);

    } else if (nodeTwo > MaxNodeNumber || nodeTwo < 0) {
        cout << "Error: node " << nodeTwo << " is out of permitted range 0-5000";
        return (1);

    } else if (name == "all") {
        cout << "Error: resistor name cannot be the keyword \"all\" ";
        return (1);
    } else if (nodeTwo == nodeOne) {
        cout << "Error: both terminals of resistor connect to node " << nodeOne << "";
        return (1);
    } else
        return (0);
}

int insertR(string command, string name, double resistance, int nodeOne, int nodeTwo) {


    cout << "Inserted: resistor " << name << " " << fixed << setprecision(2) << resistance << " Ohms " << nodeOne << " -> " << nodeTwo << "";


    return (0);
}

int modifyR(string command, string name, double resistance,stringstream &myOwnStream) {

    if (name == "all")
        cout << "Error: resistor name cannot be the keyword \"all\" ";
     else if (!myOwnStream.eof()) {
                        cout << "Error: too many arguments";
                    }
    else
        cout << "Modified: resistor " << name << " to " << fixed << setprecision(2) << resistance << " Ohms";
    return (0);


}

int printR(string command, string name) {
    if (name == "all")
        cout << "Print: all resistors";
    else

        cout << "Print: resistor " << name << "";

    return (0);

}

int printNode(string command, stringstream &myOwnStream) {
    
    int nodeOne;
    string name;
    myOwnStream>>nodeOne;
                   
    if (myOwnStream.fail()) 
    {    myOwnStream.clear();
    myOwnStream>>name;
    if (name=="all")
        cout<<"Print: all nodes";
    else
        invalidArgument(command);
    }
   
    else
    {
         if (nodeOne > MaxNodeNumber || nodeOne <= 0)
            cout << "Error: node " << nodeOne << " is out of permitted range 0-5000";
         else
        cout<<"Print: node "<<nodeOne<<"";
    }
    
   
   return (0);

}

int deleteR(string command, string name,stringstream &myOwnStream) {
   if (!myOwnStream.eof())
                    cout << "Error: too many arguments";
    if (name == "all")
        cout << "Deleted: all resistors";
    else {

        cout << "Deleted: resistor " << name << "";
    }
    return (0);

}

int main() {
    int n = 0;
    while (!cin.eof() && n == 0) {
        string line, command, name;
        int nodeOne, nodeTwo;
        double resistance;
        cout << ">  ";
        getline(cin, line); // Get a line from standard input
        stringstream myOwnStream(line);
        myOwnStream >> command;

        if (command == "insertR") {

            myOwnStream >> name;
            myOwnStream >> resistance;
            myOwnStream >> nodeOne;
            if (myOwnStream.eof())
                cout << "Error: too few arguments";

            else {
                myOwnStream >> nodeTwo;

                if (resistance < 0)
                    cout << "Error: negative resistance";

                else if (myOwnStream.fail()) {
                    invalidArgument(command);
                    myOwnStream.clear();
                    myOwnStream.ignore(1000, '\n');

                } else {

                    int x = errorTest(command, name, resistance, nodeOne, nodeTwo);
                    if (!myOwnStream.eof() && x == 0) {
                        cout << "Error: too many arguments";
                        x = 1;
                    }
                    if (x == 0)
                        insertR(command, name, resistance, nodeOne, nodeTwo);
                }
            }
        } else if (command == "modifyR") {
            myOwnStream >> name;
            if (myOwnStream.eof()) {
                cout << "Error: too few arguments";
            } else {
                myOwnStream >> resistance;
                if (myOwnStream.fail()) {
                    invalidArgument(command);
                    myOwnStream.clear();
                    myOwnStream.ignore(1000, '\n');

                } else {
                    if (resistance < 0)
                        cout << "Error: negative resistance";
                    else
                        modifyR(command, name, resistance,myOwnStream);
                }
            }
        } else if (command == "printR") {
            if (myOwnStream.eof()) {
                cout << "Error: too few arguments";

            } else {
                myOwnStream >> name;
                if (myOwnStream.fail()) {
                    invalidArgument(command);
                    myOwnStream.clear();
                    myOwnStream.ignore(1000, '\n');

                } else {
                    if (!myOwnStream.eof())
                        cout << "Error: too many arguments";
                    else

                        printR(command, name);
                }
            }
        } else if (command == "printNode") {
            if (myOwnStream.eof()) 
                cout << "Error: too few arguments";
            else
                printNode(command,myOwnStream);
            
        }
        
        else if (command == "deleteR") {
            if (myOwnStream.eof()) {
                cout << "Error: too few arguments";
            } else {
                myOwnStream >> name;
                deleteR(command, name,myOwnStream);
            }
        }
        else {
            if (!cin.eof())
                cout << "Error: invalid command";
        }
        cout << " \n";
        myOwnStream.clear();
        myOwnStream.ignore(1000, '\n');
    }


    return (0);
}

