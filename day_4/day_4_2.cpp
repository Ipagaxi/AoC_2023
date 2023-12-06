#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int getValueOfCard(vector<int> left_numbers, vector<int> right_numbers) {
    int value = 0;
    for (int right_num : right_numbers) {
        for (int left_num : left_numbers) {
            if (right_num == left_num) {
                value++;
            }
        }
    }
    return value;
}

vector<int> parseNumbers(string numbers) {
    vector<int> numbers_vec;
    for (int x = 0; x < numbers.length(); x += 3) {
        numbers_vec.push_back(stoi(numbers.substr(x, 2)));
    }
    return numbers_vec;
}

void parseLine(string line, vector<int> *left_numbers, vector<int> *right_numbers) {
    int numbers_start = line.find(":") + 2;
    int numbers_seperator = line.find("|");
    string left_numbers_string = line.substr(numbers_start, numbers_seperator - numbers_start - 1);
    string right_numbers_string = line.substr(numbers_seperator + 2);
    *left_numbers = parseNumbers(left_numbers_string);
    *right_numbers = parseNumbers(right_numbers_string);
}

int parseAndGetValueOfCard(vector<string> lines) {
    vector<int> left_numbers;
    vector<int> right_numbers;
    int num_each_card[lines.size()];
    fill_n(num_each_card, lines.size(), 1);
    int sum = 0;
    for (int line_index = 0; line_index < lines.size(); line_index++) {
        parseLine(lines[line_index], &left_numbers, &right_numbers);
        int value = getValueOfCard(left_numbers, right_numbers);
        sum += num_each_card[line_index];
        for (int array_index = 0; array_index < num_each_card[line_index]; array_index++) {
            for (int copy_index = 0; copy_index < value && line_index + copy_index + 1 < lines.size(); copy_index++) {
                num_each_card[line_index+copy_index+1]++;
            }
        }
    }
    return sum;
}

int main() {
    string line;
    ifstream file ("input.txt");
    int sum = 0;
    if (file.is_open()) {
        vector<string> lines;
        while (getline (file, line)) {
            lines.push_back(line);
        }
        sum = parseAndGetValueOfCard(lines);
        file.close();
    } else {
        cout << "Unable to open file";
    }
    cout << sum << endl;

    return 0;
}