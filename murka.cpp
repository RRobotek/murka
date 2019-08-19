#include <windows.h>


// mouse movement delta per keypress in pixels
constexpr byte mouseDeltaNormal			= 8;
constexpr byte mouseDeltaFast			= 16;
constexpr byte mouseDeltaSlow			= 3;

// key to toggle keyboard hook
constexpr DWORD keyMurkaToggle			= VK_CAPITAL;  // Caps_Lock

// keys to control mouse speed
constexpr DWORD keyMouseFast			= 0x46; // f
constexpr DWORD keyMouseSlow			= 0x53; // s
constexpr DWORD keyMouseNormal			= 0x44; // d

// keys to move the mouse
constexpr DWORD keyMouseMoveRight		= 0x4C; // l
constexpr DWORD keyMouseMoveLeft		= 0x48; // h
constexpr DWORD keyMouseMoveUp			= 0x4B; // k
constexpr DWORD keyMouseMoveDown		= 0x4A; // j

// keys to click the mouse
constexpr DWORD keyMouseClickLeft		= 0x55; // u
constexpr DWORD keyMouseClickRight		= 0x49; // i




HHOOK	hHook;

BOOL	isToggled				= FALSE;
byte	mouseDelta				= mouseDeltaNormal;

INPUT	mouseInput = {mouseInput.type					= INPUT_MOUSE,
					  mouseInput.mi.dx					= 0,	
					  mouseInput.mi.dy					= 0,	
					  mouseInput.mi.mouseData			= 0,	
					  mouseInput.mi.time				= 0,	
					  mouseInput.mi.dwExtraInfo			= NULL};
					 
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	isToggled = ((GetAsyncKeyState(keyMurkaToggle) == -32767) &&	// ??? FIXME
				 (GetAsyncKeyState(keyMurkaToggle) == -32768)) ^ 	// ??? FIXME
				(isToggled);										// ??? FIXME

	if(isToggled)
	{
		if(wParam == WM_KEYDOWN)
		{
		    KBDLLHOOKSTRUCT key = *(PKBDLLHOOKSTRUCT)lParam;

			mouseInput.mi.dx = 0;
			mouseInput.mi.dy = 0;
			
			switch (key.vkCode)
			{
				// movement
				case keyMouseMoveRight:
					mouseInput.mi.dx =+ mouseDelta;
					break;

				case keyMouseMoveLeft:
					mouseInput.mi.dx =- mouseDelta;
					break;

				case keyMouseMoveUp:
					mouseInput.mi.dy =- mouseDelta;
					break;

				case keyMouseMoveDown:
					mouseInput.mi.dy =+ mouseDelta;
					break;

				// speed
				case keyMouseFast:
					mouseDelta = mouseDeltaFast;
					break;

				case keyMouseSlow:
					mouseDelta = mouseDeltaSlow;
					break;

				case keyMouseNormal:
					mouseDelta = mouseDeltaNormal;
					break;

				// clicks

				case keyMouseClickLeft:
					mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &mouseInput, sizeof(mouseInput));

					Sleep(50);

					mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &mouseInput, sizeof(mouseInput));
					return 1;

				case keyMouseClickRight:
					mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
					SendInput(1, &mouseInput, sizeof(mouseInput));

					Sleep(50);

					mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
					SendInput(1, &mouseInput, sizeof(mouseInput));
					return 1;

				default:
					return CallNextHookEx(hHook, nCode, wParam, lParam);
			}

			mouseInput.mi.dwFlags = MOUSEEVENTF_MOVE;
			SendInput(1, &mouseInput, sizeof(mouseInput));

		}
		return 1;
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	hHook = SetWindowsHookExW(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, GetModuleHandle(NULL), NULL);

	register MSG message;

	while(true) GetMessageW(&message, NULL, 0, 0);

	return 0;
}
