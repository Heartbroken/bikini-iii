/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	base application class
/**	
 *	
 */
struct application {
	application();
	virtual ~application();
	void run();
private:
	int test_run(sint) const;
};