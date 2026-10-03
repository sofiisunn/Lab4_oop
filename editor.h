#pragma once
#include <windows.h>
#include "shape.h"

class ShapeObjectsEditor;

class Editor
{
public:
    virtual void OnLBdown(HWND hWnd) = 0;
    virtual void OnLBup(HWND hWnd) = 0;
    virtual void OnMouseMove(HWND hWnd) = 0;
    virtual void OnPaint(HDC hdc) = 0;
    virtual ~Editor() {}
};

class ShapeEditor : public Editor
{
protected:
    ShapeObjectsEditor* owner; 
    static int xStart, yStart, xEnd, yEnd;
    static bool isDrawing;

public:
    ShapeEditor(ShapeObjectsEditor* pOwner) : owner(pOwner) {}

    void OnLBdown(HWND hWnd) override;
    void OnLBup(HWND hWnd) override;
    void OnMouseMove(HWND hWnd) override;
    void OnPaint(HDC hdc) override;
};

class PointEditor : public ShapeEditor
{
public:
    PointEditor(ShapeObjectsEditor* pOwner) : ShapeEditor(pOwner) {}
    void OnLBup(HWND hWnd) override;
    void OnPaint(HDC hdc) override;
};

class LineEditor : public ShapeEditor
{
public:
    LineEditor(ShapeObjectsEditor* pOwner) : ShapeEditor(pOwner) {}
    void OnLBup(HWND hWnd) override;
    void OnPaint(HDC hdc) override;
};

class RectEditor : public ShapeEditor
{
public:
    RectEditor(ShapeObjectsEditor* pOwner) : ShapeEditor(pOwner) {}
    void OnLBup(HWND hWnd) override;
    void OnPaint(HDC hdc) override;
};

class EllipseEditor : public ShapeEditor
{
public:
    EllipseEditor(ShapeObjectsEditor* pOwner) : ShapeEditor(pOwner) {}
    void OnLBup(HWND hWnd) override;
    void OnPaint(HDC hdc) override;
};

class LineWithCirclesEditor : public ShapeEditor
{
public:
    LineWithCirclesEditor(ShapeObjectsEditor* pOwner) : ShapeEditor(pOwner) {}
    void OnLBup(HWND hWnd) override;
    void OnPaint(HDC hdc) override;
};

class CubeFrameEditor : public ShapeEditor
{
public:
    CubeFrameEditor(ShapeObjectsEditor* pOwner) : ShapeEditor(pOwner) {}
    void OnLBup(HWND hWnd) override;
    void OnPaint(HDC hdc) override;
};