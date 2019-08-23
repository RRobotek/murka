#include "config.h"
#include "log.h"

#include <psapi.h>


extern "C"
{
	#include "ini.h"
}




void Config::Load(CONFIG_DATA& _ConfigData)
{
	const char* configPath = "..\\config\\config.ini"; // TODO: same directory

	// load config 
	ini_t *config = ini_load(configPath);

	/* movement seciton */
	memcpy(&_ConfigData.keyMouseMoveRight,	ini_get(config, "mouse_movement", "right_key"),		sizeof(byte));
	memcpy(&_ConfigData.keyMouseMoveLeft,	ini_get(config, "mouse_movement", "left_key"),		sizeof(byte));
	memcpy(&_ConfigData.keyMouseMoveUp,		ini_get(config, "mouse_movement", "up_key"),		sizeof(byte));
	memcpy(&_ConfigData.keyMouseMoveDown,	ini_get(config, "mouse_movement", "down_key"),		sizeof(byte));

	/* click section */
	memcpy(&_ConfigData.keyMouseClickRight,	ini_get(config, "mouse_click", "right_key"),		sizeof(byte));
	memcpy(&_ConfigData.keyMouseClickLeft,	ini_get(config, "mouse_click", "left_key"),			sizeof(byte));

	/* speed keys*/
	memcpy(&_ConfigData.keyMouseFast,		ini_get(config, "mouse_speed", "fast_key"),			sizeof(byte));
	memcpy(&_ConfigData.keyMouseNormal,		ini_get(config, "mouse_speed", "normal_key"),		sizeof(byte));
	memcpy(&_ConfigData.keyMouseSlow,		ini_get(config, "mouse_speed", "slow_key"),			sizeof(byte));

	/* speed deltas */
	_ConfigData.mouseDeltaFast		= atoi(ini_get(config, "mouse_speed", "fast_delta"));
	_ConfigData.mouseDeltaNormal	= atoi(ini_get(config, "mouse_speed", "normal_delta"));
	_ConfigData.mouseDeltaSlow		= atoi(ini_get(config, "mouse_speed", "slow_delta"));

	/* toggle_sequence */

	_ConfigData.numberOfToggleKeys = atoi(ini_get(config, "toggle_sequence", "number_of_keys")); // number of keys to to toggle keyboard-mouse mode
	_ConfigData.toggleKeys = (byte*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, _ConfigData.numberOfToggleKeys); // FIXME not freeing! create init & uninit
	char* key = (char*)malloc(sizeof(char) * 5);	// key + 1 + \0 
													// max keys in the sequence = 9
	// loop for all keys (key1, key2, key3)
	for (int i = 1; i <= _ConfigData.numberOfToggleKeys; i++)
	{
		sprintf_s(key, 5, "key%d", i);

		// TODO: there is a better way & no support for ; and ' etc.
		if		(strcmp(ini_get(config, "toggle_sequence", key), KEYSTRING_LSHIFT) == 0)		_ConfigData.toggleKeys[i-1] = VK_LSHIFT;
		else if (strcmp(ini_get(config, "toggle_sequence", key), KEYSTRING_RSHIFT) == 0)		_ConfigData.toggleKeys[i-1] = VK_RSHIFT;

		else if (strcmp(ini_get(config, "toggle_sequence", key), KEYSTRING_LALT) == 0)		_ConfigData.toggleKeys[i-1] = VK_LMENU;
		else if (strcmp(ini_get(config, "toggle_sequence", key), KEYSTRING_RALT) == 0)		_ConfigData.toggleKeys[i-1] = VK_RMENU;

		else if (strcmp(ini_get(config, "toggle_sequence", key), KEYSTRING_LCTRL) == 0)		_ConfigData.toggleKeys[i-1] = VK_LCONTROL;
		else if (strcmp(ini_get(config, "toggle_sequence", key), KEYSTRING_RCTRL) == 0)		_ConfigData.toggleKeys[i-1] = VK_RCONTROL;

		else if (strcmp(ini_get(config, "toggle_sequence", key), KEYSTRING_TAB) == 0)		_ConfigData.toggleKeys[i-1] = VK_TAB;
		else if (strcmp(ini_get(config, "toggle_sequence", key), KEYSTRING_CAPSLOCK) == 0)	_ConfigData.toggleKeys[i-1] = VK_CAPITAL;
		else
		{
			memcpy(&_ConfigData.toggleKeys[i-1], ini_get(config, "toggle_sequence", key), sizeof(byte));
		}
	}

	ini_free(config);
}