#include <Windows.h>

int main() {
    // Get the device context of the entire screen
    HDC hdcScreen = GetDC(NULL);

    // Define the coordinates of the pixel you want to change
    int x = 100;  // Example x-coordinate
    int y = 100;  // Example y-coordinate

    // Set the pixel color to red (assuming 24-bit RGB color)
    SetPixel(hdcScreen, x, y, RGB(255, 0, 0));

    // Release the device context
    ReleaseDC(NULL, hdcScreen);

    return 0;
}
