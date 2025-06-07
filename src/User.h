#ifndef USER_H
#define USER_H
#include <fstream>

class User {
    private:
    std::vector<std::string> lines_list;
    std::ofstream user_file;

    Pet user_pet;
    int coins;
    int food_storage;
    StatTimer coin_clock;

    public:
    // Constructors
    User() : coins(0) {
        lines_list.clear();
    }

    // Continuing User will Get its information updated
    User(std::ifstream &file) {
        // Continuing User, Reading File
        std::string line;
        while (file >> line) {
            lines_list.push_back(line);
        }
        setData();
    }

    User(std::ofstream &file){
        // New User, Writing Files to 0
        coins = 0;
        food_storage = 1;
        // user_pet.setAllZero(); // set's all properties to zero.

        file << "Coins: " << coins << std::endl;
        file << "Energy_level: " << user_pet.getEnergy() << std::endl;
        file << "Hunger_level: " << user_pet.getHunger() << std::endl;
        file << "Playfullness_level: " << user_pet.getPlayfullness() << std::endl;
        file << "Cleanliness_level: " << user_pet.getCleanliness() << std::endl;
        file << "Food_Storage: " << food_storage << std::endl;
    }

    // Member Functions

    // Getters
    int getCoins() const {
        return coins;
    }
    int getFoodStorage() const {
        return food_storage;
    }
    Pet& getPet() {
        return user_pet;
    }
    StatTimer& getTimer() {
        return coin_clock;
    }

    // Setters
    void setCoins(int coin_val) {
        coins = coin_val;
    }
    void setFoodStorage (int food_num) {
        food_storage = food_num;
    }

    // Increase coins
    void increaseCoins() {
        coins += 3;
    }
    void increaseCoins(int amount) {
        coins += amount;
    }

    // Decreasing
    void decreaseFoodStorage(int amount) {
        food_storage -= amount;
    }

    // Sets the User Object / Pet Object to what is in the User File
    void setData() {
        for (int i = 0; i < lines_list.size(); ++i) {
            if (lines_list[i] == "Coins:") {
                setCoins(std::stoi(lines_list[i+1]));
            } else if (lines_list[i] == "Energy_level:") {
                user_pet.setEnergy(std::stoi(lines_list[i+1]));
            } else if (lines_list[i] == "Hunger_level:") {
                user_pet.setHunger(std::stoi(lines_list[i+1]));
            } else if (lines_list[i] == "Playfullness_level:") {
                user_pet.setPlayfullness(std::stoi(lines_list[i+1]));
            } else if (lines_list[i] == "Cleanliness_level:") {
                user_pet.setCleanliness(std::stoi(lines_list[i+1]));
            } else if (lines_list[i] == "Food_Storage:") {
                setFoodStorage(std::stoi(lines_list[i+1]));
            }
        }
    }

    // Prints Array List (just for testing)
    void printLines() const {
        for (int i = 0; i < lines_list.size(); ++i) {
            std::cout << i << " line: " << lines_list[i] << std::endl;
        }
    }

    // Method that Saves Any Real Time Changes To User Data File
    void saveToFile() const {
        std::ofstream file("User Data"); // overwrite the file
        file << "Coins: " << coins << std::endl;
        file << "Energy_level: " << user_pet.getEnergy() << std::endl;
        file << "Hunger_level: " << user_pet.getHunger() << std::endl;
        file << "Playfullness_level: " << user_pet.getPlayfullness() << std::endl;
        file << "Cleanliness_level: " << user_pet.getCleanliness() << std::endl;
        file << "Food_Storage: " << food_storage << std::endl;
    }
};

#endif //USER_H
