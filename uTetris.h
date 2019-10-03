#ifndef __HELLO_H__
#define __HELLO_H__


class CMainWindow : public CFrameWnd
{
public:
	//Tetris
	int MaxX,MaxY;
	int TetrisField[14][22];
	int fallx,fally;
	WORD fallShape;
	WORD nextfallShape,lastfallShape;
	int FallingSpeed,BkValue;
	int Score,NumberofDestroyedLines;
	int TryX,TryY;
	//Shapes
	struct Shape {
		int x;
		int y;
		WORD Structure;
	};
	BOOL Drawing;
	CGdiObject MyBitmap;
	CMainWindow();

	//{{AFX_MSG( CMainWindow )
	afx_msg void OnPaint();
	afx_msg void DrawWindow();
	afx_msg void OnAbout();
	afx_msg void OnOptions();
	//TetrisField
	afx_msg void OnSolveField();
	afx_msg void CreateField(int dx,int dy);
	//Tetris// 
	//Drawing
	afx_msg void DrawWindowStructure();
	afx_msg void DrawInfo();
	afx_msg void DrawNextShape();
	afx_msg void DrawHighScore();
	afx_msg void DrawTetrisField(int ux,int uy,int usize,int cField[14][22]);
	afx_msg void IncludeTetrisShape(Shape cShape);
	afx_msg	void OnDrawTetrisShape(int x,int y,int Shape,int Direction,int Value);
	afx_msg void DrawTetrisShape(int x,int y,int Shape,int Direction);
	afx_msg void DestroyTetrisShape(int x,int y,int Shape,int Direction);
	afx_msg void StoneTetrisShape(int x,int y,int Shape,int Direction);
	afx_msg int ReturnShape(WORD uShape);
	afx_msg int ReturnDirection(WORD uShape);
	afx_msg void MoveItRight();
	afx_msg void MoveItLeft();
	afx_msg void MoveItDown();
	afx_msg void RotateIt();
	afx_msg int CheckFieldUnder();
	afx_msg int CheckFieldLeft();
	afx_msg int CheckFieldRight();
	afx_msg int CheckFieldRotation();
	//Matrix
	int PreMoveLeft();
	int PreMoveRight();
	int PreRotate();
	void Zkouska();
	//Keyboard
	afx_msg void OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
	//Timer
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void ActivateTimer();
	afx_msg void DeActivateTimer();
	//Generation of Random Shape
	afx_msg WORD GenerateRandomShape();
	afx_msg void ControlField();
	afx_msg void DestroyLine(int uLine);
	//Game
	afx_msg void NewGame();
	afx_msg void LoadIt();
	afx_msg void SaveIt();
	afx_msg void GameOver();
	afx_msg void Exit();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

// CTheApp:
// See hello.cpp for the code to the InitInstance member function.
//
class CTheApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

	



/////////////////////////////////////////////////////////////////////////////

#endif // __HELLO_H__
