#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <memory>

// Шаблонный класс логгера
template <typename T>
class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
        if (!logFile) {
            throw std::runtime_error("Не удалось открыть файл для логирования.");
        }
    }

    void log(const T& message) {
        logFile << message << std::endl;
    }
};

// Класс персонажа
class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;
    int level;
    int experience;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d), level(1), experience(0) {}

    void attackEnemy(Character& enemy, Logger<std::string>& logger) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.health -= damage;
            if (enemy.health < 0) enemy.health = 0;
            std::string log = name + " атакует " + enemy.name + " и наносит " + std::to_string(damage) + " урона!";
            std::cout << log << std::endl;
            logger.log(log);
        } else {
            std::string log = name + " атакует " + enemy.name + ", но атака неэффективна!";
            std::cout << log << std::endl;
            logger.log(log);
        }
    }

    void heal(int amount, Logger<std::string>& logger) {
        health += amount;
        if (health > 100) health = 100;
        std::string log = name + " восстанавливает " + std::to_string(amount) + " HP!";
        std::cout << log << std::endl;
        logger.log(log);
    }

    void gainExperience(int exp) {
        experience += exp;
        if (experience >= 100) {
            level++;
            experience -= 100;
            std::cout << name << " повысил уровень до " << level << "!" << std::endl;
        }
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", HP: " << health
                  << ", Атака: " << attack << ", Защита: " << defense
                  << ", Уровень: " << level << ", Опыт: " << experience << std::endl;
    }

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
};

// Базовый класс монстра
class Monster {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    virtual void displayInfo() const {
        std::cout << "Монстр: " << name << ", HP: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }

    virtual ~Monster() = default;
};

class Goblin : public Monster {
public:
    Goblin() : Monster("Гоблин", 30, 10, 5) {}
};

class Dragon : public Monster {
public:
    Dragon() : Monster("Дракон", 100, 30, 10) {}
};

class Skeleton : public Monster {
public:
    Skeleton() : Monster("Скелет", 40, 12, 6) {}
};

class Troll : public Monster {
public:
    Vampire() : Monster("Вампир", 80, 20, 5) {}
};

// Класс инвентаря
class Inventory {
private:
    std::vector<std::string> items;

public:
    void addItem(const std::string& item) {
        items.push_back(item);
        std::cout << "Добавлен предмет: " << item << std::endl;
    }

    void removeItem(const std::string& item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
            std::cout << "Удалён предмет: " << item << std::endl;
        } else {
            std::cout << "Предмет не найден: " << item << std::endl;
        }
    }

    void displayInventory() const {
        std::cout << "Инвентарь:" << std::endl;
        for (const auto& item : items) {
            std::cout << " - " << item << std::endl;
        }
    }
};

// Класс игры
class Game {
private:
    Character player;
    Inventory inventory;
    Logger<std::string> logger;

public:
    Game() : player("Герой", 100, 20, 10), logger("game_log.txt") {}

    void start() {
        std::cout << "Начало игры..." << std::endl;
        player.displayInfo();
        inventory.addItem("Меч");
        inventory.displayInventory();
    }

    void battle(Monster& monster) {
        std::cout << "Битва с монстром: " << std::endl;
        monster.displayInfo();
        Character tempMonster(monster.name,  monster.health, monster.attack, monster.defense);

        while (player.getHealth() > 0 && tempMonster.getHealth() > 0) {
            player.attackEnemy(tempMonster, logger);
            if (tempMonster.getHealth() <= 0) {
                std::cout << "Монстр повержен!" << std::endl;
                player.gainExperience(50);
                return;
            }
            tempMonster.attackEnemy(player, logger);
            if (player.getHealth() <= 0) {
                std::cout << "Вы проиграли бой..." << std::endl;
                return;
            }
        }
    }

    void save() {
        std::ofstream file("save.txt");
        if (!file) {
            throw std::runtime_error("Ошибка при сохранении файла.");
        }
        file << player.getName() << ' ' << player.getHealth() << ' ' << player.getAttack()
             << ' ' << player.getDefense() << std::endl;
        std::cout << "Прогресс сохранён." << std::endl;
    }

    void load() {
        std::ifstream file("save.txt");
        if (!file) {
            throw std::runtime_error("Ошибка при загрузке файла.");
        }
        std::string name;
        int hp, atk, def;
        file >> name >> hp >> atk >> def;
        player = Character(name, hp, atk, def);
        std::cout << "Прогресс загружен." << std::endl;
    }
};

int main() {
    try {
        Game game;
        game.start();

        Goblin goblin;
        game.battle(goblin);

        game.save();
        game.load();

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
