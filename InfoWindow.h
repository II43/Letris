//InfoWindow.h
#ifndef __INFOWINDOW_H__
#define __INFOWINDOW_H__


class CSmallWindow  
{
protected:
	int ux,uy,uShape;
	CDC* MainWindowDC;
public:
	void Create(CDC* MainWindowDC,int x,int y,int NextShape,int LastShape);
	void DrawBitmap(int x,int y,int uBitmap);
	void DrawShape(int tBitmap);
};

#endif //__INFOWINDOW_H__