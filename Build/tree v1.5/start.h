//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Tutorial01.rc
//

#ifndef _START_H_
#define _START_H_
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;
#include <iosfwd>
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include "resource.h"
#include <xnamath.h>
#include <d3dcompiler.h>
#include <dinput.h>
struct SimpleVertex
{
    XMFLOAT3 Pos;  // Position
	XMFLOAT3 Normal; // Light Normal
	XMFLOAT4 Color; // Color
	//XMFLOAT2 Tex; // Texture Co
};
SimpleVertex* GenerateTree(int nVetvi, int vPoradi, int nTv);
int CountTree(int nVetvi, int nclanku);
UINT* GenerateTIndices();
HRESULT ReadInputState();
int GenerateRndm(int Obor,int Obor1);

//#include "DXUT.h"
//#include "DXUTcamera.h"
//#include "DXUTgui.h"
//#include "DXUTsettingsDlg.h"
//#include "SDKmisc.h"
//#include "SDKMesh.h"
#include "resource.h"
//#include "DXUTmisc.h"

#endif