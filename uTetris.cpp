#include "stdafx.h"
#include "resource.h"
#include <windows.h>

#include <afxwin.h>
#include <math.h>
#include <malloc.h>
#include <afxdlgs.h>

#include <stdlib.h>
#include <time.h>

#include "uTetris.h"
#include "InfoWindow.h"
#include "TetrisGame.h"
#include "uOptions.h"
#include "uSave.h"
#include "uLoad.h"


#define EMPTYFIELD 1
#define	STONEDFIELD 0
#define NORMALFIELD 2

CTheApp NEAR theApp;

//Beginning
CMainWindow::CMainWindow()
{
	//Window
	CRect MainWindowRect(20,20,454,548);
	Create(NULL,_T("uTetris 1.0"),WS_OVERLAPPEDWINDOW,MainWindowRect,NULL,MAKEINTRESOURCE(IDM_MENU),0,NULL);
	LoadAccelTable(MAKEINTRESOURCE(IDA_TABLE));
	//LoadFrame(IDR_MAINFRAME);
	//Tetris
	NewGame();
	ActivateTimer();
	
}

void CMainWindow::OnPaint()
{
	CRect rect;
	GetClientRect(rect);
	CPaintDC dc(this);
	DrawWindow();
}

void CMainWindow::DrawWindow()
{
    OnSolveField();
	DrawWindowStructure();
	DrawNextShape();
	DrawInfo();
	DrawHighScore();
}



//Dialogs
void CMainWindow::OnAbout()
{
	DeActivateTimer();
	CDialog about(IDD_ABOUTBOX);
	about.DoModal();
	ActivateTimer();
}

void CMainWindow::OnOptions()
{
	DeActivateTimer();
	uOptions MyOptions;
	MyOptions.DoModal();
	FallingSpeed = MyOptions.Speed;
	nextfallShape = MyOptions.Shape;
	DrawNextShape();
	ActivateTimer();
}
   


//Field

void CMainWindow::OnSolveField() {
	Shape MyShape;
	MyShape.x = fallx;
	MyShape.y = fally;
	MyShape.Structure = fallShape;
	IncludeTetrisShape(MyShape);
	DrawTetrisField(20,20,20,TetrisField);
}

void CMainWindow::CreateField(int dx,int dy)
{
	int k1,k2,kvalue;
	int p1,p2,px,py;
	int Field[14][22];
	int XCorField[4][20];
	int YCorField[4][20];
	int APos;
	/////////////////////////Defining
	XCorField[0][0]=1;XCorField[0][1]=1;XCorField[0][2]=0;
	XCorField[1][0]=1;XCorField[1][1]=2;XCorField[1][2]=0;
	XCorField[2][0]=1;XCorField[2][1]=0;
	XCorField[3][0]=1;XCorField[3][1]=2;XCorField[3][2]=0;
	YCorField[0][0]=2;YCorField[0][1]=1;YCorField[0][2]=0;
	YCorField[1][0]=1;YCorField[1][1]=0;
	YCorField[2][0]=1;YCorField[2][1]=1;YCorField[2][2]=0;
	YCorField[3][0]=2;YCorField[3][1]=1;YCorField[3][2]=0;
	for(px=0;px<dx;px++) {
		for(py=0;py<dy;py++) Field[px][py]=1;
	}
	/////////////////////////Algorithm
	for(k1=0;k1<dx;k1++) {
		kvalue = 0;
		for(k2=0;k2<20;k2++) {
			if (XCorField[k1][k2] == 0) {
				kvalue = kvalue+k2;
				break;
			}
			kvalue = kvalue + XCorField[k1][k2];
		}
		if (kvalue >= dx) {
			APos=0;
			for(p1=0;p1<20;p1++) {
				if(XCorField[k1][p1] == 0) {
					APos = APos+1;
					break;
				}
				for(p2=0;p2<XCorField[k1][p1];p2++) {
					APos = APos + p2;
					Field[k1][APos]=2;
				}
			}
		}
		DrawTetrisField(20,20,20,Field);
	
	}
	
	////Drawing
	
}

/////Tetris/////

//Drawing
void CMainWindow::DrawWindowStructure()
{
	CDC* MainWindowDC;
	MainWindowDC = GetDC();
	//MainWindowDC->SetBkMode(TRANSPARENT);
    if (Drawing) {
		CBitmap bLogo;
		CSize bLogoSize;
		CPoint Point(331,331);
		bLogo.LoadBitmap(IDB_LOGO);
		bLogoSize = bLogo.GetBitmapDimension();
		MainWindowDC->FillSolidRect(0,0,434,528,RGB(255,255,255));
		MainWindowDC->Draw3dRect(18,18,284,444,RGB(60,63,104),RGB(60,63,104));
		MainWindowDC->Draw3dRect(16,16,288,448,RGB(60,63,104),RGB(60,63,104));
		MainWindowDC->Draw3dRect(306,18,100,300,RGB(60,63,104),RGB(60,63,104));
		MainWindowDC->Draw3dRect(304,16,104,304,RGB(60,63,104),RGB(60,63,104));
		MainWindowDC->SetTextAlign(TA_CENTER);
		MainWindowDC->SetTextColor(RGB(68,71,212));
		MainWindowDC->SetBkColor(RGB(255,255,255));
		MainWindowDC->TextOut(356,30,"Lines");
		MainWindowDC->TextOut(356,70,"Score");
		MainWindowDC->TextOut(356,110,"Speed");
		MainWindowDC->DrawState(Point,bLogoSize,bLogo,DST_BITMAP);
	}
	ReleaseDC(MainWindowDC);
}

