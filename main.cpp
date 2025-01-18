#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include "DCList.h"
#include "Button.h"
#include "SongRepository.h"
#include "UserHash.h"
#include "PlaylistList.h"
#include "PlaylistManager.h"
#include "UserUI.h"
using namespace std;

int main() 
{
    UserHashTable users(100); 
    SongGraph graph;

    graph.addSong("Music/All We Know - Chainsmokers.wav");
    graph.addSong("Music/Alone - Alan Walker.wav");
    graph.addSong("Music/American Dream - Gabbie June.wav");
    graph.addSong("Music/Animal I Have Become - Three Days Grace.wav");
    graph.addSong("Music/Animals - Maroon 5.wav");
    graph.addSong("Music/Another Life - Afrojack And David Guetta.wav");
    graph.addSong("Music/Ariana Grande - No Tears Left To Cry (Lyrics).wav");
    graph.addSong("Music/Bad Blood - Taylor Swift.wav");
    graph.addSong("Music/Be Alright - Ariana Grande.wav");
    graph.addSong("Music/Frozen - Madonna.wav");
    graph.addSong("Music/Ain't No Mountain High - Stepmom.wav");
    graph.addSong("Music/I Don't Want To Miss A Thing - Aerosmith.wav");
    graph.addSong("Music/Its My Life - Bon Jovi.wav");
    graph.addSong("Music/Never Say Goodbye - Bon Jovi.wav");
    graph.addSong("Music/Oops, I Did It Again - Britney Spears.wav");
    graph.addSong("Music/Cruel Summer.wav");
    graph.addSong("Music/Blaze Of Glory - Jon Bon Jovi.wav");
    graph.addSong("Music/Tik Tok - Kesha.wav");
    graph.addSong("Music/Best Song Ever - One Direction.wav");
    graph.addSong("Music/Wind Of Change - Scorpion.wav");
    graph.addSong("Music/Eye Of The Tiger - Survivor.wav");
    graph.addSong("Music/Back To You - Louis Tomlison.wav");

    graph.addConnection("Music/American Dream - Gabbie June.wav", "Music/Another Life - Afrojack And David Guetta.wav");
    graph.addConnection("Music/Alone - Alan Walker.wav", "Music/Ariana Grande - No Tears Left To Cry (Lyrics).wav");
    graph.addConnection("Music/All We Know - Chainsmokers.wav", "Music/Animals - Maroon 5.wav");
    graph.addConnection("Music/Animals - Maroon 5.wav", "Music/Animal I Have Become - Three Days Grace.wav");
    graph.addConnection("Music/Another Life - Afrojack And David Guetta.wav", "Music/Back To You - Louis Tomlison.wav");
    graph.addConnection("Music/Ariana Grande - No Tears Left To Cry (Lyrics).wav", "Music/Animals - Maroon 5.wav");
    graph.addConnection("Music/All We Know - Chainsmokers.wav", "Music/Alone - Alan Walker.wav");
    graph.addConnection("Music/Be Alright - Ariana Grande.wav", "Music/Ariana Grande - No Tears Left To Cry (Lyrics).wav");
    graph.addConnection("Music/Bad Blood - Taylor Swift.wav", "Music/Cruel Summer.wav");
    graph.addConnection("Music/Best Song Ever - One Direction.wav", "Music/Back To You - Louis Tomlison.wav");
    graph.addConnection("Music/Blaze Of Glory - Jon Bon Jovi.wav", "Music/Its My Life - Bon Jovi.wav");
    graph.addConnection("Music/Blaze Of Glory - Jon Bon Jovi.wav", "Music/Never Say Goodbye - Bon Jovi.wav");
    graph.addConnection("Music/Never Say Goodbye - Bon Jovi.wav", "Music/Ariana Grande - No Tears Left To Cry (Lyrics).wav");
    graph.addConnection("Music/Eye Of The Tiger - Survivor.wav", "Music/Animal I Have Become - Three Days Grace.wav");
    graph.addConnection("Music/Frozen - Madonna.wav", "Music/Ariana Grande - No Tears Left To Cry (Lyrics).wav");
    graph.addConnection("Music/Its My Life - Bon Jovi.wav", "Music/Never Say Goodbye - Bon Jovi.wav");
    graph.addConnection("Music/Another Life - Afrojack And David Guetta.wav", "Music/Animals - Maroon 5.wav");
    graph.addConnection("Music/Alone - Alan Walker.wav", "Music/Ain't No Mountain High - Stepmom.wav");
    graph.addConnection("Music/Alone - Alan Walker.wav", "Music/Be Alright - Ariana Grande.wav");
    graph.addConnection("Music/Be Alright - Ariana Grande.wav", "Music/Bad Blood - Taylor Swift.wav");
    graph.addConnection("Music/Tik Tok - Kesha.wav", "Music/Best Song Ever - One Direction.wav");
    graph.addConnection("Music/Back To You - Louis Tomlison.wav", "Music/Wind Of Change - Scorpion.wav");
    graph.addConnection("Music/Wind Of Change - Scorpion.wav", "Music/Eye Of The Tiger - Survivor.wav");
    graph.addConnection("Music/Wind Of Change - Scorpion.wav", "Music/Cruel Summer.wav");
    graph.addConnection("Music/Cruel Summer.wav", "Music/Oops, I Did It Again - Britney Spears.wav");
    graph.addConnection("Music/Cruel Summer.wav", "Music/Best Song Ever - One Direction.wav");
    graph.addConnection("Music/Eye Of The Tiger - Survivor.wav", "Music/Oops, I Did It Again - Britney Spears.wav");
    graph.addConnection("Music/Oops, I Did It Again - Britney Spears.wav", "Music/Tik Tok - Kesha.wav");
    graph.addConnection("Music/Oops, I Did It Again - Britney Spears.wav", "Music/Frozen - Madonna.wav");
    graph.addConnection("Music/Bad Blood - Taylor Swift.wav", "Music/Blaze Of Glory - Jon Bon Jovi.wav");
    graph.addConnection("Music/Ain't No Mountain High - Stepmom.wav", "Music/I Don't Want To Miss A Thing - Aerosmith.wav");
    graph.addConnection("Music/Its My Life - Bon Jovi.wav", "Music/Oops, I Did It Again - Britney Spears.wav");
    graph.addConnection("Music/Frozen - Madonna.wav", "Music/I Don't Want To Miss A Thing - Aerosmith.wav");
    graph.addConnection("Music/Tik Tok - Kesha.wav", "Music/Wind Of Change - Scorpion.wav");
    graph.addConnection("Music/Back To You - Louis Tomlison.wav","Music/Oops, I Did It Again - Britney Spears.wav" );
    graph.addConnection("Music/Never Say Goodbye - Bon Jovi.wav", "Music/Frozen - Madonna.wav");
    graph.addConnection("Music/Best Song Ever - One Direction.wav", "Music/Animals - Maroon 5.wav");
    graph.addConnection("Music/I Don't Want To Miss A Thing - Aerosmith.wav", "Music/Oops, I Did It Again - Britney Spears.wav");
    graph.addConnection("Music/I Don't Want To Miss A Thing - Aerosmith.wav", "Music/Be Alright - Ariana Grande.wav");
    graph.addConnection("Music/Animal I Have Become - Three Days Grace.wav", "Music/Cruel Summer.wav");
    
    showUserManagementWindow(users, graph);

    return 0;
}