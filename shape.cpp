#include <cmath>
#include <algorithm>
#include "shape.h"

void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
};

void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, RGB(0, 0, 0));
}

void LineShape::Show(HDC hdc)
{
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
}

void RectShape::Show(HDC hdc)
{
    long dx = labs(xs2 - xs1);
    long dy = labs(ys2 - ys1);

    HBRUSH hBrush = fill ? CreateSolidBrush(RGB(255, 192, 203))
        : (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    Rectangle(hdc, xs1 - dx, ys1 - dy, xs1 + dx, ys1 + dy);

    SelectObject(hdc, hOldBrush);
    if (fill) DeleteObject(hBrush);   
}

void EllipseShape::Show(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, xs1, ys1, xs2, ys2);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void LineWithCirclesShape::Show(HDC hdc)
{
	const long r = 5;
	long x1 = xs1, y1 = ys1, x2 = xs2, y2 = ys2;

	LineShape::Show(hdc);

	xs1 = x1 - r; ys1 = y1 - r; xs2 = x1 + r; ys2 = y1 + r;
	EllipseShape::Show(hdc);
	xs1 = x2 - r; ys1 = y2 - r; xs2 = x2 + r; ys2 = y2 + r;
	EllipseShape::Show(hdc);

	xs1 = x1; ys1 = y1; xs2 = x2; ys2 = y2;
}

void CubeFrameShape::Show(HDC hdc)
{
	long x = xs1, y = ys1, x2 = xs2, y2 = ys2;
	long dx = labs(x2 - x), dy = labs(y2 - y);
	long s = 30;                                     
	if (dx < s) s = dx;
	if (dy < s) s = dy;
	s -= s % 2;
	long l = x - dx, r = x + dx, t = y - dy, b = y + dy;

	xs1 = l;     ys1 = b;     xs2 = l + s; ys2 = b - s; LineShape::Show(hdc);
	xs1 = l;     ys1 = t + s; xs2 = l + s; ys2 = t;     LineShape::Show(hdc);
	xs1 = r - s; ys1 = t + s; xs2 = r;     ys2 = t;     LineShape::Show(hdc);
	xs1 = r - s; ys1 = b;     xs2 = r;     ys2 = b - s; LineShape::Show(hdc);

	long hw = dx - s / 2, hh = dy - s / 2;
	xs1 = x - s / 2; ys1 = y + s / 2; xs2 = xs1 + hw; ys2 = ys1 + hh;
	RectShape::Show(hdc);                             
	xs1 = x + s / 2; ys1 = y - s / 2; xs2 = xs1 + hw; ys2 = ys1 + hh;
	RectShape::Show(hdc);                              

	xs1 = x; ys1 = y; xs2 = x2; ys2 = y2;           
}