void CMainWindow::DrawInfo() 
{
	CString uLines,uScore,uSpeed;
	uLines.Format("    %d    ",NumberofDestroyedLines);
	uScore.Format("    %d    ",Score);
	uSpeed.Format("    %d    ",FallingSpeed);
	CDC* MainWindowDC;
	MainWindowDC = GetDC();
	MainWindowDC->SetTextAlign(TA_CENTER);
	if (Drawing) {
		MainWindowDC->TextOut(356,48,uLines);
		MainWindowDC->TextOut(356,88,uScore);
		MainWindowDC->TextOut(356,128,uSpeed);
	}
	ReleaseDC(MainWindowDC);
}

void CMainWindow::DrawNextShape()
{
	CDC* MyDC;
	MyDC = GetDC();
	CSmallWindow MySmallWindow;
	if (Drawing) {
		MySmallWindow.Create(MyDC,308,170,ReturnShape(nextfallShape),ReturnShape(fallShape));
	}
	ReleaseDC(MyDC);
}

void CMainWindow::DrawHighScore()
{
	CDC *MyDC;
	MyDC = GetDC();
	CTetrisGame MyGame;
	CString HighScore;
	if ((MyGame.LoadHighList) == 0) {
		HighScore.Format("%s: %d  (%d)",MyGame.uHighPlayerName,MyGame.uHighScore,MyGame.uHighLines);
		MyDC->TextOut(0,0,HighScore);
	}
	ReleaseDC(MyDC);
}


void CMainWindow::DrawTetrisField(int ux,int uy,int usize,int uField[14][22]) {
	CDC* MyDC;
	CBitmap StoneField,NormalField,EmptyField;
	CSize StoneFieldSize,NormalFieldSize,EmptyFieldSize;
	CPoint Point,FieldPoint;
	FieldPoint.x = ux;
	FieldPoint.y = uy;
	StoneField.LoadBitmap(IDB_STONEFIELD);
	NormalField.LoadBitmap(IDB_NORMALFIELD);
	EmptyField.LoadBitmap(IDB_EMPTYFIELD);
	StoneFieldSize = StoneField.GetBitmapDimension();
	NormalFieldSize = NormalField.GetBitmapDimension();
	EmptyFieldSize = EmptyField.GetBitmapDimension();
	int CorX,CorY;
	int px,py;
	MyDC = GetDC();
	/*BackGround OFF
	if (BkValue != 0) {
		CBitmap	BackGround;
		CSize BackGroundSize;
		BackGroundSize = BackGround.GetBitmapDimension();
		MyDC->DrawState(FieldPoint,BackGroundSize,BackGround,DST_BITMAP);
	}*/
	//*MyBrush.CreateSolidBrush(RGB(255,255,255));
	if (Drawing) {
		for(px=0;px<14;px++) {
			for(py=0;py<22;py++) {
				CorX = ux+usize*px;
				CorY = uy+usize*py;
				Point.x = CorX;
				Point.y = CorY;
				if (uField[px][py] == 0) MyDC->DrawState(Point,StoneFieldSize,StoneField,DST_BITMAP);
				if (uField[px][py] == 1) MyDC->DrawState(Point,EmptyFieldSize,EmptyField,DST_BITMAP);
				if (uField[px][py] == 2) MyDC->DrawState(Point,NormalFieldSize,NormalField,DST_BITMAP);
			}
		}
	}
	ReleaseDC(MyDC);

}

void CMainWindow::IncludeTetrisShape(Shape cShape)
{
	int AShape,ADirection;
	AShape = ReturnShape(cShape.Structure);
	ADirection = ReturnDirection(cShape.Structure);
	if (cShape.x >= 0 && cShape.x < 13) {
		if (cShape.y >= 0 && cShape.y < 22) {
			DrawTetrisShape(cShape.x,cShape.y,AShape,ADirection);	
		
		}
	}

}

