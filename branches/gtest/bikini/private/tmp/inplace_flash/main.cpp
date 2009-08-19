#include "inplace_flash.h"

int main()
{
	ipf::playerID l_player = ipf::create_player();

	if (ipf::play_movie(l_player, "test.swf"))
	{
		//
		//
		ipf::stop_movie(l_player);
	}

	ipf::destroy_player(l_player);
}