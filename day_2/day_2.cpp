#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>

using namespace std;

map<string, int> loaded_sets = {{"red", 12}, {"green", 13}, {"blue", 14}};


int getGameID(string line, string* line_rest) {
    int id_start = line.find(" ");
    *line_rest = line.substr(id_start + 1);
    int id_end = line_rest->find(":");
    int game_id = stoi(line_rest->substr(0, id_end));
    *line_rest = line_rest->substr(id_end + 1);
    return game_id;
}

//cout << "start_index: " << start_index << endl;
//cout << "end_index: " << end_index << endl;

int evaluateGame(string line) {

    string rest = "";
    int game_id = getGameID(line, &rest);
    bool end_of_line = false;
    map<string, int> current_min_sets = {{"red", 0}, {"green", 0}, {"blue", 0}};

    while (!end_of_line && game_id != 0) {
        int start_index = rest.find(" ") + 1;
        int end_index = rest.substr(start_index).find(" ");
        int num = stoi(rest.substr(start_index, end_index));
        start_index = start_index + end_index + 1;
        end_index = rest.substr(start_index).find(" ");
        if (end_index == -1) {
            end_index = rest.length() - start_index;
            end_of_line = true;
        } else {
            end_index--;
        }
        string color = rest.substr(start_index, end_index);
        if (num > current_min_sets[color]) {
            current_min_sets[color] = num;
        }
        rest = rest.substr(start_index + end_index);
    }
    cout << "red: " << current_min_sets["red"] << ", "<< "green: " << current_min_sets["green"] << ", " << "blue: " << current_min_sets["blue"] << endl;

    return current_min_sets["red"] * current_min_sets["green"] * current_min_sets["blue"];
}

int main() {
    string line;
    ifstream myfile ("marian_input.txt");
    int sum = 0;
    if (myfile.is_open()) {
        while ( getline (myfile, line) ) {
            sum += evaluateGame(line);
        }
        myfile.close();
    } else cout << "Unable to open file";

    cout << sum << endl;

    return 0;
}