void CMainWindow::OnDrawTetrisShape(int x,int y,int Shape,int Direction,int Value) {
	switch(Shape) {
	// **
	// **
	case 1: {
		TetrisField[x][y] = Value; TetrisField[x+1][y] = Value;
		TetrisField[x][y+1] = Value; TetrisField[x+1][y+1] = Value;
		break;}
	// ****
	case 2: {
		switch(Direction) {
		case 1: {
			TetrisField[x][y] = Value; TetrisField[x+1][y] = Value;
			TetrisField[x+2][y] = Value; TetrisField[x+3][y] = Value;
			break;}
		case 2:	{
			TetrisField[x][y] = Value; TetrisField[x][y+1] = Value;
			TetrisField[x][y+2] = Value; TetrisField[x][y+3] = Value;
			break;}
		default: break;
		}
		break;
	}
	// ***
	// 	 *
	case 3: {
		switch(Direction) {
		case 1: {
			TetrisField[x][y] = Value; TetrisField[x+1][y] = Value;
			TetrisField[x][y+1] = Value; TetrisField[x][y+2] = Value;
			break;}
		case 2: {
			TetrisField[x][y] = Value; TetrisField[x+1][y] = Value;
			TetrisField[x+2][y] = Value; TetrisField[x+2][y+1] = Value;
			break;}
		case 3: {
			TetrisField[x+1][y] = Value; TetrisField[x+1][y+1] = Value;
			TetrisField[x+1][y+2] = Value; TetrisField[x][y+2] = Value;
			break;}
		case 4: {
			TetrisField[x][y] = Value; TetrisField[x][y+1] = Value;
			TetrisField[x+1][y+1] = Value; TetrisField[x+2][y+1] = Value;
			break;}
		default: break;
		}
		break;
	}
	//	 *
	// ***
	case 4: {
		switch(Direction) {
		case 1: {
			TetrisField[x][y] = Value; TetrisField[x+1][y] = Value;
			TetrisField[x+1][y+1] = Value; TetrisField[x+1][y+2] = Value;
			break;}
		case 2: {
			TetrisField[x][y+1] = Value; TetrisField[x+1][y+1] = Value;
			TetrisField[x+2][y+1] = Value; TetrisField[x+2][y] = Value;
			break;}
		case 3: {
			TetrisField[x][y] = Value; TetrisField[x][y+1] = Value;
			TetrisField[x][y+2] = Value; TetrisField[x+1][y+2] = Value;
			break;}
		case 4: {
			TetrisField[x][y] = Value; TetrisField[x+1][y] = Value;
			TetrisField[x+2][y] = Value; TetrisField[x][y+1] = Value;
			break;}
		default: break;
		}
		break;
	}
	//	*
	// ***
	case 5: {
		switch(Direction) {
		case 1: {
			TetrisField[x+1][y] = Value; TetrisField[x][y+1] = Value;
			TetrisField[x+1][y+1] = Value; TetrisField[x+2][y+1] = Value;
			break;}
		case 2: {
			TetrisField[x][y] = Value; TetrisField[x][y+1] = Value;
			TetrisField[x][y+2] = Value; TetrisField[x+1][y+1] = Value;
			break;}
		case 3: {
			TetrisField[x][y] = Value; TetrisField[x+1][y] = Value;
			TetrisField[x+2][y] = Value; TetrisField[x+1][y+1] = Value;
			break;}
		case 4: {
			TetrisField[x+1][y] = Value; TetrisField[x+1][y+1] = Value;
			TetrisField[x+1][y+2] = Value; TetrisField[x][y+1] = Value;
			break;}
		default: break;
		}
		break;
	}
	// **
	// 	**
	case 6: {
		switch(Direction) {
		case 1: {
			TetrisField[x][y] = Value; TetrisField[x+1][y] = Value;
			TetrisField[x+1][y+1] = Value; TetrisField[x+2][y+1] = Value;
			break;}
		case 2: {
			TetrisField[x+1][y] = Value; TetrisField[x+1][y+1] = Value;
			TetrisField[x][y+1] = Value; TetrisField[x][y+2] = Value;
			break;}
		default: break;
		}
		break;
	}
	//  **
	// **
	case 7: {
		switch(Direction) {
		case 1: {
			TetrisField[x][y+1] = Value; TetrisField[x+1][y+1] = Value;
			TetrisField[x+1][y] = Value; TetrisField[x+2][y] = Value;
			break;}
		case 2: {
			TetrisField[x][y] = Value; TetrisField[x][y+1] = Value;
			TetrisField[x+1][y+1] = Value; TetrisField[x+1][y+2] = Value;
			break;}
		default: break;
		}
		break;
	}

	//End of Shapes
	default: break;
	}

	
		
}

void CMainWindow::DrawTetrisShape(int x,int y,int Shape,int Direction) 
{
	OnDrawTetrisShape(x,y,Shape,Direction,NORMALFIELD);
}

void CMainWindow::DestroyTetrisShape(int x,int y,int Shape,int Direction) 
{
	OnDrawTetrisShape(x,y,Shape,Direction,EMPTYFIELD);	
}

