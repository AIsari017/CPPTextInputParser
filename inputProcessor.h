#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <string>
#include <unordered_map>


using namespace std;

// struct to represent an item associated with a payment
struct Item {
    string name;   // name of the purchased item
    double price;  // price of the purchased item
};

//handles processing of files for people.txt and payment.txt details
class inputProcessor {
public:
    // proccesses the payments.txt and people.txt, mapping list of people to their corresponding payments
    void processFiles(const string& peopleFile, const string& paymentsFile);

private:
    // loads a list of people from a file into an unordered_map
    void loadPeople(const string& peopleFile, unordered_map<string, bool>& peopleMap);

    // processes the payments.txt and people.txt, mapping list of people to their corresponding payments
    void processPayments(const string& paymentsFile, const unordered_map<string, bool>& peopleMap);
};

#endif