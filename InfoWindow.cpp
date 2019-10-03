//InfoWindow.cpp
#include <afxwin.h>

#include "stdafx.h"
#include "InfoWindow.h"
#include "resource.h"

#define EMPTYFIELD 1
#define	STONEDFIELD 0
#define NORMALFIELD 2


void CSmallWindow::Create(CDC* uMainWindowDC,int x,int y,int NextShape,int LastShape)
{
	ux = x; uy = y;
	MainWindowDC = uMainWindowDC;
	MainWindowDC->Draw3dRect(ux,uy,96,120,RGB(60,63,104),RGB(60,63,104));
	uShape = LastShape; DrawShape(EMPTYFIELD);
	uShape = NextShape; DrawShape(NORMALFIELD);
}		  

void CSmallWindow::DrawBitmap(int x,int y,int uBitmap)
{
	CBitmap aBitmap;
	CSize aSize;
	CPoint Point(x,y);
	switch(uBitmap) {
		case 0: {aBitmap.LoadBitmap(IDB_STONEFIELD); break;}
		case 1: {aBitmap.LoadBitmap(IDB_EMPTYFIELD); break;}
		case 2: {aBitmap.LoadBitmap(IDB_NORMALFIELD); break;}
		default: break;
	}
	aSize = aBitmap.GetBitmapDimension();
	MainWindowDC->DrawState(Point,aSize,aBitmap,DST_BITMAP);
}

void CSmallWindow::DrawShape(int tBitmap)
{
	if (uShape == 1) {
		DrawBitmap(ux+28,uy+40,tBitmap);
		DrawBitmap(ux+48,uy+40,tBitmap);
		DrawBitmap(ux+28,uy+60,tBitmap);
		DrawBitmap(ux+48,uy+60,tBitmap);
	}
	if (uShape == 2)  {
		DrawBitmap(ux+38,uy+20,tBitmap);
		DrawBitmap(ux+38,uy+40,tBitmap);
		DrawBitmap(ux+38,uy+60,tBitmap);
		DrawBitmap(ux+38,uy+80,tBitmap);
	}
	if (uShape == 3) {
		DrawBitmap(ux+28,uy+30,tBitmap);
		DrawBitmap(ux+28,uy+50,tBitmap);
		DrawBitmap(ux+28,uy+70,tBitmap);
		DrawBitmap(ux+48,uy+30,tBitmap);
	}
	if (uShape == 4) {
		DrawBitmap(ux+28,uy+30,tBitmap);
		DrawBitmap(ux+48,uy+30,tBitmap);
		DrawBitmap(ux+48,uy+50,tBitmap);
		DrawBitmap(ux+48,uy+70,tBitmap);
	}
	if (uShape == 5) {
		DrawBitmap(ux+18,uy+60,tBitmap);
		DrawBitmap(ux+38,uy+60,tBitmap);
		DrawBitmap(ux+58,uy+60,tBitmap);
		DrawBitmap(ux+38,uy+40,tBitmap);
	}
	if (uShape == 6) {
		DrawBitmap(ux+48,uy+30,tBitmap);
		DrawBitmap(ux+48,uy+50,tBitmap);
		DrawBitmap(ux+28,uy+70,tBitmap);
		DrawBitmap(ux+28,uy+50,tBitmap);
	}
	if (uShape == 7) {
		DrawBitmap(ux+28,uy+30,tBitmap);
		DrawBitmap(ux+28,uy+50,tBitmap);
		DrawBitmap(ux+48,uy+70,tBitmap);
		DrawBitmap(ux+48,uy+50,tBitmap);
	}
}