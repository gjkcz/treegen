//--------------------------------------------------------------------------------------
// File: Tutorial01.cpp
//
// This application demonstrates creating a Direct3D 11 device
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "start.h"
//#include "Tree.cpp"

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE							g_hInst = NULL;
HWND								g_hWnd = NULL;
D3D_DRIVER_TYPE						g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL					g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*						g_pd3dDevice = NULL;
ID3D11DeviceContext*			    g_pImmediateContext = NULL;
IDXGISwapChain*						g_pSwapChain = NULL;
ID3D11RenderTargetView*				g_pRenderTargetView = NULL;
ID3D11Texture2D*					g_pDepthStencil = NULL;
ID3D11DepthStencilView*				g_pDepthStencilView = NULL;
ID3D11VertexShader*					g_pVertexShader = NULL;
ID3D11PixelShader*					g_pPixelShader = NULL;
ID3D11PixelShader*					g_pPixelShaderSolid = NULL;
ID3D11InputLayout*					g_pVertexLayout = NULL;
ID3D11Buffer*						g_pVertexBuffer = NULL;					//VBSphere
ID3D11Buffer*						g_pIndexBuffer = NULL;					//IBSphere
ID3D11Buffer*                       g_pCBNeverChanges = NULL;
ID3D11Buffer*                       g_pCBChangeOnResize = NULL;
ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;
ID3D11ShaderResourceView*           g_pTextureRV = NULL;					//TextureSphere
ID3D11SamplerState*                 g_pSamplerLinear = NULL;
ID3D11RasterizerState*				g_pRasterizer = NULL;
ID3D11BlendState*					g_pBlendState = NULL;

ID3D11Buffer*						TVertexBf[16];				//Tree
XMMATRIX							TMatX[16];
int obsah = 1;
ID3D11Buffer*						TIndexBf = NULL;				//Tree
int									nTi;							
int									nTv;

LPDIRECTINPUT8          diiDI = NULL; // DirectInput interface       
LPDIRECTINPUTDEVICE8    diMouse = NULL; // Device interface
LPDIRECTINPUTDEVICE8    diKeybrd = NULL; // Device interface
byte Keys[256];

HWND hWindow;
XMMATRIX							g_World0;
XMMATRIX							g_World1;
XMMATRIX							g_World2;
XMMATRIX							g_View;
XMMATRIX							g_Projection;
XMFLOAT4							g_vMeshColor( 1.0f, 0.0f, 0.0f, 1.0f );
float							 v_X, v_Y, v_Z, vt_X, vt_Y, vt_Z, CamRot, CamRotRad, CamRotVel, RotUp;
bool							 Buttons[8];								
bool							 v_XY = true;
int								 IndexCount = 0;
long axX, axY, axZ, nmX,nmY;

SimpleVertex* poleStromu;
int pocetVrcholu = 2000000;


//----------------------------------------
//Physical variables
//----------------------------------------

static float dwTimeStart = 0.00000000f;
static float dwTimeCur;
static float t = 0.00000000f;
static float TimeSpan = 0.00000000f;
float LastTime;
int number = 1000;
XMFLOAT3 velocity[10];
float x = 0.f;
float y = 0.f;
bool xisten = false;
bool yisten = false;
bool b1 = false;
bool b2 = false;


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
bool Render();
HRESULT InitInputDevice(HWND hInstance);






float PI = 3.14159265358979323846;
//


struct CBChangeOnResize
{
	XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
	float Waviness;
	float Time;
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMFLOAT4 vMeshColor;
	XMFLOAT4 vLightDir[3];
	XMFLOAT4 vLightColor[3];
	XMFLOAT4 vOutputColor;
};

XMFLOAT4 vLightDirs[3] =
{
	XMFLOAT4( 0.5f, 1.0f, 0.0f, 1.0f ),
	//XMFLOAT4( 0.0f, 0.0f, 0.0f, 0.0f ),
	XMFLOAT4( 0.0f, 0.0f, -1.0f, 1.0f ),
	XMFLOAT4( -0.5f, -0.5f, 0.6f, 1.0f ),
};
XMFLOAT4 vLightColors[3] =
{
	// XMFLOAT4( 0.5f, 0.5f, 0.5f, 1.0f ),
	XMFLOAT4( 0.0f, 1.0f, 0.0f, 0.1f ),
	XMFLOAT4( 0.0f, 1.0f, 1.0f, 1.0f ),
	XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f ),
};
//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{

	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );
	
	if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
		return 0;

	if (FAILED (InitInputDevice(hWindow)))
		return 0;

	if( FAILED( InitDevice() ) )
	{
		CleanupDevice();
		return 0;
	}


	// Main message loop
	MSG msg = {0};

	//dwTimeCur = GetTickCount();
	if( dwTimeStart == 0 )
		dwTimeStart =  GetTickCount();

	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			ReadInputState();
			dwTimeCur = GetTickCount();
			if(!Render())
			{
				//InitDevice();
				//goto A;
				break;
			}
			LastTime = t;
		}
	}
		

	CleanupDevice();

	return ( int )msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	// Register class22222221222111222222222222222222211
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"DXWindowClass";
	wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
	if( !RegisterClassEx( &wcex ) )
		return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, 1920, 1080};												//rozliseni FSCREEEnn fullscreen
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	g_hWnd = CreateWindow( L"DXWindowClass", L"Start", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL );
	if( !g_hWnd )
		return E_FAIL;

	ShowWindow( g_hWnd, nCmdShow );
	hWindow = g_hWnd;
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}