void CMainWindow::StoneTetrisShape(int x,int y,int Shape,int Direction) 
{
	OnDrawTetrisShape(x,y,Shape,Direction,STONEDFIELD);	
}



int CMainWindow::ReturnShape(WORD uShape)
{
	int Shape;
	if (uShape >= 0x1000 && uShape < 0x2000) Shape = 1;
	if (uShape >= 0x2000 && uShape < 0x3000) Shape = 2;
	if (uShape >= 0x3000 && uShape < 0x4000) Shape = 3;
	if (uShape >= 0x4000 && uShape < 0x5000) Shape = 4;
	if (uShape >= 0x5000 && uShape < 0x6000) Shape = 5;
	if (uShape >= 0x6000 && uShape < 0x7000) Shape = 6;
	if (uShape >= 0x7000 && uShape < 0x8000) Shape = 7;
	return Shape;

}

int CMainWindow::ReturnDirection(WORD uShape)
{
	int Direction;
	int Increase;
	for (Increase=0;Increase<=10;Increase++) {
		if (uShape >= (Increase*0x1000)+0x0100 && uShape < (Increase*0x1000)+0x0200) Direction = 1;
		if (uShape >= (Increase*0x1000)+0x0200 && uShape < (Increase*0x1000)+0x0300) Direction = 2;
		if (uShape >= (Increase*0x1000)+0x0300 && uShape < (Increase*0x1000)+0x0400) Direction = 3;
		if (uShape >= (Increase*0x1000)+0x0400 && uShape < (Increase*0x1000)+0x0500) Direction = 4;

	}
	return Direction;
}

//Moving

void CMainWindow::MoveItRight() {
	int oldfallx,Shape,Direction;
	Shape = ReturnShape(fallShape);
	Direction = ReturnDirection(fallShape);
	oldfallx = fallx;
	DestroyTetrisShape(fallx,fally,Shape,Direction);
	if ((CheckFieldRight()) == 0) fallx = fallx+1;	//Check if it is possible
	DrawTetrisShape(fallx,fally,Shape,Direction);
	DrawTetrisField(20,20,20,TetrisField);

}

void CMainWindow::MoveItLeft() {
	int oldfallx;
	oldfallx = fallx;
	DestroyTetrisShape(fallx,fally,ReturnShape(fallShape),ReturnDirection(fallShape));
	if ((CheckFieldLeft()) == 0) fallx = fallx - 1;	//Check if it is possible
	DrawTetrisShape(fallx,fally,ReturnShape(fallShape),ReturnDirection(fallShape));
	DrawTetrisField(20,20,20,TetrisField);
}

void CMainWindow::MoveItDown() {
	int Shape,Direction;
	WORD RandomShape;
	//Generate Random Shape//
	RandomShape = GenerateRandomShape();
	if (RandomShape < 0x1100 || RandomShape > 0x8000) RandomShape = 0x1100;
	Shape = ReturnShape(fallShape);
	Direction = ReturnDirection(fallShape);
	int oldfally;
	oldfally = fally;
	DestroyTetrisShape(fallx,fally,Shape,Direction);
	if ((CheckFieldUnder()) != 0) {
		StoneTetrisShape(fallx,fally,Shape,Direction);
		ControlField();
		lastfallShape = fallShape;
		fallShape = nextfallShape;
		nextfallShape = RandomShape;
		DrawNextShape();
		fallx = 7; fally = 0; 
		if (fallShape >= 0x8000) fallShape = 0x1100;
	}
	if((CheckFieldUnder()) == 0) fally = fally + 1;
	DrawTetrisShape(fallx,fally,ReturnShape(fallShape),ReturnDirection(fallShape));
	DrawTetrisField(20,20,20,TetrisField);

}

