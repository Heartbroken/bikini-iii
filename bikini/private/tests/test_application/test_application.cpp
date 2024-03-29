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
		l_window.create(800, 600, false);
		l_window.set_caption("test_application ");
		l_window.show();
		l_window.clear();
		bk::flash::player l_player;
		l_player.create(l_window);
		l_player.play("data/gui/test.swf");
		bk::ticker l_ticker(bk::real(1.0/30.0));
		bk::rbig l_time = bk::sys_time();
		while(true) {
			bk::real l_dt = bk::real(bk::sys_time() - l_time); l_time = bk::sys_time();
			l_dt = bk::min(l_dt, bk::real(0.3));
			l_video.update(l_dt);
			if(!l_window.update(l_dt)) break;
			// do something useful
			l_player.update(l_dt);
			l_window.clear(bk::cf::all, bk::white);
			l_window.begin();
			l_player.render();
			l_window.flush_drawings();
			l_window.end();
			l_window.present();
			//
			l_ticker.sync();
		}
		l_player.destroy();
		l_window.destroy();
		l_video.destroy();
	}
};

#if defined(XBOX)
void main() {
	bk::application l_app;
	task0::info l_task0;
	l_app.spawn(l_task0);
	l_app.run();
}
#elif defined(WIN32)
int _tmain(int argc, _TCHAR* argv[]) {
	bk::application l_app;
	task0::info l_task0;
	l_app.spawn(l_task0);
	l_app.run();
	return 0;
}
#endif
