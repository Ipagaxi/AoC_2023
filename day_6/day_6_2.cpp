#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

struct Race {
	ulong time;
	ulong distance;
};



vector<Race> parseTimesIntoRaceVec(string line) {
	vector<Race> races;
	regex word_regex("(\\d+)");
    auto words_begin = 
        sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = sregex_iterator();
	for (sregex_iterator i = words_begin; i != words_end; ++i) {
		races.push_back(Race{stoul((*i).str())});
	}

	return races;
}

vector<Race> parseDistancesIntoRaceVec(string line, vector<Race> races) {
	regex word_regex("(\\d+)");
    auto words_begin = 
        sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = sregex_iterator();
	int x = 0;
	for (sregex_iterator i = words_begin; i != words_end; ++i) {
		races[x].distance = stoul((*i).str());
		x++;
	}
	return races;
}

ulong getNumOfWins(Race race) {
	int reach_dist;
	int num_wins = 0;
	for (int x = 1; x <= race.time; x++) {
		reach_dist = (race.time - x) * x;
		if (reach_dist > race.distance) {
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
		vector<Race> races = parseTimesIntoRaceVec(line);
		getline(file, line);
		races = parseDistancesIntoRaceVec(line, races);
		for (Race race : races) {
			solution *= getNumOfWins(race);
		}
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
