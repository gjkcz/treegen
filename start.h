//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Tutorial01.rc
//

#ifndef _START_H_
#define _START_H_

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx10math.h>
#include <fstream>
#include <iosfwd>
#include <windows.h>
#include <strsafe.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include <d3dcompiler.h>
#include <dinput.h>
using namespace std;
struct SimpleVertex
{
    XMFLOAT3 Pos;  // Position
    XMFLOAT3 Normal; // Light Normal
    XMFLOAT4 Color; // Color
    //XMFLOAT2 Tex; // Texture Co
};

int GenerateTree(int iPater, tType _tType);
SimpleVertex* UnpackTree();
int CountTree(int nVetvi, int nclanku);
UINT* GenerateTIndices();
HRESULT ReadInputState();
int GenerateRndm(int Obor,int Obor1);
float random();
int zaokrouhli(float _f);
//#include "DXUT.h"
//#include "DXUTcamera.h"
//#include "DXUTgui.h"
//#include "DXUTsettingsDlg.h"
//#include "SDKmisc.h"
//#include "SDKMesh.h"
//#include "resource.h"
//#include "DXUTmisc.h"

#endif
