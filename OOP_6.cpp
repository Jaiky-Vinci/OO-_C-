#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// ===== Базовый класс Сущность =====
class Entity {
protected:
    std::string name;
    int health;

public:
    Entity(const std::string& name, int health)
        : name(name), health(health) {}

    virtual void displayInfo() const = 0;
    virtual int getHealth() const { return health; }
    virtual ~Entity() = default;
};

// ===== Класс Игрок =====
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

// ===== Класс Враг =====
class Enemy : public Entity {
    std::string type;

public:
    Enemy(const std::string& name, int health, const std::string& type)
        : Entity(name, health), type(type) {}

    void displayInfo() const override {
        std::cout << "Враг: " << name << " (тип: " << type << "), Здоровье: " << health << "\n";
    }
};

// ===== Шаблонный класс GameManager с обработкой исключений =====
template <typename T>
class GameManager {
private:
    std::vector<T> entities;

public:
    void addEntity(const T& entity) {
        if (entity->getHealth() <= 0) {
            throw std::invalid_argument("Сущность имеет недопустимое здоровье!");
        }
        entities.push_back(entity);
    }

    void displayAll() const {
        std::cout << "=== Список игровых объектов ===\n";
        for (const auto& entity : entities) {
            entity->displayInfo();
        }
    }
};

// ===== Шаблонный класс Очередь с обработкой исключений =====
template <typename T>
class Queue {
private:
    std::vector<T> items;

public:
    void push(const T& item) {
        items.push_back(item);
    }

    void pop() {
        if (items.empty()) {
            throw std::out_of_range("Нельзя удалить элемент: очередь пуста!");
        }
        items.erase(items.begin());
    }

    void display() const {
        std::cout << "Содержимое очереди:\n";
        for (const auto& item : items) {
            std::cout << "- " << item << "\n";
        }
    }
};

// ===== Главная функция =====
int main() {
    // Тест GameManager с обработкой исключений
    try {
        GameManager<Entity*> manager;
        manager.addEntity(new Player("Герой", -50, 0)); // Ошибка: здоровье отрицательное
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка добавления сущности: " << e.what() << std::endl;
    }

    // Тест Queue с обработкой исключений
    try {
        Queue<std::string> strQueue;
        strQueue.push("Первый");
        strQueue.display();
        strQueue.pop();
        strQueue.pop(); // Ошибка: очередь пуста
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка при работе с очередью: " << e.what() << std::endl;
    }

    return 0;
}
