#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "DCList.h"
using namespace std;

class PlaylistManager {
public:
    PlaylistManager() {}

    void savePlaylist(const string& email, const string& name, Playlist& playlist) 
    {
        string filename = email + "_" + name + ".txt";
        ofstream outFile(filename);

        if (outFile.is_open()) 
        {
            Node* current = playlist.getHead();

            if (current) 
            {
                do 
                {
                    outFile << current->filePath << endl;
                    current = current->next;
                } while (current != playlist.getHead());
            }

            outFile.close();
        }

        else 
        {
            std::cerr << "Error saving playlist to file: " << name << endl;
        }
    }

    bool getPlaylistDetails(const string& email, const string& name, string& playlistName, vector<string>& songs) 
    {
        string filename = email + "_" + name + ".txt";
        ifstream inFile(filename);

        if (inFile.is_open()) 
        {
            playlistName = name;
            string song;
            while (getline(inFile, song)) 
            {
                songs.push_back(song);
            }

            inFile.close();
            return true;
        }

        else 
        {
            cout << "Error loading playlist from file: " << name << endl;
            return false;
        }
    }

    bool loadPlaylist(const string& email, const string& name, Playlist& playlist) 
    {
        string filename = email + "_" + name + ".txt";
        ifstream inFile(filename);

        if (inFile.is_open()) 
        {
            string song;

            while (getline(inFile, song)) 
            {
                // if (song[0] == '\0')
                //     return 0;
                playlist.add(song);
            }

            inFile.close();
            return true;
        }

        else 
        {
            cout << "Error loading playlist from file: " << name << endl;
            return false;
        }
    }

    void createPlaylist(const string& email, const string& name) 
    {
        string filename = email + "_" + name + ".txt";
        ofstream outFile(filename);

        if (outFile.is_open()) 
        {
            cout << "New playlist created: " << name << endl;
            outFile.close();
        }

        else 
        {
            std::cerr << "Error creating playlist file: " << name << endl;
        }
    }

    bool deletePlaylist(const string& email, const string& name) 
    {
        string filename = email + "_" + name + ".txt";

        if (remove(filename.c_str()) == 0) 
        {
            cout << "Playlist deleted: " << name << endl;
            return true;
        }

        else 
        {
            std::cerr << "Error deleting playlist file: " << name << endl;
            return false;
        }
    }
};
