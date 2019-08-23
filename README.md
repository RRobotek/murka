# murka
A mouseless solution which let's you control your mouse from your keyboard.

# directories
../murka
../murka/murka.exe
../murka/config/config.ini

#example of config.ini

[mouse_movement]
## only capital letters here
right_key 	= "L" # to move the cursor right
left_key 	= "H" # to move the cursor left
up_key 		= "K" # to move the cursor up
down_key 	= "J" # to move the cursor down

[mouse_click]
## only capital letters here
left_key 	= "U" # left mouse click
right_key 	= "I" # right mouse click

[mouse_speed]
## only letters here
fast_key 	= "F" # key to switch the cursor speed to fast
normal_key 	= "D" # key to switch the cursor speed to normal/default
slow_key 	= "S" # key to switch the cursor speed to slow

## only numbers < 255 here
fast_delta 	= 32 # actual speed of the cursor in fast mode in px/click
normal_delta 	= 8  # normal speed of the cursor in normal/default mode in px/click
slow_delta 	= 3  # slowspeed of the cursor in slow mode in px/click

[toggle_sequence]

number_of_keys 	= 3 # amount of letters you want to press in a sequence to activate mouse mode

## Either captital numbers or # "Right_Shift"/"Left_Shift"/"Tab"/
## "Caps_Lock"/"Left_Ctrl"/"Right_Ctrl"/
## "Left_Alt"/"Right_Alt"

key1 		= "Left_Shift"
key2 		= "M"
key3 		= "D"
## could go on like
## key4
## key5
## ..
## key9
## max number of keys in a sequence is 9

