// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib, "Shlwapi.lib")


#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma warning(disable:4100)


#include "trojuhelnik_d2d1.h"
#include "Grid_d2d1.h"
#include "collision_d2d1.h"
#include "extern/colorpick.hpp"



//#include "bitmap.h"

template<class Interface>
inline void SafeRelease(
    Interface** ppInterfaceToRelease
)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
/*
void D2D1PointInit(D2D1_POINT_2F* p, float x, float y) {
    p->x = x;
    p->y = y;
}
*/
D2D1_POINT_2F AB, AB2;//triangle points

int speed= 10;//move speed
int max_speed = 200;//max move speed

FLOAT dx=50, dy= 50;//dpi, x,y
bool _key = true;

Collision_area troj_col, rect_col, key_col;
ID2D1SolidColorBrush* m_BlackBrush;
ID2D1SolidColorBrush* m_GreenBrush;

float COLORPICK::ScaleDPI = 96.0f;
COLORPICK prx;

class DemoApp
{
public:
    DemoApp();
    ~DemoApp();

    // Register the window class and call methods for instantiating drawing resources
    HRESULT Initialize();

    // Process and dispatch messages
    void RunMessageLoop();

private:
    // Initialize device-independent resources.
    HRESULT CreateDeviceIndependentResources();

    // Initialize device-dependent resources.
    HRESULT CreateDeviceResources();

    // Release device-dependent resource.
    void DiscardDeviceResources();

    // Draw content.
    HRESULT OnRender();

    HRESULT LoadBitmapFromFile(PCWSTR uri,
        UINT destinationWidth,
        UINT destinationHeight,
        ID2D1Bitmap** ppBitmap);

    // Resize the render target.
    void OnResize(
        UINT width,
        UINT height
    );

    // The windows procedure.
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

private:
    HWND m_hwnd;
    ID2D1Factory* m_pDirect2dFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
    ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
    IWICImagingFactory* pIWICFactory;
    ID2D1EllipseGeometry* m_pEllipseGeometry;

};

DemoApp::DemoApp() :
    m_hwnd(NULL),
    m_pDirect2dFactory(NULL),
    m_pRenderTarget(NULL),
    m_pLightSlateGrayBrush(NULL),
    m_pCornflowerBlueBrush(NULL)
{
    AB.x = 200;
    AB.y = 200;
    AB2.x = 400;
    AB2.y = 200;
    troj_col.x = 200;
    troj_col.y = 0;
    troj_col.width = 200;
    troj_col.height = 200;

    key_col.x = 980;
    key_col.y = 580;
    key_col.height = 70;
    key_col.width = 70;

    rect_col.x = 570;
    rect_col.y = 570;
    rect_col.width = 70;
    rect_col.height = 220;
}


DemoApp::~DemoApp()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightSlateGrayBrush);
    SafeRelease(&m_pCornflowerBlueBrush);

}

void DemoApp::RunMessageLoop()
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HRESULT DemoApp::Initialize()
{
    HRESULT hr;

    // Initialize device-indpendent resources, such
    // as the Direct2D factory.
    hr = CreateDeviceIndependentResources();

    if (SUCCEEDED(hr))
    {
        // Register the window class.
        WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = DemoApp::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = sizeof(LONG_PTR);
        wcex.hInstance = HINST_THISCOMPONENT;
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName = NULL;
        wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
        wcex.lpszClassName = L"D2DDemoApp";

        RegisterClassEx(&wcex);


        // Because the CreateWindow function takes its size in pixels,
        // obtain the system DPI and use it to scale the window size.
        FLOAT dpiX, dpiY;

        // The factory returns the current system DPI. This is also the value it will use
        // to create its own windows.
     //   m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
        dpiX = (FLOAT)GetDpiForWindow(GetDesktopWindow());
        dpiY = dpiX;



        // Create the window.
        m_hwnd = CreateWindow(
            L"D2DDemoApp",
            L"Demonstrace relativn? a absolutn? velikosti ?tverce",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
            static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this
        );
        hr = m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            ShowWindow(m_hwnd, SW_SHOWNORMAL);
            UpdateWindow(m_hwnd);
        }
    }

    return hr;
}

HRESULT DemoApp::LoadBitmapFromFile(
    PCWSTR uri,
    UINT destinationWidth,
    UINT destinationHeight,
    ID2D1Bitmap** ppBitmap)
{
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;
    IWICBitmapScaler* pScaler = NULL;

    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );

    if (SUCCEEDED(hr))
    {
        // Create the initial frame.
        hr = pDecoder->GetFrame(0, &pSource);
    }

    if (SUCCEEDED(hr))
    {

        // Convert the image format to 32bppPBGRA
        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
        hr = pIWICFactory->CreateFormatConverter(&pConverter);

    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(
            pSource,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.f,
            WICBitmapPaletteTypeMedianCut
        );
    }
        if (SUCCEEDED(hr))
        {

            // Create a Direct2D bitmap from the WIC bitmap.
            hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );
        }

        SafeRelease(&pDecoder);
        SafeRelease(&pSource);
        SafeRelease(&pStream);
        SafeRelease(&pConverter);
        SafeRelease(&pScaler);

        return hr;
    
}