HRESULT InitInputDevice(HWND hInstance)
{
	HRESULT hr;
	for (int i = 8; i < 8; i++)
		Buttons[i] = false;
	if (FAILED(hr=DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, ( VOID** )&diiDI, NULL )))
		return hr;
	if (FAILED (hr=diiDI->CreateDevice(GUID_SysMouse,&diMouse, NULL)))
		return hr;
	if (FAILED (hr=diMouse->SetDataFormat(&c_dfDIMouse2)))
		return hr;
	if (FAILED (hr=diMouse->SetCooperativeLevel(hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return hr;
	//mouse

	if (FAILED (hr=diiDI->CreateDevice(GUID_SysKeyboard,&diKeybrd, NULL)))
		return hr;
	if (FAILED (hr=diKeybrd->SetDataFormat(&c_dfDIKeyboard)))
		return hr;
	if (FAILED (hr=diKeybrd->SetCooperativeLevel(hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return hr;


	return S_OK;
}
//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
	if( FAILED(hr) )
	{
		if( pErrorBlob != NULL )
			OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
		if( pErrorBlob ) pErrorBlob->Release();
		return hr;
	}
	if( pErrorBlob ) pErrorBlob->Release();

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect( g_hWnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 8;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;																		//FSCREEEnn fullscreen

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		return hr;

	// Create a render target view

	ID3D11Texture2D* pBackBuffer = NULL;
	hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		return hr;
	D3D11_RENDER_TARGET_VIEW_DESC g_pRentargetdesc;
	hr = g_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );
	pBackBuffer->Release();
	if( FAILED( hr ) )
		return hr;

	g_pImmediateContext->OMSetRenderTargets( 1, &g_pRenderTargetView, NULL );

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC Depthdesc;
	ZeroMemory( &Depthdesc, sizeof(Depthdesc) );
	Depthdesc.Width = width;
	Depthdesc.Height = height;
	Depthdesc.MipLevels = 1;
	Depthdesc.ArraySize = 1;
	Depthdesc.Format = DXGI_FORMAT_D16_UNORM;
	Depthdesc.SampleDesc.Count = 8;
	Depthdesc.SampleDesc.Quality = 0;
	Depthdesc.Usage = D3D11_USAGE_DEFAULT;
	Depthdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Depthdesc.CPUAccessFlags = 0;
	Depthdesc.MiscFlags = 0 ;
	Depthdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; 
	hr = g_pd3dDevice->CreateTexture2D( &Depthdesc, NULL, &g_pDepthStencil );
	if( FAILED( hr ) )
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc;
	ZeroMemory( &DSVdesc, sizeof(DSVdesc) );
	DSVdesc.Format = Depthdesc.Format;
	DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	DSVdesc.Texture2D.MipSlice = 0;
	DSVdesc.Texture2DMS.UnusedField_NothingToDefine;

	DSVdesc.Texture2DMSArray.ArraySize = 1;
	DSVdesc.Texture2DMSArray.FirstArraySlice = 0;
	hr = g_pd3dDevice->CreateDepthStencilView( g_pDepthStencil, &DSVdesc, &g_pDepthStencilView );
	if( FAILED( hr ) )
		return hr;

	g_pImmediateContext->OMSetRenderTargets( 1, &g_pRenderTargetView, g_pDepthStencilView );


	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;

	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports( 1, &vp );

	// Compile the vertex shader
	ID3DBlob* pVSBlob = NULL;
	hr = CompileShaderFromFile( L"Tutorial02.hlsl", "VS", "vs_5_0", &pVSBlob );
	if( FAILED( hr ) )
	{
		MessageBox( NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
		return hr;
	}

	// Create the vertex shader
	hr = g_pd3dDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );
	if( FAILED( hr ) )
	{	
		pVSBlob->Release();
		return hr;
	}


	// Compile the pixel shader
	ID3DBlob* pPSBlob = NULL;
	hr = CompileShaderFromFile( L"Tutorial02.hlsl", "PS", "ps_5_0", &pPSBlob );
	if( FAILED( hr ) )
	{
		MessageBox( NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
		return hr;
	}

	// Create the pixel shader
	hr = g_pd3dDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );
	pPSBlob->Release();
	if( FAILED( hr ) )
		return hr;

	// Compile the pixel shader solid
	pPSBlob = NULL;
	hr = CompileShaderFromFile( L"Tutorial02.hlsl", "PSSolid", "ps_5_0", &pPSBlob );
	if( FAILED( hr ) )
	{
		MessageBox( NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
		return hr;
	}

	// Create the pixel shader solid
	hr = g_pd3dDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShaderSolid );
	pPSBlob->Release();
	if( FAILED( hr ) )
		return hr;

	// Define the input layout
	/*D3D11_INPUT_ELEMENT_DESC layout[] =
	{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE( layout );*/
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE( layout );

	// Create the input layout
	hr = g_pd3dDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout );
	pVSBlob->Release();
	if( FAILED( hr ) )
		return hr;


	/*
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
	{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",    0, DXGI_FORMAT_R10G10B10A2_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	{ "TEXCOORD",  0, DXGI_FORMAT_R16G16_FLOAT,    0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	{ "TANGENT",  0, DXGI_FORMAT_R10G10B10A2_UNORM,   0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BINORMAL", 0, DXGI_FORMAT_R10G10B10A2_UNORM,   0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};
	UINT numElements = ARRAYSIZE( layout );
	hr = g_pd3dDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
	pVSBlob->GetBufferSize(), &g_pVertexLayout );*/

	// Set the input layout
	g_pImmediateContext->IASetInputLayout( g_pVertexLayout );

	// Create vertex buffers
	/*
	SimpleVertex vertices[] =
	{
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ),XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ),XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ),XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ),XMFLOAT3( 0.0f, -1.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ),XMFLOAT3( 0.0f, -1.0f, 0.0f ),	XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ),XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ),XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ),XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ),XMFLOAT3( -1.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ),XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ),XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ),XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ),XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ),XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ),XMFLOAT3( 0.0f, 0.0f, -1.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ),XMFLOAT3( 0.0f, 0.0f, -1.0f ),XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -10f, -1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1..0f, 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2( 0.0f, 1.0f ) },
	};
	//vertices[1].Pos.x = 10.0f;
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( SimpleVertex ) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof(InitData) );
	InitData.pSysMem = vertices;
	hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pVertexBuffer );
	if( FAILED( hr ) )
	return hr;
	*/

	// Load the mesh

	wifstream stream;
	WCHAR input;
	int PosCount = 0;
	int p = 0;
	int TextCount = 0;
	int t = 0;
	int NormalCount = 0;
	int n = 0;

	int i = 0;
	WCHAR strCommand[256] = {0};
	stream.open(L"bom.obj");
	//stream.get(input);

	/*for(;;)
	{
	stream >> strCommand;
	if( !stream )
	break;

	if( 0 == wcscmp( strCommand, L"#" ) )
	{
	// Comment
	}
	else if( 0 == wcscmp( strCommand, L"v" ) )
	{
	// Vertex Position
	PosCount++;
	}
	else if( 0 == wcscmp( strCommand, L"vt" ) )
	{
	// Vertex TexCoord
	TextCount++;

	}
	else if( 0 == wcscmp( strCommand, L"vn" ) )
	{
	// Vertex Normal
	NormalCount++;

	}
	else if( 0 == wcscmp( strCommand, L"f" ) )
	{
	IndexCount += 3;   // Face
	}
	else if( 0 == wcscmp( strCommand, L"mtllib" ) )
	{
	// Material library
	}
	else if( 0 == wcscmp( strCommand, L"usemtl" ) )
	{

	}
	else
	{
	// Unimplemented or unrecognized command
	}

	stream.ignore( 1000, '\n' );
	}*/
	stream.close();
	stream.open(L"bom.obj");
	WORD* indices = new WORD[IndexCount];
	SimpleVertex* vertices = new SimpleVertex[PosCount];
	bool* isfilled = new bool[PosCount];
	UINT* index = new UINT[PosCount];
	int cnt = 0;
	XMFLOAT3* positions = new XMFLOAT3[PosCount];
	XMFLOAT2* textcoords = new XMFLOAT2[TextCount];
	XMFLOAT3* normals = new XMFLOAT3[NormalCount];

	/*
	for(;;)
	{
	stream >> strCommand;
	if( !stream )
	break;

	if( 0 == wcscmp( strCommand, L"#" ) )
	{
	// Comment
	}
	else if( 0 == wcscmp( strCommand, L"v" ) )
	{
	// Vertex Position
	float x, y, z;
	stream >> x >> y >> z;
	positions[p] = XMFLOAT3(x, y, z);
	p++;
	}
	else if( 0 == wcscmp( strCommand, L"vt" ) )
	{
	// Vertex TexCoord
	float u, v;
	stream >> u >> v;
	textcoords[t] = XMFLOAT2(u, v);
	t++;
	}
	else if( 0 == wcscmp( strCommand, L"vn" ) )
	{
	// Vertex Normal
	float x, y, z;
	stream >> x >> y >> z;
	normals[n] = XMFLOAT3(x, y, z);
	n++;
	}
	else if( 0 == wcscmp( strCommand, L"f" ) )
	{
	// Face
	UINT iPosition, iTexCoord, iNormal;
	//VERTEX vertex;

	for( UINT iFace = 0; iFace < 3; iFace++ )
	{
	//ZeroMemory( &vertex, sizeof( VERTEX ) );

	// OBJ format uses 1-based arrays
	stream >> iPosition;

	if( '/' == stream.peek() )
	{
	stream.ignore();

	if( '/' != stream.peek() )
	{
	// Optional texture coordinate
	stream >> iTexCoord;
	vertices[cnt].Tex = textcoords[ iTexCoord-1  ];
	}

	if( '/' == stream.peek() )
	{
	stream.ignore();

	// Optional vertex normal
	stream >> iNormal;
	vertices[cnt].Normal.x = normals[ iNormal-1 ].x;
	vertices[cnt].Normal.y = normals[ iNormal-1 ].y;
	vertices[cnt].Normal.z = normals[ iNormal-1 ].z;
	}
	}


	if(!isfilled[iPosition-1])
	{
	indices[i] = index[iPosition-1];
	i++;
	}
	else
	{
	vertices[cnt].Pos.x = positions[iPosition-1].x;
	vertices[cnt].Pos.y = positions[iPosition-1].y;
	vertices[cnt].Pos.z = positions[iPosition-1].z;
	isfilled[iPosition-1] = false;
	index[iPosition-1] = cnt;
	indices[i] = cnt;
	cnt++;
	i++;
	}
	//vertex.position = positions[ iPosition - 1 ];
	//if((vertices[iPosition].Pos.x != positions[iPosition - 1].x) && (vertices[iPosition].Pos.y != positions[iPosition - 1].y) && (vertices[iPosition].Pos.z != positions[iPosition - 1].z))
	//{

	//vertices[iPosition-1].Pos = positions[iPosition-1];
	//}
	//vertices[iPosition].Color.y = 1.0f;




	// If a duplicate vertex doesn't exist, add this vertex to the Vertices
	// list. Store the index in the Indices array. The Vertices and Indices
	// lists will eventually become the Vertex Buffer and Index Buffer for
	// the mesh.

	}
	//m_Attributes.Add( dwCurSubset );
	}
	else if( 0 == wcscmp( strCommand, L"mtllib" ) )
	{
	// Material library
	//stream >> strMaterialFilename;
	}
	else if( 0 == wcscmp( strCommand, L"usemtl" ) )
	{
	// Material

	}
	else
	{
	// Unimplemented or unrecognized command
	}

	stream.ignore( 1000, '\n' );
	}*/

	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( SimpleVertex ) * PosCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof(InitData) );
	//InitData.pSysMem = vertices;
	//hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pVertexBuffer );
	if( FAILED( hr ) )
		return hr;




	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( WORD ) * IndexCount;        // 36 vertices needed for 12 triangles in a triangle list
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	//InitData.pSysMem = indices;
	//hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &g_pIndexBuffer );
	if( FAILED( hr ) )
		return hr;

	nTv = 0;
	nTi = 0;
	float r = 1.0f; //radius
	float rp = 0.0f; //radius prechodu
	float r2 = 1.0f; //radius															VŠECHNO JSOU RADIÁNY
	float rp2 = rp; //radius prechodu
	int vPoradi = 0;
	float sklonx = 0.f; //=uhel v rad, sklonx
	float sklony = 0.f;
	//float Uzk2;	//uzkost2
	float Uzk; //uzkost

	float axDens = 0.01f;

	float Dens = 1.25* PI/180;
	float	Zkoord = 0.0f;
	Uzk = 0.0f;
	//Uzk2 = 0.1f;



	//
	//
	//VYPOCET MISTA
	//
	//
	int Tunnel = 100.0f;

	for (float x = 0.f; x<= Tunnel; x+=1.f)
	{

		for (float a = 2*PI; a>= 0.f; a-=Dens)																					//Pulkruh
		{
			if(cos(a) <= 0.f)
			{
				vPoradi++;
			}
		}
		for (float a = 2*PI; a>= 0.f; a-=Dens)																					//Vysec
		{
			if(cos((float)a) >= 0.f && cos((float)a) <= Uzk && sin((float)a) >= 0.f)
			{
				vPoradi++;
			}
		}

		float PodminkaY, PodminkaX;
		PodminkaY =  -sin(acos(Uzk/r));

		for (float a = 2*PI; a>= 0.f; a-=Dens)																					//Prechod1
		{
			if(sin((float)a) <= PodminkaY && cos((float)a)*rp <= 0)
			{

				vPoradi++;
			}
		}

		PodminkaX = (cos(asin((sin(acos(Uzk/r))*(r + rp))/(r2 + rp)))*rp)/rp2;
		PodminkaY = -rp*(cos(acos(Uzk/r)) - cos(acos(Uzk/r)))/rp2;

		for (float a = 2*PI; a>= 0.f; a-=Dens)																					//Prechod2
		{

			if(cos((float)a) >= PodminkaY && cos((float)a) <= PodminkaX && rp2*sin((float)a) <= 0.f)
			{
				vPoradi++;
			}
		}


		float PodminkaX1;
		PodminkaX1 = -(cos(asin((sin(acos(Uzk/r))*(r + rp))/(r2 + rp)))*r2);

		for (float a = 2*PI; a>= 0.f; a-=Dens)																					//Vysec2 + pulkruh2
		{
			if((cos((float)a)) * r2 >= PodminkaX1)
			{
				vPoradi++;
			}
		}

		PodminkaX = (cos(asin((sin(acos(Uzk/r))*(r + rp))/(r2 + rp)))*rp)/rp2;
		PodminkaY = -rp*(cos(acos(Uzk/r)) - cos(acos(Uzk/r)))/rp2;

		for (float a = 2*PI; a>= 0.f; a-=Dens)																						//Prechod2 dole
		{
			if(cos((float)a) >= PodminkaY && cos((float)a) <= PodminkaX && rp2*sin((float)a) >= 0.f)
			{
				vPoradi++;
			}
		}

		PodminkaY =  sin(acos(Uzk/r));

		for (float a = 2*PI; a>= 0.f; a-=Dens)																					//Prechod1 dole
		{
			if(sin((float)a) >= PodminkaY && cos((float)a)*rp <= 0)
			{
				vPoradi++;
			}
		}

		for (float a = 2*PI; a>= 0.f; a-=Dens)																					//Vysec dole
		{
			if(cos((float)a) >= 0.f && cos((float)a) <= Uzk && sin((float)a) <= 0.f)
			{
				vPoradi++;
			}
		}


		//
		//Pomocne obrazce
		//
		/*for (int a = 0; a <= 600; a++)
		{
		//Tvertices[vPoradi].Pos = XMFLOAT3((float)a * axDens - r, 0.f, Zkoord);
		vPoradi++;
		if(a%6 == 0)
		{
		for (int b = 0; b <= 2; b++)												//osa x
		{
		//Tvertices[vPoradi].Pos = XMFLOAT3( (float)a * axDens - r, (float)b * axDens, Zkoord);
		vPoradi++;
		}
		}
		if(a%24 == 0)
		{
		for (int b = 0; b <= 4; b++)												//osa x
		{
		//Tvertices[vPoradi].Pos = XMFLOAT3( (float)a * axDens - r, (float)b * axDens, Zkoord);
		vPoradi++;
		}
		}
		}
		for (int a = 0; a <= 600; a++)
		{
		if(a%6 == 0)
		{
		for (int b = 0; b <= 2; b++)												//osa x
		{
		//Tvertices[vPoradi].Pos = XMFLOAT3( (float)a * axDens - r, (float)b * axDens, Zkoord);
		vPoradi++;
		}
		}

		}
		for (int a = 0; a <= 600; a++)																	//graf 4a kvad
		{
		//Tvertices[vPoradi].Pos = XMFLOAT3(a * axDens, tan(acos(Uzk/r)) *  a * axDens, Zkoord);
		vPoradi++;
		}*/
		/*for (int a = 0; a <= 600; a++)															
		{
		//Tvertices[vPoradi].Pos = XMFLOAT3(a * axDens, tan(acos(Uzk/r)) *  a * axDens, Zkoord);
		vPoradi++;
		}
		for (int a = 0; a <= 600; a++)
		{
		//Tvertices[vPoradi].Pos = XMFLOAT3(a * axDens + Uzk, (tan(asin(Uzk/r)) *  a * -axDens) + tan(acos(Uzk/r))*Uzk, Zkoord);
		vPoradi++;
		}*/
		//Zkoord+=1.f;
		//Zkoord+=1.5f;
		rp+=0.001;
		rp2=rp;
		Uzk += 0.01;
	}
	//vPoradi = 290 * (Tunnel+1);

	/*for (int a = 500; a >= 49; a-=1)
	{
	if(sin((float)a) >= 0.7f)
	{
	Tvertices[a].Pos = XMFLOAT3(( cos((float)a)) * r, (sin((float)a)) * r, 0.f);
	Tvertices[a + 1].Pos = XMFLOAT3(( -cos((float)a)) * r, (sin((float)a)) * r, 2.f);
	}
	}*/

	//
	//ZÁVORKY
	//
	/*

	for (int a = 1000; a>= 0; a--)
	{
	if(sin((float)a) >= 0.f)
	{
	Tvertices[vPoradi].Pos = XMFLOAT3(( cos((float)a)) * r, (sin((float)a)) * r, 0.f);
	vPoradi++;
	}
	}
	for (int a = 1000; a>= 0; a--)
	{
	if(sin((float)a) <= 0.f)
	{
	Tvertices[vPoradi].Pos = XMFLOAT3(( cos((float)a)) * r, (sin((float)a)) * r - 1.f, 0.f);
	vPoradi++;
	}
	}
	*/

	//
	//KOLMÉ ZÁVORKY
	//
	/*
	for (int a = 1000; a>= 0; a--)
	{
	if(cos((float)a) <= 0.f)
	{
	Tvertices[vPoradi].Pos = XMFLOAT3(( cos((float)a)) * r, (sin((float)a)) * r, 0.f);
	vPoradi++;
	}
	}
	for (int a = 1000; a>= 0; a--)
	{
	if(cos((float)a) >= 0.f)
	{
	Tvertices[vPoradi].Pos = XMFLOAT3(( cos((float)a)) * r + 1.f, (sin((float)a)) * r, 0.f);
	vPoradi++;
	}
	}
	*/


	/*r=2;
	for (int a = 1000; a >= 500; a-=1)
	{
	if(sin((float)a) >= 0.7f)
	{
	//Tvertices[a].Pos = XMFLOAT3(( cos((float)a)) * r, (sin((float)a)) * r, 0.f);
	Tvertices[a ].Pos = XMFLOAT3(( cos((float)a)) * r, -(sin((float)a)) * r, 2.f);
	}
	}*/
	/*for (int a = 500; a >= 0; a--)
	{
	if(sin((float)a) <= 0.f)
	Tvertices[a].Pos = XMFLOAT3(( cos((float)a)) * r, (sin((float)a)) * r, 0.f);
	}*/

	//Tvertices[49]
	
	float xoffset = -2*150.f;
	float yoffset = -2*150.f;
	
	pocetVrcholu=2000000;
	//ZeroMemory( &SimpleVertex*, sizeof(SimpleVertex*) );
	//SimpleVertex* Tvertices = new SimpleVertex[vPoradi];
	poleStromu = new SimpleVertex[pocetVrcholu];

	for(int i = 0; i<obsah; i++)
	{
		poleStromu = new SimpleVertex[pocetVrcholu];
			xoffset = (i/sqrt((float)obsah)) * 150.f-(sqrt((float)obsah)/2)*150.f;
			yoffset = (i-(i/(int)sqrt((float)obsah)*(int)sqrt((float)obsah)))* 150.f-(sqrt((float)obsah)/2)*150.f;
		poleStromu = GenerateTree(10, pocetVrcholu, nTv);
		nTv=pocetVrcholu;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( SimpleVertex ) * pocetVrcholu;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		ZeroMemory( &InitData, sizeof(InitData) );
		InitData.pSysMem = poleStromu;
		hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &TVertexBf[i] );
		TMatX[i] = XMMatrixIdentity();
		TMatX[i] =  XMMatrixTranslation(xoffset,yoffset,0.f);
		if( FAILED( hr ) )
			return hr;
	}

	//g_pd3dDevice->

	//TVertexBf->GetPrivateData(;
	//TVertexBf->SetPrivateData(;


	//po49t8n9 indexu
	//1 troj na každý V
	//3*2*360
	//nTi = 3*361*2;
	nTi = 3*1000;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( UINT ) *nTi;        // 36 vertices needed for 12 triangles in a triangle list

	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = GenerateTIndices();
	hr = g_pd3dDevice->CreateBuffer( &bd, &InitData, &TIndexBf);
	if( FAILED( hr ) )
		return hr;
	/*
	g_Mesh.Create(g_pd3dDevice, L"Squid\\squid.sdkmesh", false );
	//V_RETURN( g_Mesh.Create( g_pd3dDevice, L"Tiny\\tiny.sdkmesh", true ) );


	UINT Strides[1];
	UINT Offsets[1];
	ID3D11Buffer* pVB[1];
	pVB[0] = g_Mesh.GetVB11( 0, 0 );
	Strides[0] = ( UINT )g_Mesh.GetVertexStride( 0, 0 );
	Offsets[0] = 0;
	g_pImmediateContext->IASetVertexBuffers( 0, 1, pVB, Strides, Offsets );
	g_pImmediateContext->IASetIndexBuffer( g_Mesh.GetIB11( 0 ), g_Mesh.GetIBFormat11( 0 ), 0 );
	*/
	// Create the constant buffers
	//D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.ByteWidth = sizeof(CBChangeOnResize);
	hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangeOnResize );
	if( FAILED( hr ) )
		return hr;

	bd.ByteWidth = sizeof(CBChangesEveryFrame);
	hr = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pCBChangesEveryFrame );
	if( FAILED( hr ) )
		return hr;

	// Load the Texture
	/*hr = D3DX11CreateShaderResourceViewFromFile( g_pd3dDevice, L"texture2.dds", NULL, NULL, &g_pTextureRV, NULL );
	if( FAILED( hr ) )
		return hr;*/

	// Create the sample state
	D3D11_SAMPLER_DESC SampleDesc;
	ZeroMemory( &SampleDesc, sizeof(SampleDesc) );
	SampleDesc.Filter =  D3D11_FILTER_ANISOTROPIC ;
	SampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SampleDesc.MinLOD = 1;
	SampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = g_pd3dDevice->CreateSamplerState( &SampleDesc, &g_pSamplerLinear );
	if( FAILED( hr ) )
		return hr;

	//Create Rasterizer State
	D3D11_CULL_MODE CMode = D3D11_CULL_NONE;   
	D3D11_FILL_MODE FMode = D3D11_FILL_WIREFRAME;
	D3D11_RASTERIZER_DESC rastadesc[] =
	{
		FMode, CMode, FALSE, 0, 0.0f, 0.0f, TRUE, FALSE, TRUE, FALSE
	};
	g_pd3dDevice->CreateRasterizerState(rastadesc, &g_pRasterizer);

	/*
	D3D11_RENDER_TARGET_BLEND_DESC RenderTargetBD;
	RenderTargetBD.BlendEnable = TRUE;
	RenderTargetBD.SrcBlend = D3D11_BLEND_ONE;
	RenderTargetBD.DestBlend = D3D11_BLEND_ZERO;
	RenderTargetBD.BlendOp = D3D11_BLEND_OP_ADD;
	RenderTargetBD.SrcBlendAlpha = D3D11_BLEND_ONE;
	RenderTargetBD.DestBlendAlpha = D3D11_BLEND_ZERO;
	RenderTargetBD.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	RenderTargetBD.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	D3D11_BLEND_DESC bledesc;
	bledesc.AlphaToCoverageEnable = TRUE;
	bledesc.IndependentBlendEnable = FALSE;
	bledesc.RenderTarget[0] = RenderTargetBD;
	g_pd3dDevice->CreateBlendState(&bledesc, &g_pBlendState);
	*/
	// Initialize the world matrix
	g_World0 = XMMatrixIdentity();
	g_World1 = XMMatrixIdentity();
	g_World2 = XMMatrixIdentity();

	v_X = 100.0f;
	v_Y = 0.0f;

	axY = 0;
	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV2, width / (FLOAT)height, 1.f, 102000.0f );
	//g_Projection = XMMatrixPerspectiveFovLH( 120.0f, width / (FLOAT)height, 0.000001f, 1000000000000000000000.0f );
	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );
	g_pImmediateContext->UpdateSubresource( g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );
	//CamRotRad = 2.f;
	//CamRotVel = 0.0f;
	CamRotRad  =  200.f;
	CamRotVel = 0.1f;
	return S_OK;
}


