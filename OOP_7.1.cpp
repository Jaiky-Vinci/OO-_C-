#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <sstream>

class Entity {
protected:
    std::string name;
    int health;

public:
    Entity(const std::string& name, int health)
        : name(name), health(health) {}

    virtual void displayInfo() const = 0;
    virtual std::string serialize() const = 0;
    virtual int getHealth() const { return health; }
    virtual ~Entity() = default;
};

class Player : public Entity {
    int experience;

public:
    Player(const std::string& name, int health, int experience)
        : Entity(name, health), experience(experience) {}

    void displayInfo() const override {
        std::cout << "Игрок: " << name << ", Здоровье: " << health
                  << ", Опыт: " << experience << "\n";
    }

    std::string serialize() const override {
        return "Player " + name + " " + std::to_string(health) + " " + std::to_string(experience);
    }

    static std::unique_ptr<Entity> deserialize(std::istringstream& iss) {
        std::string name;
        int health, exp;
        iss >> name >> health >> exp;
        return std::make_unique<Player>(name, health, exp);
    }
};

class Enemy : public Entity {
    std::string type;

public:
    Enemy(const std::string& name, int health, const std::string& type)
        : Entity(name, health), type(type) {}

    void displayInfo() const override {
        std::cout << "Враг: " << name << " (тип: " << type << "), Здоровье: " << health << "\n";
    }

    std::string serialize() const override {
        return "Enemy " + name + " " + std::to_string(health) + " " + type;
    }

    static std::unique_ptr<Entity> deserialize(std::istringstream& iss) {
        std::string name, type;
        int health;
        iss >> name >> health >> type;
        return std::make_unique<Enemy>(name, health, type);
    }
};

class GameManager {
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void addEntity(std::unique_ptr<Entity> entity) {
        entities.push_back(std::move(entity));
    }

    void displayAll() const {
        std::cout << "=== Список персонажей ===\n";
        for (const auto& entity : entities) {
            entity->displayInfo();
        }
    }

    const std::vector<std::unique_ptr<Entity>>& getEntities() const {
        return entities;
    }

    void clear() {
        entities.clear();
    }
};

void saveToFile(const GameManager& manager, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }

    for (const auto& entity : manager.getEntities()) {
        file << entity->serialize() << "\n";
    }

    std::cout << "Сохранение выполнено успешно в файл: " << filename << "\n";
}

void loadFromFile(GameManager& manager, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для чтения.");
    }

    manager.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "Player") {
            manager.addEntity(Player::deserialize(iss));
        } else if (type == "Enemy") {
            manager.addEntity(Enemy::deserialize(iss));
        } else {
            std::cerr << "Неизвестный тип сущности: " << type << "\n";
        }
    }

    std::cout << "Загрузка выполнена успешно из файла: " << filename << "\n";
}

int main() {
    try {
        GameManager manager;
        manager.addEntity(std::make_unique<Player>("Герой", 100, 15));
        manager.addEntity(std::make_unique<Enemy>("Гоблин", 50, "Воин"));

        saveToFile(manager, "game_save.txt");

        GameManager loadedManager;
        loadFromFile(loadedManager, "game_save.txt");
        loadedManager.displayAll();

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
