#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;


ulong getTime(string line) {
	regex word_regex("(\\d+)");
	string time = "";
    auto words_begin = 
        sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = sregex_iterator();
	for (sregex_iterator i = words_begin; i != words_end; ++i) {
		time += (*i).str();
	}

	return stoul(time);
}

ulong getDistance(string line) {
	string distance = "";
	regex word_regex("(\\d+)");
    auto words_begin = 
        sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = sregex_iterator();
	int x = 0;
	for (sregex_iterator i = words_begin; i != words_end; ++i) {
		distance += (*i).str();
		x++;
	}
	return stoul(distance);
}

ulong getNumOfWins(ulong time, ulong distance) {
	ulong reach_dist;
	ulong num_wins = 0;
	for (int x = 1; x <= time; x++) {
		reach_dist = (time - x) * x;
		if (reach_dist > distance) {
			num_wins++;
		}
	}
	return num_wins;
}

ulong getSolvedValue() {
	string line;
	ifstream file ("input.txt");
	ulong solution = 1;
	if (file.is_open()) {
		getline(file, line);
		ulong time = getTime(line);
		getline(file, line);
		ulong distance = getDistance(line);
		solution = getNumOfWins(time, distance);
		file.close();
	} else {
		cout << "Unable to open file!" << endl;
	}
	return solution;
}

int main() {
	int value = getSolvedValue();
	cout << value << endl;
	return 0;
}
67