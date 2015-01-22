#include <iostream>
#include <windows.h>
#include <d3dx9.h>
//#include <d3dx9math.h>
#include <dinput.h>
//#include <xnamath.h>
#include "globals.hpp"
#include "helper.hpp"
using namespace std;

#ifndef __CUSTOMVERTEX_H_INCLUDED__
#define __CUSTOMVERTEX_H_INCLUDED__

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
};
#endif // __CUSTOMVERTEX_H__

//HRESULT InitD3D( HWND hWnd, LPDIRECT3DDEVICE9& g_pd3dDevice, D3DXMATRIX* treeMatrix );
VOID render(const LPDIRECT3DDEVICE9& g_pd3dDevice, int* Pocet,
             byte* Keys, float * axs, D3DXMATRIX* treeMatrix,
              LPDIRECT3DVERTEXBUFFER9* treeVertexBuffers );
void clearScreen();
