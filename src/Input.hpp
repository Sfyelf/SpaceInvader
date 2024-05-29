#pragma once

#include "SDL.h"

class Input
{
private:
    Input();
    ~Input();
    static Input& Instance()
    {
        static Input _instance;
        return _instance;
    }

private:
    bool _keysPressState[SDL_NUM_SCANCODES];
    bool _keysDownState[SDL_NUM_SCANCODES];
    bool _keysUpState[SDL_NUM_SCANCODES];

    //v2f _mousePos;
    //bool _mouseDown;

    bool _isQuit;

public:
    static void Update();

    static bool GetKey(int key);
    static bool GetKeyDown(int key);
    static bool GetKeyUp(int key);

    //static v2f getMousePosition();
    //static bool getMouseButtonDown();

    static bool IsQuit();

private:
    void UpdateKeyInputEvent();
};
