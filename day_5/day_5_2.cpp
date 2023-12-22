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

struct SeedIntervall {
    ulong start;
    ulong end;
};

vector<SeedIntervall> structureSeeds(vector<ulong> seeds) {
    vector<SeedIntervall> seed_intervalls;
    for (int x = 0; x < seeds.size(); x += 2) {
        seed_intervalls.push_back(SeedIntervall{seeds[x], seeds[x] + seeds[x+1]-1});
    }
    return seed_intervalls;
}

vector<SeedIntervall> mergeSeeds(vector<ulong> seeds) {
    vector<SeedIntervall> rest_seeds = structureSeeds(seeds);
    vector<SeedIntervall> merged_seeds;
    merged_seeds.push_back(rest_seeds.back());
    rest_seeds.pop_back();
    for (int y = 0; y < merged_seeds.size() && rest_seeds.size() != 0; y++){
        for (int x = 0; x < rest_seeds.size(); x++) {
            if (rest_seeds[x].start <= merged_seeds[y].end && rest_seeds[x].end >= merged_seeds[y].start) {
                merged_seeds[y].start = min(merged_seeds[y].start, rest_seeds[x].start);
                merged_seeds[y].end = max(merged_seeds[y].end, rest_seeds[x].end);
                rest_seeds.erase(rest_seeds.begin()+x);
                x = -1;
            }
        }
        if (rest_seeds.size() != 0) {
            merged_seeds.push_back(rest_seeds.back());
            rest_seeds.pop_back();
        }
    }
    return merged_seeds;
}

void resolveSeedIntervall(vector<vector<MapEntry>> maps, int map_index, SeedIntervall seed_intervall, ulong *lowest_location) {
    for (int x = map_index; x < maps.size(); x++) {
        for (MapEntry map_entry : maps[x]) {
            if (seed_intervall.start >= map_entry.source_start && seed_intervall.start <= map_entry.source_end) {
                seed_intervall.start = map_entry.dest_start + seed_intervall.start - map_entry.source_start;
                if (seed_intervall.end > map_entry.source_end) {
                    resolveSeedIntervall(maps, x, SeedIntervall{map_entry.source_end +1, seed_intervall.end}, lowest_location);
                    seed_intervall.end = map_entry.source_end;
                }
                seed_intervall.end = map_entry.dest_start + seed_intervall.end - map_entry.source_start;
                break;
            }
        }
    }
    if (seed_intervall.start < *lowest_location) {
        *lowest_location = seed_intervall.start;
    }
}

ulong getLowestLocation(vector<ulong> *seeds, vector<vector<MapEntry>> maps) {
	ulong out_lowest_location = ULONG_MAX;
    vector<SeedIntervall> merged_seeds = mergeSeeds(*seeds);
	for (ulong x = 0; x < merged_seeds.size(); x++) {
        resolveSeedIntervall(maps, x, merged_seeds[x], &out_lowest_location);

	}
	return out_lowest_location;
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
		map_entry.source_end = stoul(source_range_start) + stoul(range)-1;
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