int WINAPI WinMain(
    HINSTANCE  hInstance ,
    HINSTANCE  hPrevInstance ,
    LPSTR  lpCmdLine ,
    int  nCmdShow 
)
{
    // Use HeapSetInformation to specify that the process should
    // terminate if the heap manager detects an error in any heap used
    // by the process.
    // The return value is ignored, because we want to continue running in the
    // unlikely event that HeapSetInformation fails.
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        {
            DemoApp app;

            if (SUCCEEDED(app.Initialize()))
            {
                app.RunMessageLoop();
            }
        }
        CoUninitialize();
    }

    return 0;
}

HRESULT DemoApp::CreateDeviceIndependentResources()
{
    HRESULT hr = S_OK;

    // Create a Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

    return hr;
}

HRESULT DemoApp::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if (!m_pRenderTarget)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top
        );

        // Create a Direct2D render target.
        hr = m_pDirect2dFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &m_pRenderTarget
        );


        if (SUCCEEDED(hr))
        {
            // Create a gray brush.
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::LightSlateGray),
                &m_pLightSlateGrayBrush
            );
        }
        if (SUCCEEDED(hr))
        {
            // Create a blue brush.
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
                &m_pCornflowerBlueBrush
            );
        }
        if (SUCCEEDED(hr))
        {
            // Create a blue brush.
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Black),
                &m_BlackBrush
            );
        }
        if (SUCCEEDED(hr))
        {
            // Create a blue brush.
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Green),
                &m_GreenBrush
            );
        }
    }

    return hr;
}


void DemoApp::DiscardDeviceResources()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightSlateGrayBrush);
    SafeRelease(&m_pCornflowerBlueBrush);
}


LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        DemoApp* pDemoApp = (DemoApp*)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pDemoApp)
        );

        result = 1;
    }
    else
    {
        DemoApp* pDemoApp = reinterpret_cast<DemoApp*>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )));

        bool wasHandled = false;

        if (pDemoApp)
        {
            switch (message)
            {
            case WM_SIZE:
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                pDemoApp->OnResize(width, height);
            }
            result = 0;
            wasHandled = true;
            break;
            case WM_LBUTTONDOWN:
            {
            
            }break;
            case WM_DISPLAYCHANGE:
            {
                InvalidateRect(hwnd, NULL, FALSE);
            }
            result = 0;
            wasHandled = true;
            break;
            
            case WM_KEYDOWN:
            {


                 if ((GetAsyncKeyState(0x27) & 0x8000 ) && (GetAsyncKeyState(0x28) & 0x8000)) {
                    //key-right and key-down pressed
                    AB.x = AB.x + speed;
                    AB2.x = AB2.x + speed;
                    AB.y = AB.y + speed;
                    AB2.y = AB2.y + speed;
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }
                else if ((GetAsyncKeyState(0x27) & 0x8000) && (GetAsyncKeyState(0x26) & 0x8000)) {
                    //key-right and key-up pressed
                    AB.x = AB.x + speed;
                    AB2.x = AB2.x + speed;
                    AB.y = AB.y - speed;
                    AB2.y = AB2.y - speed;
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }
                else if ((GetAsyncKeyState(0x25) & 0x8000) && (GetAsyncKeyState(0x28) & 0x8000)) {
                    //key-left and key-down pressed
                    AB.x = AB.x - speed;
                    AB2.x = AB2.x - speed;
                    AB.y = AB.y + speed;
                    AB2.y = AB2.y + speed;
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }
                else if ((GetAsyncKeyState(0x25) & 0x8000) && (GetAsyncKeyState(0x26) & 0x8000)) {
                    //key-left and key-up pressed
                    AB.x = AB.x - speed;
                    AB2.x = AB2.x - speed;
                    AB.y = AB.y - speed;
                    AB2.y = AB2.y - speed;
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }else if (GetAsyncKeyState(0x27) & 0x8000) {
                    //key-right pressed
                    AB.x = AB.x + speed;
                    AB2.x = AB2.x + speed;
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }
                else if (GetAsyncKeyState(0x25) & 0x8000) {
                    //key-left pressed
                    AB.x = AB.x - speed;
                    AB2.x = AB2.x - speed;
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }
                else if (GetAsyncKeyState(0x28) & 0x8000) {
                    //key-down pressed
                    AB.y = AB.y + speed;
                    AB2.y = AB2.y + speed;
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                }
                else if (GetAsyncKeyState(0x26) & 0x8000) {
                    //key-up pressed
                    AB.y = AB.y - speed;
                    AB2.y = AB2.y - speed;
                    SendMessage(hwnd, WM_PAINT, 0, 0);
                 }
                else if ((GetAsyncKeyState(0x43) & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                     D2D1_COLOR_F c1 = {};// = { 1.0f,0,0,1.0f };
                     prx.Show(0, c1);
                     m_GreenBrush->SetColor(c1);
                     SendMessage(hwnd, WM_PAINT, 0, 0);
                 }
                else if (GetAsyncKeyState(0x43) & 0x8000) {
                     D2D1_COLOR_F col = GetColorFromChooseColorDialog();
                     m_GreenBrush->SetColor(col);
                     SendMessage(hwnd, WM_PAINT, 0, 0);
                 }
                else if ((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) && (GetAsyncKeyState(0x53) & 0x8000)) {
                     //  MessageBox(NULL, L"SUB", L"SUB", MB_OK);
                     if (speed != 1) {
                         speed--;
                     }
                 }
                else if ((GetAsyncKeyState(VK_ADD) & 0x8000) && (GetAsyncKeyState(0x53) & 0x8000)) {
                     //  MessageBox(NULL, L"ADD", L"ADD", MB_OK);
                     if (speed != max_speed) {
                         speed++;
                     }
                 }
                else if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000) {
                     dx = dx - 1;
                     dy = dy - 1;
                     SendMessage(hwnd, WM_PAINT, 0, 0);
                 }
                else if (GetAsyncKeyState(VK_ADD) & 0x8000) {
                     dy = dy + 1;
                     dx = dx + 1;
                     SendMessage(hwnd, WM_PAINT, 0, 0);
                 }
                 troj_col.x = AB.x;//200
                 troj_col.y = AB.y - 200;//200
                 troj_col.width = 200;//200
                 troj_col.height = 200;//200
                 if (Collision(troj_col, key_col)) {
                     _key = false;
                     SendMessage(hwnd, WM_PAINT, 0, 0);
                 }
                 if (Collision(troj_col, rect_col)) {
                     MessageBox(NULL, L"Collision detected!", L"Info", MB_OK);
                 }

            }break;
            case WM_PAINT:
            {
                pDemoApp->OnRender();
                ValidateRect(hwnd, NULL);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            result = 1;
            wasHandled = true;
            break;
            }
        }

        if (!wasHandled)
        {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    return result;
}


