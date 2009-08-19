#pragma once

#include <windows.h>

namespace ipf { // --------------------------------------------------------------------------------

//
typedef unsigned int playerID;

//
playerID create_player();

//
void destroy_player(playerID _player);

//
bool play_movie(playerID _player, char* _path);

//
bool stop_movie(playerID _player);

} // namespace ipf --------------------------------------------------------------------------------