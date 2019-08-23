/*
	- Reads config in ../murka.config
	- Default settings if config not found
*/
#pragma once


#include <windows.h>


// TODO: Add other keys like ; , . / " ' [ ]
#define KEYSTRING_TAB			"Tab"
#define KEYSTRING_CAPSLOCK		"Caps_Lock"

#define KEYSTRING_LSHIFT		"Left_Shift"
#define KEYSTRING_RSHIFT		"Right_Shift"

#define KEYSTRING_LCTRL			"Left_Ctrl"
#define KEYSTRING_RCTRL			"Right_Ctrl"

#define KEYSTRING_LALT			"Left_Alt"
#define KEYSTRING_RALT			"Right_Alt"


extern struct CONFIG_DATA
{
	byte mouseDeltaNormal;
	byte mouseDeltaFast;
	byte mouseDeltaSlow;

	byte keyMouseFast;
	byte keyMouseSlow;
	byte keyMouseNormal;

	byte keyMouseMoveRight;
	byte keyMouseMoveLeft;
	byte keyMouseMoveUp;
	byte keyMouseMoveDown;

	byte keyMouseClickLeft;
	byte keyMouseClickRight;

	byte* toggleKeys;
	byte  numberOfToggleKeys;
};

namespace Config
{

	/**
	* @fn	void Config::Load(CONFIG_DATA& _ConfigData, const char* configPath)
	*
	* @brief	Loads keybinds and stuff from a file to memory
	*
	* @date	8/23/2019
	*
	* @param [in,out]	_ConfigData	global struct containing configuration data.
	* @param [in]	  	configPath 	Full pathname of the configuration file.
	*/
	void Load(CONFIG_DATA &_ConfigData);
}