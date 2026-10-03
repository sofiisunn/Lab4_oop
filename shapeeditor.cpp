#include "shape_editor.h"
#include "editor.h"
#include "Resource.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

ShapeObjectsEditor::ShapeObjectsEditor()
{
    capacity = 121;                    
    pcshape = new Shape* [capacity];
    currentIndex = 0;
    pse = nullptr;
    currentTool = -1;
    for (int i = 0; i < 121; i++)
    {
        pcshape[i] = nullptr;
    }
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
    delete pse;
    for (int i = 0; i < currentIndex; i++)
    {
        delete pcshape[i];
    }
    delete[] pcshape;
}

void ShapeObjectsEditor::AddShape(Shape* shape)
{
    if (currentIndex < capacity && shape != nullptr)
    {
        pcshape[currentIndex] = shape;
        currentIndex++;
    }
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd)
{
    if (pse) pse->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd)
{
    if (pse) pse->OnLBup(hWnd);
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
    if (pse) pse->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);


    for (int i = 0; i < currentIndex; i++)
    {
        if (pcshape[i])
        {
            pcshape[i]->Show(hdc);
        }
    }


    if (pse)
    {
        pse->OnPaint(hdc);
    }

    EndPaint(hWnd, &ps);
}

void ShapeObjectsEditor::StartPointEditor()
{
    delete pse;
    currentTool = 0;
    pse = new PointEditor(this);
}

void ShapeObjectsEditor::StartLineEditor()
{
    delete pse;
    currentTool = 1;
    pse = new LineEditor(this);
}

void ShapeObjectsEditor::StartRectEditor()
{
    delete pse;
    currentTool = 2;
    pse = new RectEditor(this);
}

void ShapeObjectsEditor::StartEllipseEditor()
{
    delete pse;
    currentTool = 3;
    pse = new EllipseEditor(this);
}

void ShapeObjectsEditor::StartLineWithCirclesEditor()
{
    delete pse;
    pse = new LineWithCirclesEditor(this);
}

void ShapeObjectsEditor::StartCubeFrameEditor()
{
    delete pse;
    pse = new CubeFrameEditor(this);
}

void ShapeObjectsEditor::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    if (pnmh->code == TTN_GETDISPINFO)
    {
        LPNMTTDISPINFO pDispInfo = (LPNMTTDISPINFO)lParam;
        switch (pDispInfo->hdr.idFrom)
        {
        case ID_POINT:
            pDispInfo->lpszText = (LPWSTR)L"Крапка";
            break;
        case ID_LINE:
            pDispInfo->lpszText = (LPWSTR)L"Лінія";
            break;
        case ID_RECT:
            pDispInfo->lpszText = (LPWSTR)L"Прямокутник";
            break;
        case ID_ELLIPSE:
            pDispInfo->lpszText = (LPWSTR)L"Еліпс";
            break;
        case ID_LINE_CIRCLES:
            pDispInfo->lpszText = (LPWSTR)L"Лінія з кружечками";
            break;
        case ID_CUBEFRAME:
            pDispInfo->lpszText = (LPWSTR)L"Каркас куба";
            break;
        }
    }
}