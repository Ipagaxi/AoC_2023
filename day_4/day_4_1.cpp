#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int getValueOfCard(vector<int> left_numbers, vector<int> right_numbers) {
    float value = 0.5;
    for (int right_num : right_numbers) {
        for (int left_num : left_numbers) {
            if (right_num == left_num) {
                value *= 2;
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

int parseAndGetValueOfCard(string line) {
    vector<int> left_numbers;
    vector<int> right_numbers;
    parseLine(line, &left_numbers, &right_numbers);
    return getValueOfCard(left_numbers, right_numbers);
}

int main() {
    string line;
    ifstream file ("input.txt");
    int sum = 0;
    if (file.is_open()) {
        while (getline (file, line)) {
            sum += parseAndGetValueOfCard(line);
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }
    cout << sum << endl;

    return 0;
}