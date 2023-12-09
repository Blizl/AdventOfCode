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

std::ostream& operator<<(std::ostream& os, HAND_TYPE handType) {
    switch (handType) {
        case HAND_TYPE::HIGH_CARD:
            os << "High Card";
            break;
        case HAND_TYPE::ONE_PAIR:
            os << "One Pair";
            break;
        case HAND_TYPE::TWO_PAIR:
            os << "Two Pair";
            break;
        case HAND_TYPE::THREE_OF_A_KIND:
            os << "Three of a Kind";
            break;
        case HAND_TYPE::FULL_HOUSE:
            os << "Full House";
            break;
        case HAND_TYPE::FOUR_OF_A_KIND:
            os << "Four of a Kind";
            break;
        case HAND_TYPE::FIVE_OF_A_KIND:
            os << "Five of a Kind";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

enum class CARD {
    JACK,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
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
    int maxCount = 0;
    for (const auto& pair : cardCount) {
        if (pair.second > maxCount && pair.first != 'J') {
            maxCount = pair.second;
        }
    }
    if (maxCount + cardCount['J'] >= 5) {
        return true;
    }
    return false;
}

bool isFourOfKind(string handValue) {
    unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }
    int maxCount = 0;
    for (const auto& pair : cardCount) {
        if (pair.second > maxCount && pair.first != 'J') {
            maxCount = pair.second;
        }
    }
    if (maxCount + cardCount['J'] >= 4) {
        return true;
    }
    return false;
}

bool isThreeOfKind(string handValue) {
    unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }

    int uniqueCards = 0;
    int maxCount = 0;

    for (const auto& pair : cardCount) {
        if (pair.second > maxCount && pair.first != 'J') {
            maxCount = pair.second;
        }
        if (pair.second > 0 && pair.first != 'J') {
            uniqueCards++;
        }
    }

    return (maxCount + cardCount['J'] >= 3) && uniqueCards <= 3;
}


bool isTwoPairs(const std::string handValue) {
    std::unordered_map<char, int> cardCount;
    int jokerCount = 0;
    for (char card : handValue) {
        if (card == 'J') {
            jokerCount++;
        } else {
            cardCount[card]++;
        }
    }
    int pairCount = 0;
    for (const auto& pair : cardCount) {
        if (pair.second == 2) {
            pairCount++;
        } else if (pair.second == 1 && jokerCount > 0){
            pairCount++;
            jokerCount--;
        }
    }
    return pairCount == 2;
}


bool isFullHouse(string handValue) {
    unordered_map<char, int> cardCount;
    int jokerCount = 0;

    for (char card : handValue) {
        if (card != 'J') {
            cardCount[card]++;
        } else {
            jokerCount++;
        }
    }
    if (!isThreeOfKind(handValue) &&  (isTwoPairs(handValue) && jokerCount == 1)) {
        cout << "returning here" << endl;
        return true;
    }

    bool hasThreeOfKind = false;
    bool hasPair = false;

    for (const auto& pair : cardCount) {
        if (pair.second == 3) {
            hasThreeOfKind = true;
        }
        if (pair.second == 2) {
            hasPair = true;
        }
    }
    return hasThreeOfKind && hasPair;
}

bool isOnePair(const std::string handValue) {
    std::unordered_map<char, int> cardCount;
    for (char card : handValue) {
        cardCount[card]++;
    }

    bool hasPair = false;
    bool hasJoker = cardCount['J'] > 0;

    for (const auto& pair : cardCount) {
        if (pair.second == 2 || (hasJoker && pair.second == 1)) {
            hasPair = true;
            break;
        }
    }

    return hasPair;
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
        cout << "Cards: " << hands.top().cards << " type is " << hands.top().type << " bid is: " << hands.top().bid << endl;

        int winAmount = hands.top().bid * i;
        currentScore += winAmount;
        hands.pop();
        i++;  
    }
    // cout << "isFullHouse: (Q2KJJ) " << boolalpha << !isFullHouse("Q2KJJ") << endl;
    cout << "isThreeKind: (2344J) " << boolalpha << isThreeOfKind("2344J")
         << endl;
    cout << "isFullHouse: (2344J) " << boolalpha << !isFullHouse("2344J")
         << endl;
    cout << "isFullHouse: (2233J) " << boolalpha << isFullHouse("2233J") << endl;
    cout << "isThreeOfKind: (2233J) " << boolalpha << isThreeOfKind("2233J") << endl;
    // cout << "isFullHouse: (T3T3J) " << boolalpha << isFullHouse("T3T3J")<<
    // endl; cout << "isFourOfKind: (Q22JJ) " << boolalpha <<
    // isFourOfKind("Q22JJ") << endl; cout << "isThreeOfKind: (Q2KJJ) " <<
    // boolalpha << isThreeOfKind("Q2KJJ") << endl; cout << "isThreeOfKind:
    // (Q2KKK) " << boolalpha << isThreeOfKind("Q2KKK") << endl; cout <<
    // "isTwoPairs(TT223)" << boolalpha << isTwoPairs("TT223") << endl; cout <<
    // "isTwoPairs(TT23J)" << boolalpha << isTwoPairs("TT23J") << endl; cout <<
    // "isOnePair(J1234)" << boolalpha << isOnePair("J1234") << endl; cout <<
    // "isOnePair(32T3K)" << boolalpha << isOnePair("32T3K") << endl; cout <<
    // "isTwoPair(KK677)" << boolalpha << isTwoPairs("KK677") << endl; cout <<
    // "isFourOfKind: (T55J5) " << boolalpha << isFourOfKind("T55J5")<< endl;
    // cout << "isFourOfKind: (KTJJT) " << boolalpha << isFourOfKind("KTJJT")
    //      << endl;
    // cout << "isFourOfKind: (QQQJA) " << boolalpha << isFourOfKind("QQQJA")
    //      << endl;
    // cout << "isFiveOfKind: (JJJJJ) " << boolalpha << isFourOfKind("JJJJJ")
    //      << endl;
    // cout << "isFourOfKind: (96J66) " << boolalpha << isFourOfKind("96J66")
    //      << endl;
    // cout << "isThreeOfKind: (J6569) " << boolalpha << isThreeOfKind("J6569")
    //      << endl;
    // cout << "isThreeOfKind: (JKK92) " << boolalpha << isThreeOfKind("JKK92")
    //      << endl;
    cout << "score is " << currentScore << endl;
    return 0;
}