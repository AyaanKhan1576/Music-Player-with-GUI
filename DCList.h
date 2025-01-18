#pragma once
#include <iostream>
#include <string>
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "hashing.h"
using namespace std;

struct Node 
{
    string filePath;
    Node* next;
    Node* prev;
    sf::Music music; 

    Node(const string& path) : filePath(path), next(nullptr), prev(nullptr) 
    {
        if (!music.openFromFile(filePath)) 
        {
            std::cerr << "Error loading the MP3 file: " << filePath << endl;
        }
    }
};

class Playlist 
{
public:
    Node* head;
    Node* tail;
    CustomHashTable hashTable;
    Node* current;

    Playlist() : head(nullptr), tail(nullptr), hashTable(20), current(nullptr) {}

    Playlist(size_t hashTableSize) : head(nullptr), tail(nullptr), hashTable(hashTableSize), current(nullptr) {}

    bool isEmpty() const 
    {
        return head == nullptr;
    }

    Node* getHead() const 
    {
        return head;
    }

    Node* getCurrent() const 
    {
        return current;
    }

    void setCurrent(string x) 
    {
        Node* ptr = new Node(x);
        current = ptr;
    }

    string getCurrentSongFilePath() const 
    {
        if (current) 
        {
            return current->filePath;
        }

        else 
        {
            return "No song is currently playing";
        }
    }

    void add(const string& filePath) 
    {
        if (hashTable.find(filePath)) 
        {
            std::cerr << "File already in playlist: " << filePath << endl;
            return;
        }

        hashTable.insert(filePath);
        Node* newNode = new Node(filePath);

        if (!head) 
        {
            head = newNode;
            tail = newNode;
            head->next = head;
            head->prev = head;
        }

        else 
        {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }

        if (!current) 
        {
            current = head;
        }
    }

    void display() const 
    {
        if (!head) 
            return;

        Node* current = head;

        do 
        {
            cout << current->filePath << endl;
            current = current->next;
        } while (current != head);
    }

void remove(const string& filePath) 
{
    if (!hashTable.find(filePath)) 
    {
        std::cerr << "File not found in playlist: " << filePath << endl;
        return;
    }

    hashTable.remove(filePath);

    if (!head) 
    {
        return;
    }

    Node* current = head;

    do 
    {
        if (current->filePath == filePath) 
        {
            if (current == head) 
            {
                if (head == tail) 
                {
                    delete current;
                    head = nullptr;
                    tail = nullptr;
                    this->current = nullptr;
                    return;
                } 
                else 
                {
                    head = head->next;
                    tail->next = head;
                    head->prev = tail;
                }
            } 
            else if (current == tail) 
            {
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
            } 
            else 
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            if (this->current == current) 
            {
                this->current = head ? head : nullptr;
            }

            delete current;

            return;
        }

        current = current->next;
    } while (current != head);
}

    void play() 
    {
        if (!head) 
        {
            std::cerr << "Playlist is empty." << endl;
            return;
        }

        if (head && !current)
        {
            current = head;
            return;
        }

        if (current->music.getStatus() == sf::Music::Playing) 
        {
            current->music.stop();
        }

        current->music.play();
        cout << "Playing: " << current->filePath << endl;
    }

    void pause() 
    {
        if (!current) 
        {
            std::cerr << "No song is currently playing." << endl;
            return;
        }

        if (current->music.getStatus() == sf::Music::Playing) 
        {
            current->music.pause();
            cout << "Paused: " << current->filePath << endl;
        }

        else 
        {
            std::cerr << "Current song is not playing." << endl;
        }
    }

    void next() 
    {
        if (!current) 
        {
            std::cerr << "Playlist is empty." << endl;
            return;
        }

        current->music.stop();
        current = current->next;

        if (current) 
        {
            play(); 
        }
    }

    void previous() 
    {
        if (!current) 
        {
            std::cerr << "Playlist is empty." << endl;
            return;
        }

        current->music.stop();
        current = current->prev;

        if (current) 
        {
            play(); 
        }
    }

    string search(string& query) const 
    {
        string filePath = query;

        if (hashTable.find2(query, filePath) != 0) 
        {
            return filePath;
        }

        return ""; 
    }

    ~Playlist() 
    {
        if (head) 
        {
            Node* current = head;

            do 
            {
                Node* next = current->next;
                delete current;
                current = next;
            } while (current != head);
        }
    }
};
