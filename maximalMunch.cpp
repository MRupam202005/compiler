#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

void lexicalAnalyzer(const string& input) {
    int i = 0;
    int n = input.length();

    while (i < n) {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (input[i] == '=') {
            if (i + 1 < n && input[i + 1] == '=') {
                cout << "Token: RELATIONAL_OP, Lexeme: ==" << endl;
                i += 2; 
            } else {
                cout << "Token: ASSIGNMENT_OP, Lexeme: =" << endl;
                i++;    
            }
        } 
        else if (input[i] == '>') {
            if (i + 1 < n && input[i + 1] == '=') {
                cout << "Token: RELATIONAL_OP, Lexeme: >=" << endl;
                i += 2;
            } else {
                cout << "Token: RELATIONAL_OP, Lexeme: >" << endl;
                i++;
            }
        }
        else if (isalpha(input[i])) {
            string lexeme = "";
            while (i < n && isalnum(input[i])) {
                lexeme += input[i];
                i++;
            }
            if (lexeme == "int" || lexeme == "return" || lexeme == "if") {
                cout << "Token: KEYWORD, Lexeme: " << lexeme << endl;
            } else {
                cout << "Token: IDENTIFIER, Lexeme: " << lexeme << endl;
            }
        }
        else {
            cout << "Token: UNKNOWN/PUNCTUATOR, Lexeme: " << input[i] << endl;
            i++;
        }
    }
}

int main() {
    ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file 'input.txt'. Make sure it exists in the same directory." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string sourceCode = buffer.str();
    
    inputFile.close();

    cout << "--- Reading from input.txt ---\n" << sourceCode << "\n------------------------------\n\n";
    
    lexicalAnalyzer(sourceCode);
    
    return 0;
}


/*

--- Reading from input.txt ---
int a = 5;
if (a >= 5)
    a == b;
------------------------------

Token: KEYWORD, Lexeme: int
Token: IDENTIFIER, Lexeme: a
Token: ASSIGNMENT_OP, Lexeme: =
Token: UNKNOWN/PUNCTUATOR, Lexeme: 5
Token: UNKNOWN/PUNCTUATOR, Lexeme: ;
Token: KEYWORD, Lexeme: if
Token: UNKNOWN/PUNCTUATOR, Lexeme: (
Token: IDENTIFIER, Lexeme: a
Token: RELATIONAL_OP, Lexeme: >=
Token: UNKNOWN/PUNCTUATOR, Lexeme: 5
Token: UNKNOWN/PUNCTUATOR, Lexeme: )
Token: IDENTIFIER, Lexeme: a
Token: RELATIONAL_OP, Lexeme: ==
Token: IDENTIFIER, Lexeme: b
Token: UNKNOWN/PUNCTUATOR, Lexeme: ;


*/