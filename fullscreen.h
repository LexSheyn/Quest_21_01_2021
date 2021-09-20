#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <dshow.h>

#include "wtypes.h"
#include <iostream>

#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "quartz.lib")

#pragma warning(disable : 4996)

using namespace std;

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

int PlayVideo(const std::string& pFile)
{
    int horizontal;
    int vertical;

    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    horizontal = desktop.right;
    vertical = desktop.bottom;

    IGraphBuilder* pGraph = NULL;
    IVideoWindow* pWin = NULL;
    IMediaControl* pControl = NULL;
    IMediaEvent* pEvent = NULL;

    // Initialize the COM library.
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) return 1;

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr)) return 1;

    // Get interfaces
    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    hr = pGraph->QueryInterface(IID_IVideoWindow, (void**)&pWin);

    // Build the graph (convert unicode filename)
    size_t _size = mbstowcs(NULL, pFile.c_str(), 2); // Add 2 for ZT
    wchar_t* _wfile = new wchar_t[_size + 2];
    _size = mbstowcs(_wfile, pFile.c_str(), pFile.length() + 1); // Add 1 for ZT
    hr = pGraph->RenderFile(_wfile, NULL);
    delete[] _wfile;

    // Uncomment next line for borderless window display
    pWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);

    // For fullscreen play, get Windows screen parameters and replace
    //pWin->SetWindowPosition(0, 0, 1920, 1080);
    pWin->SetWindowPosition(0, 0, horizontal, vertical);

    if (SUCCEEDED(hr))
    {
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            long evCode;
            pEvent->WaitForCompletion(INFINITE, &evCode);
        }
    }

    pControl->Release();
    pEvent->Release();
    pWin->Release();
    pGraph->Release();
    CoUninitialize();

    return 0;
}

/*
int main()
{
    PlayVideo("D:\\dfs.avi"); // play any format Windows can handle, avi/mpg etc.
    return 0;
}
*/