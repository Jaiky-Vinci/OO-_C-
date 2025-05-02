#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Entity {
protected:
    std::string name;
    int health;

public:
    Entity(const std::string& name, int health)
        : name(name), health(health) {}

    virtual void displayInfo() const = 0;
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
};

class Enemy : public Entity {
    std::string type;

public:
    Enemy(const std::string& name, int health, const std::string& type)
        : Entity(name, health), type(type) {}

    void displayInfo() const override {
        std::cout << "Араг: " << name << " (тип: " << type << "), Здоровье: " << health << "\n";
    }
};

class Inventory {
private:
    std::unique_ptr<std::string[]> items;
    size_t capacity;
    size_t count;

public:
    Inventory(size_t size)
        : capacity(size), count(0), items(std::make_unique<std::string[]>(size)) {}

    void addItem(const std::string& item) {
        if (count < capacity) {
            items[count++] = item;
        } else {
            std::cout << "Инвентарь переполнен!\n";
        }
    }

    void displayInventory() const {
        std::cout << "Инвентарь (" << count << " из " << capacity << "):\n";
        for (size_t i = 0; i < count; ++i) {
            std::cout << "- " << items[i] << "\n";
        }
    }
};

int main() {
    std::unique_ptr<Entity> entities[] = {
        std::make_unique<Player>("Герой", 100, 0),
        std::make_unique<Enemy>("Макака", 50, "Макака")
    };

    std::cout << "=== Существа ===\n";
    for (const auto& entity : entities) {
        entity->displayInfo();
    }

    std::cout << "\n=== Инвентарь ===\n";
    Inventory playerInventory(5);
    playerInventory.addItem("Меч");
    playerInventory.addItem("Зелье здоровья");
    playerInventory.addItem("Шит");
    playerInventory.displayInventory();

    return 0;
}