void CMainWindow::RotateIt() {
	int Shape,Direction;
	WORD oldShape;
	oldShape = fallShape;
	Shape = ReturnShape(fallShape);
	Direction = ReturnDirection(fallShape);
	DestroyTetrisShape(fallx,fally,Shape,Direction);
	if (Shape == 2) {
		if (Direction == 1 && (CheckFieldRotation()) == 0 && fally < 19) fallShape = fallShape+0x0100;
		if (Direction == 2 && fallx < 11 && (CheckFieldRotation()) == 0) fallShape = fallShape-0x0100;
		if (fallShape >= 0x2300 || fallShape < 0x2100) fallShape = oldShape;
	}
	if (Shape == 3) {
		if ((CheckFieldRotation()) == 0) fallShape = fallShape+0x0100;
		if (Direction == 1 && fallx >= 12) fallShape = oldShape;
		if (Direction == 2 && fally >= 20) fallShape = oldShape;
		if (Direction == 3 && fallx >= 12) fallShape = oldShape;
		if (Direction == 4 && fally >= 20) fallShape = oldShape;
		if (fallShape >= 0x3500 && fallShape != oldShape) fallShape = 0x3100;
	}
	if (Shape == 4) {
		if ((CheckFieldRotation()) == 0) fallShape = fallShape+0x0100;
		if (Direction == 1 && fallx >= 12) fallShape = oldShape;
		if (Direction == 2 && fally >= 20) fallShape = oldShape;
		if (Direction == 3 && fallx >= 12) fallShape = oldShape;
		if (Direction == 4 && fally >= 20) fallShape = oldShape;
		if (fallShape >= 0x4500 && fallShape != oldShape) fallShape = 0x4100;
	}
	
	if (Shape == 5) {
		if ((CheckFieldRotation()) == 0) fallShape = fallShape+0x0100;
		if (Direction == 1 && fally >= 20) fallShape = oldShape;
		if (Direction == 2 && fallx >= 12) fallShape = oldShape;
		if (Direction == 3 && fally >= 20) fallShape = oldShape;
		if (Direction == 4 && fallx >= 12) fallShape = oldShape;
		if (fallShape >= 0x5500 && fallShape != oldShape) fallShape = 0x5100;
	}
	if (Shape == 6) {
		if (Direction == 1 && (CheckFieldRotation()) == 0 && fally < 20) fallShape = fallShape+0x0100;
		if (Direction == 2 && fallx < 12 && (CheckFieldRotation()) == 0) fallShape = fallShape-0x0100;
		if (fallShape >= 0x6300 || fallShape < 0x6100) fallShape = oldShape;
	}
	if (Shape == 7) {
		if (Direction == 1 && (CheckFieldRotation()) == 0) fallShape = fallShape+0x0100;
		if (Direction == 2 && fallx < 12 && (CheckFieldRotation()) == 0 && fally < 20) fallShape = fallShape-0x0100;
		if (fallShape >= 0x7300 || fallShape < 0x7100) fallShape = oldShape;
	}
	Shape = ReturnShape(fallShape);
	Direction = ReturnDirection(fallShape);
	DrawTetrisShape(fallx,fally,Shape,Direction);
	DrawTetrisField(20,20,20,TetrisField);
}

//Checking Fields
int CMainWindow::CheckFieldUnder()
{
	int Shape,Direction;
	Shape = ReturnShape(fallShape);
	Direction = ReturnDirection(fallShape);
	if (Shape == 1) {
		if (TetrisField[fallx][fally+2]   == 0 || 
			TetrisField[fallx+1][fally+2] == 0 ||
			fally+2 >= 22) return 1;
	}
	if (Shape == 2) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				TetrisField[fallx+3][fally+1] == 0 ||
				fally+1 >= 22) return 1;
		}
		if (Direction == 2) {	
			if (TetrisField[fallx][fally+4] == 0 ||
				fally+4 >= 22) return 1;
		}	
	}
	if (Shape == 3) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+3]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				fally+3 >= 22) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fally+2 >= 22) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx][fally+3]   == 0 ||
				TetrisField[fallx+1][fally+3] == 0 ||
				fally+3 >= 22) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx][fally+2]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fally+2 >= 22) return 1;
		}
	
	}
	if (Shape == 4) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+1][fally+3] == 0 ||
				fally+3 >= 22) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fally+2 >= 22) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx][fally+3]   == 0 ||
				TetrisField[fallx+1][fally+3] == 0 ||
				fally+3 >= 22) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx][fally+2]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				fally+2 >= 22) return 1;
		}
	
	}	
	if (Shape == 5) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+2]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fally+2 >= 22) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx][fally+3]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				fally+3 >= 22) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				fally+2 >= 22) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx][fally+2]   == 0 ||
				TetrisField[fallx+1][fally+3] == 0 ||
				fally+3 >= 22) return 1;
		}
	}	
	if (Shape == 6) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fally+2 >= 22) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx][fally+3]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				fally+3 >= 22) return 1;
		}
	}
	if (Shape == 7) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+2]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				fally+2 >= 22) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx][fally+2]   == 0 ||
				TetrisField[fallx+1][fally+3] == 0 ||
				fally+3 >= 22) return 1;
		}
	}


	return 0;	
}

