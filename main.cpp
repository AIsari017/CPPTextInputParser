#include <iostream>
#include "inputCheck.h"
#include "inputProcessor.h"

using namespace std;

int main() {

    //input files
    string peopleFile = "people.txt";
    string paymentsFile = "payments.txt";

    // an instance of inputCheck to validate the input files
    inputCheck check;


    if (!check.isFileEmpty(peopleFile) && !check.isFileEmpty(paymentsFile))
    {
        cout << "Processing files.." << endl;

        // an instance of inputProcessor to handle file processing
        inputProcessor processor;

        // process the files and associate people with their payment details
        processor.processFiles(peopleFile, paymentsFile);
    }
    //call the isFileEmpty method from inputCheck in order to determine whether the people.txt file is empty
    else if(check.isFileEmpty(peopleFile)) {
        cout << "The people.txt file is empty." << endl;
    }

    return 0;
}
