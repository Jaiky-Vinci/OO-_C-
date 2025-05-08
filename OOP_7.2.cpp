#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

class Monster {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Monster(const std::string& name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {}

    void displayInfo() const {
        std::cout << "Монстр: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << "\n";
    }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    std::string getName() const { return name; }
};

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Character(const std::string& name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {}

    void displayInfo() const {
        std::cout << "Персонаж: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << "\n";
    }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    std::string getName() const { return name; }
};

std::vector<Monster> monsters;
std::mutex monstersMutex;
std::mutex battleMutex;

void generateMonsters() {
    int count = 0;
    while (count < 5) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::lock_guard<std::mutex> lock(monstersMutex);
        monsters.emplace_back("Гоблин", 50 + rand() % 20, 10 + rand() % 5, 5);
        std::cout << "Новый монстр сгенерирован!\n";
        ++count;
    }
}

void fight(Character& hero, Monster& monster) {
    while (hero.getHealth() > 0 && monster.getHealth() > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(battleMutex);
            monster.takeDamage(hero.getAttack());
            std::cout << hero.getName() << " атакует " << monster.getName() << "!\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        {
            std::lock_guard<std::mutex> lock(battleMutex);
            hero.takeDamage(monster.getAttack());
            std::cout << monster.getName() << " атакует " << hero.getName() << "!\n";
        }
    }

    std::lock_guard<std::mutex> lock(battleMutex);
    if (hero.getHealth() <= 0) {
        std::cout << hero.getName() << " проиграл бой!\n";
    } else {
        std::cout << monster.getName() << " побеждён!\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Character hero("Герой", 100, 20, 10);

    std::thread generator(generateMonsters);
    generator.detach();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));

        Monster monster("Огр", 60, 15, 8);
        std::cout << "\n== Новый бой начинается! ==\n";
        hero.displayInfo();
        monster.displayInfo();

        std::thread battleThread(fight, std::ref(hero), std::ref(monster));
        battleThread.join();

        if (hero.getHealth() <= 0) {
            std::cout << "Игра окончена.\n";
            break;
        }
    }

    return 0;
}
