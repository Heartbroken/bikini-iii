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
		m_window.create(GetModuleHandle(0), 1024U, 640U, 0);
		m_window.set_caption(L".application ");
		m_window.show();
		bk::rbig l_time = bk::sys_time();
		while(true) {
			bk::thread::task l_step(THREAD_PRIORITY_TIME_CRITICAL);
			l_step.run(bk::sleep, 0.03f);
			if(!m_window.update(bk::real(bk::sys_time() - l_time))) break;
			// do something useful
			l_step.wait();
			l_time = bk::sys_time();
		}
	}
private:
	bk::window m_window;
};

int _tmain(int argc, _TCHAR* argv[])
{
	//
	typedef HWND (WINAPI *GetConsoleWindow_fn)(void);
	HMODULE l_kernel32_h = GetModuleHandle(L"kernel32.dll");
	GetConsoleWindow_fn GetConsoleWindow = (GetConsoleWindow_fn)GetProcAddress(l_kernel32_h, "GetConsoleWindow");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//
	{
	SetConsoleTitle(L" bikini-iii");
	bk::application l_app;
	task0::info l_task0; l_app.spawn(l_task0);
	l_app.run();
	//bk::sleep(3.f);
	}
	return 0;
}
