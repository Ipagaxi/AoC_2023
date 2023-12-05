#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

bool charIsDigit(int symbol) {
    return ((symbol >= 48) && (symbol <= 57));
}

string getCompleteNumber(string line, int index, int direction) {
    string num = "";
    while (index >= 0 && index <= line.length()-1 && charIsDigit(line[index])) {
        if (direction > 0) {
            num += line[index];
        } else {
            num = line[index] + num;
        }
        index += direction;
    }
    return num;
}
// 76517756
int getSumOfLegalValues(list<string> input_matrix) {
    int sum = 0;
    list<string>::iterator matrix_iter = input_matrix.begin();
    int last_index = (*matrix_iter).length()-1;
    bool is_valid_num = false;
    int counter = 1;
    
    for (matrix_iter = input_matrix.begin(); matrix_iter != input_matrix.end(); matrix_iter++) {
        cout << "------------------" << counter << "------------------"<< endl;
        counter++;
        for (int x = 0; x < (*matrix_iter).length(); x++) {
            is_valid_num = false;
            // unicode(42) = '*'
            if ((*matrix_iter)[x] == 42) {
                list<int> factors;
                int num_index = x;

                // Check if number exists before '*'
                if (num_index != 0) {
                    // unicode(46) = '.'
                    if (charIsDigit((*matrix_iter)[num_index-1])) {
                        string number = getCompleteNumber(*matrix_iter, num_index - 1, -1);
                        //cout << "number before: " << number << endl;
                        factors.push_back(stoi(number));
                    }
                }
                // Check if number exists after '*'
                if (num_index != last_index) {
                    if (charIsDigit((*matrix_iter)[num_index+1])) {
                        string number = getCompleteNumber(*matrix_iter, num_index + 1, 1);
                        //cout << "number after: " << number << endl;
                        factors.push_back(stoi(number));
                    }
                }
                // Check if number above '*' exists
                if (matrix_iter != input_matrix.begin()) {
                    if (charIsDigit((*prev(matrix_iter,1))[x])) {
                        string number = getCompleteNumber(*prev(matrix_iter, 1), x, -1);
                        if (x < last_index) {
                            number += getCompleteNumber(*prev(matrix_iter, 1), x+1, 1);
                        }
                        //cout << "number above: " << number << endl;
                        factors.push_back(stoi(number));
                    } else {
                        if (charIsDigit((*prev(matrix_iter))[max(x-1, 0)])) {
                            string number = getCompleteNumber(*prev(matrix_iter), x-1, -1);
                            //cout << "number above: " << number << endl;
                            factors.push_back(stoi(number));
                        }
                        if (charIsDigit((*prev(matrix_iter, 1))[min(x+1, last_index)])) {
                            string number = getCompleteNumber(*prev(matrix_iter, 1), x+1, 1);
                            //cout << "number above: " << number << endl;
                            factors.push_back(stoi(number));
                        }
                    }
                }
                // Check if number under '*' exists
                if (next(matrix_iter, 1) != input_matrix.end()) {
                    if (charIsDigit((*next(matrix_iter,1))[x])) {
                        string number = getCompleteNumber(*next(matrix_iter, 1), x, -1);
                        if (x < last_index) {
                            number += getCompleteNumber(*next(matrix_iter, 1), x+1, 1);
                        }
                        //cout << "number under: " << number << endl;
                        factors.push_back(stoi(number));
                    } else {
                        if (charIsDigit((*next(matrix_iter))[max(x-1, 0)])) {
                            string number = getCompleteNumber(*next(matrix_iter), x-1, -1);
                            //cout << "number under: " << number << endl;
                            factors.push_back(stoi(number));
                        }
                        if (charIsDigit((*next(matrix_iter, 1))[min(x+1, last_index)])) {
                            string number = getCompleteNumber(*next(matrix_iter, 1), x+1, 1);
                            //cout << "number under: " << number << endl;
                            factors.push_back(stoi(number));
                        }
                    } 
                }
                if (factors.size() == 2) {
                    cout << factors.front() << " * " << factors.back() << endl;
                    sum += (factors.front() * factors.back());
                }
                //cout << "#######" << endl;
            }
        }
    }

    return sum;
}

int main() {
    string line;
    ifstream myfile ("input.txt");
    list<string> input_matrix;
    if (myfile.is_open()) {
        while ( getline (myfile, line) ) {
            input_matrix.push_back(line);
        }
        myfile.close();
    } else cout << "Unable to open file" << endl;

    int sum = getSumOfLegalValues(input_matrix);

    cout << sum << endl;

    return 0;
}