void DemoApp::OnResize(UINT width, UINT height)
{
    if (m_pRenderTarget)
    {
        // Note: This method can fail, but it's okay to ignore the
        // error here, because the error will be returned again
        // the next time EndDraw is called.
        m_pRenderTarget->Resize(D2D1::SizeU(width, height));
    }
}


HRESULT DemoApp::OnRender()
{
    HRESULT hr = S_OK;

    hr = CreateDeviceResources();
    if (SUCCEEDED(hr))
    {
        m_pRenderTarget->BeginDraw();

        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
        D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

        int width = static_cast<int>(rtSize.width);
        int height = static_cast<int>(rtSize.height);


        m_pRenderTarget->SetDpi(dx, dy);

        D2D1_RECT_F rectangle1 = D2D1::RectF(
            600,
            600,
            650,
            800
        );
        D2D1_RECT_F key = D2D1::RectF(
            1000,
            600,
            1050,
            650
        );
        if (_key) {
            m_pRenderTarget->FillRectangle(key, m_pCornflowerBlueBrush);
        }
        m_pRenderTarget->DrawRectangle(rectangle1, m_BlackBrush);
        /*    AB.x = 200;
    AB.y = 200;
    AB2.x = 200;
    AB2.y = 400;*/
        TrojBody2 troj2;
        troj2.Ax = AB.x;//200
        troj2.Ay = AB.y;//200
        troj2.Bx = AB2.x;//400
        troj2.By = AB2.y;//200
        troj2.Cx = AB.x;//200
        troj2.Cy = AB2.y-200;//0
        Trojuhelnik troj(m_pRenderTarget, m_GreenBrush,troj2, 55);
        troj.Move2(20, 20, false);
        troj.Draw();
       /* m_pRenderTarget->DrawLine(AB, AB2, m_BlackBrush);

      /*  DrawGrid(m_pRenderTarget, m_pCornflowerBlueBrush, rtSize.width, rtSize.height);
       
        D2D1_COLOR_F color;
        color.r = 255;
        color.g = 0;
        color.b = 0;
        color.a = 255;
        m_pLightSlateGrayBrush->SetColor(color);
        troj.SetBrush(m_pLightSlateGrayBrush);*/

       // troj.Draw();
     //   troj.Rotate(35);
        
      /*  D2D1_POINT_2F point1, point2;
        point1.x = 200;
        point1.y = 200;
        point2.x = 400;
        point2.y = 200;*/

        /*
        D2D1_POINT_2F test = RotatePrimka2(AB, AB2, 0);
         m_pRenderTarget->DrawLine(AB, AB2, m_GreenBrush);
         for (float i = 0; i < 360;i = i++) {
             test = RotatePrimka2(AB, AB2, i);
             m_pRenderTarget->DrawLine(AB, test, m_GreenBrush);
         }*/
         
       // troj.Erase();
        hr = m_pRenderTarget->EndDraw();

    }
    if (hr == D2DERR_RECREATE_TARGET)
    {
        hr = S_OK;
        DiscardDeviceResources();
    }
    return hr;
}
