#pragma once
#include <windows.h>

class Shape 
{
protected:
	long xs1 = 0, ys1 = 0, xs2 = 0, ys2 = 0;
public:
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC hdc) = 0;
	virtual ~Shape() {}
};

class PointShape : public Shape
{
public:
	void Show(HDC hdc) override;
};

class LineShape : public virtual Shape
{
public:
	void Show(HDC hdc) override;
};

class RectShape : public virtual Shape
{
protected:
	bool fill = true;   
public:
	void Show(HDC hdc) override;
};

class EllipseShape : public virtual Shape
{
public:
	void Show(HDC hdc) override;
};

class LineWithCirclesShape : public LineShape, public EllipseShape
{
public:
	void Show(HDC hdc) override;
};

class CubeFrameShape : public RectShape, public LineShape
{
public:
	CubeFrameShape() { fill = false; }                
	void Show(HDC hdc) override;
};