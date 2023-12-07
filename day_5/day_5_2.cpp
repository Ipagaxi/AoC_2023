#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits.h>

using namespace std;

struct MapEntry {
	ulong source_start;
	ulong source_end;
	ulong dest_start;
};

int getLowestLocation(vector<ulong> *seeds, vector<vector<MapEntry>> maps) {
	ulong lowest_location = ULONG_MAX;
	for (ulong x = 0; x < (*seeds).size(); x += 2) {
		ulong mapped_seed = seed;
		cout << "Seed: " << seed << endl;
		cout << "########" << endl;
		for (vector<MapEntry> map : maps) {
			for (MapEntry map_entry : map) {
				if (mapped_seed >= map_entry.source_start && mapped_seed <= map_entry.source_end) {
					mapped_seed = map_entry.dest_start + mapped_seed - map_entry.source_start;
					break;
				}
			}
			cout << mapped_seed << endl;
		}
		if (mapped_seed < lowest_location) {
			lowest_location = mapped_seed;
		}
	}
	return lowest_location;
}

vector<ulong> getSeedsVector(string line) {
	vector<ulong> seeds;
	ulong start_num = line.find(" ") + 1;
	ulong num_size = line.substr(start_num).find(" ");
	string number;
	while (num_size != -1) {
		number = line.substr(start_num, num_size);
		seeds.push_back(stoul(number));
		start_num = start_num + num_size + 1;
		num_size = line.substr(start_num).find(" ");
	}
	number = line.substr(start_num, line.length() - start_num);
	seeds.push_back(stoul(number));
	return seeds;
}

vector<ulong> parseSeedInit(ifstream *file, string delim) {
	string line;
	while (getline(*file, line) && line.substr(0, delim.length()) != delim) {}
	return getSeedsVector(line);
}

vector<MapEntry> parseMap(ifstream *file, string delim) {
	string line;
	vector<MapEntry> map_entries;
	while(getline(*file, line) && line.substr(0, delim.length()) != delim) {}
	while(getline(*file, line) && line.length() != 0) {
		string rest = line;
		string dest_range_start = line.substr(0, line.find(" "));
		rest = line.substr(dest_range_start.length()+1);
		string source_range_start = rest.substr(0, rest.find(" "));
		string range = rest.substr(source_range_start.length());
		MapEntry map_entry;
		map_entry.source_start = stoul(source_range_start);
		map_entry.source_end = stoul(source_range_start) + stoul(range);
		map_entry.dest_start = stoul(dest_range_start);
		map_entries.push_back(map_entry);
	}
	return map_entries;
}

vector<vector<MapEntry>> parseFile(vector<ulong> *seeds) {
	string line;
	vector<vector<MapEntry>> maps;
	ifstream file ("input.txt");
	if (file.is_open()) {
		*seeds = parseSeedInit(&file, "seeds");
		maps.push_back(parseMap(&file, "seed-"));
		maps.push_back(parseMap(&file, "soil"));
		maps.push_back(parseMap(&file, "fert"));
		maps.push_back(parseMap(&file, "water"));
		maps.push_back(parseMap(&file, "light"));
		maps.push_back(parseMap(&file, "temp"));
		maps.push_back(parseMap(&file, "hum"));
		file.close();
	} else {
		cout << "Unable to open file" << endl;
	}
	return maps;
}

int main() {
	vector<ulong> seeds;
	vector<vector<MapEntry>> maps = parseFile(&seeds);
	cout << getLowestLocation(&seeds, maps) << endl;
	return 0;
}
