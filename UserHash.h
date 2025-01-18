#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include <sstream>
using namespace std;


class User 
{
public:
    string email;
    size_t hashedPassword;

    User(const string& email = "", const string& password = "")
        : email(email), hashedPassword(hashPassword(password)) {}

    static size_t hashPassword(const string& password) 
    {
        return hash<string>{}(password);
    }

    void saveToFile() const 
    {
        ofstream outFile("users.txt", ios::app);

        if (outFile.is_open()) 
        {
            outFile << email << " " << hashedPassword << "\n";
            outFile.close();
        }

        else 
        {
            cerr << "Error saving user to file" << endl;
        }
    }

    static bool loadFromFile(const string& email, User& user) 
    {
        ifstream inFile("users.txt");

        if (inFile.is_open()) 
        {
            string line;
            while (getline(inFile, line)) 
            {
                istringstream iss(line);
                string storedEmail;
                size_t storedHashedPassword;

                if (iss >> storedEmail >> storedHashedPassword) 
                {
                    if (storedEmail == email) 
                    {
                        user.email = storedEmail;
                        user.hashedPassword = storedHashedPassword;
                        return true;
                    }
                }
            }

            inFile.close();
        }

        return false;
    }

    static bool verifyPassword(const string& email, const string& password) 
    {
        User user;
        return loadFromFile(email, user) && user.hashedPassword == hashPassword(password);
    }

    static bool emailExists(const string& email) 
    {
        ifstream inFile("users.txt");

        if (inFile.is_open()) 
        {
            string line;

            while (getline(inFile, line)) 
            {
                istringstream iss(line);
                string storedEmail;
                if (iss >> storedEmail) 
                {
                    if (storedEmail == email) 
                    {
                        return true;
                    }
                }
            }

            inFile.close();
        }

        return false;
    }

    string getEmail()
    {
        return email;
    }

    size_t getHashedPassword()
    {
        return hashedPassword;
    }
};

class UserHashNode 
{
public:
    User user;
    UserHashNode* next;

    UserHashNode(const User& user) : user(user), next(nullptr) {}
};

class UserHashTable 
{
private:
    vector<UserHashNode*> table;
    size_t tableSize;
    hash<string> hashFunction;

    size_t hash(const string& key) const 
    {
        return hashFunction(key) % tableSize;
    }

public:
    UserHashTable(size_t size) : tableSize(size) 
    {
        table.resize(size, nullptr);
    }

    void insert(const User& user) 
    {
        size_t index = hash(user.email);
        UserHashNode* newNode = new UserHashNode(user);

        if (!table[index]) 
        {
            table[index] = newNode;
        }

        else 
        {
            UserHashNode* entry = table[index];

            while (entry->next && entry->user.email != user.email) 
            {
                entry = entry->next;
            }

            if (entry->user.email == user.email) 
            {
                delete newNode;
            }

            else 
            {
                entry->next = newNode;
            }
        }
    }

    bool find(const string& email, User& user) const 
    {
        size_t index = hash(email);
        UserHashNode* entry = table[index];

        while (entry) 
        {
            if (entry->user.email == email) 
            {
                user = entry->user;
                return true;
            }

            entry = entry->next;
        }

        return false;
    }

    void remove(const string& email) 
    {
        size_t index = hash(email);
        UserHashNode* entry = table[index];
        UserHashNode* prev = nullptr;

        while (entry) 
        {
            if (entry->user.email == email) 
            {
                if (prev) 
                {
                    prev->next = entry->next;
                }

                else 
                {
                    table[index] = entry->next;
                }

                delete entry;
                return;
            }

            prev = entry;
            entry = entry->next;
        }
    }

    User getUser(const string& email) 
    {
        int index = hash(email);
        UserHashNode* current = table[index];

        while (current) 
        {
            if (current->user.getEmail() == email) 
            {
                return current->user;
            }
            current = current->next;
        }
    }


    void saveToFile(const string& filename) 
    {
        std::ofstream outFile(filename);

        if (outFile.is_open()) 
        {
            for (size_t i = 0; i < table.size(); ++i) 
            {
                UserHashNode* current = table[i];
                while (current) 
                {
                    outFile << current->user.getEmail() << " " << current->user.getHashedPassword() << endl;
                    current = current->next;
                }
            }

            outFile.close();
        }

        else 
        {
            std::cerr << "Error opening file for saving user data" << endl;
        }
    }

    void loadFromFile(const std::string& filename) 
    {
        std::ifstream inFile(filename);

        if (inFile.is_open()) 
        {
            string email;
            string hashedPassword;

            while (inFile >> email >> hashedPassword) 
            {
                User user(email, hashedPassword);
                insert(user);
            }

            inFile.close();
        }

        else 
        {
            std::cerr << "Error opening file for loading user data" << endl;
        }
    }



    ~UserHashTable() 
    {
        for (size_t i = 0; i < tableSize; i++) 
        {
            UserHashNode* entry = table[i];
            while (entry) 
            {
                UserHashNode* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }
};
