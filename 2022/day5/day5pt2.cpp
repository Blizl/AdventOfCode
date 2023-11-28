#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct MoveInstruction {
    int quantity;
    int from;
    int to;

    MoveInstruction(int quantity, int from, int to):  quantity(quantity), from(from), to(to){}

    bool operator==(const MoveInstruction& other) const {
        return quantity == other.quantity && from == other.from && to == other.to;
    }

    friend std::ostream& operator<<(std::ostream& os, const MoveInstruction& move) {
        os << "Quantity: " << move.quantity << ", From: " << move.from << ", To: " << move.to;
        return os;
    }
};

void printVectorOfVectors(const std::vector<std::vector<char>>& vectorOfVectors) {
    for (size_t i = 0; i < vectorOfVectors.size(); ++i) {
        std::cout << "Vector " << i << ": ";
        for (char ch : vectorOfVectors[i]) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
}

void printStack(std::stack<char>  s) {
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

MoveInstruction to_move_instruction(std::string line) {
    // parse 'move 1 from 2 to 1'
    int quantity = 0, from = 0, to = 0;

    // Find positions of keywords 'from' and 'to'
    size_t pos_from = line.find("from");
    size_t pos_to = line.find("to");

    if (pos_from != std::string::npos && pos_to != std::string::npos) {
        // Extracting quantity
        std::istringstream iss(line.substr(5, pos_from - 6)); // Extracting substring from 'move ' to ' from'
        iss >> quantity;

        // Extracting 'from' position
        std::istringstream iss_from(line.substr(pos_from + 5, pos_to - pos_from - 6)); // Extracting substring from ' from ' to ' to'
        iss_from >> from;

        // Extracting 'to' position
        std::istringstream iss_to(line.substr(pos_to + 3)); // Extracting substring from ' to ' to the end
        iss_to >> to;
    }

    return MoveInstruction(quantity, from, to);
}

std::vector<std::stack<char>> to_stacks(std::vector<std::vector<char>> lines, int stack_size) {
    std::vector<std::stack<char>> res;
    for (int i = 0; i< stack_size; i++){
        res.push_back(std::stack<char>());
    }

    for (int j = 0; j < stack_size; j++) {
        for (int i = lines.size() - 1; i >=  0; i--){
            if (lines[i][j] != '\0') {
                res[j].push(lines[i][j]);
            }
        }
    }

    return res;
}


void process_move(MoveInstruction move, std::vector<std::stack<char>>& stacks) {
    // MoveInstruction(move 1, from 2, to 1)
    int move_count = move.quantity;

    std::stack<char> temp_stack;
    while (move_count-- > 0) {
        char char_to_move = stacks[move.from - 1].top();
        // remove from the 'from' stack
        stacks[move.from - 1].pop();
        temp_stack.push(char_to_move);
    }
    while (!temp_stack.empty()) {
        char to_push = temp_stack.top();
        temp_stack.pop();
        stacks[move.to -1].push(to_push);
    }
}

std::vector<char> to_vector(std::string line, int stack_size) {
    // should return ["", "", "", "", "", L, "", H, W]
    std::vector<char> res;
    // for each line, you have 2 empty spaces, 1 in the front, 1 in the end
    // you also have a stack size and number total number of spaces in a line is
    // (stack_size -1) * 3 + 2 + stack_size = length of line

    // Skip the first space and last space
    for (int i = 1; i < line.length() - 1; i++) {
        // std::cout << "i is " << i << "character is: " << line[i] <<std::endl;
        if (std::isalpha(line[i])) {
            // contains a letter 

            // line[i] is the letter
            char letter = line[i];
            // std::cout << "Found character: " << letter << std::endl;
            res.push_back(letter);
            // [A], so move it forward twice and one more additional index for the space
            i+=3;
        } else {
            // Ran into empty space
            // std::cout << "Found empty space" << std::endl;
            res.push_back('\0');
            // Skip to next index 
            i+=3;
        }
    }

    return res;
}




int find_stack_size(std::vector<std::string> lines) {
    int stack_size;
    for (std::string line: lines) {
        if (std::isdigit(line[1])) {
            char size =  line[line.length() -2];
            stack_size =  size - '0';
            break;
        }
    }
    return stack_size;
}


int main() { 
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile("input.txt");
    std::string line;
    std::string res;
    std::vector<std::string> input_lines;
    while (std::getline(inputFile, line)) {
        input_lines.push_back(line);
    }

    std::vector<std::vector<char>> lines;
    int stack_size = find_stack_size(input_lines);
    int move_instructions_start = 0;

    // // Parse into vector of vectors
    for (auto line: input_lines) {
        move_instructions_start++;
        if (line == "") {
            // stop at move instructions
            break;
        }
        // should return ["", "", "", "", "", L, "", H, W]
        std::vector<char> line_vector = to_vector(line, stack_size);
        lines.push_back(line_vector);
    }

    std::vector<std::vector<char>> lines_without_last;
    for (int i = 0; i < lines.size() - 1; i++) {
        lines_without_last.push_back(lines[i]);
    }
    // printVectorOfVectors(lines_without_last);

    std::vector<std::stack<char>> stacks = to_stacks(lines_without_last, stack_size);
    // for (const std::stack<char> stack : stacks) {
    //     std::cout << "Stack contents: ";
    //     printStack(stack);
    // }

    
    // parse move instructions
    for (int i = move_instructions_start; i < input_lines.size(); i++) {
        MoveInstruction move = to_move_instruction(input_lines[i]);
        process_move(move, stacks);
    }
    
    // Take the top of each stack, add to result
    for (std::stack<char> stack: stacks) {
        res += stack.top();
    }


    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start);
    std::vector<char> test_case_1_expected = {'\0','D','\0'};
    std::vector<char> test_case_1_actual = to_vector("    [D]    ", 3);

    std::vector<char> test_case_2_expected = {'N','C','\0'};
    std::vector<char> test_case_2_actual = to_vector("[N] [C]    ", 3);
    std::vector<char> test_case_3_expected = {'Z','M','P'};
    std::vector<char> test_case_3_actual = to_vector("[Z] [M] [P]", 3);
    std::vector<std::stack<char>> stacks_test = to_stacks({{'\0','D','\0'}, {'N','C','\0'}, {'Z','M','P'}}, 3);
    for (const std::stack<char> stack : stacks_test) {
        std::cout << "Stack contents: ";
        printStack(stack);
    }


    
    std::cout << "(to_vector) Test Case 1: " << (test_case_1_actual == test_case_1_expected) << std::endl;
    std::cout << "(to_vector) Test Case 2: " << (test_case_2_actual == test_case_2_expected) << std::endl;
    std::cout << "(to_vector) Test Case 3: " << (test_case_2_actual == test_case_2_expected) << std::endl;
    std::cout << "(find_stack_size) Test Case 4: " << (find_stack_size({"    [D]    ", "[N] [C]    ", "[Z] [M] [P]", " 1   2   3 ", "", "move 1 from 2 to 1", "move 3 from 1 to 3"}) == 3)<< std::endl;
    std::cout << "(find_stack_size) Test Case 5: " << (find_stack_size({"    [D]        ", "[N] [C]        ", "[Z] [M] [P] [L]", " 1   2   3   4 ", "", "move 1 from 2 to 1", "move 3 from 1 to 3"}) == 4)<< std::endl;
    std::cout << "(to_move_instruction) Test Case 6: " << (to_move_instruction("move 1 from 2 to 1") == MoveInstruction(1,2,1))<< std::endl;
    std::cout << "(to_move_instruction) Test Case 7: " << (to_move_instruction("move 3 from 1 to 3") == MoveInstruction(3,1,3))<< std::endl;
    std::cout << "(to_move_instruction) Test Case 8: " << (to_move_instruction("move 2 from 2 to 1") == MoveInstruction(2,2,1))<< std::endl;
    std::cout << "(to_move_instruction) Test Case 9: " << (to_move_instruction("move 7 from 10 to 12") == MoveInstruction(7,10,12))<< std::endl;

    std::cout << "Top of each stack is: " << res << std::endl;
    std::cout << "Time used (milliseconds): " << duration.count() << std::endl;

    return 0;

}

