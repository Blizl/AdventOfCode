#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


enum Move {
    ROCK,
    PAPER,
    SCISSORS
};

// rock
int points_for_rock = 1;
// paper 
int points_for_paper = 2;
// scissors
int points_for_scissors = 3;

int lose = 0;
int draw = 3;
int win = 6;

Move to_move(char character) {
    if (character == 'A') {
        return ROCK;
    } else if (character == 'B') {
        return PAPER;
    } else if (character == 'C') {
        return SCISSORS;
    } else if (character == 'X') {
        return ROCK;
    } else if (character == 'Y') {
        return PAPER;
    } else if (character == 'Z') {
        return SCISSORS;
    } else {
        return ROCK;
    }
}

int move_to_points(Move move) {
    if (move == ROCK) {
        return points_for_rock;
    } else if (move == PAPER) {
        return points_for_paper;
    } else {
        return points_for_scissors;
    }
    
}

bool is_draw(std::string line) {
    return to_move(line[0]) == to_move(line[2]);
}
bool is_loss(std::string line) {
    if (is_draw(line)) {
        return false;
    }
    Move opponent_move = to_move(line[0]);
    Move my_move = to_move(line[2]);
    // rock beats scissors
    // scissors beats paper
    // paper beats rock
    return !((my_move == ROCK && opponent_move == SCISSORS) || (my_move == SCISSORS && opponent_move == PAPER) || (my_move == PAPER && opponent_move == ROCK));
}


int main() {
    
    std::ifstream inputFile("input.txt");
    std::string line;
    int total_points = 0;
    while (std::getline(inputFile, line)) {
        Move my_move = to_move(line[2]);
        // win 
        if (is_draw(line)) {
            total_points += (draw + move_to_points(my_move));
        } else if (is_loss(line)) {
            total_points += move_to_points(my_move);
        } else {
            total_points += (win + move_to_points(my_move));
        }

        // draw
        
        // lose

    }
    // is_draw tests
    std::cout << "is_draw tests, all should equal 1"<< std::endl;
    std::cout << "paper draws paper: " << is_draw("A X") << std::endl;
    std::cout << "rock draws rock: " << is_draw("B Y") << std::endl;
    std::cout << "paper draws paper: " << is_draw("C Z") << std::endl;
    std::cout << "rock does not draw with paper: " << !is_draw("A Y") << std::endl;
    std::cout << "rock does not draw with scissors: " << !is_draw("A Z") << std::endl;
    std::cout << "paper does not draw with rock: " << !is_draw("B X") << std::endl;
    std::cout << "paper does not draw with scissors: " << !is_draw("B Z") << std::endl;
    std::cout << "scissors does not draw with rock:" << !is_draw("C X") << std::endl;
    std::cout << "scissors does not draw with paper: " << !is_draw("C Y") << std::endl;
    std::cout <<"\n\n\n" << std::endl;
    
    std::cout << "is_loss tests, all should equal 1"<< std::endl;
    std::cout << "oponnent: rock, me: rock" << !is_loss("A X") << std::endl;
    std::cout << "oppenent: paper,  me: rock: " << is_loss("B X") << std::endl;
    std::cout << "oponnent: scissors, me: rock" << !is_loss("C X") << std::endl;

    std::cout << "oponnent: rock, me: paper" << !is_loss("A Y") << std::endl;
    std::cout << "oppenent: paper,  me: paper: " << !is_loss("B Y") << std::endl;
    std::cout << "oponnent: scissors, me: paper" << is_loss("C Y") << std::endl;


    std::cout << "oponnent: rock, me: scissors" << is_loss("A Z") << std::endl;
    std::cout << "oppenent: paper,  me: scissors: " << !is_loss("B Z") << std::endl;
    std::cout << "oponnent: scissors, me: scissors" << !is_loss("C Z") << std::endl;




    std::cout <<"\n\n\n" << std::endl;

    std:: cout << "total points is " << total_points << std::endl;



    return 0;
}
