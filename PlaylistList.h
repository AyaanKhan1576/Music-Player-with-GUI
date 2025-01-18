#pragma once
#include<iostream>
#include "DCList.h"
#include "UserHash.h"
#include<string>
using namespace std;


struct PlaylistNode 
{
    string name;
    Playlist playlist;
    PlaylistNode* next;

    PlaylistNode(const std::string& name, const Playlist& playlist)
        : name(name), playlist(playlist), next(nullptr) {}
};

class PlaylistList 
{
private:
    User user;
    PlaylistNode* head;

public:
    PlaylistList(const User& user) : user(user), head(nullptr) {}

    void addPlaylist(const string& name, const Playlist& playlist) 
    {
        PlaylistNode* newNode = new PlaylistNode(name, playlist);
        newNode->next = head;
        head = newNode;
    }

    Playlist* findPlaylist(const std::string& name) 
    {
        PlaylistNode* current = head;

        while (current) 
        {
            if (current->name == name) 
            {
                return &(current->playlist);
            }

            current = current->next;
        }

        return nullptr;
    }

    void displayPlaylists() 
    {
        PlaylistNode* current = head;

        while (current) 
        {
            cout << current->name << endl;
            current = current->next;
        }
    }

    ~PlaylistList() 
    {
        PlaylistNode* current = head;
        
        while (current) 
        {
            PlaylistNode* next = current->next;
            delete current;
            current = next;
        }
    }
};