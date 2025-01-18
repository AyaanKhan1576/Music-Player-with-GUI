# i220832_i220849_DS_Project
Data Structures Final Project - Summers 2024. 
FAST NUCES. 
Ayaan Khan (22i-0832) and Minahil Ali (22i-0849). 
BAI-A

GitHub Link to Project:
https://github.com/i220832/i220832_i220849_DS_Project

**To compile this program:**
1. Make sure you have SFML installed and setup correctly for your Visual Studio or Visual Studio Code
2. Configure the IDE settings appropriately to ensure SFML programs can be compiled
3. Download the files as they are with their folders without changing the naming convention or contents
4. Follow instructions in music_link.txt in Music folder to download the songs. Only .wav files will work with this program.
5. This program will only run on Windows OS. Functionalities are not designed for any other OS.
6. For Visual Studio Code, run the following lines in the terminal:
   
   g++ -IC:\SFML-2.5.1\include -c main.cpp
   g++ -LC:\SFML-2.5.1\lib .\main.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main
   ./app


**Project Details:**

The goal of this project is to create a music player such as the popular music streaming program, Spotify, using advanced data structures to improve the efficiency of the program as well as to minimize the resources it utilizes and minimize the time complexity.

**Data Structures Used:**
1. Graphs
2. HashTables
3. Singly Linked List
4. Doubly Circular Linked List

**Project Structure**
1. Project Starts off with initialising all songs in a Graph Data Structure which is to be used for the song recommendation system and also as the base where all the songs are stored to be retrived by the other data structures

2. Following this the User login/sign-up system is implemented via hashing and a hashTable.

3. All user information is hashed and stored to a user.txt file which is used to retrieve, store and reinitialise hashTable values everytime the program is restarted so that user information is kept saved

4. User can then create or load a playlist which is stored into a Singly Linked List called the PlaylistList. These are unique to each user and cannot be accessed by other users.

5. These too are saved to files via file handling so that information is stored and retrieved even after the program is closed.

6. The nodes of the Singly Linked List are the Playlist class which themselves are Doubly Circular Linked Lists to actually host the playlists themselves.

7. The Doubly circular linked lists have the songs (in .wav) files as their Nodes.

8. Simultaneously, each Doubly Circular Linked List of the Playlist class has a unique HashTable associated with it which hashes and stores their songs so that searching can be conducted optimally in an average case of O(1) time complexity.

**Files Descriptions**

1. main.cpp
   Initialises the graphs with songs as well as their connections for the recommendation system and calls the main UserUI function

2. UserUI.h
   Handles display and functions of the User Interface for the Login/Sign-Up screen via SFML as well as handles all file handling, user authentication and calls upon hashing functions for user related information

3. UserHash.h
   Hosts the Data Structure for the User related Hash Tables and hashing functions which are utilised by UserUI.h

4. MainUI.h
   Responsible for the main interface of the program via SFML such as Creating/Loading Playlists, Playing Songs, Removing, and Searching. 

5. PlaylistList.h
   Hosts the PlaylistList Singly Linked List

6. PlaylistManager.h
   Responsible for most playlist related file handling tasks. Used in conjunction with MainUI.h

7. SongRepository.h
   Stores the Graph data structure used for songs and recommendation

8. Button.h
   A helper class made to seamlessly interact with buttons created via SFML for all interface related tasks.

9. DCList.h
   Stores the Playlist Doubly Circular Linked List

10. hashing.h
    Hosts the hashTable and hashing functions for songs, specifically for the search function in the DCList. 
