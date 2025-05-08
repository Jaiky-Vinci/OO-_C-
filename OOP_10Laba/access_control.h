#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include "users.h"
#include "resource.h"

template<typename U, typename R>
class AccessControlSystem {
    std::vector<std::shared_ptr<U>> users;
    std::vector<R> resources;

public:
    void addUser(const std::shared_ptr<U>& user) {
        users.push_back(user);
    }

    void addResource(const R& resource) {
        resources.push_back(resource);
    }

    void displayAllUsers() const {
        for (const auto& user : users)
            user->displayInfo();
    }

    void checkAccessForAll() const {
        for (const auto& user : users) {
            for (const auto& resource : resources) {
                std::cout << user->getName() << " access to " << resource.getName()
                          << ": " << (resource.checkAccess(*user) ? "GRANTED" : "DENIED") << std::endl;
            }
        }
    }

    void saveUsersToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& user : users) {
            file << user->toCSV() << std::endl;
        }
    }

    void saveResourcesToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& resource : resources) {
            file << resource.toCSV() << std::endl;
        }
    }

    void findUserByName(const std::string& searchName) const {
        for (const auto& user : users) {
            if (user->getName() == searchName) {
                user->displayInfo();
                return;
            }
        }
        std::cout << "User not found." << std::endl;
    }

    void sortUsersByAccessLevel() {
        std::sort(users.begin(), users.end(), [](const std::shared_ptr<U>& a, const std::shared_ptr<U>& b) {
            return a->getAccessLevel() > b->getAccessLevel();
        });
    }
};
