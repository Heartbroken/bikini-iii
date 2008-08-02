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
		bk::video l_video;
		l_video.create();
		bk::window l_window(l_video);
#if defined(XBOX)
		l_window.create();
#elif defined(WIN32)
		l_window.create(1024U, 640U);
		l_window.set_caption("test_application ");
		l_window.show();
#endif
		bk::gui l_gui;
		l_gui.create();
		bk::ticker l_ticker(1.f/30.f);
		bk::rbig l_time = bk::sys_time();
		while(true) {
			bk::real l_dt = bk::real(bk::sys_time() - l_time);
			l_time = bk::sys_time();
			l_video.update(l_dt);
			if(!l_window.update(l_dt)) break;
			l_time = bk::sys_time();
			// do something useful
			//
			l_ticker.sync();
		}
		l_gui.destroy();
		l_window.destroy();
		l_video.destroy();
	}
};

#if defined(XBOX)
void main()
#elif defined(WIN32)
int _tmain(int argc, _TCHAR* argv[])
#endif
{
	{
	bk::application l_app;
	task0::info l_task0;
	l_app.spawn(l_task0);
	//l_app.spawn(l_task0);
	l_app.run();
	}
#if defined(WIN32)
	return 0;
#endif
}

