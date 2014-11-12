#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx10math.h>
#include <fstream>
#include <iosfwd>
#include <windows.h>
#include <strsafe.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <dinput.h>
#include "JednoduchyVertex.h"
#include "globals.h"

#ifndef __CUSTOMVERTEX_H__
#define __CUSTOMVERTEX_H__
// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
};
#endif // __CUSTOMVERTEX_H__

struct tType
{
    int _iSType;
    int _iRType;
    int _iDType;
};

int* InitGeometry();
int GenerateTree(int iPater, tType _tType);
SimpleVertex* UnpackTree();
float random();
