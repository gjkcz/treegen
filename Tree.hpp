#ifndef __TREE_H__
#define __TREE_H__
//#include <d3d11.h>
//#include <d3dx9.h>
//#include <d3dx10math.h>
#include <fstream>
#include <iosfwd>
#include <windows.h>
//#include <strsafe.h>
//#include <d3d11.h>
//#include <d3dx11.h>
//#include <xnamath.h>
//#include <d3dcompiler.h>
#include <dinput.h>
#include "JednoduchyVertex.hpp"
#include "TreeType.hpp"
#include "Helper.hpp"
//struct SimpleVertex
//{
//    XMFLOAT3 Pos;  // Position
//    XMFLOAT3 Normal; // Light Normal
//    XMFLOAT4 Color; // Color
//    //XMFLOAT2 Tex; // Texture Co
//};
//struct tType
//{
//    int _iSType;
//    int _iRType;
//    int _iDType;
//};

int GenerateTree(int iPater, tType _tType);
SimpleVertex* getTree();

void RostClanek(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ);
void RostClanekRozdvojeni(float r, float rp, float r2, float radiusZ, float sklony, float sklonX1, float sklonY1, float sklonz,float rotace, float Dens, float Uzk, float posunX, float posunY, float posunZ, float tU);
void RostOsy();
float random();
int helper::zaokrouhli(float _f);
int integratePower(int _zakl, float _doMocniny);


class Tree
{
public:
    Tree();
    ~Tree();
protected:
private:
    SimpleVertex* vrcholy;
    UINT* indicie;
    Vetev* vetve;
    void generujVetve();
    void generujKmen();
    void generujListy();
    void spoctiVertexy();
    void generujPlosky();
};


#endif // __TREE_H__