int CMainWindow::CheckFieldLeft() 
{
	int Shape,Direction;
	Shape = ReturnShape(fallShape);
	Direction = ReturnDirection(fallShape);
	if (Shape == 1) {
		if (TetrisField[fallx-1][fally]   == 0 ||
			TetrisField[fallx-1][fally+1] == 0 ||
			fallx <= 0) return 1;
	}
	if (Shape == 2) {
		if (Direction == 1) {
			if (TetrisField[fallx-1][fally] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 2) {	
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				TetrisField[fallx-1][fally+2] == 0 ||
				TetrisField[fallx-1][fally+3] == 0 ||
				fallx <= 0) return 1;
		}	
	}
	if (Shape == 3) {
		if (Direction == 1) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				TetrisField[fallx-1][fally+2] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx-1][fally+2] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				fallx <= 0) return 1;
		}
	
	}
	if (Shape == 4) {
		if (Direction == 1) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx-1][fally+2] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				TetrisField[fallx-1][fally+2] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				fallx <= 0) return 1;
		}
	
	}	
	if (Shape == 5) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				TetrisField[fallx-1][fally+2] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx-1][fally] == 0 ||
				TetrisField[fallx][fally+1] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				TetrisField[fallx][fally+2]   == 0 ||
				fallx <= 0) return 1;
		}
	}	
	if (Shape == 6) {
		if (Direction == 1) {
			if (TetrisField[fallx-1][fally] == 0 ||
				TetrisField[fallx][fally+1] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				TetrisField[fallx-1][fally+2] == 0 ||
				fallx <= 0) return 1;
		}
	}
	if (Shape == 7) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				fallx <= 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx-1][fally]   == 0 ||
				TetrisField[fallx-1][fally+1] == 0 ||
				TetrisField[fallx][fally+2] == 0 ||
				fallx <= 0) return 1;
		}
	}
	return 0;	
}

int CMainWindow::CheckFieldRight() 
{
	int Shape,Direction;
	Shape = ReturnShape(fallShape);
	Direction = ReturnDirection(fallShape);
	if (Shape == 1) {
		if (TetrisField[fallx+2][fally]   == 0 ||
			TetrisField[fallx+2][fally+1] == 0 ||
			fallx >= 12) return 1;	
	}

	if (Shape == 2) {
		if (Direction == 1) {
			if (TetrisField[fallx+4][fally]   == 0 ||
				fallx >= 10) return 1;
		}
		if (Direction == 2) {	
			if (TetrisField[fallx+1][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				TetrisField[fallx+1][fally+3] == 0 ||
				fallx >= 13) return 1;
		}	
	}
	if (Shape == 3) {
		if (Direction == 1) {
			if (TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				fallx >= 12) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx+3][fally]   == 0 ||
				TetrisField[fallx+3][fally+1] == 0 ||
				fallx >= 11) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx+1][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fallx >= 12) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx+3][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				fallx >= 11) return 1;
		}
	
	}
	if (Shape == 4) {
		if (Direction == 1) {
			if (TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fallx >= 12) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx+3][fally]   == 0 ||
				TetrisField[fallx+3][fally+1] == 0 ||
				fallx >= 11) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx+1][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fallx >= 12) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx+3][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				fallx >= 11) return 1;
		}
	
	}	
	if (Shape == 5) {
		if (Direction == 1) {
			if (TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+3][fally+1] == 0 ||
				fallx >= 11) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx+1][fally]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				fallx >= 12) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx+3][fally]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				fallx >= 11) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fallx >= 12) return 1;
		}
	}	
	if (Shape == 6) {
		if (Direction == 1) {
			if (TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+3][fally+1] == 0 ||
				fallx >= 11) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				fallx >= 12) return 1;
		}
	}
	if (Shape == 7) {
		if (Direction == 1) {
			if (TetrisField[fallx+3][fally]     == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				fallx >= 11) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx+1][fally]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0 ||
				TetrisField[fallx+2][fally+2] == 0 ||
				fallx >= 12) return 1;
		}
	}
	return 0;	
}

int CMainWindow::CheckFieldRotation()
{
	int Shape,Direction;
	Shape = ReturnShape(fallShape);
	Direction = ReturnDirection(fallShape);
	if (Shape == 2) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+1] == 0 ||
				TetrisField[fallx][fally+2] == 0 ||
				TetrisField[fallx][fally+3] == 0) return 1;
		}
		if (Direction == 2) {	
			if (TetrisField[fallx+1][fally] == 0 ||
				TetrisField[fallx+2][fally] == 0 ||
				TetrisField[fallx+3][fally] == 0) return 1;
		}	
	}
	if (Shape == 3) {
		if (Direction == 1) {
			if (TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+1][fally+2] == 0 ||
				TetrisField[fallx][fally+2]   == 0) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+2][fally+1] == 0) return 1;
		}
	
	}
	if (Shape == 4) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+2][fally+1] == 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx][fally+2]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx+1][fally] == 0 ||
				TetrisField[fallx+2][fally] == 0) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+2][fally+1] == 0) return 1;
		}
	
	}	
	if (Shape == 5) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally]   == 0 ||
				TetrisField[fallx][fally+2] == 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx+1][fally] == 0 ||
				TetrisField[fallx+2][fally] == 0) return 1;
		}
		if (Direction == 3) {
			if (TetrisField[fallx][fally+1]   == 0 ||
				TetrisField[fallx+1][fally+2] == 0) return 1;
		}
		if (Direction == 4) {
			if (TetrisField[fallx+2][fally+1] == 0) return 1;
		}
	}	
	if (Shape == 6) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally+1] == 0 ||
				TetrisField[fallx][fally+2] == 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx+2][fally+1] == 0) return 1;
		}
	}
	if (Shape == 7) {
		if (Direction == 1) {
			if (TetrisField[fallx][fally]     == 0 ||
				TetrisField[fallx+1][fally+1] == 0 ||
				TetrisField[fallx+1][fally+2] == 0) return 1;
		}
		if (Direction == 2) {
			if (TetrisField[fallx+1][fally]   == 0 ||
				TetrisField[fallx+2][fally]   == 0 ||
				TetrisField[fallx+1][fally+1] == 0) return 1;
		}
	}
	return 0;	


}

