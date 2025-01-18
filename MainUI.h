#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "DCList.h"
#include"SongRepository.h"
#include "Button.h"
#include "PlaylistList.h"
#include "PlaylistManager.h"
using namespace std;

bool deleteSongFromPlaylist(const string& email, const string& playlistName, const string& songFilePath) 
{
    string filename = email + "_" + playlistName + ".txt";
    ifstream file(filename);

    if (!file.is_open()) 
    {
        cerr << "Error opening playlist file: " << filename << endl;
        return false;
    }

    vector<string> songs;
    string line;
    bool songFound = false;

    while (getline(file, line)) 
    {
        if (line != songFilePath) 
        {
            songs.push_back(line);
        }
        else 
        {
            songFound = true;
        }
    }

    file.close();

    if (!songFound) 
    {
        cerr << "Song not found in playlist: " << songFilePath << endl;
        return false;
    }

    if (songs.empty()) 
    {
        if (remove(filename.c_str()) != 0) 
        {
            cerr << "Error deleting playlist file: " << filename << endl;
            return false;
        }
        cout << "Playlist file deleted: " << filename << endl;
        return true;
    }

    ofstream outFile(filename, ofstream::trunc);

    if (!outFile.is_open()) 
    {
        cerr << "Error opening playlist file for writing: " << filename << endl;
        return false;
    }

    for (const string& song : songs) 
    {
        outFile << song << endl;
    }

    outFile.close();
    cout << "Song deleted from playlist: " << songFilePath << endl;
    return true;
}

bool showPlaylistContentsWindow(Playlist& playlist, const string& email, const string& playlistName)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Playlist Contents");
    sf::Font font;

    if (!font.loadFromFile("font2.ttf"))
    {
        std::cerr << "Error loading font" << endl;
        return false;
    }

    vector<sf::Text> songTexts;
    vector<string> songs;
    sf::Text text;

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("sprites/bg1.jpg"))
    {
        std::cerr << "Error loading background image" << endl;
        return false;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(1.1, 1.333);

    Node* current = playlist.getHead();
    Node* head = playlist.getHead();
    bool deleted = false;

    if (current)
    {
        do
        {
            sf::Text songText;

            songText.setFont(font);
            songText.setCharacterSize(24);
            songText.setFillColor(sf::Color::White);
            songText.setString(current->filePath);
            songText.setPosition(20, songTexts.size() * 40 + 20);
            songTexts.push_back(songText);
            songs.push_back(current->filePath);

            current = current->next;
        } while (current != head);
    }

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    float scrollSpeed = 20.0f;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                    for (size_t i = 0; i < songTexts.size(); ++i)
                    {
                        if (songTexts[i].getGlobalBounds().contains(worldPos))
                        {
                            playlist.remove(songs[i]);
                            deleted = deleteSongFromPlaylist(email, playlistName, songs[i]);
                            cout << "Removed from playlist: " << songs[i] << endl;

                            songTexts.clear();
                            songs.clear();
                            Node* current = playlist.getHead();
                            Node* head = playlist.getHead();
                            
                            if (current == NULL) {
                                cout << "\ncurrent is null\n";
                                return true;

                            }
                            if (current)
                            {
                                do
                                {
                                    sf::Text songText;

                                    songText.setFont(font);
                                    songText.setCharacterSize(24);
                                    songText.setFillColor(sf::Color::White);
                                    songText.setString(current->filePath);//exception
                                    songText.setPosition(20, songTexts.size() * 40 + 20);
                                    songTexts.push_back(songText);
                                    songs.push_back(current->filePath);

                                    current = current->next;
                                } while (current != head);
                            }
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                for (size_t i = 0; i < songTexts.size(); ++i)
                {
                    sf::Text& songText = songTexts[i];

                    if (songText.getGlobalBounds().contains(worldPos))
                    {
                        songText.setFillColor(sf::Color(30, 215, 96));
                    }
                    else
                    {
                        songText.setFillColor(sf::Color::White);
                    }
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    view.move(0, -scrollSpeed);
                }
                else
                {
                    view.move(0, scrollSpeed);
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    view.move(0, -scrollSpeed);
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    view.move(0, scrollSpeed);
                }
            }
        }

        window.clear(sf::Color(18, 18, 18));
        window.setView(window.getDefaultView());
        window.draw(backgroundSprite);
        window.setView(view);

        for (size_t i = 0; i < songTexts.size(); ++i)
        {
            window.draw(songTexts[i]);
        }

        window.display();
    }

    playlist.current = playlist.head;
    return false;
}

