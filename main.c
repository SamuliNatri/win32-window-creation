#define WIN32_LEAN_AND_MEAN
#include <windows.h>

LRESULT CALLBACK 
WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch(Message) {
        case WM_KEYDOWN: {
            switch(WParam) { 
                case 'O': { 
                    DestroyWindow(Window); 
                } break; 
            }
        } break;
        case WM_DESTROY: { 
            PostQuitMessage(0); 
        } break;
        default: { 
            return DefWindowProc(Window, Message, WParam,  LParam); 
        }
    }
    return 0;
}

int WINAPI 
WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CmdLine, int CmdShow) {
    
    WNDCLASS WindowClass = {0};
    const char ClassName[] = "MyWindowClass";
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = ClassName;
    WindowClass.hCursor = LoadCursor(NULL, IDC_CROSS);
    
    if(!RegisterClass(&WindowClass)) {
        MessageBox(0, "RegisterClass failed", 0, 0);
        return GetLastError();
    }
    
    HWND Window = CreateWindowEx(0, ClassName, "Title",
                                 WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 0, 0, Instance, 0);
    
    if(!Window) {
        MessageBox(0, "CreateWindowEx failed", 0, 0);
        return GetLastError();
    }
    
    int Running = 1;
    
    while(Running) {
        MSG Message;
        while(PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
            if(Message.message == WM_QUIT) Running = 0;
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
    }
    
    return 0;
}
