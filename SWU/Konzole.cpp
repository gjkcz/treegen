#include "Konzole.hpp"
namespace sk
{

//	HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  );
//
//    cout << "'moo";
//    cout << "'moo" << "\t\v";
//    std::cout.put('d');
//    std::cout << "\b\b\b";
//    std::cout << "\r";
//    long pos = cout.tellp();
//    cout << pos << endl;


using namespace std;

Konzole::Konzole() : soucasnaBarva(0xF)
{
    sablony["ok"] = Sablona(bmodra, "ok");
//    presmerujIODoKonzole();     // Presmeruj IO do nasi nove konzole
}

//void Konzole::presmerujIODoKonzole()
//{
//
//    int hConHandle;
//
//    long lStdHandle;
//
//    CONSOLE_SCREEN_BUFFER_INFO coninfo;
//
//    FILE *fp;
//
//// allocate a console for this app
//
//    AllocConsole();
//
//
//// set the screen buffer to be big enough to let us scroll text
//    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
//
//                               &coninfo);
//
//    coninfo.dwSize.Y = MAX_CONSOLE_LINES;
//
//    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
//
//                               coninfo.dwSize);
//
//// redirect unbuffered STDOUT to the console
//
//    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
//
//    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
//
//    fp = _fdopen( hConHandle, "w" );
//
//    *stdout = *fp;
//
//    setvbuf( stdout, NULL, _IONBF, 0 );
//// set the screen bounds
////    HWND console = GetConsoleWindow();
//    SMALL_RECT rectCon = {-4, 0, 50, 100};
//    SetConsoleWindowInfo( GetStdHandle(STD_OUTPUT_HANDLE),
//                          true,
//                          &rectCon );
//
//// redirect unbuffered STDIN to the console
//
//    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
//
//    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
//
//    fp = _fdopen( hConHandle, "r" );
//
//    *stdin = *fp;
//
//    setvbuf( stdin, NULL, _IONBF, 0 );
//
//// redirect unbuffered STDERR to the console
//
//    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
//
//    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
//
//    fp = _fdopen( hConHandle, "w" );
//
//    *stderr = *fp;
//
//    setvbuf( stderr, NULL, _IONBF, 0 );
//
//
//// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
//
//// point to console as well
//
//    ios::sync_with_stdio();
//
////    cout << status;
//
//}

void Konzole::nastavBarvuPisma(Barva eiBarva)
{
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

    SetConsoleTextAttribute( hstdout, eiBarva );
}
void Konzole::nastavBarvuPisma(WORD wBarva)
{
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hstdout, wBarva );
}

void Konzole::vytiskniSablonu(std::string klic)
{
    zjistiSoucasnouBarvu();
    nastavBarvuPisma(sablony[klic].barva);
    vytiskniXEnteru(3);
    cout << sablony[klic].text << "\n";
    nastavBarvuPisma(soucasnaBarva);
}

void Konzole::zjistiSoucasnouBarvu()
{
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO ptrCsbi;
    GetConsoleScreenBufferInfo(hstdout, &ptrCsbi);
    soucasnaBarva = ptrCsbi.wAttributes;
}

void Konzole::vytiskniXEnteru(int x)
{
    for (int i=0; i<x; ++i)
        cout << "\n";
}

}
