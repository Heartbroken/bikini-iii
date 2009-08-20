#pragma once

#include <windows.h>

namespace ipf { // --------------------------------------------------------------------------------

//
typedef unsigned int player_ID;

//
player_ID create_player();

//
void destroy_player(player_ID _ID);

//
bool player_load(player_ID _ID, char* _movie);

//
bool player_play(player_ID _ID);

//
bool player_pause(player_ID _ID);

//
bool player_stop(player_ID _ID);

//
bool player_draw(player_ID _ID, HDC _hdc);

//
bool player_mouse(player_ID _ID, int _x, int _y, bool _pressed);

} // namespace ipf --------------------------------------------------------------------------------