#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

class BigNum {
private:
    string number;
    bool negative;

public:
    BigNum(string num = "0") {
        if (num[0] == '-') {
            negative = true;
            number = num.substr(1);
        }
        else {
            negative = false;
            number = num;
        }
    }

    string toString()  {
        if (negative && number != "0") {
            return "-" + number;
        }
        else {
            return number;
        }
    }

    bool isNegative()  { return negative; }

    bool Less(const string& a, const string& b)  {
        if (a.length() != b.length()) return a.length() < b.length();
        return a < b;
    }

    string addStrings(const string& a, const string& b)  {
        string ans = "";
        int nho = 0;
        int i = a.size() - 1, j = b.size() - 1;
        while (i >= 0 || j >= 0 || nho) {
            int x;
            if (i >= 0) {
                x = a[i] - '0';
                i--;
            }
            else {
                x = 0;
            }

            int y;
            if (j >= 0) {
                y = b[j] - '0';
                j--;
            }
            else {
                y = 0;
            }

            int sum = x + y + nho;
            ans.push_back(sum % 10 + '0');
            nho = sum / 10;
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }

    string subtractStrings(const string& a, const string& b)  {
        string ans = "";
        int muon = 0, i = a.size() - 1, j = b.size() - 1;

        while (i >= 0) {
            int x = a[i--] - '0';
            int y = (j >= 0 ? b[j--] - '0' : 0) + muon;
            if (x < y) {
                x += 10;
                muon = 1;
            }
            else {
                muon = 0;
            }
            ans.push_back(x - y + '0');
        }
        while (ans.length() > 1 && ans.back() == '0') ans.pop_back();
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string multiplyStrings(const string& a, const string& b)  {
        vector<int> ans(a.size() + b.size(), 0);
        for (int i = a.size() - 1; i >= 0; --i) {
            for (int j = b.size() - 1; j >= 0; --j) {
                ans[i + j + 1] += (a[i] - '0') * (b[j] - '0');
            }
        }
        for (int i = ans.size() - 1; i > 0; --i) {
            ans[i - 1] += ans[i] / 10;
            ans[i] %= 10;
        }
        string res = "";
        for (int i = 0; i < ans.size(); i++)
            res += (ans[i] + '0');
        res.erase(0, res.find_first_not_of('0'));
        if (res.empty())
            return "0";
        else return res;
    }

    string divideStrings(const string& a, const string& b, bool& error)  {
        if (b == "0") {
            error = true;
            return "";
        }

        string result = "0", temp = "0";
        string divisor = b;
        BigNum bichia(a), sochia(b);
        BigNum count("0");
        BigNum one("1");

        while (!sochia.Less(temp = sochia.multiplyStrings(sochia.toString(), count.toString()), a)) {
            count = BigNum(sochia.addStrings(count.toString(), one.toString()));
        }

        return sochia.subtractStrings(count.toString(), one.toString());
    }

    BigNum operator+(const BigNum& other)  {
        if (negative == other.negative) {
            if (negative) {
                return BigNum("-" + addStrings(number, other.number));
            }
            else {
                return BigNum(addStrings(number, other.number));
            }
        }
        else {
            if (Less(number, other.number)) {
                if (other.negative) {
                    return BigNum("-" + subtractStrings(other.number, number));
                }
                else {
                    return BigNum(subtractStrings(other.number, number));
                }
            }
            else {
                if (negative) {
                    return BigNum("-" + subtractStrings(number, other.number));  
                }
                else {
                    return BigNum(subtractStrings(number, other.number));  
                }
            }
        }
    }

    BigNum operator-(const BigNum& other)  {
        BigNum negOther = other;
        negOther.negative = !negOther.negative;
        return *this + negOther;
    }

    BigNum operator*(const BigNum& other)  {
        string result = multiplyStrings(number, other.number);
        bool resNeg = negative ^ other.negative;
        if (resNeg) {
            return BigNum("-" + result);
        }
        else {
            return BigNum(result);
        }
    }

    BigNum operator/(const BigNum& other)  {
        bool error = false;
        string result = divideStrings(number, other.number, error);
        if (error) {
            return BigNum("Error");
        }
        bool resNeg = negative ^ other.negative;
        if (resNeg) {
            return BigNum("-" + result);
        }
        else {
            return BigNum(result);
        }
    }
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    int i = 0;
    while (i < expr.length()) {
        if (isspace(expr[i])) {
            ++i;
            continue;
        }
        if (isdigit(expr[i])) {
            string num = "";
            while (i < expr.length() && isdigit(expr[i])) {
                num += expr[i++];
            }
            tokens.push_back(num);
        }
        else if (expr[i] == '(' || expr[i] == ')') {
            tokens.push_back(string(1, expr[i++])); 
        }
        else if (isOperator(expr[i])) {
            if (expr[i] == '-' && (tokens.empty() || tokens.back() == "(" || isOperator(tokens.back()[0]))) {
                string num = "-";
                ++i;
                while (i < expr.length() && isdigit(expr[i])) {
                    num += expr[i++];
                }
                tokens.push_back(num);
            }
            else {
                tokens.push_back(string(1, expr[i++])); 
            }
        }
        else {
            return { "Error" };  
        }
    }
    return tokens;
}

vector<string> infixToPostfix(const vector<string>& tokens) {
    vector<string> ans;
    stack<string> ops;

    for (const string& token : tokens) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            ans.push_back(token);
        }
        else if (token == "(") {
            ops.push(token);
        }
        else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                ans.push_back(ops.top());
                ops.pop();
            }
            if (ops.empty()) return { "Error" };  
            ops.pop();  
        }
        else if (isOperator(token[0])) {
            while (!ops.empty() && precedence(ops.top()[0]) >= precedence(token[0])) {
                ans.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }

    while (!ops.empty()) {
        if (ops.top() == "(" || ops.top() == ")") return { "Error" };
        ans.push_back(ops.top());
        ops.pop();
    }

    return ans;
}

string evaluatePostfix(const vector<string>& postfix) {
    stack<BigNum> st;
    for (const string& token : postfix) {
        if (isOperator(token[0]) && token.length() == 1) {
            if (st.size() < 2) return "Error"; 
            BigNum b = st.top(); st.pop();
            BigNum a = st.top(); st.pop();

            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else if (token == "/") st.push(a / b);
        }
        else {
            st.push(BigNum(token));
        }
    }
    if (st.size() != 1) return "Error"; 
    return st.top().toString();
}

string evaluateExpression(const string& expr) {
    vector<string> tokens = tokenize(expr);
    if (tokens.front().substr(0, 5) == "Error") return tokens.front();
    vector<string> postfix = infixToPostfix(tokens);
    if (postfix.front().substr(0, 5) == "Error") return postfix.front();
    return evaluatePostfix(postfix);
}

int main() {
    ifstream fIn("tests.txt");
    if (!fIn.is_open()) {
        cerr << "Error" << endl;
        return 1;
    }
    ofstream fOut("output_24120346.txt");
    if (!fOut.is_open()) {
        cerr << "Error" << endl;
        return 1;
    }
    string s;
    while (getline(fIn, s)) {
        string result = evaluateExpression(s);
        fOut << result << endl;
        cout << result << endl;
    }
    fIn.close();
    fOut.close();
    return 0;
}
