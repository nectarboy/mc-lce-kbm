#include "stdafx.h"
#include "PCInput.h"
#include <windows.h>
#include <windef.h>

void PCInput::Initialise() {
    for (int i = 0; i < 256; i++) {
        keys[i] = UpState;
    }
	for (int i = 0; i < 2; i++) {
		mouseButtons[i] = UpState;
	}
    mouseSensitivity = 1;

	mouseX = 0.0;
	mouseY = 0.0;
	mouseOldX = 0.0;
	mouseOldY = 0.0;	
	wheel = 0.0;
	wheelDelta = 0.0;
	coarseWheelDelta = 0;
	mouseLocked = false;
	menuDisplayed = false;
}

void PCInput::SetCursorLock(int iPad, bool lock) {
	if (iPad != 0) return;

	if (lock && !mouseLocked) {
		mouseLocked = true;
		ShowCursor(false);
	}
	else if (!lock && mouseLocked) {
		mouseLocked = false;
		ShowCursor(true);
	}
}

void PCInput::SetMenuDisplayed(int iPad, bool bVal) {
	if (iPad != 0) return;
	menuDisplayed = bVal;
}


bool PCInput::GetMenuDisplayed(int iPad) {
	if (iPad != 0) return false;
	return menuDisplayed;
}

bool PCInput::KeyPressed(int iPad, int key) {
	if (iPad != 0) return false;
	if (key < 0) return false;
    return keys[key] == PressedState;
}

bool PCInput::KeyReleased(int iPad, int key) {
	if (iPad != 0) return false;
	if (key < 0) return false;
    return keys[key] == ReleasedState;
}

bool PCInput::KeyDown(int iPad, int key) {
	if (iPad != 0) return false;
	if (key < 0) return false;
    return keys[key] >= DownState;
}

void PCInput::SetKeyState(int iPad, unsigned int key, PressState state) {
	if (iPad != 0) return;
    keys[key] = state;
}

// Emulates controller buttons
unsigned char PCInput::GetEmulatedControllerKey(int iPad, int key) {
	if (iPad != 0) return UpState;

	switch (key) {
	case ACTION_MENU_A: return keys[VK_RETURN];
	case ACTION_MENU_B: return keys[VK_BACK];
	case ACTION_MENU_X: return keys['E'];
	case ACTION_MENU_Y: return keys['R'];
	case ACTION_MENU_UP: return keys['W'];
	case ACTION_MENU_DOWN: return keys['S'];
	case ACTION_MENU_RIGHT: return keys['D'];
	case ACTION_MENU_LEFT: return keys['A'];
	//ACTION_MENU_PAGEUP,
	//ACTION_MENU_PAGEDOWN,
	//ACTION_MENU_RIGHT_SCROLL,
	//ACTION_MENU_LEFT_SCROLL,
	//ACTION_MENU_STICK_PRESS,
	//ACTION_MENU_OTHER_STICK_PRESS,
	//ACTION_MENU_OTHER_STICK_UP,
	//ACTION_MENU_OTHER_STICK_DOWN,
	//ACTION_MENU_OTHER_STICK_LEFT,
	//ACTION_MENU_OTHER_STICK_RIGHT,
	case ACTION_MENU_PAUSEMENU: return keys[VK_ESCAPE];
	case ACTION_MENU_OK: return keys[VK_RETURN];
	case ACTION_MENU_CANCEL: return keys[VK_BACK];

	//MINECRAFT_ACTION_JUMP,
	//MINECRAFT_ACTION_FORWARD,
	//MINECRAFT_ACTION_BACKWARD,
	//MINECRAFT_ACTION_LEFT,
	//MINECRAFT_ACTION_RIGHT,
	//MINECRAFT_ACTION_LOOK_LEFT,
	//MINECRAFT_ACTION_LOOK_RIGHT,
	//MINECRAFT_ACTION_LOOK_UP,
	//MINECRAFT_ACTION_LOOK_DOWN,
	case MINECRAFT_ACTION_USE: return mouseButtons[1];
	case MINECRAFT_ACTION_ACTION: return mouseButtons[0];
	//MINECRAFT_ACTION_LEFT_SCROLL,
	//MINECRAFT_ACTION_RIGHT_SCROLL,
	case MINECRAFT_ACTION_INVENTORY: return keys['E'];
	case MINECRAFT_ACTION_PAUSEMENU: return keys[VK_ESCAPE];
	case MINECRAFT_ACTION_DROP: return keys['Q'];
	case MINECRAFT_ACTION_SNEAK_TOGGLE: return keys['J'];
	case MINECRAFT_ACTION_CRAFTING: return keys['R'];
	case MINECRAFT_ACTION_RENDER_THIRD_PERSON: return keys[VK_F5];
	//MINECRAFT_ACTION_GAME_INFO
	//case MINECRAFT_ACTION_DPAD_LEFT: return keys[VK_LEFT];
	//case MINECRAFT_ACTION_DPAD_RIGHT: return keys[VK_RIGHT];
	//case MINECRAFT_ACTION_DPAD_UP: return keys[VK_UP];
	//case MINECRAFT_ACTION_DPAD_DOWN: return keys[VK_DOWN];

	default:
		return UpState;
	}
}

