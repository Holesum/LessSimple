/*
 * CSC016 Assignment 3: Welcome to Recursion!
 *
 * This client program contains a text menu for running your
 * code for the different problems in this assignment.
 *
 * You don't need to modify this file.
 * 
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
//#include "console.h"
#include "filelib.h"
//#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "WelcomeToRecursion.h"
using namespace std;

// provided helpers
bool ask(string prompt);

// testing function prototype declarations
void test_combinations();
void test_strToInt();
void test_intToStr();

int mainWelcometorecursion() {
    cout << "CSC016 Assignment 2: Welcome to Recursion!" << endl;
    while (true) {
        cout << endl;
        cout << "Choose a problem:" << endl;
        cout << "1) Combinations and Pascal's Triangle" << endl;
        cout << "2) String to Integer" << endl;
        cout << "3) Integer to String" << endl;

        int choice = getInteger("Enter your choice (or 0 to quit): ");
        cout << endl;
        if (choice == 0)      { break; }
        else if (choice == 1) { test_combinations(); }
        else if (choice == 2) { test_strToInt(); }
        else if (choice == 3) { test_intToStr(); }
    }

    cout << "Exiting." << endl;
    return 0;
}


/* Prompts the user for a natural number (a nonnegative integer) */
int getNaturalNumber(string prompt) {
    while (true) {
        int value = getInteger(prompt);
        if (value >= 0) return value;

        cout << "Please enter a nonnegative value." << endl;
    }
}

/*
 * This function tests your combination function
 */
void test_combinations() {
    do {
        int n = getNaturalNumber("Enter n (the number of people in the big group): ");

        int k;
        while (true) {
            k = getNaturalNumber("Enter k (the number of people to choose from the group): ");
            if (k <= n) break;

            cout << "Please enter a number less than or equal to " << n << endl;
        }
        cout << "Result (the number of ways to pick " << k << " people from an " << n << "-person group): " << nChooseK(n, k) << endl;
        cout << endl;
    } while (ask("Continue"));
}

/* Determines whether a string is a valid number. We use this to
 * filter bad inputs out so that you don't have to worry about
 * them in stringToInt.
 */
bool isNumericString(string line) {
    try {
        /* Try converting the string to an integer. If it succeeds,
         * great!
         */
        (void) stringToInteger(line);
        return true;
    } catch (...) {
        /* If it fails, it's not a valid integer. */
        return false;
    }
}

/*
 * This function tests your string to int function
 */
void test_strToInt() {
    while (true) {
        string line = getLine("Provide a number (or Enter to quit): ");
        if (line.length() == 0) break;

        if (isNumericString(line)) {
            int integer = stringToInt(line);
            cout << "Result: " << integer << endl;
        } else {
            cout << "Please enter a valid number." << endl;
        }
    }
}


/*
 * This function tests your int to string function
 */
void test_intToStr() {
    do {
        int line = getInteger("Provide a number: ");
        string str = intToString(line);
        cout << "Result: " << str << endl;
    } while (ask("Continue"));
}


/*
 * This function asks the user with a yes/no prompt and returns the answer.
 */
bool ask(string prompt) {
    while (true) {
        string answer = toLowerCase(getLine(prompt + " (Y/n): "));
        if (answer.length() == 0 || answer.at(0) == 'y') {
            return true;
        } else if (answer.at(0) == 'n') {
            return false;
        } else {
            cout << "Invalid answer. Please answer either \"y\" or \"n\"" << endl;
        }
    }
}
