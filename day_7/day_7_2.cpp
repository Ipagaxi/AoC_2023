#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

const int HAND_LENGTH = 5;

const int FIVE_OF_KIND = 6;
const int FOUR_OF_KIND = 5;
const int FULL_HOUSE = 4;
const int THREE_OF_KIND = 3;
const int TWO_PAIR = 2;
const int ONE_PAIR = 1;
const int ALL_DIFF = 0;

struct Hand {
    string cards_str;
    vector<int> cards;
    int bid;
    int strength;
};

string getCardsStr(string line) {
    return line.substr(0, line.find(" "));
}

vector<int> getCards(string line) {
    string cards_str = line.substr(0, line.find(" "));
    vector<int> cards_values;
    for (int x = 0; x < HAND_LENGTH; x++) {
        switch (cards_str[x])
        {
        case 'A':
            cards_values.push_back(14);
            break;
        case 'K':
            cards_values.push_back(13);
            break;
        case 'Q':
            cards_values.push_back(12);
            break;
        case 'J':
            cards_values.push_back(1);
            break;
        case 'T':
            cards_values.push_back(10);
            break;
        default:
            // ASCII value substraction to convert char to int;
            cards_values.push_back(cards_str[x] - '0');
            break;
        }
    }
    return cards_values;
}

int getBid(string line) {
    return stoi(line.substr(line.find(" ")+1)); 
}

int addJokerPossibilities(string hand_str, int current_strength) {
    int final_strength = current_strength;
    int num_j = 0;
    for (char hand_card : hand_str) {
            if (hand_card == 'J') {
                num_j++;
            }
        }
    switch (num_j) {
    case 3:
        // Current: pair
        if (current_strength == ONE_PAIR) {
            return FIVE_OF_KIND;
        //Current: Each card different
        } else {
            return FOUR_OF_KIND;
        }
        break;
    case 2:
        if (current_strength == THREE_OF_KIND) {
            return FIVE_OF_KIND;
        } else if (current_strength == ONE_PAIR) {
            return FOUR_OF_KIND;
        } else {
            return THREE_OF_KIND;
        }
        break;
    case 1:
        if (current_strength == FOUR_OF_KIND) {
            return FIVE_OF_KIND;
        } else if (current_strength == THREE_OF_KIND) {
            return FOUR_OF_KIND;
        } else if (current_strength == TWO_PAIR) {
            return FULL_HOUSE;
        } else if (current_strength == ONE_PAIR) {
            return THREE_OF_KIND;
        } else {
            return ONE_PAIR;
        }
        break;
    case 0:
        return current_strength;
    default:
        return FIVE_OF_KIND;
        break;
    }
}

int getStrength(string cards) {
    char poss_cards[13] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
    bool found_2_occurences = false;
    bool found_3_occurences = false;
    bool three_occ = false;
    bool two_occ = false;
    int num;
    for (char poss_card : poss_cards) {
        num = 0;
        for (char hand_card : cards) {
            if (hand_card == poss_card) {
                num++;
            }
        }
        switch (num)
        {
        case 5:
            // Five of a kind
            return FIVE_OF_KIND;
            break;
        case 4:
            // Four of a kind
            return addJokerPossibilities(cards, FOUR_OF_KIND);
            break;
        case 3:
            if (two_occ) {
                // Full house
                return FULL_HOUSE;
            }
            three_occ = true;
            break;
        case 2:
            if (three_occ) {
                // Full house
                return FULL_HOUSE;
            }
            if (two_occ) {
                // Two pair
                return addJokerPossibilities(cards, TWO_PAIR);
            }
            two_occ = true;
            break;
        default:
            break;
        }
    }
    if (three_occ) {
        // Three of a kind
        return addJokerPossibilities(cards, THREE_OF_KIND);
    }
    if (two_occ) {
        // One pair
        return addJokerPossibilities(cards, ONE_PAIR);
    }
    // All different
    return addJokerPossibilities(cards, ALL_DIFF);
}

Hand parseLineToHand(string line) {
    string cards_str = getCardsStr(line);
    vector<int> cards = getCards(line);
    int bid = getBid(line);
    int strength = getStrength(cards_str);

    Hand hand = {cards_str, cards, bid, strength};
    return hand;
}

void compareAndInsertIfEqStrength(Hand hand, vector<Hand> *sorted_hands, int pos) {
    if (hand.cards_str == (*sorted_hands)[pos].cards_str || hand.strength != (*sorted_hands)[pos].strength) {
        sorted_hands->insert(sorted_hands->begin() + pos, hand);
        cout << "Strongest of same strength or equal" << endl;
    } else if (pos == sorted_hands->size()) {
        cout << "Strongest of all" << endl;
        sorted_hands->push_back(hand);
    } else {
        int y = 0;
        while (y < 5) {
            if (hand.cards[y] < (*sorted_hands)[pos].cards[y]) {
                cout << "Weaker than " << (*sorted_hands)[pos].cards_str << endl;
                sorted_hands->insert(sorted_hands->begin() + pos, hand);
                break;
            } else if (hand.cards[y] == (*sorted_hands)[pos].cards[y]) {
                y++;
            } else {
                compareAndInsertIfEqStrength(hand, sorted_hands, pos+1);
                break;
            }
        }
    }
}


void insertHandIntoSortedHands(Hand hand, vector<Hand> *sorted_hands) {
    cout << "######" << endl;
    cout << "Hand: " << hand.cards_str << endl;
    //cout << "Size: " << sorted_hands->size() << endl;
    if (sorted_hands->size() == 0) {
        cout << "First Hand" << endl;
        sorted_hands->push_back(hand);
    } else {
        int x = 0;
        while (x < sorted_hands->size() && hand.strength > (*sorted_hands)[x].strength) {
            x++;
        } if (x == sorted_hands->size()) {
            cout << "Hand strongest" << endl;
            sorted_hands->push_back(hand);
        } else {
            if (hand.strength == (*sorted_hands)[x].strength) {
                cout << "Same strengths" << endl;
                compareAndInsertIfEqStrength(hand, sorted_hands, x);
            } else if (hand.strength < (*sorted_hands)[x].strength) {
                cout << "Hand is weaker than " << (*sorted_hands)[x].cards_str << endl;
                sorted_hands->insert(sorted_hands->begin() + x, hand);
            }
        }
    }
}

int getResolvedValue() {
    string line;
    vector<Hand> hands;
    ifstream file ("input.txt");
    int solution = 0;
    if (file.is_open()) {
        vector<Hand> out_sorted_hands;
        Hand hand;
        while (getline(file, line)) {
            hand = parseLineToHand(line);
            insertHandIntoSortedHands(hand, &out_sorted_hands);
        }
        for (int x = 0; x < out_sorted_hands.size(); x++) {
            cout << out_sorted_hands[x].bid << " * " << x+1 << endl;
            solution += (out_sorted_hands[x].bid * (x +1));
        }
        file.close();
    } else {
        cout << "unable to open fille" << endl;
    }
    return solution;
}

int main() {
    int value = getResolvedValue();
    cout << value << endl;
    return 0;
}