//Matrix Solution
int CMainWindow::PreMoveLeft() 
{
	return 0;
}

int CMainWindow::PreMoveRight()
{
	return 0;
}

int CMainWindow::PreRotate()
{
	return 0;
}

void CMainWindow::Zkouska()
{
   	WORD Shape;
	int IncreaseX,IncreaseY,Bit;
	int Increase = 0;
	CDC* MyDC;
	CShape TryShape;
	CBitmap MyBitmap,OtherBitmap; 
	MyBitmap.LoadBitmap(IDB_NORMALFIELD);
	OtherBitmap.LoadBitmap(IDB_EMPTYFIELD);
	CSize MySize = MyBitmap.GetBitmapDimension();
	CSize OtherSize = OtherBitmap.GetBitmapDimension();
	CPoint MyPoint;
	MyDC = GetDC();
	Shape = TryShape.LoadShape(TryX,TryY);
	//////
	
	for(IncreaseX=0;IncreaseX<4;IncreaseX++) {
		for(IncreaseY=0;IncreaseY<4;IncreaseY++) {
			Bit = ((Shape >> Increase) & 1);
			MyPoint.x = 420+IncreaseY*20;
			MyPoint.y = 20+IncreaseX*20;
			if (Bit == 1) MyDC->DrawState(MyPoint,MySize,MyBitmap,DST_BITMAP);
			if (Bit == 0) MyDC->DrawState(MyPoint,OtherSize,OtherBitmap,DST_BITMAP);
			Increase++;
		}
	}
	TryY++;
	if (TryY > 3) {TryY =  0; TryX++;}
}







//Keyboard
void CMainWindow::OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags)
{
	if (nChar == 0x25) MoveItLeft();     //Left Array is pressed
	if (nChar == 0x27) MoveItRight();	 //Right Array is pressed
	if (nChar == 0x28) MoveItDown();     //Down Array is pressed
	if (nChar == 0x20) RotateIt();       //Space is pressed
	if (nChar == 0x11) Zkouska();
}

//Timer
void CMainWindow::OnTimer(UINT nIDEvent) 
{
	MoveItDown();
}

void CMainWindow::ActivateTimer() 
{
	SetTimer(1,FallingSpeed,NULL);
}

void CMainWindow::DeActivateTimer()
{
	KillTimer(1);
}

//Generation of Random Shape
WORD CMainWindow::GenerateRandomShape()
{
  	
	int Increase;
	WORD Shape,RandomShapeValue = 0x0000;
	srand((unsigned)time(NULL));
	for(Increase=0;Increase<2;Increase++) {	
		RandomShapeValue = RandomShapeValue+rand();
	}			 
	////////////
	//for (Increase=0;Increase<16;Increase++) {
	if (RandomShapeValue >= 0x1000 && RandomShapeValue < 0x2000 ||
		RandomShapeValue >= 0x8000 && RandomShapeValue < 0x9000) Shape = 0x1100;
	if (RandomShapeValue >= 0x2000 && RandomShapeValue < 0x3000 ||
		RandomShapeValue >= 0x9000 && RandomShapeValue < 0xA000) Shape = 0x2100;
	if (RandomShapeValue >= 0x3000 && RandomShapeValue < 0x4000 ||
		RandomShapeValue >= 0xA000 && RandomShapeValue < 0xB000) Shape = 0x3100;
	if (RandomShapeValue >= 0x4000 && RandomShapeValue < 0x5000 ||
		RandomShapeValue >= 0xB000 && RandomShapeValue < 0xC000) Shape = 0x4100;
	if (RandomShapeValue >= 0x5000 && RandomShapeValue < 0x6000 ||
		RandomShapeValue >= 0xC000 && RandomShapeValue < 0xD000) Shape = 0x5100;
	if (RandomShapeValue >= 0x6000 && RandomShapeValue < 0x7000 ||
		RandomShapeValue >= 0xD000 && RandomShapeValue < 0xE000) Shape = 0x6100;
	if (RandomShapeValue >= 0x7000 && RandomShapeValue < 0x8000 ||
		RandomShapeValue >= 0xE000 && RandomShapeValue < 0xF000) Shape = 0x7100;
	if (RandomShapeValue >= 0xF000) Shape = 0x2100;
	//////////////
	return Shape;
}

