

#include <windows.h>
#include <fstream>
#include <wdmguid.h>

#include "config.h"

extern "C"
{
#include "ini.h"
}

struct CONFIG_DATA _ConfigData;

BOOL				isToggled				= false;
HHOOK				hHook;
byte				mouseDelta				= 5; // FIXME

// mouseInput struct for SendInput()
INPUT	mouseInput = {mouseInput.type					= INPUT_MOUSE,
					  mouseInput.mi.dx					= 0,	
					  mouseInput.mi.dy					= 0,	
					  mouseInput.mi.mouseData			= 0,	
					  mouseInput.mi.time				= 0,	
					  mouseInput.mi.dwExtraInfo			= NULL};


byte toggleCounter		= 0;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_KEYUP) // when keys get "pushed up"
	{
		KBDLLHOOKSTRUCT key = *(PKBDLLHOOKSTRUCT)lParam;

		// recoginze the sequence of keys
		if (memcmp(_ConfigData.toggleKeys+toggleCounter, &key.vkCode, 1) == 0) // if equal
		{
			if (toggleCounter == _ConfigData.numberOfToggleKeys - 1) // if last
			{
				isToggled = !isToggled;
				return 1;
			}
			else // if not last
			{
				toggleCounter++;
				return 1;
			}
		}
		else // if not equal
		{
			toggleCounter = 0;
		}
	}

	if(isToggled)
	{
		if(wParam == WM_KEYDOWN) // when keys get pushed down
		{
		    KBDLLHOOKSTRUCT key = *(PKBDLLHOOKSTRUCT)lParam;
			
			mouseInput.mi.dx = 0;
			mouseInput.mi.dy = 0;
		

			// movement
			if(key.vkCode == _ConfigData.keyMouseMoveRight)
			{
				mouseInput.mi.dx = mouseDelta;
			}
			if(key.vkCode == _ConfigData.keyMouseMoveLeft)
			{
				mouseInput.mi.dx = -mouseDelta;
			}
			if(key.vkCode == _ConfigData.keyMouseMoveUp)
			{
				mouseInput.mi.dy = -mouseDelta;
			}
			if(key.vkCode == _ConfigData.keyMouseMoveDown)
			{
				mouseInput.mi.dy = mouseDelta;
			}

			// speed (changes delta to one of the 3 specified in the config)
			if(key.vkCode == _ConfigData.keyMouseFast)
			{
				mouseDelta = _ConfigData.mouseDeltaFast;
			}
			if(key.vkCode == _ConfigData.keyMouseSlow)
			{
				mouseDelta = _ConfigData.mouseDeltaSlow;
			}
			if(key.vkCode == _ConfigData.keyMouseNormal)
			{
				mouseDelta = _ConfigData.mouseDeltaNormal;
			}

			// clicks

			if(key.vkCode == _ConfigData.keyMouseClickLeft)
			{
				mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				SendInput(1, &mouseInput, sizeof(mouseInput));

				Sleep(50);

				mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
				SendInput(1, &mouseInput, sizeof(mouseInput));
			}
			if(key.vkCode == _ConfigData.keyMouseClickRight)
			{
				mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
				SendInput(1, &mouseInput, sizeof(mouseInput));

				Sleep(50);

				mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
				SendInput(1, &mouseInput, sizeof(mouseInput));
			}
			
			// send move message
			mouseInput.mi.dwFlags = MOUSEEVENTF_MOVE;
			SendInput(1, &mouseInput, sizeof(mouseInput));
			return 1;
		}
	}
	CallNextHookEx(hHook, nCode, wParam, lParam);
}
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{

	Config::Load(_ConfigData);
	mouseDelta = _ConfigData.mouseDeltaNormal;

	hHook = SetWindowsHookExW(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, GetModuleHandle(NULL), NULL);

	// loop messages
	register MSG message; while(true) GetMessageW(&message, NULL, 0, 0);

	return 0;
}