#include "Input.hpp"

Input::Input():
    _keysPressState{false},
    _keysDownState{false},
    _keysUpState{false},
//    _mousePos(v2f::zero()),
//    _mouseDown(false),
    _isQuit(false)
{}

Input::~Input()
{}

void Input::Update()
{
    memset(Instance()._keysDownState, 0, SDL_NUM_SCANCODES);
    memset(Instance()._keysUpState, 0, SDL_NUM_SCANCODES);
//    Instance()._mouseDown = false;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            Instance()._isQuit = true;
        }

//        if (event.type == SDL_MOUSEMOTION)
//        {
//            int x, y;
//            SDL_GetMouseState(&x, &y);
//
//            Instance()._mousePos = v2f(x, y);
//        }

//        if (event.type == SDL_MOUSEBUTTONDOWN)
//        {
//            Instance()._mouseDown = true;
//        }

        if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN)
        {
            Instance().UpdateKeyInputEvent();
        }
    }
}

bool Input::GetKey(int key)
{
    return Instance()._keysPressState[key];
}
bool Input::GetKeyDown(int key)
{
    return Instance()._keysDownState[key];
}
bool Input::GetKeyUp(int key)
{
    return Instance()._keysUpState[key];
}
//v2f Input::getMousePosition()
//{
//    return Instance()._mousePos;
//}
//bool Input::getMouseButtonDown()
//{
//    return Instance()._mouseDown;
//}
bool Input::IsQuit()
{
    return Instance()._isQuit;
}

void Input::UpdateKeyInputEvent()
{
    const uint8_t* _currentKeyState = SDL_GetKeyboardState(NULL);

    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        if (!_keysPressState[i] && _currentKeyState[i])
        {
            _keysDownState[i] = 1;
        }
        if (_keysPressState[i] && !_currentKeyState[i])
        {
            _keysUpState[i] = 1;
        }

        _keysPressState[i] = _currentKeyState[i];
    }
}
