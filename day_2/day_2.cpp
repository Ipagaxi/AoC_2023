#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>

using namespace std;

map<string, int> loaded_sets = {{"red", 12}, {"green", 13}, {"blue", 14}};

struct {             // Structure declaration
  string color;         // Member (int variable)
  int value;   // Member (string variable)
} set; 


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
    cout << line.substr(0, 7) << endl;
    bool end_of_line = false;

    while (!end_of_line && game_id != 0) {
        cout << "rest:" << rest << endl;
        int start_index = rest.find(" ") + 1;
        int end_index = rest.substr(start_index).find(" ");
        cout << "start_index: " << start_index << endl;
        cout << "end_index: " << end_index << endl;
        int num = stoi(rest.substr(start_index, end_index));
        start_index = start_index + end_index + 1;
        end_index = rest.substr(start_index).find(" ");
        cout << "End_index: " << end_index << endl;
        if (end_index == -1) {
            end_index = rest.length() - start_index;
            end_of_line = true;
        } else {
            end_index--;
        }
        cout << "start_index: " << start_index << endl;
        cout << "end_index: " << end_index << endl;
        string color = rest.substr(start_index, end_index);
        cout << "color: " << color << endl;
        if (num > loaded_sets[color]) {
            game_id = 0;
        }
        rest = rest.substr(start_index + end_index);
    }
    cout << "Game ID: " << game_id << endl;
    return game_id;
}

int main() {
    string line;
    ifstream myfile ("input.txt");
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