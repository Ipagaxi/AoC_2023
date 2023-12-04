#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int getSumOfLegalValues(list<string> input_matrix) {
    int sum = 0;
    list<string>::iterator matrix_iter = input_matrix.begin();
    int last_index = (*matrix_iter).length()-1;
    bool is_valid_num = false;
    
    for (matrix_iter = input_matrix.begin(); matrix_iter != input_matrix.end(); matrix_iter++) {
        for (int x = 0; x < (*matrix_iter).length(); x++) {
            is_valid_num = false;

            if ((*matrix_iter)[x] >= 48 && (*matrix_iter)[x] <= 57) {
                string num = "";
                num += (*matrix_iter)[x];
                int num_indices[2];
                num_indices[0] = x;
                num_indices[1] = x;
                int y = x+1;
                // Get the complete number
                while (((*matrix_iter)[y] >= 48) && ((*matrix_iter)[y] <= 57)) {
                    num += (*matrix_iter)[y];
                    num_indices[1] = y;
                    y++;
                }

                // Check if symbol exists before number
                if (num_indices[0] != 0) {
                    // unicode(46) = '.'
                    if ((*matrix_iter)[num_indices[0]-1] != 46) {
                        is_valid_num = true;
                    }
                }
                // Check if symbol exists after number
                if (num_indices[1] != last_index) {
                    if ((*matrix_iter)[num_indices[1]+1] != 46) {
                        is_valid_num = true;
                    }
                }
                // Check if symbol above number exists
                if (matrix_iter != input_matrix.begin()) {
                    list<string>::iterator prev_iter = matrix_iter;
                    prev_iter--;

                    for (int x = max(0, num_indices[0]-1); x <= min(last_index, num_indices[1]+1); x++) {
                        if (((*prev_iter)[x] < 48 || (*prev_iter)[x] > 57) && (*prev_iter)[x] != 46) {
                            is_valid_num = true;
                        }
                    }
                }
                // Check if symbol under number exists
                if (next(matrix_iter, 1) != input_matrix.end()) {
                    list<string>::iterator next_iter = matrix_iter;
                    next_iter++;

                    for (int x = max(0, num_indices[0]-1); x <= min(last_index, num_indices[1]+1); x++) {
                        if (((*next_iter)[x] < 48 || (*next_iter)[x] > 57) && (*next_iter)[x] != 46) {
                            is_valid_num = true;
                        }
                    }
                }
                if (is_valid_num) {
                    sum += stoi(num);
                }
                x = y-1;
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