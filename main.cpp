#include <iostream>
#include <windows.h>
#include <random>

using std::cout;
using std::endl;

// Function to create and initialize the overlay window
HWND initOverlayWindow() {
    WNDCLASSW wc = {};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"OverlayWindowClass";

    if (!RegisterClassW(&wc)) {
        std::cerr << "Failed to register window class\n";
        return nullptr;
    }

    HWND overlayWnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW,
        wc.lpszClassName,
        nullptr,
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        nullptr, nullptr, wc.hInstance, nullptr);

    if (!overlayWnd) {
        std::cerr << "Failed to create overlay window\n";
        return nullptr;
    }

    SetLayeredWindowAttributes(overlayWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(overlayWnd, SW_SHOW);
    UpdateWindow(overlayWnd);

    return overlayWnd;
}

// Function to clear the overlay window
void clearOverlayWindow(HWND overlayWnd) {
    if (!overlayWnd)
        return;

    HDC hdc = GetDC(overlayWnd);
    RECT rect;
    GetClientRect(overlayWnd, &rect);

    // Fill the entire client area with a transparent color to clear the screen
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

    ReleaseDC(overlayWnd, hdc);
}

// Function to draw a single colored rectangle on the overlay window
void drawRectangle(HWND overlayWnd) {
    if (!overlayWnd)
        return;

    clearOverlayWindow(overlayWnd);            

    HDC hdc = GetDC(overlayWnd);

    int startX = rand() % (GetSystemMetrics(SM_CXSCREEN) - 50);
    int startY = rand() % (GetSystemMetrics(SM_CYSCREEN) - 50);
    int width = 25 + rand() % 200;
    int height = 25 + rand() % 200;

    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    COLORREF color = RGB(r, g, b);

    // Create a solid brush with the specified color
    HBRUSH hBrush = CreateSolidBrush(color);

    // Select the brush into the device context and draw the rectangle
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    Rectangle(hdc, startX, startY, startX + width, startY + height);

    // Clean up: restore the original brush and delete the created brush
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);

    ReleaseDC(overlayWnd, hdc);
}

// LPCWSTR imagePath = L"skul.png";
// // Function to display an image on the overlay window
// void displayImage(HWND overlayWnd) {
//     if (!overlayWnd)
//         return;

//     clearOverlayWindow(overlayWnd);

//     HDC hdc = GetDC(overlayWnd);

//     // Load the image from file
//     HBITMAP hBitmap = (HBITMAP)LoadImageW(nullptr, imagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//     if (!hBitmap) {
//         std::cerr << "Failed to load image: " << GetLastError() << std::endl;
//         ReleaseDC(overlayWnd, hdc);
//         return;
//     }
// }    

// Function to perform the prank for a specified duration (in milliseconds)
void performPrankForDuration(HWND overlayWnd, int durationMillis) {
    DWORD startTime = GetTickCount();

    while (true) {
        DWORD currentTime = GetTickCount();
        DWORD elapsedTime = currentTime - startTime;

        if (elapsedTime >= durationMillis)
            break;

        drawRectangle(overlayWnd);
        //displayImage(overlayWnd);
        Sleep(50);
    }
}


int main() {
    HWND overlayWnd = initOverlayWindow();
    if (!overlayWnd) {
        return 1;
    }

    int nbRep = 5;
    while (nbRep > 0) {
        if (nbRep==0) break;
        cout << "TIMES: " << nbRep <<endl;
        performPrankForDuration(overlayWnd, 10000 / 3); // Perform prank for 5 seconds
        clearOverlayWindow(overlayWnd);
        Sleep(2000); // Wait for 2 seconds before the next prank repetition
        nbRep--;
    }

    // Cleanup: Release resources
    clearOverlayWindow(overlayWnd);
    DestroyWindow(overlayWnd); // Destroy the overlay window

    return 0;
}