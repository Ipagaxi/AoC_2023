#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int getSumOfLegalValues(list<string> input_matrix) {
    int sum;
    list<string>::iterator matrix_iter = input_matrix.begin();
    string num;
    int num_indices[2];
    int last_index = (*matrix_iter).length()-1;
    bool is_valid_num = false;
    for (int x = 0; x < (*matrix_iter).length(); x++) {
        if ((*matrix_iter)[x] >= 48 && (*matrix_iter)[x] <= 57) {
            num_indices[0] = x;
            int y = x;
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
                string top_line = matrix_iter.prev;

                for (int x = max(0, num_indices[0]-1); x <= min(last_index, num_indices[1]+1); x++) {
                    if ()
                }
            }
        }
    }
    while (matrix_iter != input_matrix.end()) {

        matrix_iter++;
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
    } else cout << "Unable to open file";

    int sum = getSumOfLegalValues(input_matrix);

    cout << sum << endl;

    return 0;
}