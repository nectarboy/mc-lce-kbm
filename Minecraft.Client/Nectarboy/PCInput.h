#pragma once

class PCInput
{
public:
    enum PressState : unsigned char {
        UpState = 0x1,
        ReleasedState = 0x2,
        DownState = 0x4,
        PressedState = 0x8
    };

    void                Initialise();
    void                SetMouseSensitivity(int iPad, float sensitivity);
    void                SetKeyState(int iPad, unsigned int key, PressState state);
	void				SetMouseState(int iPad, int mouse, PressState state);
	void				SetMouseCoords(int iPad, unsigned int x, unsigned int y);
	void				AddMouseDelta(int iPad, LONG x, LONG y);
	void				AddWheelDelta(int iPad, float delta);
	void				SetCursorLock(int iPad, bool lock);
	void				SetMenuDisplayed(int iPad, bool bVal);
	bool				GetMenuDisplayed(int iPad); // why didnt they include this man

    bool                KeyPressed(int iPad, int key);
    bool                KeyReleased(int iPad, int key);
    bool                KeyDown(int iPad, int key);

	bool                ButtonPressed(int iPad, int key);
    bool                ButtonReleased(int iPad,  int key);
    bool                ButtonDown(int iPad, int key);

    bool                MousePressed(int iPad, int mouse);
    bool                MouseReleased(int iPad, int mouse);
    bool                MouseDown(int iPad, int mouse);

	float				GetMouseDeltaX(int iPad);
	float				GetMouseDeltaY(int iPad);
	float				GetWheelDelta(int iPad);
	int					GetCoarseWheelDelta(int iPad);

    float               GetJoypadStick_LX(int iPad, bool bCheckMenuDisplay=true);
    float               GetJoypadStick_LY(int iPad, bool bCheckMenuDisplay=true);
    float               GetJoypadStick_RX(int iPad, bool bCheckMenuDisplay=true);
    float               GetJoypadStick_RY(int iPad, bool bCheckMenuDisplay=true);

    void                Tick();
	void                UpdateWindow(HWND* hwnd);


private:

	unsigned char		GetEmulatedControllerKey(int iPad, int key);

    float mouseX;
    float mouseY;
    float mouseOldX;
	float mouseOldY;
	float mouseDeltaX;
	float mouseDeltaY;

    float wheel;
	float wheelDelta;
	int coarseWheelDelta;

	bool mouseLocked;
	bool menuDisplayed;

    unsigned char keys[256];
	unsigned char mouseButtons[2];
    float mouseSensitivity;
};

// Singleton
extern PCInput PCInputManager;