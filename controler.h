#include <windows.h>
#include <dinput.h>

HRESULT InitInputDevice(HWND hInstance);
HRESULT ReadInputState( long* axs, byte* cKeys );
