#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;

// Function to check if a token is an operator
bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^" || token == "v";
}

bool isNumber(const string& token) {
    stringstream ss(token);
    double num;
    // Try to extract a number from the stringstream
    return ss >> num && ss.eof(); // Return true if extraction successful and no further characters left
}

// Function to evaluate an operation
double evaluateOperation(double operand1, double operand2, const string& op) {
    if (op == "+")
        return operand1 + operand2;
    else if (op == "-")
        return operand1 - operand2;
    else if (op == "*")
        return operand1 * operand2;
    else if (op == "/")
        return operand1 / operand2;
    else if (op == "%")
        return fmod(operand1, operand2);
    else if (op == "^")
        return pow(operand1, operand2);
    else if (op == "v")
        return sqrt(operand1);
    else {
        cerr << "Invalid operator: " << op << endl;
        return NAN; // Not a number
    }
}

// Function to evaluate a PostFix expression
double evaluatePostFix(const string& expression) {
    stack<double> operands; // Stack to hold operands

    stringstream ss(expression); // String stream to tokenize the expression
    string token;

    while (ss >> token) { // Tokenize the expression
        if (isNumber(token)) { // If token is a number, push it onto the stack
            operands.push(stod(token));
        } else if (isOperator(token)) { // If token is an operator
            if (operands.size() < 2) { // Ensure there are enough operands in the stack
                cerr << "Invalid expression: insufficient operands for operator " << token << endl;
                return NAN;
            }
            // Pop the top two operands from the stack
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            // Evaluate the operation and push the result onto the stack
            operands.push(evaluateOperation(operand1, operand2, token));
        } else { // If token is neither a number nor an operator
            cerr << "Invalid token: " << token << endl;
            return NAN;
        }
    }

    // At the end, there should be exactly one operand left in the stack
    if (operands.size() != 1) {
        cerr << "Invalid expression: too many operands" << endl;
        return NAN;
    }

    // Return the final result
    return operands.top();
}

int main(int argc, char *argv[]) {
    // Check if the program was invoked with the -p flag for prompt
    bool prompt = false;
    if (argc > 1 && string(argv[1]) == "-p") {
        prompt = true;
    }

    string expression;
    if (prompt) {
        // Print prompt
        cout << "Enter a PostFix expression: ";
        getline(cin, expression);
    } else {
        // Read the expression directly
        getline(cin, expression);
    }

    // Evaluate the expression and print the result
    double result = evaluatePostFix(expression);
    if (!isnan(result))
        cout << result << endl;

    return 0;
}
