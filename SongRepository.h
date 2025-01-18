#pragma once
#include<iostream>

class GraphNode 
{
public:
    string songFilePath;
    string genre;  
    string artist; 
    GraphNode* next;
    GraphNode* connections;

    GraphNode(const string& path, const string& genre = "", const string& artist = "")
        : songFilePath(path), genre(genre), artist(artist), next(nullptr), connections(nullptr) {}

    void addConnection(GraphNode* other) 
    {
        GraphNode* newConnection = new GraphNode(other->songFilePath, other->genre, other->artist);
        newConnection->next = connections;
        connections = newConnection;
    }

    ~GraphNode() 
    {
        GraphNode* current = connections;

        while (current) 
        {
            GraphNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

class SongGraph 
{
private:
    GraphNode* head;

public:
    SongGraph() : head(nullptr) {}

    ~SongGraph() 
    {
        GraphNode* current = head;

        while (current) 
        {
            GraphNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    GraphNode* getHead()
    { 
        return head; 
    }

    void addSong(const string& filePath, const string& genre = "", const string& artist = "") 
    {
        GraphNode* newNode = new GraphNode(filePath, genre, artist);
        newNode->next = head;
        head = newNode;
    }

    void addConnection(const string& path1, const string& path2) 
    {
        GraphNode* node1 = findNode(path1);
        GraphNode* node2 = findNode(path2);

        if (node1 && node2) 
        {
            node1->addConnection(node2);
        }

        else 
        {
            cerr << "One or both songs not found: " << path1 << ", " << path2 << endl;
        }
    }

    vector<string> recommendSongs(const string& filePath) const 
    {
        vector<string> recommendations;
        GraphNode* node = findNode(filePath);

        if (node) 
        {
            GraphNode* connection = node->connections;

            while (connection) 
            {
                recommendations.push_back(connection->songFilePath);
                connection = connection->next;
            }
        }

        return recommendations;
    }

    vector<string> recommendSimilarSongs(const string& filePath) const 
    {
        vector<string> recommendations;
        GraphNode* node = findNode(filePath);

        if (node) 
        {
            GraphNode* current = head;

            while (current) 
            {
                if (current != node && (current->genre == node->genre || current->artist == node->artist)) 
                {
                    recommendations.push_back(current->songFilePath);
                }

                current = current->next;
            }
        }

        return recommendations;
    }



    GraphNode* findNode(const string& filePath) const 
    {
        GraphNode* current = head;

        while (current) 
        {
            if (current->songFilePath == filePath) 
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

};
