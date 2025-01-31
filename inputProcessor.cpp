#include "inputProcessor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

// Processes the payments.txt and people.txt, mapping list of people to their corresponding payments
void inputProcessor::processFiles(const string& peopleFile, const string& paymentsFile) {
    unordered_map<string, bool> peopleMap; // map to store valid people
    loadPeople(peopleFile, peopleMap); // load the list of people into the map
    processPayments(paymentsFile, peopleMap); // process payments and match them with valid people
}

// Loads a list of people from a file into an unordered_map
void inputProcessor::loadPeople(const string& peopleFile, unordered_map<string, bool>& peopleMap) {
    ifstream file(peopleFile);
    if (!file) { // this is the check to see if the file was successfully opened
        cerr << "Error: Unable to open people file." << endl;
        return;
    }

    string name; //variable that stores names of the people
    while (getline(file, name)) { //read each line and add the name to the map
        if (!name.empty()) {
            peopleMap[name] = true;
        }
    }
    file.close();
}

// Processes payment data and associates it with valid people from the peopleMap
void inputProcessor::processPayments(const string& paymentsFile, const unordered_map<string, bool>& peopleMap) {
    ifstream file(paymentsFile);
    if (!file) { //check to see whether the file was succesfully opened
        cerr << "Error: Unable to open payments file." << endl;
        return;
    }

    unordered_map<string, vector<Item>> personItems; //map to store items for each person
    string line;                                     //variable to store each line
    int lineNumber = 0;                              //counter to keep the number of the current line

    while (getline(file, line)) {              //read file line by line
        lineNumber++;
        istringstream iss(line);
        string name, item;
        double price;

        //check to validate the line format (<name> <item> <price>), throws an error for unexpected format
        if (!(iss >> name >> item >> price)) {
            cerr << "Error: Invalid format on line " << lineNumber << ": \"" << line << "\"" << endl;
            cerr << "Each line must be in the format: <name> <item> <price>" << endl;
            exit(1);
        }

        //check for the extra unexpected fields, throws an error if there's extra fields
        string extraField;
        if (iss >> extraField) {
            cerr << "Error: Too many fields on line " << lineNumber << ": \"" << line << "\"" << endl;
            cerr << "Each line must contain exactly three fields." << endl;
            exit(1);
        }

        // if the name exists in the peopleMap, add the item and price to their list
        if (peopleMap.find(name) != peopleMap.end()) {
            personItems[name].push_back({item, price});
        }
    }
    file.close();

    //final formating for the output of the results
    for (const auto& person : personItems) {
        cout << person.first << endl; //prints persons name
        double total = 0;
        for (const auto& item : person.second) {
            cout << item.name << " " << item.price << endl; //prints the items and their price
            total += item.price; //accumulates the total
        }
        cout << "Total: " << total << endl; //prints total cost
    }
}
