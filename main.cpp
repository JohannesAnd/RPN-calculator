#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

int calculateRPN(vector<string> inn){
    stack<int> st;
    for(vector<string>::iterator it = inn.begin(); it != inn.end(); it++){
        if(isdigit((*it)[0]) || (*it).length()>1){
            st.push(stoi(*it));
        }else {
            int op1 = st.top(); st.pop();
            int op2 = st.top(); st.pop();
            switch((*it)[0]){
                case '+':
                    st.push(op2+op1);
                    break;
                case '-':
                    st.push(op2-op1);
                    break;
                case '*':
                    st.push(op2*op1);
                    break;
                case '/':
                    st.push(op2/op1);
                    break;
                case '^':
                    st.push(pow(op2, op1));
            }
        }
    }
    return st.top();
}

vector<string> separateString(string str){
    vector<string> out;
    int sind = 0;
    for(int i = 0; i < str.length(); i++){
        if(!isdigit(str[i])) {
            if(sind!=i){
                out.push_back(str.substr(sind, i-sind));
            }
            out.push_back(str.substr(i, 1));
            sind = i+1;
        }
    }
    if(sind != str.length()){
        out.push_back(str.substr(sind));
    }
    return out;
}

bool crazytest(string a, string b){
    if (a=="^" || b=="("){
        return false;
    }else if ((a=="/" || a=="*") && (b=="+" || b=="-")){
         return false;
    }else{
        return true;
    }
}

vector<string> infixToRPN(vector<string> inn){
    vector<string> out;
    stack<string> opstack;
    for(vector<string>::iterator it = inn.begin(); it != inn.end(); it++){
        if(isdigit((*it)[0]) || (*it).length() > 1){        //Is a number
            out.push_back(*it);
        }else if((*it) == "("){
            opstack.push(*it);
        }else if ((*it) == ")"){
            while(opstack.top() != "("){
                out.push_back(opstack.top());
                opstack.pop();
            }
            opstack.pop();

        }else{
            while(!opstack.empty() && crazytest((*it), opstack.top())) {
                out.push_back(opstack.top());
                opstack.pop();
            }
            opstack.push(*it);
        }
    }
    while(!opstack.empty()){
        out.push_back(opstack.top());
        opstack.pop();
    }
    return out;
}

int main() {
    string exp = "((0-4)/(0-1))^(6)+(4+2^4)*5";
    cout << exp << " = "<< calculateRPN(infixToRPN(separateString(exp))) << endl;
    return 0;
}