#include "msgProc.hpp"

namespace sw
{

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProcedure( HWND hWnd, UINT messages, WPARAM wParam, LPARAM lParam )
{
    switch( messages ) {
    case WM_DESTROY: {
        //Cleanup();
//        std::cout << "Okno zavirano" << std::endl;
        PostQuitMessage( 0 );               // post quit message
        return 0;
    }
    break;
    default:
        return DefWindowProc( hWnd, messages, wParam, lParam );
        break;
    }

}


}
