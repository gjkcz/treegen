#include "msgProc.h"

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case WM_DESTROY:
        //Cleanup();
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}
