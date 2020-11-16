// dllmain.cpp : Define o ponto de entrada para o aplicativo DLL.
#include "pch.h"
#include "framework.h"
#include "Dll1.h"

#pragma data_seg(".SData") 
HHOOK hMsgHook = NULL; // Handle of  our hook
HINSTANCE hInstHookDll = NULL; // The instance of the DLL
HWND hHandle = NULL; // C# window handle
UINT customMsg = RegisterWindowMessage(L"CustomMessage"); // Custom message
#pragma data_seg()

#pragma comment(linker,"/SECTION:.SData,RWS") //Directive to the linker to create a shared section with RWS attributes

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hInstHookDll = (HINSTANCE)hModule;		//we initialize our variable with the value that is passed to us
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

LRESULT CALLBACK procCharMsg(int code, WPARAM wParam, LPARAM lParam)		// this is the hook procedure
{
    MSG* msg;																// a pointer to hold the MSG structure that is passed as lParam
    if (code >= 0)									                        // if nCode is less than 0 call CallNextHookEx
    {
        msg = (MSG*)lParam;													// lParam contains pointer to MSG structure.
        if (msg->message == WM_CHAR)										// we handle only WM_CHAR messages
        {
            PostMessage(hHandle, customMsg, msg->wParam, msg->lParam);
        }
    }
    return CallNextHookEx(hMsgHook, code, wParam, lParam);				    // passing this message to target application
}

extern "C"
{
    //set the hook
    DLL1_API int __stdcall SetHook(HWND appHandle)
    {
        hHandle = appHandle;
        if (hMsgHook == NULL)
            hMsgHook = ::SetWindowsHookEx(WH_GETMESSAGE, procCharMsg, hInstHookDll, 0);
        if (hMsgHook == NULL)
            return -1;
        return 0;
    }

    //remove the hook
    DLL1_API int __stdcall RemoveHook()
    {
        if (hMsgHook != NULL)
            UnhookWindowsHookEx(hMsgHook);
        hMsgHook = NULL;
        return 0;
    }
}

