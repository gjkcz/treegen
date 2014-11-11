#ifndef __TREE_H__
#define __TREE_H__
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
struct SimpleVertex
{
    XMFLOAT3 Pos;  // Position
    XMFLOAT3 Normal; // Light Normal
    XMFLOAT4 Color; // Color
    //XMFLOAT2 Tex; // Texture Co
};
struct tType
{
    int _iSType;
    int _iRType;
    int _iDType;
};
#endif // __TREE_H__
