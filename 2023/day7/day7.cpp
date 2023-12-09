#include <iostream>
#include <queue>
#include "../utils.h"

using namespace std;

enum class HAND_TYPE {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

enum class CARD {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};
std::ostream& operator<<(std::ostream& os, CARD card) {
    switch (card) {
        case CARD::TWO:
            os << "2";
            break;
        case CARD::THREE:
            os << "3";
            break;
        case CARD::FOUR:
            os << "4";
            break;
        case CARD::FIVE:
            os << "5";
            break;
        case CARD::SIX:
            os << "6";
            break;
        case CARD::SEVEN:
            os << "7";
            break;
        case CARD::EIGHT:
            os << "8";
            break;
        case CARD::NINE:
            os << "9";
            break;
        case CARD::TEN:
            os << "T";
            break;
        case CARD::JACK:
            os << "J";
            break;
        case CARD::QUEEN:
            os << "Q";
            break;
        case CARD::KING:
            os << "K";
            break;
        case CARD::ACE:
            os << "A";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}

static const std::unordered_map<char, CARD> charToCardMap = {
    {'2', CARD::TWO}, {'3', CARD::THREE}, {'4', CARD::FOUR},  {'5', CARD::FIVE},
    {'6', CARD::SIX}, {'7', CARD::SEVEN}, {'8', CARD::EIGHT}, {'9', CARD::NINE},
    {'T', CARD::TEN}, {'J', CARD::JACK},  {'Q', CARD::QUEEN}, {'K', CARD::KING},
    {'A', CARD::ACE}};

struct Hand {
    HAND_TYPE type;
    vector<CARD> cards;
    int bid;

    Hand(HAND_TYPE type, vector<CARD> cards, int bid) : type(type), cards(cards), bid(bid) {}


    bool operator<(const Hand& other) const {
        if (type != other.type) {
            return type > other.type;  
        }
        for (size_t i = 0; i < cards.size() && i < other.cards.size(); ++i) {
            if (cards[i] != other.cards[i]) {
                return cards[i] > other.cards[i];  // Compare cards at index i
            }
        }
    }

    bool operator==(const Hand& other) const {
        return cards == other.cards && type == other.type;
    }
};

bool isFiveOfKind(string handValue) {
    unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }
    for (const auto& pair : cardCount) {
        if (pair.second >= 5) {
            return true;
        }
    }
    return false;
}


bool isFourOfKind(string handValue) {
    unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }
    for (const auto& pair : cardCount) {
        if (pair.second >= 4) {
            return true;
        }
    }
    return false;
}

bool isThreeOfKind(string handValue) {
    unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }
    for (const auto& pair : cardCount) {
        if (pair.second >= 3) {
            return true;
        }
    }
    return false;
}

bool isTwoPairs(const std::string handValue) {
    std::unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }

    int pairCount = 0;
    for (const auto& pair : cardCount) {
        if (pair.second == 2) {
            pairCount++;
        }
    }

    return pairCount == 2;
}

bool isFullHouse(string handValue) {
    unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }

    bool hasThreeOfKind = false;
    bool hasTwoOfKind = false;

    for (const auto& pair : cardCount) {
        if (pair.second == 3) {
            hasThreeOfKind = true;
        } else if (pair.second == 2) {
            hasTwoOfKind = true;
        }
    }

    return hasThreeOfKind && hasTwoOfKind;
}

bool isOnePair(const std::string handValue) {
    std::unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }

    int pairCount = 0;
    for (const auto& pair : cardCount) {
        if (pair.second == 2) {
            pairCount++;
        }
    }

    return pairCount == 1;
}

HAND_TYPE toHandType(string handValue) {
    if (isFiveOfKind(handValue)) {
        return HAND_TYPE::FIVE_OF_A_KIND;
    }
    if (isFourOfKind(handValue)) {
        return HAND_TYPE::FOUR_OF_A_KIND;
    }
    if (isFullHouse(handValue)) {
        return HAND_TYPE::FULL_HOUSE;
    }
    if (isThreeOfKind(handValue)) {
        return HAND_TYPE::THREE_OF_A_KIND;
    }
    if (isTwoPairs(handValue)) {
        return HAND_TYPE::TWO_PAIR;
    }
    if (isOnePair(handValue)) {
        return HAND_TYPE::ONE_PAIR;
    }
    return HAND_TYPE::HIGH_CARD;
}

vector<CARD> toCards(string hand) {
    vector<CARD> cards;
    for (char c : hand) {
        cards.push_back(charToCardMap.find(c)->second);
    }
    return cards;
}

int main() {
    vector<string> lines = readLines("input.txt");
    priority_queue<Hand> hands;
    for (auto line : lines) {
        vector<string> splitLine = splitString(line, ' ');
        HAND_TYPE type = toHandType(splitLine[0]);
        hands.push(Hand(type, toCards(splitLine[0]), stoi(splitLine[1])));
    }
    int currentScore = 0;

    int i = 1;  

    while (!hands.empty()) {
        int winAmount =
            hands.top().bid *i; 
        currentScore += winAmount;
        hands.pop();
        i++;  
    }
    cout << "score is " << currentScore << endl;
    return 0;
}