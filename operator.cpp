
#include <iostream>
#include <stack>
#include <string>
using namespace std;

char precedence(char a, char b) {
    if (a == '+' || a == '-') {
        if (b == '+' || b == '-' || b == ')' || b == '$')
            return '>';
        return '<';
    }

    if (a == '*' || a == '/') {
        if (b == '+' || b == '-' || b == ')' || b == '$')
            return '>';
        return '<';
    }

    if (a == '(') {
        if (b == ')') return '=';
        return '<';
    }

    if (a == ')') return '>';

    if (a == '$') {
        if (b == '$') return '=';
        return '<';
    }

    if (a == 'i') {
        return '>';
    }

    return ' ';
}

int main() {
    string input;
    cout << "Enter expression: ";
    cin >> input;

    input += "$";

    stack<char> st;
    st.push('$');

    int i = 0;

    while (true) {
        char top = st.top();
        char current = input[i];

        if (top == '$' && current == '$') {
            cout << "Expression Accepted\n";
            break;
        }

        if (current == 'i') {
            st.push('i');
            i++;
            continue;
        }

        char relation = precedence(top, current);

        if (relation == '<' || relation == '=') {
            st.push(current);
            i++;
        }
        else if (relation == '>') {
            st.pop();
        }
        else {
            cout << "Expression Rejected\n";
            break;
        }
    }

    return 0;
}


/*

Enter expression: i+i*i
Expression Accepted

Enter expression: i+i
Expression Accepted

Enter expression: i+*i
Expression Rejected

Enter expression: (i+i)*i
Expression Accepted


*/