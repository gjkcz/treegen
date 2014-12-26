#include <windows.h>
#include <dinput.h>
#include "guicon.h"

HRESULT InitInputDevice(HWND hInstance);
HRESULT ReadInputState( long* axs, byte* cKeys );
