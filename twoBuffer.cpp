#include<iostream>
#include<fstream>
#include<unordered_set>

using namespace std;

const int BUFFER_SIZE = 8;

char buffer1[BUFFER_SIZE + 1];
char buffer2[BUFFER_SIZE + 1];

ifstream fin;

char* forwardPtr;
char* lexemeBegin;
bool usingFirstBuffer = true;

void loadBuffer(char buffer[]){
    fin.read(buffer,BUFFER_SIZE);
    int n = fin.gcount();
    buffer[n] = '\0';
}

char getChar(){
    char ch = *forwardPtr;

    if(ch == '\0'){
        if(usingFirstBuffer){
            loadBuffer(buffer2);
            forwardPtr = buffer2;
            usingFirstBuffer = false;
        }else{
            loadBuffer(buffer1);
            forwardPtr = buffer1;
            usingFirstBuffer = true;
        }

        ch = *forwardPtr;
    }

    forwardPtr++;
    return ch;
}

bool isKeyWord(string s){
    unordered_set<string> keyWordSet = {
        "int", "float", "char", "if", "else", "while", "for", "return", "void", "double"
    };

    return keyWordSet.contains(s);
}


int main(){
    fin.open("input.txt");
    
    if(!fin){
        cout<<"File not found"<<endl;
        return 0;
    }

    loadBuffer(buffer1);
    loadBuffer(buffer2);

    forwardPtr = buffer1;
    lexemeBegin = buffer2;

    string lexeme = "";

    while(true){
        char ch = getChar();
        
        if(ch == '\0'){
            break;
        }

        if(isalnum(ch) || ch == '_'){
            lexeme += ch;
        }else{
            if(!lexeme.empty()){
                if(isKeyWord(lexeme)){
                    cout<<lexeme<<"-> Keyword"<<endl;
                }else{
                    cout<<lexeme<<"-> Indentifier"<<endl;
                }
                lexeme.clear();
            }
        }
    }

    if(!lexeme.empty()){
        if(isKeyWord(lexeme)){
            cout<<lexeme<<"-> Keyword"<<endl;
        }else{
            cout<<lexeme<<"-> Indentifier"<<endl;
        }
    }

    fin.close();
    return 0;
}



