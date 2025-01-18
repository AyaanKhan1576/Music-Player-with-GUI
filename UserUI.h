#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "UserHash.h"
#include "SongRepository.h"
#include "Button.h"
#include "MainUI.h"
using namespace std;


void showUserManagementWindow(UserHashTable& users, SongGraph& graph)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "User Management");
    sf::Font font;

    if (!font.loadFromFile("font2.ttf"))
    {
        std::cerr << "Error loading font" << endl;
        return;
    }

    Button signUpButton(115, 50, "Sign Up", font);
    Button loginButton(115, 50, "Login", font);
    Button exitButton(70, 25, "Exit", font);
    exitButton.text.setCharacterSize(18);
    signUpButton.setPosition(200, 400);
    loginButton.setPosition(450, 400);
    exitButton.setPosition(670, 560);
    exitButton.text.setPosition(690, 560);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/bg1.jpg"))
    {
        std::cerr << "Error loading background image" << endl;
        return;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(1.1, 1.33);

    sf::Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(24);
    nameText.setFillColor(sf::Color::White);
    nameText.setPosition(50, 75);
    nameText.setCharacterSize(40);
    nameText.setString("music app");

    sf::Text emailText;
    emailText.setFont(font);
    emailText.setCharacterSize(24);
    emailText.setFillColor(sf::Color::White);
    emailText.setPosition(250, 300);

    sf::Text passwordText;
    passwordText.setFont(font);
    passwordText.setCharacterSize(24);
    passwordText.setFillColor(sf::Color::White);
    passwordText.setPosition(250, 350);

    string email, password;
    bool isSignUp = false;
    bool isLogin = false;
    bool exitRequested = false;
    bool waitingForPassword = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            signUpButton.update(window);
            loginButton.update(window);
            exitButton.update(window);

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == '\b')
                    {
                        if (waitingForPassword && !password.empty())
                        {
                            password.pop_back();
                        }

                        else if (!email.empty())
                        {
                            email.pop_back();
                        }
                    }
                    else if (event.text.unicode == '\r')
                    {
                        if (waitingForPassword)
                        {
                            if (isSignUp)
                            {
                                if (User::emailExists(email))
                                {
                                    std::cerr << "User already exists" << endl;
                                }

                                else
                                {
                                    User newUser(email, password);
                                    newUser.saveToFile();
                                    users.insert(newUser);
                                    cout << "Sign up successful" << endl;
                                }

                                isSignUp = false;
                                isLogin = false;
                            }

                            else if (isLogin)
                            {
                                if (User::verifyPassword(email, password))
                                {
                                    cout << "Login successful" << endl;
                                    User loggedUser(email, password);
                                    users.insert(loggedUser);
                                    User loggedInUser = users.getUser(email);
                                    showPlaylistManagementWindow(graph, users, loggedInUser);
                                    window.close();
                                }

                                else
                                {
                                    std::cerr << "Invalid email or password" << endl;
                                }

                                isLogin = false;
                                isSignUp = false;
                            }

                            email.clear();
                            password.clear();
                            waitingForPassword = false;
                        }

                        else
                        {
                            waitingForPassword = true;
                            emailText.setString("Username: " + email);
                            passwordText.setString("Password: " + string(password.size(), '*'));
                        }
                    }

                    else
                    {
                        if (!waitingForPassword)
                        {
                            if (email.size() < 50)
                            {
                                email += static_cast<char>(event.text.unicode);
                            }
                        }

                        else
                        {
                            if (password.size() < 50)
                            {
                                password += static_cast<char>(event.text.unicode);
                            }
                        }

                        emailText.setString("Username: " + email);
                        passwordText.setString("Password: " + string(password.size(), '*'));
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isButtonClicked(signUpButton, window))
                    {
                        if (!waitingForPassword)
                        {
                            isSignUp = true;
                            isLogin = false;
                            emailText.setString("Sign Up\nUsername: " + email);
                            passwordText.setString("Password: " + string(password.size(), '*'));
                        }
                    }

                    else if (isButtonClicked(loginButton, window))
                    {
                        if (!waitingForPassword)
                        {
                            isSignUp = false;
                            isLogin = true;
                            emailText.setString("Login\nUsername: " + email);
                            passwordText.setString("Password: " + string(password.size(), '*'));
                        }
                    }

                    else if (isButtonClicked(exitButton, window))
                    {
                        exitRequested = true;
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        signUpButton.draw(window);
        loginButton.draw(window);
        exitButton.draw(window);
        window.draw(emailText);
        window.draw(nameText);

        if (waitingForPassword)
            window.draw(passwordText);

        window.display();
    }
}