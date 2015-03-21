set CESTA_KOMPILATORU=H:\TDM-GCC-64

mkdir .objs
mkdir .objs\SWU

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Engine.cpp" -o .objs\Engine.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Helper.cpp" -o .objs\Helper.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Input.cpp" -o .objs\Input.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Kamera.cpp" -o .objs\Kamera.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Kontroler3d.cpp" -o .objs\Kontroler3d.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "main.cpp" -o .objs\main.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "msgProc.cpp" -o .objs\msgProc.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "SWU\Konzole.cpp" -o .objs\SWU\Konzole.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "SWU\Okno.cpp" -o .objs\SWU\Okno.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Tree.cpp" -o .objs\Tree.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Tree3.cpp" -o .objs\Tree3.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Tvar.cpp" -o .objs\Tvar.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe -g -std=gnu++1y -I"boost_1_57_0" -c "Usecka.cpp" -o .objs\Usecka.o

%CESTA_KOMPILATORU%\bin\x86_64-w64-mingw32-g++.exe  -o bin\mingwTreegen.exe .objs\Engine.o .objs\Helper.o .objs\Input.o .objs\Kamera.o .objs\Kontroler3d.o .objs\main.o .objs\msgProc.o .objs\SWU\Konzole.o .objs\SWU\Okno.o .objs\Tree.o .objs\Tree3.o .objs\Tvar.o .objs\Usecka.o   -ld3d9 -ld3dx9_43 -ldinput8 -ldxguid