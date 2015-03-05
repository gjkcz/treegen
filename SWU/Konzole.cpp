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
    pocetSloupcu = 60;
//    sablony["ok"] = Sablona(bmodra, "ok");
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

const string& Konzole::zjistiNazevKonzole()
{
    char * str = new char[100];
    LPTSTR pStr = str;
    GetConsoleTitle(str, 100);
    string* nazev = new string(str);
    delete[] str;
    return nazev[0];
}

void Konzole::nastavDoPopredi()
{
//    this->nazevKonzole = zjistiNazevKonzole();
//    std::cout << "\nNazev: "<< nazevKonzole << std::endl;
//    HWND hWnd = ::FindWindow(NULL, nazevKonzole.c_str());
    HWND hWnd = GetConsoleWindow();
    if (hWnd) {
        // move to foreground
        SetForegroundWindow(hWnd);
    }
}

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
//    nastavBarvuPisma(sablony[klic].barva);
    vytiskniXEnteru(3);
//    cout << sablony[klic].text << "\n";
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

void Konzole::vytiskniXMezer(int x)
{
    for (int i=0; i<x; ++i)
        cout << " ";
}


void Konzole::vytiskniIndicie(const int* paIndicie, int pocet)
{
    if(paIndicie!=nullptr) {
        zjistiSoucasnouBarvu();
        nastavBarvuPisma(Barva::fjasnezluta);
        std::cout << "\nIndicie: \n";
        nastavBarvuPisma(Barva::bbilafcerna);
        if(pocet%2 != 0) {
            std::cout << "Indicii neni sudy pocet!" << std::endl;
        }
        for (int o = 1; o >= 0; --o) {
            for (int i = o; i < pocet; i+=2) {
                std::cout << "[" << paIndicie[i];
                int pocetCiferS, pocetCiferL, rozdil;
                pocetCiferS = helper::pocetCifer(paIndicie[i]);
                pocetCiferL = helper::pocetCifer(paIndicie[(o==0)?i+1:i-1]);
                rozdil = pocetCiferL-pocetCiferS;
                if(rozdil > 0)
                    vytiskniXMezer(rozdil);
                std::cout << "]";
            }
//        if(o==0)
            std::cout << "\n";
        }
        nastavBarvuPisma(soucasnaBarva);
    }
}

void Konzole::vytiskniIndicie(const int* paIndicie, int pocet, int indiciiNaClanek)
{
    if(paIndicie!=nullptr) {
        zjistiSoucasnouBarvu();
        nastavBarvuPisma(Barva::fjasnezluta);
        std::cout << "\nIndicie po "<<indiciiNaClanek<<": \n";
        nastavBarvuPisma(Barva::bbilafcerna);
        if(pocet%2 != 0) {
            std::cout << "Indicii neni sudy pocet!" << std::endl;
        }
        if(pocet%indiciiNaClanek != 0) {
            std::cout << "Chybny pocet indicii na clanek, pocitas s koncovym spojem(+2 indexy)?" << std::endl;
            nastavBarvuPisma(soucasnaBarva);
            vytiskniIndicie(paIndicie, pocet);
            nastavBarvuPisma(Barva::fjasnezluta);
            std::cout << "Indicie po clankach:" << std::endl;
            nastavBarvuPisma(Barva::bbilafcerna);
        }
        int pocetCasti = pocet/indiciiNaClanek;
//        if( pocetCasti == 1 ) indiciiNaClanek *= 2;
//    pocetCasti = 2;
        if(indiciiNaClanek>pocetSloupcu){
            pocetCasti = pocet/pocetSloupcu;
            indiciiNaClanek = pocetSloupcu;
        }
        for ( int p = 0; p < pocetCasti; ++p) {
            for (int o = 1; o >= 0; --o) {
                nastavBarvuPisma(Barva::fjasnezluta);
                for (int i = o+p*(indiciiNaClanek); i < indiciiNaClanek+p*(indiciiNaClanek); i+=2) {
                    std::cout << "[" << paIndicie[i];
                    int pocetCiferS, pocetCiferL, rozdil;
                    pocetCiferS = helper::pocetCifer(paIndicie[i]);
                    pocetCiferL = helper::pocetCifer(paIndicie[(o==0)?i+1:i-1]);
                    rozdil = pocetCiferL-pocetCiferS;
                    if(rozdil > 0)
                        vytiskniXMezer(rozdil);
                    std::cout << "]";
                    nastavBarvuPisma(Barva::bbilafcerna);
//            if(o==1 && i%7==0)
//            std::cout << "\n\n";
//            else if(o==0 && i%6==0 && i!=0)
//            std::cout << "\n\n";
                }
                std::cout << "\n";
                if(o==0)
                    std::cout << "\n";
            }

        }

        nastavBarvuPisma(soucasnaBarva);
    }
}


}
