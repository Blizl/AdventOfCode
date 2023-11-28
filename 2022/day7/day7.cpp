
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Node;

namespace std {
template <>
struct hash<Node> {
    size_t operator()(const Node &n) const;
};
}  // namespace std

struct Node {
    unordered_set<Node> childNodes;
    string name;
    int size;
    bool isDirectory = false;
    // Node(const std::string& nodeName, int nodeSize = 0, bool isDir = false)
    // : name(nodeName), size(nodeSize), isDirectory(isDir) {}
    // Node(std::string name, bool isDirectory) : name(name),
    // isDirectory(isDirectory) {}
    Node(string name) : name(name) {}
    Node(string name, bool isDirectory)
        : name(name), isDirectory(isDirectory) {}
    // Node(std::string name, int size): name(name), size(size) {}
    // Node(const std::string& nodeName, int nodeSize, bool isDir, const
    // std::unordered_set<Node>& children)
    //     : name(nodeName), size(nodeSize), isDirectory(isDir),
    //     childNodes(children) {}

    bool operator==(const Node &other) const {
        return (name == other.name && size == other.size &&
                isDirectory == other.isDirectory &&
                childNodes ==
                    other.childNodes);  // Equality comparison for childNodes
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

// // Overloading the << operator for Node struct
// std::ostream& operator<<(std::ostream& os, const Node& node) {
//     os << "Node Name: " << node.name << ", Size: " << node.size << ",
//     isDirectory: " << node.isDirectory << std::endl;

//     // Print child nodes if any
//     if (!node.childNodes.empty()) {
//         os << "Child Nodes: {" << std::endl;
//         for (const auto& child : node.childNodes) {
//             os << "  " << child; // Recursive call to print child nodes
//         }
//         os << "}" << std::endl;
//     }

//     return os;
// }

// Node currentNode = Node("/");
// Node rootNode = currentNode;

enum class Command { CHANGE_DIRECTORY, LIST_FILES };

class CommandLine {
   public:
    Node currentNode;

    unordered_map<string, Command> stringToCommand = {
        {"ls", Command::LIST_FILES},
        {"cd ", Command::CHANGE_DIRECTORY},
    };

    bool isDir(string line) { return line.find("dir") != string::npos; }

    string getDirectoryName(string line) {
        // 4 because dir + space is 4 characters
        return line.substr(4, line.length() - 4);
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

    void buildNodes(ifstream &inputFile) {
        std::string line;
        while (getline(inputFile, line) && line[0] != '$') {
            if (isDir(line)) {
                // If it's a directory, build a directory node
                currentNode.childNodes.insert(
                    Node(getDirectoryName(line), true));
            } else {
                currentNode.childNodes.insert(
                    Node(getFileName(line), getFileSize(line)));
            }
        }
    }
    std::string findDirectoryToChange(std::string line) {
        // find cd + space, which is 3 characters
        return line.substr(3, line.length() - 3);
    }

    bool isDirectoryDirectChild(std::string line) {
        return currentNode.childNodes.find(
                   Node(getDirectoryName(line), true)) !=
               currentNode.childNodes.end();
    }

    void processCommand(std::string command, std::ifstream &inputFile,
                        std::string line) {
        auto it = stringToCommand.find(command);
        if (it != stringToCommand.end()) {
            switch (stringToCommand[command]) {
                case Command::LIST_FILES:
                    // if it is ls, parse all the lines until the next command
                    buildNodes(inputFile);
                    break;
                case Command::CHANGE_DIRECTORY:
                    std::string directory = findDirectoryToChange(line);
                    // make sure directory exists
                    if (isDirectoryDirectChild(directory)) {
                        // change current node to what it is supposed to be
                        auto foundNode =
                            currentNode.childNodes.find(Node(directory, true));
                        if (foundNode != currentNode.childNodes.end()) {
                            currentNode = *foundNode;  // Assign the found node
                                                       // to currentNode
                        } else {
                            std::cout << "Directory not found as a child node."
                                      << std::endl;
                        }
                    } else {
                        std::cout << "Cannot navigate to this directory, not a "
                                     "direct child"
                                  << std::endl;
                    }
                    break;
            }
        } else {
            std::cout << "Command not found" << std::endl;
        }
    }
};

void printNodes(const Node &node, int depth = 0) {
    // Print the current node at the given depth
    for (int i = 0; i < depth; ++i) {
        cout << "  ";  // Indentation based on the depth of the node
    }
    cout << node.name << endl;

    // Recursively print child nodes
    for (const auto &child : node.childNodes) {
        printNodes(
            child,
            depth + 1);  // Recursive call for each child with increased depth
    }
}

int main() {
    Node rootNode = Node("/");
    Node child1 = Node("child1");
    Node child2 = Node("child2");
    rootNode.childNodes.insert(child1);
    rootNode.childNodes.insert(child2);
    // rootNode->childNodes.insert(Node("child1", 10, true));
    // rootNode->childNodes.insert(Node("child2", 20, false));
    cout << "hi" << endl;
    cout << "root node name: " << rootNode.name << endl;

    // Test printNodes function
    printNodes(rootNode);  // You can use your printNodes function here

    return 0;
}

// int main() {
//     std::ifstream inputFile("input.txt");
//     std::string line;
//     // skip the first line, it will always be cd /
//     std::getline(inputFile, line);
//     while (std::getline(inputFile, line)) {
//         // process each terminal output
//         // cd, dir, ls,
//         if (line[0] == '$') {
//             // process command if it is a command
//             // processCommand(line.substr(2), inputFile, line);
//         }
//     }
//     // Node rootNode = Node();
//     // rootNode.name = "/";
//     // printNodes(rootNode);
//     return 0;
// }
