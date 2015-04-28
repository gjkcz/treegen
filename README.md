# Treegen - generátor modelů stromů

Cílem mé práce bylo vytvořit software - generátor realistikckých modelů stromů

- **Ukázka:** Úplně dole ↓ 
- **Download:** [release](https://bitbucket.org/xmegapopcornz/treegen/src/9f29d8bd35ff0f40b4e47a9e57d8ed7258c17904/bin/?at=master)
- **Dokumentace:** [uživatelská i programátorská dokumentace](https://bytebucket.org/xmegapopcornz/treegen/raw/b14edb64b1c4ed8d0ebf9be15981715ce925bf8c/dok.pdf)
- **Repozitář:** [xmegapopcornz/Treegen](https://bitbucket.org/xmegapopcornz/treegen) + [fork](http://github.com/gjkcz/Treegen) v archivu maturitních prací
- **Autor:** jiroberf@seznam.cz
- **Maturitní práce 2014/15** na [GJK](https://github.com/gjkcz/gjkcz)

## Dokumentace pro uživatele


### Spuštění
* Spuštění provedete následujícími příkazy pro git:
	+ git init
	+ git remote add r https://xmegapopcornz@bitbucket.org/xmegapopcornz/treegen.git
	+ git pull r master
	+ Spustitelný soubor je v podadresáři \bin, pokud máte nainstalované DírectX půjde spustit.    

* Nemáte-li DirectX, program vypíše chybu jako "V počítači chybí knihovna d3dx9_43"  V tomto případě si stáhněte chybějící knihovny z branche knihovnyDx9 a vložte je k binárnímu souboru.  

	+ Knihovny stáhnete pomocí následujících příkazů pro git:
		- V adresáři projektu spusťte příkazovou řádku/powershell
		- git init
		- git remote add r https://xmegapopcornz@bitbucket.org/xmegapopcornz/treegen.git
		- git fetch r
		- git checkout knihovnyDx9

### Ovládáni: ###

* w, s, a, d - dopredu, dozadu, doleva, doprava
* q, e - nahoru, dolu
* ↑, ↓, ←, → - pohled nahoru, dolu, vlevo, vpravo
* myš - směr kamery
* levé tlačítko myši - přidá strom, náhodně vygenerovaný v reálném čase
* příkazy:
	- Pro zadání příkazu stiskněte mezerník+příkaz[+mezera+argument]+enter. Argument je celé číslo.   Není-li specifikován příkaz, program předpokládá nastavení rychlosti.
	- "testy" - spustí testy programu, které otestují všechny možné příkazy
	- "jeden" - vymaže geometrii scény a vygeneruje jeden strom.
	- "rychl" - nastaví rychlost pohybu kamery, výchozí rychlost je 5000
	- "odebe" - odebere posledně přidaný strom
	- "gener" / "pride" - přidá zadaný počet stromů, je-li menší než 200
	- "eleme" + 0(bod), 1(primka), 2(plocha) - tam, kde je to možné, změní vykreslovaný element na zvolený element
	- "backc" - prohodí barvu pozadí mezi černou/bílou
	- "vymaz" - vymaže všechnu geometrii na scéně
	- "regen" - znovu vygeneruje počáteční scénu
	- "reset" - obnoví počáteční podmínky programu
	- "fovde" + číslo z <2, 50) - změní horizontální zorný úhel, číslo je jmenovatelem pro úhel v radiánech(PI/x)
	- "citli" + číslo z <0, 10> - změní citlivost myši
	- "wiref" - prohodí render state mezi solid/wireframe
	- "osvet" - vypne/zapne osvětlování
	- "nerot" - zastaví rotaci všech modelů
	- "zhasn" - zhasne baterku(světlo ve směru hledí)
	- "rozzn" - rozžne baterku
	- "shadi" - prohodí způsob stínování Goraud/flat
	- "culli" - vypne/zapne culling(technika, kdy se nevykreslují skryté trojuhelníky)

## Dokumentace pro programátory
[programátorská dokumentace](https://bytebucket.org/xmegapopcornz/treegen/raw/b14edb64b1c4ed8d0ebf9be15981715ce925bf8c/dok.pdf)

### Kompilace 

**Budete potřebovat:**

* [TDM GCC 4.9 (64x)](http://tdm-gcc.tdragon.net/download)
* [Boost 1.57.0](http://www.boost.org/users/history/version_1_57_0.html)
* [Git](http://git-scm.com/download/win)
* [knihovny DirectX9]()

**Příkazy pro git:**

* git init
* git remote add r0 https://xmegapopcornz@bitbucket.org/xmegapopcornz/treegen.git
* git pull r0 master


**Úprava kompiluj.bat**

* V souboru kompiluj.bat v adresáři projektu změňte hodnotu proměnné CESTA_KOMPILATORU na složku s instalací TDM GCC

* Nyní je vše připraveno. 
    + spusťte soubor kompiluj.bat
    + spusťte bin/mingwTreegen.exe

### Instalace prostředí: ###

**Budete potřebovat:**

* [Codeblocks](http://sourceforge.net/projects/codeblocks/files/Binaries/13.12/Windows/codeblocks-13.12-setup.exe/download)
* [TDM GCC 4.9 (64x)](http://tdm-gcc.tdragon.net/download)
* [Boost 1.57.0](http://www.boost.org/users/history/version_1_57_0.html)
* [Git](http://git-scm.com/download/win)

**Příkazy pro git:**

* git init
* git remote add r0 https://xmegapopcornz@bitbucket.org/xmegapopcornz/treegen.git
* git fetch r0
* git checkout kmen

**Další kroky:**

* V Codeblocks nastavte nový kompilátor:

    + Settings -> Compiler -> v selected compiler vyberte položku GNU GCC Compiler -> Copy -> zadat název nového kompilátoru, např.: "Twilight Dragon Media compiler"
    + přejděte na záložku Toolchain executables
    + Compiler´s installation directory nastavte na adresář kompilátoru obsahující podsložku "bin"
    + C++ compiler nastavte na: "x86_64-w64-mingw32-g++.exe"
    + Linker pro dyn. knihovny na totéž   
   
* Nastavte projektu Build options:

    + Project -> Build options
    + Vlevo vyberte target "tdmDebug"
    + Vyberte nově přidaný kompilátor "Twilight Dragon Media compiler"
    + V záložce "Compiler settings" -> "other options" -> přidejte "-g -std=gnu++1y"
    + V záložce "Linker settings" by již mělo být "d3d9, d3dx9_43, dinput8, dxguid"
    + V záložce "Search directories" -> "compiler" -> add -> najděte cestu kořenového adresáře boostu, pozor cesta nesmí končit lomítkem!   
   
* Výsledný Build log by měl vypadat nějak takto:    

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.c}
-------------- Build: tdmDebug in mingwTreegen (compiler: Twilight Dragon Media compiler)---------------

x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Engine.cpp" -o .objs\Engine.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Helper.cpp" -o .objs\Helper.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Input.cpp" -o .objs\Input.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Kamera.cpp" -o .objs\Kamera.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Kontroler3d.cpp" -o .objs\Kontroler3d.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\main.cpp" -o .objs\main.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\msgProc.cpp" -o .objs\msgProc.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\SWU\Konzole.cpp" -o .objs\SWU\Konzole.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\SWU\Okno.cpp" -o .objs\SWU\Okno.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Tree.cpp" -o .objs\Tree.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Tree3.cpp" -o .objs\Tree3.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Tvar.cpp" -o .objs\Tvar.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\Treegen\Usecka.cpp" -o .objs\Usecka.o
x86_64-w64-mingw32-g++.exe  -o mingwTreegen.exe .objs\Engine.o .objs\Helper.o .objs\Input.o .objs\Kamera.o .objs\Kontroler3d.o .objs\main.o .objs\msgProc.o .objs\SWU\Konzole.o .objs\SWU\Okno.o .objs\Tree.o .objs\Tree3.o .objs\Tvar.o .objs\Usecka.o  -static  -ld3d9 -ld3dx9_43 -ldinput8 -ldxguid
Output file is mingwTreegen.exe with size 4.33 MB
Process terminated with status 0 (0 minute(s), 17 second(s))
0 error(s), 0 warning(s) (0 minute(s), 17 second(s))
 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Struktura kódu

### vstupní bod programu: main ###

1. Inicializace statických proměnných pocetInstanciStromu třídy

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.c .numberLines}
#include <windows.h>
#include "Engine.hpp"
#include "globals.hpp"

int t::Tree::pocetInstanciStromu = 0;   // inicializace staticke promenne tridy Tree, slouzi k uchovani poctu strukturovych stromu. Inicializace statickych promennych je nutne provest vzdy mimo tridu.
int t3::Tree3::pocetInstanciStromu = 0;     // inicializace staticke promenne tridy Tree3, slouzi k uchovani poctu 3D stromu
int se::Svetlo::pocetInstanciSvetla = 0;       // inicializace staticke promenne tridy Svetlo, slouzi k uchovani poctu svetel sceny

int main (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    sk::Konzole iKonzole;       // inicializace  instance tridy Konzole, ktera se stara o okno konzole, vstup a vystup konzole
    sw::Pozice iPozice {0, 0};      // inicializace objektu Pozice, ktery nese informace o pozici okna
    sw::Rozmery iRozmery {windowWidth, windowHeight};
    sw::Okno iOkno(iPozice, "Tree", hThisInstance);    // inicializace objektu tridy Okno, ktery ma za ukol starat se o okno Win programu, jeho presouvani do popredi a zpravy z systemu
    se::Engine iEngine(&iOkno);         // inicializace objektu tridy Engine, jehoz funkce potrebuji(zejmena kvuli DX) pristup k informacim o oknu
    iEngine.dejKonzoli(iKonzole);           // predani reference na iKonzoli objektu iEngine, aby mohl pouzivat jeji funkce
    iEngine.priprav();    // Pripravi rozhrani DirectX, vyhradi pristup ke graficke karte, nastavi BackBuffer, Depth stencil, svetla, Render state, vytvori geometrii stromu
    iOkno.ukaz();       // ukaze okno
    while ( iOkno.jeOtevrene() ) {              // smycka programu
        iEngine.prectiVstupAUpravKameru();      // zavola metodu Kontroleru3d iKontroler3d.prectiVstupAUpravKameru(arg), ktera aktualizuje matice View podle uzivatelskeho vstupu
        if(!iOkno.postarejSeOZpravy()){                     // Zmacknul-li uzivatel krizek, ukonci program.
            iEngine.releaseD3d();               // uvolni pamet alokovanou v prubehu programu, uvolni pristup ke GP, klavesnici a mysi
            break;
        }
        else if(iEngine.prikaz == "odejdi" ){               // , v pripade zpravy odejdi ukonci program (prave tlacitko mysi, nebo prikaz)
            break;
        }
        iEngine.render3d();                     // vykresli scenu, neboli prohodi back a front buffer, predchozi obsah backbuffru je smazan
    }
    return 0;
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



## (Changelog)
oblémů:
	+ fractal stromu
 	+ základy DX
 	+ promýšlení indexování vertexů
 	+ zkoumání shaderů
 	+ přemýšlení nad využitím možností jazyka c++11

**27.10.2014>>**

* Hledání a čtení existujících prací:
	+ [Creation and Rendering of Realistic Trees (Jason Weber, Joseph Penn)](http://www.cs.duke.edu/courses/fall02/cps124/resources/p119-weber.pdf)

**10.11.2014>>**

* Instalace codeblocks
* Řešení problémů s knihovnami DX
* Instalace GitBash na ntb

**18.11.2014>>**

* Přidání konzole k GUI
![screenshot.jpg](https://bitbucket.org/repo/xG7A9k/images/3861489895-screenshot.jpg)

**25.11.2014>>**

* Přidání ovládání kamery myší + volný pohyb ve směrech hledícího vektoru.

**8.12.2014>>**

* Jetbrains CLion IDE

**5.1.2015>>**

* Řešení problému s CodeBlocks a VC++2013

* Úprava struktury programu

**12.1.2015>>**

* Sem se zaseknul. Nejde mi rozchodit kompilátor VC++, který potřebuju kvůli podpoře knihoven DirectX. Kód se normálně zkompiluje, ale po chvíli se zaseknou Codeblocks. Vůbec nevim proč. Clion IDE nepodporuje VC++ zatim.

**19.1.2015>>**

* Předělal jsem to tak, že to funguje s mingw.

**26.1.2015>>**

* Vyřešil jsem problém s Code:blocks a nainstaloval nová TDM, takže můžu psát podle standardu c++14 a mít Code:blocks a používat DirectX. Taky jsem vylepšil strukturu programu. Plánuju teď dát konzoli do jednoho vlákna a renderování do jiného, abych mohl psát do konzole příkazy.

**16.2.2015>>**

* Kompletně jsem přepsal třídu stromu.
Instance stromů se nyní alokují dynamicky, o jejich paměť se stará template třída std::vector<>.
Bylo potřeba připsat speciální členné funkce move ctor, move assign.
Implementoval jsem dále Mersenne twister algoritmus pro generování náhodných čísel z knihovny boost boost::random::mt11213b. Nyní se již pseudonáhodná čísla neopakují.

## Screenshoty, obrázky

Tento obrázek ukazuje graficky znázorněné normály každého vertexu modelu. Grafickou reprezentaci normál je možné zapnout v souboru globals.h odkomentováním definice konstanty ZOBRAZ_NORMALY.

![Každý vrchol musí mít svoji normálu, symbolika protikladů.](H:\local new\programování\CB\struktury stromu\Treegen\Dokumenty k projektu\Normaly.png)

Následující dvojice obrázků ukazuje rozdíl mezi Goraud a Flat technikou stínování.

![Plynulá lineární interpolace barvy](H:\local new\programování\CB\struktury stromu\Treegen\Dokumenty k projektu\Goraud.png)
![Bez interpolace.](H:\local new\programování\CB\struktury stromu\Treegen\Dokumenty k projektu\Flat.png)
