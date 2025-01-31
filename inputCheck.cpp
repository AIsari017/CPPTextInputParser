#include "inputCheck.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// check if a given file is empty
bool inputCheck::isFileEmpty(const string& filename) {
    ifstream file(filename, ios::ate |ios::binary);

    // Check if the file exists and its size is zero
    return file && file.tellg() == 0;
}


