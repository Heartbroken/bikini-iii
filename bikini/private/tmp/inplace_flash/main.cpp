#include "inplace_flash.h"

ipf::player_ID g_player_ID;

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		case WM_TIMER : {
			InvalidateRect(hWnd, NULL, FALSE);
		} return 0;
		case WM_PAINT : {
			PAINTSTRUCT l_paint;
			HDC l_hdc = BeginPaint(hWnd, &l_paint);
			ipf::player_draw(g_player_ID, l_hdc);
			EndPaint(hWnd, &l_paint);
		} return 0;
		case WM_MOUSEMOVE :
		case WM_LBUTTONUP :
		case WM_LBUTTONDOWN :
		case WM_LBUTTONDBLCLK : {
			int l_x = LOWORD(lParam);
			int l_y = HIWORD(lParam);
			bool l_pressed = wParam&MK_LBUTTON;
			ipf::player_mouse(g_player_ID, l_x, l_y, l_pressed);
		} return 0;
		case WM_KEYDOWN :
		case WM_KEYUP :
		case WM_CHAR :
		case WM_DEADCHAR :
		case WM_SYSKEYDOWN :
		case WM_SYSKEYUP :
		case WM_SYSDEADCHAR :
		case WM_CANCELMODE : {
			if(ipf::player_message(g_player_ID, msg, wParam, lParam)) return 0;
		} break;
		case WM_DESTROY : {
			PostQuitMessage(0);
		} return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

int main()
{
//
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, (HBRUSH)GetStockObject(GRAY_BRUSH), NULL,
		TEXT("DxFlashViewer"), NULL };
	RegisterClassEx( &wc );

	// Create the application's window
	HWND hWnd = CreateWindow( TEXT("DxFlashViewer"), TEXT("DxFlashViewer"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL );
//
	ShowWindow(hWnd, SW_SHOW);
	SetTimer(hWnd, 0, 16, 0);


	g_player_ID = ipf::create_player();

	if (ipf::player_load(g_player_ID, "D:/BACKUP!!! viktor.reutskyy/Trash/FYEO/bikini-iii/private/tmp/inplace_flash/sheriff.swf"))
	{
		ipf::player_play(g_player_ID);
		//
		MSG msg;
		ZeroMemory( &msg, sizeof(msg) );
		while( msg.message!=WM_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		//
		ipf::player_stop(g_player_ID);
	}

	ipf::destroy_player(g_player_ID);
}