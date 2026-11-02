#include <iostream>
#include <string>

using namespace std;

void generateCFG(const string& input) {
    string repeating_unit = "aab";
    string tail = "aa";
   
    cout << "Analyzing string: " << input << "\n";
    cout << "--------------------------------------------------\n";
   
    cout << "1. Language Pattern:\n";
    cout << "   The string consists of the repeating block '" << repeating_unit
         << "' followed by a terminating '" << tail << "'.\n";
    cout << "   Pattern formula: L = { (" << repeating_unit << ")^n " << tail << " | n > 0 }\n";

    int n = (input.length() - tail.length()) / repeating_unit.length();
    cout << "   For the given input '" << input << "', n = " << n << ".\n\n";

    cout << "2. Context-Free Grammar (CFG):\n";
    cout << "   S -> " << repeating_unit << "S | " << tail << "\n\n";
   
    cout << "3. Derivation for n = " << n << ":\n";
    string current = "S";
    cout << "   " << current << "\n";
   
    for (int i = 0; i < n; i++) {
        current = current.replace(current.find("S"), 1, repeating_unit + "S");
        cout << "   => " << current << "\n";
    }
   
    current = current.replace(current.find("S"), 1, tail);
    cout << "   => " << current << " (Final derived string)\n";
}

int main() {
    string terminals = "aabaabaa";
    generateCFG(terminals);
    return 0;
}


