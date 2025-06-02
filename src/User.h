#ifndef USER_H
#define USER_H
#include <fstream>

class User {
    private:
    std::vector<std::string> lines_list;
    int coins;

    public:
    // Constructors
    User() : coins(0) {
        lines_list.clear();
    }
    User(std::ifstream &file) {
        std::string line;
        while (file >> line) {
            lines_list.push_back(line);
        }

        if (lines_list.size() > 1) {
            coins = std::stoi(lines_list[1]);
        } else {
            coins = 0; // default value or error handling
        }
    }

    User(std::ofstream &file) {
        coins = 0;
        file << "Coins: " << coins << std::endl;
    }

    // Member Functions

    int getCoins() const {
        return coins;
    }
    void printLines() const {
        for (int i = 0; i < lines_list.size(); ++i) {
            std::cout << i << " line: " << lines_list[i] << std::endl;
        }
    }
};

#endif //USER_H
