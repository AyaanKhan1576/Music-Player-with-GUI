#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <functional>
using namespace std;

class HashNode
{
public:
    string key;
    HashNode* next;

    HashNode(const string& k) : key(k), next(nullptr) {}
};

class CustomHashTable
{
public:
    vector<HashNode*> table;
    size_t tableSize;
    hash<string> hashFunction;

    size_t hash(const string& key) const 
    {
        return hashFunction(key) % tableSize;
    }


    CustomHashTable(size_t size) : tableSize(size) 
    {
        table.resize(size, nullptr);
    }

    void insert(const string& key) 
    {
        size_t index = hash(key);
        HashNode* newNode = new HashNode(key);

        if (!table[index]) 
        {
            table[index] = newNode;
        }

        else 
        {
            HashNode* entry = table[index];

            while (entry->next && entry->key != key) 
            {
                entry = entry->next;
            }

            if (entry->key == key) 
            {
                delete newNode;
            }

            else 
            {
                entry->next = newNode;
            }
        }
    }

    bool find(const string& key) const 
    {
        size_t index = hash(key);
        HashNode* entry = table[index];

        while (entry) 
        {
            if (entry->key == key) 
            {
                return true;
            }

            entry = entry->next;
        }

        return false;
    }

    bool find2(string& key, string& filePath) const
    {
        string found = "";
        size_t index = hash(key);
        HashNode* entry = table[index];

        while (entry) 
        {
            if (entry->key == key) 
            {
                filePath = entry->key;
                return 1;
            }

            entry = entry->next;
        }

        return 0;
    }

    void remove(const string& key) 
    {
        size_t index = hash(key);
        HashNode* entry = table[index];
        HashNode* prev = nullptr;

        while (entry) 
        {
            if (entry->key == key) 
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

    void display() const 
    {
        for (size_t i = 0; i < tableSize; ++i) 
        {
            cout << "Bucket " << i << ": ";
            HashNode* entry = table[i];

            if (!entry) 
            {
                cout << "Empty" << endl;
            }

            else 
            {
                while (entry) 
                {
                    cout << entry->key;
                    if (entry->next) 
                    {
                        cout << " -> ";
                    }

                    entry = entry->next;
                }

                cout << endl;
            }
        }
    }

    ~CustomHashTable() 
    {
        for (size_t i = 0; i < tableSize; i++) 
        {
            HashNode* entry = table[i];
            
            while (entry) 
            {
                HashNode* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }
};
