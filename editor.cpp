#include "editor.h"
#include "shape_editor.h"

int ShapeEditor::xStart = 0;
int ShapeEditor::yStart = 0;
int ShapeEditor::xEnd = 0;
int ShapeEditor::yEnd = 0;
bool ShapeEditor::isDrawing = false;

void ShapeEditor::OnLBdown(HWND hWnd)
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    xStart = xEnd = pt.x;
    yStart = yEnd = pt.y;
    isDrawing = true;
}

void ShapeEditor::OnMouseMove(HWND hWnd)
{
    if (isDrawing)
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        xEnd = pt.x;
        yEnd = pt.y;
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void ShapeEditor::OnLBup(HWND hWnd)
{
    if (isDrawing)
    {
        isDrawing = false;
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void ShapeEditor::OnPaint(HDC hdc)
{
}

void PointEditor::OnLBup(HWND hWnd)
{
    if (isDrawing)
    {
        isDrawing = false;
        PointShape* shape = new PointShape();
        shape->Set(xStart, yStart, xEnd, yEnd);
        owner->AddShape(shape); 
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void PointEditor::OnPaint(HDC hdc)
{
    if (isDrawing)
    {
        PointShape shape;
        shape.Set(xStart, yStart, xEnd, yEnd);
        shape.Show(hdc);
    }
}

void LineEditor::OnLBup(HWND hWnd)
{
    if (isDrawing)
    {
        isDrawing = false;
        LineShape* shape = new LineShape();
        shape->Set(xStart, yStart, xEnd, yEnd);
        owner->AddShape(shape); 
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void LineEditor::OnPaint(HDC hdc)
{
    if (isDrawing)
    {
        HPEN hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        MoveToEx(hdc, xStart, yStart, NULL);
        LineTo(hdc, xEnd, yEnd);

        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }
}

void RectEditor::OnLBup(HWND hWnd)
{
    if (isDrawing)
    {
        isDrawing = false;
        RectShape* shape = new RectShape();
        shape->Set(xStart, yStart, xEnd, yEnd);
        owner->AddShape(shape);
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void RectEditor::OnPaint(HDC hdc)
{
    if (isDrawing)
    {
        HPEN hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

        int dx = abs(xEnd - xStart);
        int dy = abs(yEnd - yStart);

        Rectangle(hdc, xStart - dx, yStart - dy, xStart + dx, yStart + dy);

        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }
}

void EllipseEditor::OnLBup(HWND hWnd)
{
    if (isDrawing)
    {
        isDrawing = false;
        EllipseShape* shape = new EllipseShape();
        shape->Set(xStart, yStart, xEnd, yEnd);
        owner->AddShape(shape); 
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void EllipseEditor::OnPaint(HDC hdc)
{
    if (isDrawing)
    {
        HPEN hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

        Ellipse(hdc, xStart, yStart, xEnd, yEnd);

        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }
}

void LineWithCirclesEditor::OnLBup(HWND hWnd)
{
    if (isDrawing)
    {
        isDrawing = false;
        LineWithCirclesShape* shape = new LineWithCirclesShape();
        shape->Set(xStart, yStart, xEnd, yEnd);
        owner->AddShape(shape);
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void LineWithCirclesEditor::OnPaint(HDC hdc)
{
    if (isDrawing)
    {
        HPEN hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

        MoveToEx(hdc, xStart, yStart, NULL);
        LineTo(hdc, xEnd, yEnd);
        Ellipse(hdc, xStart - 5, yStart - 5, xStart + 5, yStart + 5);
        Ellipse(hdc, xEnd - 5, yEnd - 5, xEnd + 5, yEnd + 5);

        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }
}

void CubeFrameEditor::OnLBup(HWND hWnd)
{
    if (isDrawing)
    {
        isDrawing = false;
        CubeFrameShape* shape = new CubeFrameShape();
        shape->Set(xStart, yStart, xEnd, yEnd);
        owner->AddShape(shape);
        InvalidateRect(hWnd, NULL, TRUE);
    }
}

void CubeFrameEditor::OnPaint(HDC hdc)
{
    if (isDrawing)
    {
        HPEN hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

        long dx = labs(xEnd - xStart), dy = labs(yEnd - yStart);
        long s = 30;
        if (dx < s) s = dx;
        if (dy < s) s = dy;
        s -= s % 2;                                    
        long l = xStart - dx, r = xStart + dx, t = yStart - dy, b = yStart + dy;

        Rectangle(hdc, l, t + s, r - s, b);            
        Rectangle(hdc, l + s, t, r, b - s);            
        MoveToEx(hdc, l, t + s, NULL);     LineTo(hdc, l + s, t);
        MoveToEx(hdc, r - s, t + s, NULL); LineTo(hdc, r, t);
        MoveToEx(hdc, r - s, b, NULL);     LineTo(hdc, r, b - s);
        MoveToEx(hdc, l, b, NULL);         LineTo(hdc, l + s, b - s);

        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);
    }
}