int GenerateRndm(int Obor, int Obor1)
{

	while(nmX==0 || nmY==0)
		ReadInputState();
	for(int g = 0; g < 1000/*9000000*/; g++)	//waiting for rndm mouse
	{
	}
	ReadInputState();
	Obor1-=Obor;
	int x;
	int y;
	int z;
	if (nmX < 0)
		nmX = -nmX;
	if (nmY < 0)
		nmY = -nmY;

	if (Obor1/100!=0)
		x = (int)nmX - ((int)nmX/(Obor1/100))*(Obor1/100);
	else
		x = 0;

	if (((Obor1 - (Obor1/100)*100)/10)!=0 && x < (Obor1/100))
		y = (int)nmY - ((int)nmY/10)*10;
	else if (((Obor1 - (Obor1/100)*100)/10)!=0 && x == (Obor1/100))	
		y = (int)nmY - ((int)nmY/((Obor1 - (Obor1/100)*100)/10))*((Obor1 - (Obor1/100)*100)/10);
	else if (((Obor1 - (Obor1/100)*100)/10)==0 && x < (Obor1/100))
		y = (int)nmY - ((int)nmY/10)*10;
	else
		y = 0;

	if (x < Obor1/100)
		z = (int)nmX - ((int)nmX/10)*10;
	else if (y < Obor1/10)	
		z = (int)nmX - ((int)nmX/10)*10;
	else if ((Obor1 - (Obor1/100)*100 - (Obor1/10)*10)!=0)
		z = (int)nmX - ((int)nmX/(Obor1 - (Obor1/100)*100 - (Obor1/10)*10))*(Obor1 - (Obor1/100)*100 - (Obor1/10)*10);
	else
		z = 0;

	nmY=0;
	nmX=0;
	if (!Buttons[0])
		return Obor+ x*100 + y*10 + z;
	else
		return Obor+ 1;
}