void showSongSelectionWindow(SongGraph& graph, Playlist& playlist)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Select Songs");
    sf::Font font;

    if (!font.loadFromFile("font2.ttf"))
    {
        cerr << "Error loading font" << endl;
        return;
    }

    vector<sf::Text> songTexts;
    vector<string> songs;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/bg1.jpg"))
    {
        cerr << "Error loading background image" << endl;
        return;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(1.1, 1.33);

    GraphNode* current = graph.getHead();

    while (current)
    {
        sf::Text songText;
        songText.setFont(font);
        songText.setCharacterSize(24);
        songText.setFillColor(sf::Color::White);
        songText.setString(current->songFilePath);
        songText.setPosition(20, songTexts.size() * 40 + 20);
        songTexts.push_back(songText);
        songs.push_back(current->songFilePath);

        current = current->next;
    }

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    float scrollSpeed = 20.0f;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                    for (size_t i = 0; i < songTexts.size(); ++i)
                    {
                        if (songTexts[i].getGlobalBounds().contains(worldPos))
                        {
                            playlist.add(songs[i]);
                            cout << "Added to playlist: " << songs[i] << endl;
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                for (size_t i = 0; i < songTexts.size(); ++i)
                {
                    sf::Text& songText = songTexts[i];

                    if (songText.getGlobalBounds().contains(worldPos))
                    {
                        songText.setFillColor(sf::Color(30, 215, 96));
                    }

                    else
                    {
                        songText.setFillColor(sf::Color::White);
                    }
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    view.move(0, -scrollSpeed);
                }
                else
                {
                    view.move(0, scrollSpeed);
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    view.move(0, -scrollSpeed);
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    view.move(0, scrollSpeed);
                }
            }
        }

        window.clear(sf::Color(18, 18, 18));
        window.setView(window.getDefaultView());
        window.draw(backgroundSprite);
        window.setView(view);

        for (size_t i = 0; i < songTexts.size(); ++i)
        {
            window.draw(songTexts[i]);
        }

        window.display();
    }
}

bool isButtonClicked(Button& button, const sf::RenderWindow& window) 
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return button.isClickedFunc();
}