void CMainWindow::ControlField()
{
	int px,py,ControlValue=0,NumberofLines = 0;
	for(py=0;py<22;py++) {
		for(px=0;px<14;px++) {
			if (TetrisField[px][py] == 0) ControlValue++;
		}
		if (ControlValue >= 14) {
			DestroyLine(py); 
			NumberofDestroyedLines++; 
			NumberofLines++;
			
		}
		if (ControlValue > 0 && py == 0) GameOver();
		//if (py = 0 && ControlValue > 0) GameOver();
		ControlValue = 0;
	}
	if (NumberofLines > 0) {
		Score = Score + (NumberofLines*10)+(NumberofLines-1)*10;
		FallingSpeed = 600-(Score/1000)*50;
		ActivateTimer();
		DrawInfo();
	}
}

void CMainWindow::DestroyLine(int uLine)
{
	int px;
	for(uLine;uLine>= 0;uLine--) {
		for(px=0;px<14;px++) {
			if (uLine != 0) TetrisField[px][uLine] = TetrisField[px][uLine-1];
			if (uLine == 0) TetrisField[px][uLine] = 1;
		}
	}
}

//Game
void CMainWindow::GameOver()
{
	CDC* MyDC;
	MyDC= GetDC();
	DeActivateTimer();
	CBitmap bGameOver;
	CSize bGameOverSize;
	bGameOver.LoadBitmap(IDB_GAMEOVER);
	bGameOverSize = bGameOver.GetBitmapDimension();
	CPoint Point(65,172);
	MyDC->DrawState(Point,bGameOverSize,bGameOver,DST_BITMAP);
	Drawing = FALSE;
	////////
	CTetrisGame MyGame;
	MyGame.SaveHighList(Score,NumberofDestroyedLines,"Lukas");
	ReleaseDC(MyDC);
}

void CMainWindow::NewGame()
{
	int px,py;
	for (px=0;px<14;px++) {
		for (py=0;py<22;py++) TetrisField[px][py] = 1;
	}
	fallShape = GenerateRandomShape();
	nextfallShape = GenerateRandomShape();
	fallx = 7; fally = 0;
	FallingSpeed = 500; NumberofDestroyedLines = 0; Score = 0;
	MaxX = 14; MaxY = 22; TryX = 0; TryY = 0;
	ActivateTimer();
	Drawing = TRUE; DrawWindow();
}

void CMainWindow::LoadIt()
{
	int px,py;
	CTetrisGame LoadGame;
	uLoad MyLoadDialog;
	DeActivateTimer();
	if ((MyLoadDialog.DoModal()) == IDOK) {
		LoadGame.LoadFile(MyLoadDialog.FileName);
		FallingSpeed = LoadGame.uFallingSpeed;
		Score = LoadGame.uScore;
		NumberofDestroyedLines = LoadGame.uLines;
		fallx = LoadGame.uFallX;
		fally = LoadGame.uFallY;
		fallShape = LoadGame.uFallShape;
		nextfallShape = LoadGame.uNextFallShape;
		for (px=0;px<14;px++) {
			for (py=0;py<22;py++) TetrisField[px][py] = LoadGame.uTetrisField[px][py];
		}
		DrawWindow();
	}
	ActivateTimer();
}

void CMainWindow::SaveIt()
{
	CTetrisGame SaveGame;
	uSave MySaveDialog;
	DeActivateTimer();
	if ((MySaveDialog.DoModal()) == IDOK) {
		SaveGame.SaveFile(MySaveDialog.FileName,TetrisField,fallx,fally,fallShape,nextfallShape,FallingSpeed,Score,NumberofDestroyedLines);
	}
	ActivateTimer();
}

void CMainWindow::Exit()
{
	DestroyWindow();
}

//Message Map
BEGIN_MESSAGE_MAP( CMainWindow, CFrameWnd )
	//{{AFX_MSG_MAP( CMainWindow )
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_APP_ABOUT, OnAbout)
	ON_COMMAND(ID_ACTIVATETIMER,ActivateTimer)
	ON_COMMAND(ID_DEACTIVATETIMER,DeActivateTimer)
	//GAME
	ON_COMMAND(ID_NEWGAME,NewGame)
	ON_COMMAND(ID_LOADGAME,LoadIt)
	ON_COMMAND(ID_SAVEGAME,SaveIt)
	ON_COMMAND(ID_OPTIONS,OnOptions)
	//ON_COMMAND(ID_PAUSE,PauseIt)
	ON_COMMAND(ID_EXIT,Exit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//App
BOOL CTheApp::InitInstance()
{
	TRACE0("CTheApp::InitInstance\n");
	Enable3dControls(); // use 3d controls in dialogs

	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


