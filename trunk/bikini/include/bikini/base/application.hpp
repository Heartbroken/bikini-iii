/*---------------------------------------------------------------------------------------------*//*

	Binary Kinematics 3 - C++ Game Programming Library
	Copyright (C) 2008 Viktor Reutzky
	reutzky@bitchingames.com

*//*---------------------------------------------------------------------------------------------*/

#pragma once

///	base application class
/**	[TODO]
 *	
 */
struct application : manager {
	/// base application task class
	/**	[TODO]
	 *	
	 */
	struct task : manager::object {
		struct info : manager::object::info {
			typedef task object;
			typedef application manager;
			info(uint _type);
		};
		task(const info &_info, application &_application);
		~task();
		inline application& get_application() const { return static_cast<application&>(get_manager()); }
		inline bool done() const { return m_task.done(); }
		inline void wait() const { return m_task.wait(); }
	protected:
		virtual void main() = 0;
	private:
		thread::task m_task;
	};
	virtual bool run();
};