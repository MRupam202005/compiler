#include<iostream>
#include<fstream>
#include<unordered_set>
#include<iomanip>

using namespace std;

const int BUFFER_SIZE = 4096;
char buffer1[BUFFER_SIZE + 1];
char buffer2[BUFFER_SIZE + 1];

bool isKeyWord(string s){
    unordered_set<string> keyWordSet = {
        "int", "float", "char", "if", "else", "while", "for", "return", "void", "double"
    };

    return keyWordSet.contains(s);
}

int main(){
    ifstream file("input.txt");

    if(!file){
        cout<<"Cannot open file"<<endl;
        return 0;
    }

    bool firstBuffer = true;

    int line = 1;

    while(true){
        if(firstBuffer){
            file.read(buffer1,BUFFER_SIZE);
        }else{
            file.read(buffer2, BUFFER_SIZE);
        }

        int count = file.gcount();

        if(count == 0) break;

        if(firstBuffer){
            buffer1[count] = '$';
        }else{
            buffer2[count] = '$';
        }

        char *current = firstBuffer ? buffer1 : buffer2;
        int i = 0;

        while(current[i] != '$'){
            char ch = current[i];

            if(ch== '\n'){
                line++;
                i++;
                continue;
            }

            if(isspace(ch)){
                i++;
                continue;
            }

            if(ch == '/' && current[i+1] == '/'){
                while(current[i] != '\n' && current[i]!= '$'){
                    i++;
                }
                continue;
            }

            if(isalpha(ch) || ch == '_'){
                string word = "";

                while(isalnum(current[i]) || current[i] == '_'){
                    word += current[i];
                    i++;
                }
                
                cout<<left<<setw(8)<<line<<setw(20)<<word;
                if(isKeyWord(word)){
                    cout<<"Keyword";
                }else{
                    cout<<"Indentifier";
                }

                cout<<endl;
                continue;
            }

            if(isdigit(ch)){
                string num;

                while(isdigit(current[i]) || current[i] == '.'){
                    num += current[i];
                    i++;
                }

                cout<<left<<setw(8)<<line<<setw(20)<<num << "Constant"<<endl;

                continue;
            }

            if(ch == '"'){
                string str;
                str += ch;
                i++;

                while(current[i] != '"' && current[i] != '$'){
                    str += current[i];
                    i++;
                }

                if(current[i] == '"'){
                    str += '"';
                    i++;
                }

                cout<<left<<setw(8)<<line<<setw(20)<< str<<"Literal"<<endl;

                continue;
            }

            if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>' || ch == '!' || ch == '%'){
                string op;
                op += ch;

                if((ch == '=' || ch == '<' || ch == '>' || ch == '!') && current[i+1] == '='){
                    op += '=';
                    i++;
                }

                cout<<left<<setw(8)<<line<<setw(20)<< op<<"Literal"<<endl;
                i++;
                continue;
            }

            if(ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']'){
                string d;
                d += ch;

                cout<<left<<setw(8)<<line<<setw(20)<<d<<"Delimiter"<<endl;
                i++;
                continue;
            }
            i++;
        }

        firstBuffer != firstBuffer;
    }

    file.close();
    return 0;
}


/*
input.txt
int main()
{
    int a = 10;
    float b = 20.5;
    char ch = 'A';
    // this is comment

    if(a > 5)
    {
        a = a + 1;
        return a;
    }

    printf("Hello World");
}

*/
