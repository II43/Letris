//TetrisGame.h
#ifndef __TETRISGAME_H__
#define __TETRISGAME_H__

class CTetrisGame
{
public:
	int uTetrisField[14][22];
	int uFallingSpeed;
	int uScore;
	int uLines;
	WORD uFallShape;
	int uFallX,uFallY;
	WORD uNextFallShape;
	DWORD uHighScore,uHighLines;
	CString uHighPlayerName;
	///////////////////	
	void LoadFile(CString FileName);
	void SaveFile(CString FileName,int TetrisField[14][22],
				  unsigned char CorX,unsigned char CorY,WORD Shape,
				  WORD nextShape,WORD Speed,WORD Score,WORD Lines);
	void SaveHighList(DWORD HighScore,DWORD Lines,CString PlayerName);
	int LoadHighList();
};

class CShape
{
public:
	WORD LoadShape(int Shape,int Direction);
};

class uShape
{
public:
	int Bitmap;
	WORD Position[4];
};




#endif // __TETRISGAME_H__
