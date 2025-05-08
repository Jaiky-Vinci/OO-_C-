#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    std::string email;
    std::string address;

public:
    // Геттеры
    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    std::string getEmail() const {
        return email;
    }

    std::string getAddress() const {
        return address;
    }

    // Сеттеры
    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        } else {
            std::cerr << "Ошибка: имя не может быть пустым!" << std::endl;
        }
    }

    void setAge(int newAge) {
        if (newAge >= 0 && newAge <= 120) {
            age = newAge;
        } else {
            std::cerr << "Ошибка: возраст должен быть в диапазоне от 0 до 120!" << std::endl;
        }
    }

    void setEmail(const std::string& newEmail) {
        if (newEmail.find('@') != std::string::npos) {
            email = newEmail;
        } else {
            std::cerr << "Ошибка: некорректный формат email!" << std::endl;
        }
    }

    void setAddress(const std::string& newAddress) {
        if (!newAddress.empty()) {
            address = newAddress;
        } else {
            std::cerr << "Ошибка: адрес не может быть пустым!" << std::endl;
        }
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Возраст: " << age
                  << ", Email: " << email << ", Адрес: " << address << std::endl;
    }
};

int main() {
    Person person;

    person.setName("Иван Иванов");
    person.setAge(30);
    person.setEmail("ivan@example.com");
    person.setAddress("г. Москва, ул. Пушкина, д. 10");

    std::cout << "Имя: " << person.getName() << std::endl;
    std::cout << "Возраст: " << person.getAge() << std::endl;
    std::cout << "Email: " << person.getEmail() << std::endl;
    std::cout << "Адрес: " << person.getAddress() << std::endl;

    std::cout << "\nПроверка работы метода displayInfo():\n";
    person.displayInfo();

    std::cout << "\nПопытка задать некорректные значения:\n";
    person.setName("");
    person.setAge(200);
    person.setEmail("notanemail");
    person.setAddress("");

    std::cout << "\nИнформация после попытки ввода ошибок:\n";
    person.displayInfo();

    return 0;
}
