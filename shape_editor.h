#pragma once
#include <windows.h>

class Shape;
class ShapeEditor;

class ShapeObjectsEditor
{
protected:
	Shape** pcshape;
	int capacity;
	int currentIndex;
	ShapeEditor* pse = nullptr;
	int currentTool = 0;
public:
	ShapeObjectsEditor();
	~ShapeObjectsEditor();

	void AddShape(Shape* shape);

	void StartPointEditor();
	void StartLineEditor();
	void StartRectEditor();
	void StartEllipseEditor();
	void StartLineWithCirclesEditor(); 
	void StartCubeFrameEditor();

	void OnLBdown(HWND hWnd);
	void OnLBup(HWND hWnd);
	void OnMouseMove(HWND hWnd);
	void OnPaint(HWND hWnd);

	void OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
};

using MyEditor = ShapeObjectsEditor;