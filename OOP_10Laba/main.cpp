#include "access_control.h"

int main() {
    try {
        AccessControlSystem<User, Resource> system;

        system.addUser(std::make_shared<Student>("Alice", 1, 2, "CS-101"));
        system.addUser(std::make_shared<Teacher>("Bob", 2, 4, "Physics"));
        system.addUser(std::make_shared<Administrator>("Charlie", 3, 5, "IT Admin"));

        system.addResource(Resource("Library", 1));
        system.addResource(Resource("Lab", 3));
        system.addResource(Resource("Server Room", 5));

        std::cout << "\n=== USERS ===\n";
        system.displayAllUsers();

        std::cout << "\n=== ACCESS CHECK ===\n";
        system.checkAccessForAll();

        std::cout << "\n=== SORTED USERS ===\n";
        system.sortUsersByAccessLevel();
        system.displayAllUsers();

        std::cout << "\n=== FIND USER: Bob ===\n";
        system.findUserByName("Bob");

        system.saveUsersToFile("users.csv");
        system.saveResourcesToFile("resources.csv");

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
