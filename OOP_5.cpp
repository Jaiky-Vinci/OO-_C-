#include <iostream>
#include <vector>
#include <string>

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
        std::cout << "Враг: " << name << " (тип: " << type << "), Здоровье: " << health << "\n";
    }
};

template <typename T>
class GameManager {
private:
    std::vector<T> entities;

public:
    void addEntity(const T& entity) {
        entities.push_back(entity);
    }

    void displayAll() const {
        std::cout << "=== Список игровых объектов ===\n";
        for (const auto& entity : entities) {
            entity->displayInfo(); // Предполагается, что T — указатель на объект с displayInfo()
        }
    }
};

template <typename T>
class Queue {
private:
    std::vector<T> items;

public:
    void push(const T& item) {
        items.push_back(item);
    }

    void pop() {
        if (!items.empty()) {
            items.erase(items.begin());
        } else {
            std::cout << "Очередь пуста!\n";
        }
    }

    void display() const {
        std::cout << "Содержимое очереди:\n";
        for (const auto& item : items) {
            std::cout << "- " << item << "\n";
        }
    }
};

int main() {
    GameManager<Entity*> manager;
    manager.addEntity(new Player("Герой", 100, 10));
    manager.addEntity(new Enemy("Орк", 80, "Воин"));
    manager.displayAll();

    std::cout << "\n=== Очередь строк ===\n";
    Queue<std::string> stringQueue;
    stringQueue.push("Первый");
    stringQueue.push("Второй");
    stringQueue.display();
    stringQueue.pop();
    stringQueue.display();

    std::cout << "\n=== Очередь чисел ===\n";
    Queue<int> intQueue;
    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);
    intQueue.display();
    intQueue.pop();
    intQueue.display();

    return 0;
}