HRESULT ReadInputState()
{
	HRESULT hr;
	DIMOUSESTATE2 ms;
	hr = diMouse->Poll();
	if (FAILED(hr))
	{
		hr = diMouse->Acquire();
		while(hr == DIERR_INPUTLOST)
			hr = diMouse->Acquire();
		return S_OK;
	}
	diMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &ms);

	for (int i = 0; i < 8; i++)
	{
		if (ms.rgbButtons[i])
			Buttons[i] = true;
		else
			Buttons[i] = false;
	}
	if(Buttons[2])
	{
		axX += ms.lX;																	//Mouse
		axY += (ms.lY)*PI/180;
		axZ += ms.lZ;
	}
	nmX+=ms.lX;
	nmY+=ms.lY;
	//axX += ms.lX;			
	hr = diKeybrd->Poll();
	if (FAILED(hr))
	{
		hr = diKeybrd->Acquire();
		while(hr == DIERR_INPUTLOST)
			hr = diKeybrd->Acquire();
		return S_OK;
	}
	diKeybrd->GetDeviceState(256, &Keys);


	return S_OK;
}
//--------------------------------------------------------------------------------------
// Render the frame
//--------------------------------------------------------------------------------------
bool Render()
{
	//
	// prepare skysphere
	//
	XMMATRIX mScale2 = XMMatrixScaling( 3.09f, 3.09f, 3.09f );
	velocity[1].x += x/50;
	g_World0 = mScale2 * XMMatrixTranslation(0.f,0.f,0.f);

	
	//axY = PI/4;

	if (v_XY && (v_X - 0.1f) > 0.0f)
	{
		v_X -= 0.1f;
		v_Y += 0.1f;
	}	
	else if (v_XY && (v_X - 0.1f) <= 0.0f)
	{
		v_XY = false;
	}
	else if (!v_XY && (v_X + 0.1f) < 100.0f)
	{
		v_X += 0.1f;
		v_Y -= 0.1f;
	}
	else if(!v_XY && (v_X + 0.1f) >= 100.0f)
	{
		v_XY = true;
	}
	
	//KBD
	if (Keys[DIK_W] & 0x80)
		CamRotRad -=0.7;
	//vt_Z -= 0.1;
	if (Keys[DIK_S] & 0x80)
		CamRotRad += 0.7;
	//vt_Z += 0.1;
	if (Keys[DIK_A] & 0x80)
		CamRot =  PI/2;
	if (Keys[DIK_D] & 0x80)
		CamRot =  2*PI;
	if (Keys[DIK_Q] & 0x80)
		vt_Y -= 0.7;
	if (Keys[DIK_E] & 0x80)
		vt_Y += 0.7;
	if (Keys[DIK_1] & 0x80)
		CamRotVel -= 0.001;
	if (Keys[DIK_2] & 0x80)
		CamRotVel += 0.001;
	if (Keys[DIK_3] & 0x80)
		CamRot -= PI/27;
	if (Keys[DIK_4] & 0x80)
		CamRot +=  PI/27;
	if (Keys[DIK_5] & 0x80)
		CamRotVel =  0.f;
	if (Keys[DIK_DOWN] & 0x80)
		RotUp -=  PI/32;
	if (Keys[DIK_UP] & 0x80)
		RotUp +=  PI/32;
	if (Keys[DIK_INSERT] & 0x80)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory( &InitData, sizeof(InitData) );
		float xoffset = -2*150.f;
		float yoffset = -2*150.f;
		//int vPoradi=2000000;
		//SimpleVertex* poleStromu;
		ZeroMemory( &poleStromu, sizeof(SimpleVertex*) );

		for(int i = 0; i<obsah; i++)
		{
			//TVertexBf[i]->Release();
			//poleStromu = new SimpleVertex[pocetVrcholu];
			ZeroMemory( &poleStromu, sizeof(SimpleVertex*) );
			xoffset = (i/sqrt((float)obsah)) * 150.f-(sqrt((float)obsah)/2)*150.f;
			yoffset = (i-(i/(int)sqrt((float)obsah)*(int)sqrt((float)obsah)))* 150.f-(sqrt((float)obsah)/2)*150.f;
			poleStromu = GenerateTree(10, pocetVrcholu, nTv);
			ZeroMemory( &poleStromu, sizeof(SimpleVertex*) );
			nTv=pocetVrcholu;
			ZeroMemory( &bd, sizeof(bd) );
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof( SimpleVertex ) * pocetVrcholu;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			ZeroMemory( &InitData, sizeof(InitData) );
			InitData.pSysMem = poleStromu;
			g_pd3dDevice->CreateBuffer( &bd, &InitData, &TVertexBf[i] );
			TMatX[i] = XMMatrixIdentity();
			TMatX[i] =  XMMatrixTranslation(xoffset,yoffset,0.f);
		}
	}
	//
	// Animate the cube1
	//
	// Initialize the view matrix
	XMMATRIX mRotateVX;
	XMMATRIX mRotateVZ;
	// Rotate the view
	//axY+= PI/180;
	mRotateVX = XMMatrixRotationX(RotUp+PI/4);

	//XMMATRIX mRotateVY = XMMatrixRotationY(axX * 0.001f); //mouse


	mRotateVZ = XMMatrixRotationZ(axZ *0.001f);
	XMVECTOR At = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );

	//At = XMVector3Transform( At, mRotateVX);
	//At = XMVector3Transform( At, mRotateVY);
	if(CamRot <= 2 * 3.14159265358979323846)
		CamRot += CamRotVel*3.14159265358979323846/180;
	else
		CamRot = 0.f;
	XMMATRIX mRotateVY = XMMatrixRotationY( -3.14159265358979323846/2 + CamRot + axX * PI/11520); 
	//CamRot = 3.14159265358979323846/2;
	XMMATRIX mRotateW = XMMatrixRotationX( -3.14159265358979323846/2); 

	//XMVECTOR Eye = XMVectorSet( cos(CamRot) * CamRotRad, sin(CamRot) * CamRotRad, 0.0f, 0.0f );
	XMVECTOR Up = XMVectorSet( 1.0f, 0.0f, 0.0f, 0.0f );
	//g_View = XMMatrixLookAtLH( Eye, At, Up );

	XMMATRIX mScale = XMMatrixScaling( 0.2f, 0.2f, 0.2f );
	XMMATRIX mOrbitionx = XMMatrixRotationY((velocity[1].x) / 4);
	XMMATRIX mOrbition = XMMatrixRotationX(velocity[1].x);
	XMMATRIX mTranslation = XMMatrixTranslation(0.f,-(3.f + y), 0.f);
	XMMATRIX mTranslationx = XMMatrixTranslation(-(-1.f + y/3),0.f, 0.f);
	//g_World1 = mScale * (mTranslation *  mOrbition) * mTranslationx * mOrbitionx;
	//XMMATRIX translate = XMMatrixTranslation(vt_X, vt_Y, vt_Z);
	XMMATRIX translate = XMMatrixTranslation(cos(CamRot) * CamRotRad + cos((float)axX * PI/11520) , vt_Y, sin(CamRot) * CamRotRad +sin((float)axX * PI/11520)+ vt_X);
	g_World1 = mScale * mRotateW;// * translate;
	g_View = translate * mRotateVZ * mRotateVY * mRotateVX;


	// Animate the cube2
	//
	XMMATRIX mScale1 = XMMatrixScaling( 1.0f, 1.0f, 1.0f );
	XMMATRIX mOrbition1x = XMMatrixRotationY((velocity[1].x) );
	XMMATRIX mOrbition1 = XMMatrixRotationX(velocity[1].x *0);
	XMMATRIX mTranslation1 = XMMatrixTranslation(0.f,0.f, 0.f);
	XMMATRIX mTranslation1x = XMMatrixTranslation(-1.f + y/3,0.f, 0.f);
	//g_World2 =mScale1 * (mTranslation1 *  mOrbition1) * mTranslation1x * mOrbition1x;
	g_World2 = mTranslation1 * mRotateW;

	// Rotate the second light around the origin
	XMMATRIX mRotateL = XMMatrixRotationY(0.01);
	XMVECTOR vLightDir = XMLoadFloat4( &vLightDirs[1] );
	vLightDir = XMVector3Transform( vLightDir, mRotateL );
	XMStoreFloat4( &vLightDirs[1], vLightDir );


	//
	// Clear the back buffer
	//
	//float ClearColor[4] = {1.0f, 1.0f, 1.0f, 1.0f }; // red,green,blue,alpha{ 0.0f, 0.325f, 0.1f, 1.0f };
	float ClearColor[4] = {0.0f, 0.0f, 0.0f, 0.0f }; // red,green,blue,alpha{ 0.0f, 0.325f, 0.1f, 1.0f };
	
	g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );

	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	g_pImmediateContext->ClearDepthStencilView( g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

	//
	// Update matrix variables and lighting variables
	//

	/*
	CBChangesEveryFrame cbL;
	cbL.vLightDir[0] = vLightDirs[0];
	cbL.vLightDir[1] = vLightDirs[1];
	cbL.vLightColor[0] = vLightColors[0];
	cbL.vLightColor[1] = vLightColors[1];
	cbL.vOutputColor = XMFLOAT4(0, 0, 0, 0);
	cbL.Time = t;
	cbL.Waviness = 0;
	g_pImmediateContext->UpdateSubresource( g_pCBChangesEveryFrame, 0, NULL, &cbL, 0, 0 );
	*/

	//
	// Update variables for cube0
	//

	//
	// Render the cube0
	//

	// Set vertex buffer
	UINT stride = sizeof( SimpleVertex );
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers( 0, 1, &TVertexBf[0], &stride, &offset );
	// Set index buffer
	//g_pImmediateContext->IASetIndexBuffer( TIndexBf, DXGI_FORMAT_R32_UINT, 0 );
	// Set primitive topology
	//g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
	g_pImmediateContext->VSSetConstantBuffers( 1, 1, &g_pCBChangeOnResize );
	g_pImmediateContext->VSSetConstantBuffers( 2, 1, &g_pCBChangesEveryFrame );
	g_pImmediateContext->VSSetSamplers( 0, 1, &g_pSamplerLinear );
	g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );
	g_pImmediateContext->PSSetConstantBuffers( 2, 1, &g_pCBChangesEveryFrame );
	g_pImmediateContext->PSSetSamplers( 0, 1, &g_pSamplerLinear );
	g_pImmediateContext->RSSetState(g_pRasterizer);
	//g_pImmediateContext->DrawIndexed( 3, 0, 0 );        // 36 vertices needed for 12 triangles in a triangle list

	//
	// Update variables for cube1
	//

	//
	// Update variables for cube2
	//
	CBChangesEveryFrame cb2;
	cb2.mWorld = XMMatrixTranspose( g_World2 );

	cb2.mView = XMMatrixTranspose(g_View);



	// Set vertex buffer

	//g_pImmediateContext->IASetVertexBuffers( 0, 1, &TVertexBf[0], &stride, &offset );
	// Set index buffer
	g_pImmediateContext->IASetIndexBuffer( TIndexBf, DXGI_FORMAT_R32_UINT, 0 );
	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST); //TRIANGLELIST
	//g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //TRIANGLELIST
	for (int i = 0; i < obsah; i++)
	{
		g_pImmediateContext->IASetVertexBuffers( 0, 1, &TVertexBf[i], &stride, &offset );
		cb2.mWorld = XMMatrixTranspose( TMatX[i]* mRotateW) ;
		g_pImmediateContext->UpdateSubresource( g_pCBChangesEveryFrame, 0, NULL, &cb2, 0, 0 );
		g_pImmediateContext->Draw( nTv, 0);
	}//g_pImmediateContext->PSSetShader( g_pPixelShaderSolid, NULL, 0 );
	//
	// Renders a cube2
	//
	//g_pImmediateContext->Draw( nTv, 0);
	//g_pImmediateContext->DrawIndexed( nTi, 0, 0 );//INDEXED
	//
	// Render each light
	//

	//


	//slowdown
	 g_pSwapChain->Present( 0, 0 );
	 if (Keys[DIK_DELETE] & 0x80)
	{
		//CleanupDevice();
		return false;
		
	}
	/*while(((( dwTimeCur - dwTimeStart ) /100.0f) - t) < 100.9f)//49888521f)
	{
	dwTimeCur = GetTickCount();
	}*/
	/*int i = 0;
	while(i < 5000000)
	{
	i++;
	}*/
	 else
		return true;

}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if( g_pImmediateContext ) g_pImmediateContext->ClearState();

	if( g_pSamplerLinear ) g_pSamplerLinear->Release();
	if( g_pTextureRV ) g_pTextureRV->Release();
	if( g_pCBNeverChanges ) g_pCBNeverChanges->Release();
	if( g_pCBChangeOnResize ) g_pCBChangeOnResize->Release();
	if( g_pCBChangesEveryFrame ) g_pCBChangesEveryFrame->Release();
	if( g_pVertexBuffer ) g_pVertexBuffer->Release();
	if( g_pIndexBuffer ) g_pIndexBuffer->Release();
	if( g_pVertexLayout ) g_pVertexLayout->Release();
	if( g_pVertexShader ) g_pVertexShader->Release();
	if( g_pPixelShader ) g_pPixelShader->Release();
	if( g_pDepthStencil ) g_pDepthStencil->Release();
	if( g_pDepthStencilView ) g_pDepthStencilView->Release();
	if( g_pRenderTargetView ) g_pRenderTargetView->Release();
	if( g_pSwapChain ) g_pSwapChain->Release();
	if( g_pImmediateContext ) g_pImmediateContext->Release();
	if( g_pd3dDevice ) g_pd3dDevice->Release();
}