bool PCInput::ButtonPressed(int iPad, int key) {
    return GetEmulatedControllerKey(iPad, key) == PressedState;
}

bool PCInput::ButtonReleased(int iPad, int key) {
    return GetEmulatedControllerKey(iPad, key) == ReleasedState;
}

bool PCInput::ButtonDown(int iPad, int key) {
    return GetEmulatedControllerKey(iPad, key) >= DownState;
}

// Mouse
bool PCInput::MousePressed(int iPad, int mouse) {
	if (iPad != 0) return false;
	return mouseButtons[mouse] == PressedState;
}

bool PCInput::MouseReleased(int iPad, int mouse) {
	if (iPad != 0) return false;
	return mouseButtons[mouse] == ReleasedState;
}

bool PCInput::MouseDown(int iPad, int mouse) {
	if (iPad != 0) return false;
	return mouseButtons[mouse] >= DownState;
}

void PCInput::SetMouseState(int iPad, int mouse, PressState state) {
	if (iPad != 0) return;
	mouseButtons[mouse] = state;
}

void PCInput::SetMouseSensitivity(int iPad, float sensitivity) {
	if (iPad != 0) return;
    mouseSensitivity = sensitivity;
}

float PCInput::GetMouseDeltaX(int iPad) {
	if (iPad != 0) return 0;
	return mouseDeltaX;
}

float PCInput::GetMouseDeltaY(int iPad) {
	if (iPad != 0) return 0;
	return mouseDeltaY;
}

void PCInput::SetMouseCoords(int iPad, unsigned int x, unsigned int y) {
	if (iPad != 0) return;
	mouseX = (float)x;
	mouseY = (float)y;
}

void PCInput::AddMouseDelta(int iPad, LONG x, LONG y) {
	if (iPad != 0) return;
	static const double scale = 1;
	mouseDeltaX += (double)x * scale;
	mouseDeltaY += (double)y * scale;
}

void PCInput::AddWheelDelta(int iPad, float delta) {
	if (iPad != 0) return;
	wheelDelta += delta;
	wheel += delta;
	coarseWheelDelta = (int)wheel;
}

float PCInput::GetWheelDelta(int iPad) {
	if (iPad != 0) return 0;
	return wheelDelta;
}

int PCInput::GetCoarseWheelDelta(int iPad) {
	if (iPad != 0) return 0;
	return coarseWheelDelta;
}

float PCInput::GetJoypadStick_LX(int iPad, bool bCheckMenuDisplay) {
	if (iPad != 0) return false;
	if (bCheckMenuDisplay && menuDisplayed) return false;
	return (float)KeyDown(iPad, 'D') - (float)KeyDown(iPad, 'A');
}

float PCInput::GetJoypadStick_LY(int iPad, bool bCheckMenuDisplay) {
	if (iPad != 0) return false;
	if (bCheckMenuDisplay && menuDisplayed) return false;
	return (float)KeyDown(iPad, 'W') - (float)KeyDown(iPad, 'S');
}

float PCInput::GetJoypadStick_RX(int iPad, bool bCheckMenuDisplay) {
	if (iPad != 0) return false;
	if (bCheckMenuDisplay && menuDisplayed) return false;
	return GetMouseDeltaX(iPad) * mouseSensitivity;
}

float PCInput::GetJoypadStick_RY(int iPad, bool bCheckMenuDisplay) {
	if (iPad != 0) return false;
	if (bCheckMenuDisplay && menuDisplayed) return false;
	return GetMouseDeltaY(iPad) * mouseSensitivity;
}

void PCInput::Tick() {
    for (int i = 0; i < 256; i++) {
        if (keys[i] == PressedState) {
            keys[i] = DownState;
        }
        else if (keys[i] == ReleasedState) {
            keys[i] = UpState;
        }
    }

	for (int i = 0; i < 2; i++) {
        if (mouseButtons[i] == PressedState) {
            mouseButtons[i] = DownState;
        }
        else if (mouseButtons[i] == ReleasedState) {
            mouseButtons[i] = UpState;
        }
    }

	mouseOldX = mouseX;
	mouseOldY = mouseY;
	wheel = fmodf(wheel, 1.0f);
	wheelDelta = 0.0;
	coarseWheelDelta = 0;
	mouseDeltaX = 0.0;
	mouseDeltaY = 0.0;
}

void PCInput::UpdateWindow(HWND* hwnd) {
	if (mouseLocked) {
		RECT rect;
		GetClientRect(*hwnd, &rect);

		int cx = (rect.left + rect.right) / 2;
		int cy = (rect.top + rect.bottom) / 2;
		rect.left = cx;
		rect.right = cx + 1;
		rect.top = cy;
		rect.bottom = cy + 1;

		ClipCursor(&rect);
	}
	else {
		ClipCursor(NULL);
	}
}

PCInput PCInputManager;