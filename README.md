# CTIME #


### Spuštění programu ###

* Spuštění provedete následujícími příkazy pro git:

    + git init
    + git remote add r https://xmegapopcornz@bitbucket.org/xmegapopcornz/treegen.git
    + git pull r master
    + Spustitelný soubor je v podadresáři \bin, pokud máte nainstalované DírectX půjde spustit.  

* Nemáte-li DirectX, program vypíše chybu jako "V počítači chybí knihovna d3dx9_43"  V tomto případě si stáhněte chybějící knihovny z branche knihovny a vložte je k binárnímu souboru.  
    + Knihovny stáhnete pomocí následujících příkazů pro git:
        - V adresáři projektu spusťte příkazovou řádku/powershell
        - git init
        - git remote add r https://xmegapopcornz@bitbucket.org/xmegapopcornz/treegen.git
        - git fetch r
        - git checkout knihovnyDx9

### Kompilace projektu: ###

**Budete potřebovat:**

* [TDM GCC 4.9 (64x)](http://tdm-gcc.tdragon.net/download)
* [Boost 1.57.0](http://www.boost.org/users/history/version_1_57_0.html)
* [Git](http://git-scm.com/download/win)
* knihovny DirectX(většinout jsou předinstalované, chybí-li návod na jejich instalaci naleznete zde na konci sekce Spuštění programu )

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
-------------- Build: tdmDebug in mingwTreegen (compiler: Twilight Dragon Media compiler)---------------

x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\Engine.cpp" -o .objs\Engine.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\Helper.cpp" -o .objs\Helper.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\Input.cpp" -o .objs\Input.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\Kamera.cpp" -o .objs\Kamera.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\Kontroler3d.cpp" -o .objs\Kontroler3d.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\main.cpp" -o .objs\main.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\msgProc.cpp" -o .objs\msgProc.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\SWU\Konzole.cpp" -o .objs\SWU\Konzole.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\SWU\Okno.cpp" -o .objs\SWU\Okno.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\Tree.cpp" -o .objs\Tree.o
x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"H:\local new\programování\CB\struktury stromu\Treegen\devpaks\boost_1_57_0" -c "H:\local new\programování\CB\struktury stromu\tempTreegen\Usecka.cpp" -o .objs\Usecka.o
x86_64-w64-mingw32-g++.exe  -o mingwTreegen.exe .objs\Engine.o .objs\Helper.o .objs\Input.o .objs\Kamera.o .objs\Kontroler3d.o .objs\main.o .objs\msgProc.o .objs\SWU\Konzole.o .objs\SWU\Okno.o .objs\Tree.o .objs\Usecka.o   -ld3d9 -ld3dx9_43 -ldinput8 -ldxguid
Output file is mingwTreegen.exe with size 3.81 MB
Process terminated with status 0 (0 minute(s), 14 second(s))
0 error(s), 0 warning(s) (0 minute(s), 14 second(s))
 

### Ovladani: ###

* w, s, a, d - dopredu, dozadu, doleva, doprava
* q, e - nahoru, dolu
* ↑, ↓ - pohled nahoru, dolu
* myš
* příkazy

### Changelog: ###

**20.10.2014>>**

* Prvni commit
* Tutorial na markdown
* Rešerše problémů:
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
Dále jsem upravil třídu DruhStromu, přidal indexBuffer.