void showPlaylistManagementWindow(SongGraph& graph, UserHashTable& users, User& loggedInUser)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Manage Playlists");
    sf::Font font;

    if (!font.loadFromFile("font2.ttf"))
    {
        std::cerr << "Error loading font" << endl;
        return;
    }

    Button createPlaylistButton(210, 50, "Create/Add to Playlist", font);
    Button loadPlaylistButton(210, 50, "Load Playlist", font);
    Button playButton(210, 50, "Play Playlist", font);
    Button nextButton(200, 50, "Next", font);
    Button prevButton(200, 50, "Previous", font);
    Button pauseButton(40, 50, "||", font);
    Button searchButton(210, 50, "Search", font);
    Button deleteButton(210, 50, "Delete Playlist", font);
    Button deleteButton2(210, 50, "Delete Song", font);
    Button backButton(70, 25, "Back", font);
    Button exitButton(70, 25, "Exit", font);

    backButton.text.setCharacterSize(18);
    exitButton.text.setCharacterSize(18);

    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("sprites/bg2.jpg"))
    {
        std::cerr << "Error loading background image" << endl;
        return;
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    backgroundSprite.setScale(0.625, 0.5);
    createPlaylistButton.setPosition(50, 50);
    loadPlaylistButton.setPosition(50, 120);
    playButton.setPosition(50, 190);
    searchButton.setPosition(50, 260);
    deleteButton.setPosition(50, 330);
    deleteButton2.setPosition(50, 400);
    nextButton.setPosition(350, 500);
    prevButton.setPosition(50, 500);
    pauseButton.setPosition(280, 500);
    backButton.setPosition(570, 560);
    exitButton.setPosition(670, 560);
    exitButton.text.setPosition(690, 560);
    backButton.text.setPosition(590, 560);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(50, 465);

    sf::Text currentSongText;
    currentSongText.setFont(font);
    currentSongText.setCharacterSize(24);
    currentSongText.setFillColor(sf::Color::Green);
    currentSongText.setPosition(50, 470);

    sf::Text searchResultText;
    searchResultText.setFont(font);
    searchResultText.setCharacterSize(24);
    searchResultText.setFillColor(sf::Color::Yellow);
    searchResultText.setPosition(50, 500);

    sf::Text playlistContentsText;
    playlistContentsText.setFont(font);
    playlistContentsText.setCharacterSize(18);
    playlistContentsText.setFillColor(sf::Color::White);
    playlistContentsText.setPosition(340, 50);

    sf::Text recommendationsText;
    recommendationsText.setFont(font);
    recommendationsText.setCharacterSize(18);
    recommendationsText.setFillColor(sf::Color::Cyan);
    recommendationsText.setPosition(50, 550);

    string enteredText;

    bool isCreating = false;
    bool isLoading = false;
    bool isPlaying = false;
    bool isSearching = false;
    bool isDeleting = false;
    bool isDeleting2 = false;
    bool forMySake = false;
    bool showPlaylistContents = false;

    PlaylistList playlistList(loggedInUser);
    PlaylistManager playlistManager;
    Playlist* currentPlaylist = nullptr;
    string playlistFileName;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            forMySake = 0;

            createPlaylistButton.update(window);
            loadPlaylistButton.update(window);
            playButton.update(window);
            nextButton.update(window);
            prevButton.update(window);
            searchButton.update(window);
            deleteButton.update(window);
            deleteButton2.update(window);
            backButton.update(window);
            exitButton.update(window);

            if (isPlaying && currentPlaylist)
            {
                pauseButton.update(window);
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (isCreating || isLoading || isSearching || isDeleting)
                    {
                        if (event.text.unicode == '\b')
                        {
                            if (!enteredText.empty())
                            {
                                enteredText.erase(enteredText.size() - 1, 1);
                            }
                        }
                        else if (event.text.unicode == '\r')
                        {
                            if (isCreating)
                            {
                                if (currentPlaylist && currentPlaylist->getCurrent())
                                {
                                    if (currentPlaylist->getCurrent()->music.getStatus() == sf::Music::Playing)
                                        currentPlaylist->getCurrent()->music.stop();
                                }

                                playlistFileName = enteredText;
                                playlistManager.createPlaylist(loggedInUser.getEmail(), playlistFileName);
                                currentPlaylist = new Playlist();
                                showSongSelectionWindow(graph, *currentPlaylist);
                                playlistList.addPlaylist(playlistFileName, *currentPlaylist);
                                playlistManager.savePlaylist(loggedInUser.getEmail(), playlistFileName, *currentPlaylist);
                                isCreating = false;
                                enteredText.clear();
                            }

                            else if (isLoading)
                            {
                                if (currentPlaylist && currentPlaylist->getCurrent())
                                {
                                    if (currentPlaylist->getCurrent()->music.getStatus() == sf::Music::Playing)
                                        currentPlaylist->getCurrent()->music.stop();
                                }

                                playlistFileName = enteredText;
                                currentPlaylist = new Playlist();

                                if (playlistManager.loadPlaylist(loggedInUser.getEmail(), playlistFileName, *currentPlaylist))
                                {
                                    std::cout << "Playlist loaded from: " << playlistFileName << std::endl;
                                    playlistList.addPlaylist(playlistFileName, *currentPlaylist);
                                    showPlaylistContents = true;
                                    isLoading = false;
                                    enteredText.clear();
                                }

                                else
                                {
                                    cout << "Error loading playlist file" << endl;
                                    isLoading = false;
                                    enteredText.clear();
                                    playlistFileName.clear();
                                }
                            }

                            else if (isSearching)
                            {
                                string result = currentPlaylist ? currentPlaylist->search(enteredText) : "";

                                if (result != "")
                                {
                                    searchResultText.setString("Found: " + result);
                                    currentPlaylist->getCurrent()->music.stop();
                                    currentPlaylist->setCurrent(result);
                                    currentPlaylist->play();
                                }

                                else
                                {
                                    searchResultText.setString("No results found");
                                }

                                enteredText.clear();
                            }

                            else if (isDeleting)
                            {
                                playlistFileName = enteredText;
                                if (playlistManager.deletePlaylist(loggedInUser.getEmail(), playlistFileName))
                                {
                                    cout << "Playlist deleted: " << playlistFileName << endl;

                                    if (currentPlaylist && playlistFileName == playlistFileName)
                                    {
                                        delete currentPlaylist;
                                        currentPlaylist = nullptr;
                                    }
                                }

                                else
                                {
                                    std::cerr << "Error deleting playlist" << endl;
                                }

                                isDeleting = false;
                                enteredText.clear();
                            }
                        }

                        else
                        {
                            enteredText += event.text.unicode;
                        }

                        inputText.setString(enteredText);
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (createPlaylistButton.isClickedFunc())
                    {
                        isCreating = true;
                        isLoading = false;
                        isPlaying = false;
                        isSearching = false;
                        isDeleting = false;
                        forMySake = true;
                        showPlaylistContents = false;
                        inputText.setString("Enter new playlist name:");
                        enteredText.clear();
                    }

                    else if (loadPlaylistButton.isClickedFunc())
                    {
                        isCreating = false;
                        isLoading = true;
                        isPlaying = false;
                        isSearching = false;
                        isDeleting = false;
                        forMySake = true;
                        showPlaylistContents = true;
                        inputText.setString("Enter playlist file name:");
                        enteredText.clear();
                    }

                    else if (playButton.isClickedFunc() && currentPlaylist)
                    {
                        isCreating = false;
                        isLoading = false;
                        isPlaying = true;
                        isSearching = false;
                        isDeleting = false;
                        forMySake = true;
                        showPlaylistContents = true;

                        if (currentPlaylist->isEmpty())
                        {
                            std::cerr << "No song in the playlist to play" << endl;
                        }

                        else
                        {
                            currentPlaylist->play();
                        }
                    }

                    else if (searchButton.isClickedFunc())
                    {
                        isCreating = false;
                        isLoading = false;
                        isPlaying = false;
                        isSearching = true;
                        isDeleting = false;
                        forMySake = true;
                        showPlaylistContents = true;
                        inputText.setString("Enter search query:");
                        enteredText.clear();
                    }

                    else if (deleteButton.isClickedFunc())
                    {
                        isCreating = false;
                        isLoading = false;
                        isPlaying = false;
                        isSearching = false;
                        isDeleting = true;
                        forMySake = true;
                        showPlaylistContents = false;
                        inputText.setString("Enter playlist name to delete:");
                        enteredText.clear();
                    }

                    else if (deleteButton2.isClickedFunc() && currentPlaylist)
                    {
                        isCreating = false;
                        isLoading = false;
                        isPlaying = false;
                        isSearching = false;
                        isDeleting = false;
                        showPlaylistContents = false;
                        isDeleting2 = true;
                        forMySake = true;
                        enteredText.clear();
                    }

                    else if (pauseButton.isClickedFunc() && isPlaying && currentPlaylist)
                    {
                        currentPlaylist->pause();
                        isPlaying = false;
                        forMySake = true;
                        pauseButton.isClicked = 0;
                    }

                    else if (nextButton.isClickedFunc() && isPlaying && currentPlaylist)
                    {
                        currentPlaylist->next();
                        forMySake = true;
                    }

                    else if (prevButton.isClickedFunc() && isPlaying && currentPlaylist)
                    {
                        currentPlaylist->previous();
                        forMySake = true;
                    }

                    else if (backButton.isClickedFunc())
                    {
                        isCreating = false;
                        isLoading = false;
                        isPlaying = false;
                        isSearching = false;
                        isDeleting = false;
                        isDeleting2 = false;
                        forMySake = true;
                        showPlaylistContents = false;
                        inputText.setString("");
                        enteredText.clear();
                    }

                    else if (exitButton.isClickedFunc())
                    {
                        window.close();
                    }

                    if (isDeleting2)
                    {
                        isDeleting2 = false;
                        bool flag=showPlaylistContentsWindow(*currentPlaylist, loggedInUser.getEmail(), playlistFileName);
                        if (flag) {
                            delete currentPlaylist;
                            currentPlaylist = nullptr;
                        }
                        isDeleting2 = false;
                        deleteButton2.isClicked = 0;
                    }
                }
            }
        }

        window.clear(sf::Color(18, 18, 18));

        window.draw(backgroundSprite);
        createPlaylistButton.draw(window);
        loadPlaylistButton.draw(window);
        playButton.draw(window);
        searchButton.draw(window);
        deleteButton.draw(window);
        deleteButton2.draw(window);
        backButton.draw(window);
        exitButton.draw(window);

        if (isPlaying && currentPlaylist)
        {
            nextButton.draw(window);
            prevButton.draw(window);
            pauseButton.draw(window);
        }

        if (showPlaylistContents && currentPlaylist && (playlistFileName[0] != '\0'))
        {
            sf::RectangleShape backgroundRect(sf::Vector2f(400, 420));
            backgroundRect.setPosition(320, 40);
            backgroundRect.setFillColor(sf::Color(50, 50, 50, 200));
            window.draw(backgroundRect);

            Node* currentNode = currentPlaylist->getHead();
            Node* h = currentPlaylist->getHead();
            string playlistContents;
            playlistContents = playlistFileName + "\n\n";

            do
            {
                playlistContents += currentNode->filePath + "\n";
                currentNode = currentNode->next;
            } while (currentNode != h);

            playlistContentsText.setString(playlistContents);
            window.draw(playlistContentsText);
        }

        window.draw(inputText);

        if (isSearching)
        {
            window.draw(searchResultText);
        }

        else if (isPlaying && currentPlaylist)
        {
            string currentFilePath = currentPlaylist->getCurrentSongFilePath();
            currentSongText.setString("Playing: " + currentFilePath);
            window.draw(currentSongText);

            vector<string> recommendations = graph.recommendSongs(currentFilePath);
            string recommendationsString;

            if (recommendations.empty())
            {
                recommendationsString = "No recommendations available";
            }
            else
            {
                for (size_t i = 0; i < recommendations.size(); ++i)
                {
                    string& rec = recommendations[i];
                    recommendationsString += rec + "\n";
                }
            }

            recommendationsText.setString(recommendationsString);
            window.draw(recommendationsText);
        }

        window.display();
    }
}