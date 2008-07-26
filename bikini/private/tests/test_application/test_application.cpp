// test_application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

namespace at { enum application_tasks {
	task0
};}

struct task0 : bk::application::task {
	struct info : bk::application::task::info {
		typedef task0 object;
		inline info() : bk::application::task::info(at::task0) {}
	};
	inline task0(const info &_info, bk::application &_application) :
		bk::application::task(_info, _application)
	{}
	void main() {
		bk::window l_window;
		l_window.create(1024U, 640U);
		l_window.set_caption("test_application ");
		l_window.show();
		//m_video.create();
		//m_video.activate(l_window.handle());
		bk::ticker l_ticker(1.f/30.f);
		bk::rbig l_time = bk::sys_time();
		while(true) {
			if(!l_window.update(bk::real(bk::sys_time() - l_time))) break;
			//m_video.begin_scene();
			//m_video.clear_viewport();
			//m_video.end_scene();
			//m_video.present();
			l_time = bk::sys_time();
			// do something useful
			//
			l_ticker.sync();
		}
		l_window.destroy();
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	{
	bk::application l_app;
	task0::info l_task0;
	l_app.spawn(l_task0);
	//l_app.spawn(l_task0);
	l_app.run();
	}
	return 0;
}

