#include <windows.h>
#include <dinput.h>

HRESULT InitInputDevice(HWND hInstance);
byte* ReadInputState(long* axs);
