#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

// Morse code dictionary
map<char, string> englishToMorse = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
    {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
    {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
    {'0', "-----"}, {' ', "/"}
};
map<string, char> morseToEnglish;

map<char, string> englishToBraille = {
    {'A', "100000"}, {'B', "101000"}, {'C', "110000"}, {'D', "110100"}, {'E', "100100"},
    {'F', "111000"}, {'G', "111100"}, {'H', "101100"}, {'I', "011000"}, {'J', "011100"},
    {'K', "100010"}, {'L', "101010"}, {'M', "110010"}, {'N', "110110"}, {'O', "100110"},
    {'P', "111010"}, {'Q', "111110"}, {'R', "101110"}, {'S', "011010"}, {'T', "011110"},
    {'U', "100011"}, {'V', "101011"}, {'W', "011101"}, {'X', "110011"}, {'Y', "110111"},
    {'Z', "100111"}, {'1', "100000"}, {'2', "101000"}, {'3', "110000"}, {'4', "110100"},
    {'5', "100100"}, {'6', "111000"}, {'7', "111100"}, {'8', "101100"}, {'9', "011000"},
    {'0', "011100"}, {' ', "000000"}
};
map<string, char> brailleToEnglish;

// Initialize reverse mappings
void initializeReverseMappings() {
    for (const auto& pair : englishToMorse)
        morseToEnglish[pair.second] = pair.first;

    for (const auto& pair : englishToBraille)
        brailleToEnglish[pair.second] = pair.first;
}

// Convert English to Morse
string convertToMorse(const string& text) {
    stringstream morseCode;
    for (char c : text) {
        c = toupper(c);
        if (englishToMorse.count(c)) {
            morseCode << englishToMorse[c] << " ";
        }
    }
    return morseCode.str();
}

// Convert English to Braille
string convertToBraille(const string& text) {
    stringstream brailleCode;
    for (char c : text) {
        c = toupper(c);
        if (englishToBraille.count(c)) {
            brailleCode << englishToBraille[c] << " ";
        }
    }
    return brailleCode.str();
}

// Convert Morse to English
string convertMorseToEnglish(const string& morseCode) {
    stringstream englishText;
    stringstream morseStream(morseCode);
    string code;

    while (morseStream >> code) {
        if (morseToEnglish.count(code)) {
            englishText << morseToEnglish[code];
        }
    }
    return englishText.str();
}

// Convert Braille to English
string convertBrailleToEnglish(const string& brailleCode) {
    stringstream englishText;
    stringstream brailleStream(brailleCode);
    string code;

    while (brailleStream >> code) {
        if (brailleToEnglish.count(code)) {
            englishText << brailleToEnglish[code];
        }
    }
    return englishText.str();
}

// Save to file in append mode
void saveToFile(const string& filename, const string& content) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << content << "\n";
        file.close();
        cout << "Output appended to file: " << filename << endl;
    }
    else {
        cout << "Error saving file." << endl;
    }
}

// Main function
int main() {
    initializeReverseMappings();

    cout << "Welcome to the Language Conversion Tool!\n";
    cout << "Choose an option:\n";
    cout << "1. Convert English to Morse code\n";
    cout << "2. Convert English to Braille\n";
    cout << "3. Convert English to both Morse and Braille\n";
    cout << "4. Convert Morse code to English\n";
    cout << "5. Convert Braille to English\n";
    int choice;
    cin >> choice;
    cin.ignore();

    string input, output;

    switch (choice) {
    case 1:
        cout << "Enter English text: ";
        getline(cin, input);
        output = convertToMorse(input);
        cout << "\nMorse Code Output:\n" << output << endl;
        saveToFile("MorseCodeOutput.txt", output);
        break;

    case 2:
        cout << "Enter English text: ";
        getline(cin, input);
        output = convertToBraille(input);
        cout << "\nBraille Code Output:\n" << output << endl;
        saveToFile("BrailleCodeOutput.txt", output);
        break;

    case 3:
        cout << "Enter English text: ";
        getline(cin, input);
        output = "Morse: " + convertToMorse(input) + "\nBraille: " + convertToBraille(input);
        cout << "\nCombined Output:\n" << output << endl;
        saveToFile("CombinedOutput.txt", output);
        break;

    case 4:
        cout << "Enter Morse code (separate characters with spaces, words with '/'): ";
        getline(cin, input);
        output = convertMorseToEnglish(input);
        cout << "\nEnglish Text Output:\n" << output << endl;
        saveToFile("MorseToEnglishOutput.txt", output);
        break;

    case 5:
        cout << "Enter Braille code (separate characters with spaces): ";
        getline(cin, input);
        output = convertBrailleToEnglish(input);
        cout << "\nEnglish Text Output:\n" << output << endl;
        saveToFile("BrailleToEnglishOutput.txt", output);
        break;

    default:
        cout << "Invalid choice. Exiting.\n";
    }

    return 0;
}
