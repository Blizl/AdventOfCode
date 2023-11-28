
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct Node;

namespace std {
template <>
struct hash<Node> {
    size_t operator()(const Node &n) const;
};
}  // namespace std

struct Node {
    unordered_set<unique_ptr<Node> > childNodes;
    Node* parent;
    string name;
    int size;
    bool isDirectory = false;
    Node(string name) : name(name) {}
    Node(string name, bool isDirectory)
        : name(name), isDirectory(isDirectory) {}
    Node(string name, bool isDirectory, Node* parent)
        : name(name), isDirectory(isDirectory), parent(parent) {}
    Node(string name, bool isDirectory, int fileSize, Node *parent)
        : name(name), isDirectory(isDirectory), size(fileSize), parent(parent) {}

    bool operator==(const Node &other) const {
        return (name == other.name && size == other.size &&
                isDirectory == other.isDirectory &&
                childNodes ==
                    other.childNodes);  // Equality comparison for childNodes
    }

    void addChild(std::unique_ptr<Node> child) {
        childNodes.insert(std::move(child));
    }
};
namespace std {
size_t hash<Node>::operator()(const Node &n) const {
    // Your hashing logic here
    size_t hashName = hash<string>{}(n.name);
    size_t hashSize = hash<int>{}(n.size);
    size_t hashIsDir = hash<bool>{}(n.isDirectory);

    // Combine the hash values using XOR (^)
    return hashName ^ (hashSize << 1) ^ (hashIsDir << 2);
}
}  // namespace std

void printNodes(const Node &node, int depth = 0) {
    // Print the current node at the given depth
    for (int i = 0; i < depth; ++i) {
        cout << "  ";  // Indentation based on the depth of the node
    }
    cout << node.name << endl;

    // Recursively print child nodes
    for (const auto &child : node.childNodes) {
        printNodes(
            *child,
            depth + 1);  // Recursive call for each child with increased depth
    }
}

void printDirectChilds(const Node &node) {

    // Recursively print child nodes
    for (const auto &child : node.childNodes) {
        cout << (*child).name << endl;
    }
}

enum class Command { CHANGE_DIRECTORY, LIST_FILES };

class CommandLine {
   public:
    unique_ptr<Node> root = make_unique<Node>("/");
    Node *currentNode;
    vector<string> lines;
    int currentLine = 1;
    CommandLine() : currentNode(root.get()) {}

    unordered_map<string, Command> stringToCommand = {
        {"ls", Command::LIST_FILES},
        {"cd", Command::CHANGE_DIRECTORY},
    };

    bool isDir(string line) { return line.find("dir") != string::npos; }

    string getDirectoryName(string line) {
        // 4 because dir + space is 4 characters
        return line.substr(4);
    }

    string getFileName(string line) {
        // first space
        int firstSpaceIndex = line.find(" ");
        return line.substr(firstSpaceIndex + 1,
                           line.length() - firstSpaceIndex);
    }

    int getFileSize(std::string line) {
        // first space
        int firstSpaceIndex = line.find(" ");
        return std::stoi(line.substr(0, firstSpaceIndex));
    }

    void buildNodes() {
        while (currentLine < lines.size() && lines[currentLine][0] != '$') {
            if (isDir(lines[currentLine])) {
                // If it's a directory, build a directory node
                (*currentNode)
                    .addChild(
                        move(make_unique<Node>(getDirectoryName(lines[currentLine]), true, currentNode)));
            } else {
                (*currentNode)
                    .addChild(move(make_unique<Node>(getFileName(lines[currentLine]),
                                                    false,
                                                     getFileSize(lines[currentLine]),
                                                     currentNode
                                                     )));
            }
            currentLine++;
        }
    }
    string findDirectoryToChange(std::string line) {
        // find $ cd + space, which is 5 characters
        string directoryToChange = line.substr(5);
        return directoryToChange;
    }

    bool isDirectoryDirectChild(std::string directoryName) {
        return find_if((*currentNode).childNodes.begin(),
                       (*currentNode).childNodes.end(),
                       [directoryName](const auto &nodePtr) {
                           return nodePtr->name == directoryName &&
                                  nodePtr->isDirectory;
                       }) != (*currentNode).childNodes.end();
    }

    void goUpDirectory() { 
        currentNode = currentNode->parent;
        cout << "going up a directory, currentNode is now " << currentNode->name << endl;
    }

    void processCommand(std::string command,
                        std::string line) {
        // cout << "processing command " << command << endl;
        // cout << "processCommand: line is  " << line << endl;
        auto it = stringToCommand.find(command);
        if (it != stringToCommand.end()) {
            switch (stringToCommand[command]) {
                case Command::LIST_FILES:
                    // if it is ls, parse all the lines until the next command
                    currentLine++;
                    buildNodes();
                    cout << "$ ls\n" << endl;
                    printDirectChilds(*currentNode);
                    cout << "\n" << endl;
                    break;
                case Command::CHANGE_DIRECTORY:
                    string directory = findDirectoryToChange(line);
                    if (directory == "..")  {
                        goUpDirectory();
                        currentLine++;
                        break;
                    } 
                    // make sure directory exists
                    if (isDirectoryDirectChild(directory)) {
                        // change current node to what it is supposed to be
                        auto foundNode =
                            find_if((*currentNode).childNodes.begin(),
                                    (*currentNode).childNodes.end(),
                                    [directory](const auto &nodePtr) {
                                        return nodePtr->name == directory &&
                                               nodePtr->isDirectory;
                                    });
                        if (foundNode != (*currentNode).childNodes.end()) {
                            // cout << "found node, node is " <<  (*foundNode)->name << endl;
                            // cout << "found node, node's parent is " <<  (*foundNode)->parent->name << endl;
                            currentNode = foundNode->get();
                        } else {
                            cout << "Directory not found as a child node."
                                      << endl;
                        }
                    } else {
                        cout << "Cannot navigate to this directory, not a "
                                     "direct child,  we are directory " << currentNode->name
                                  << endl;
                    }
                    currentLine++;
                    break;
            }
        } else {
            std::cout << "Command not found" << std::endl;
        }
    }

    void process(vector<string> lines) { 
        this->lines = lines;
        cout << "lines[currentLine] is " << lines[currentLine] << endl;
        while (currentLine < lines.size()) {
            processCommand(lines[currentLine].substr(2,2), lines[currentLine]);
        }
    }
};

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<string> lines; 
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    CommandLine cmdLine = CommandLine();
    cmdLine.process(lines);
    return 0;
}
