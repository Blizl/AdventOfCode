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

int loss = 0;
int draw = 3;
int win = 6;

int move_to_points(Move move) {
    if (move == ROCK) {
        return points_for_rock;
    } else if (move == PAPER) {
        return points_for_paper;
    } else {
        return points_for_scissors;
    }
}

int get_result_points(char result) {
    if (result == 'X') {
        return loss;
    } else if (result == 'Y') {
        return draw;
    } else {
        return win;
    }
}

Move to_same(char move_in_char) {
    if (move_in_char == 'A') {
        return ROCK;
    } else if (move_in_char == 'B') {
        return PAPER;
    } else {
        return SCISSORS;
    }
}

Move to_opposite_win(char move_in_char) {
    if (move_in_char == 'A') {
        // beat rock with paper
        return PAPER;
    } else if (move_in_char == 'B') {
        // beat paper with scissors 
        return SCISSORS;
    } else {
        return ROCK;
    }
}
Move to_opposite_loss(char move_in_char) {
    if (move_in_char == 'A') {
        // loss to rock with scissors
        return SCISSORS;
    } else if (move_in_char == 'B') {
        // lose to paper with rock
        return ROCK;
    } else {
        return PAPER;
    }
}


Move find_move(std::string line) {
    if (line[2] == 'X') {
        // loss
        return to_opposite_loss(line[0]);
    } else if (line[2] == 'Y') {
        // draw
        return to_same(line[0]);
    } else {
        // win
        return to_opposite_win(line[0]);
    }
}

int main() {
    
    std::ifstream inputFile("input.txt");
    std::string line;
    int total_points = 0;
    while (std::getline(inputFile, line)) {
        Move my_move = find_move(line);
        int result_points = get_result_points(line[2]);
        total_points += (result_points + move_to_points(my_move));
    }

    std:: cout << "total points is " << total_points << std::endl;



    return 0;
}
