//TetrisGame.cpp
#include <afxwin.h>
#include <stdio.h>

#include "stdafx.h"
#include "resource.h"


#include "TetrisGame.h"



void CTetrisGame::SaveFile(CString FileName,int TetrisField[14][22],
						   unsigned char CorX,unsigned char CorY,WORD Shape,
						   WORD nextShape,WORD Speed,WORD Score,WORD Lines)
{
	int px,py,pi=0;
	unsigned char Value[308];
	unsigned char Cor[2];
	WORD Identity[1];
	WORD Description[5];
	Identity[0] = 0x1312;
	Description[0] = Shape; Description[1] = nextShape;
	Description[2] = Speed;	Description[3] = Score;
	Description[4] = Lines;
	Cor[0] = CorX; Cor[1] = CorY;
	FILE *SaveGame;
	if((SaveGame = fopen(FileName,"wb")) != NULL) {
		fwrite(Identity,2,1,SaveGame);
		fwrite(Cor,1,2,SaveGame);
		fwrite(Description,2,5,SaveGame);
		for (px=0;px<14;px++) {
			for (py=0;py<22;py++) {
				Value[pi] = TetrisField[px][py];
				pi++;
			}
		}	
		fwrite(Value,1,308,SaveGame);
		fclose(SaveGame);
	}

}

void CTetrisGame::LoadFile(CString FileName)
{
	int px,py,pi=0;
	unsigned char Value[308];
	unsigned char Cor[2];
	WORD Description[5];
	WORD Identify[1];
	FILE *LoadGame;
	if((LoadGame = fopen(FileName,"rb")) != NULL) {
		fread(Identify,2,1,LoadGame);
		if (Identify[0] == 0x1312) {
			fread(Cor,1,2,LoadGame);
			fread(Description,2,5,LoadGame);
			uFallX = Cor[0]; uFallY = Cor[1];
			uFallShape = Description[0]; uNextFallShape = Description[1];
			uFallingSpeed = Description[2];
			uScore = Description[3]; uLines = Description[4];
			fread(Value,1,308,LoadGame);
			for (px=0;px<14;px++) {
				for (py=0;py<22;py++) {
					uTetrisField[px][py] = Value[pi];
					pi++;
				}
			}
		}	
		fclose(LoadGame);
	}
	
}

void CTetrisGame::SaveHighList(DWORD HighScore,DWORD Lines,CString PlayerName)
{
	int Lenght;
	Lenght = PlayerName.GetLength(); 
	CString Identity("uTetris");
	DWORD Description[3];
	Description[0] = HighScore;
	Description[1] = Lines;
	Description[2] = Lenght;
	unsigned char Splitter = ',';
	CString FileName("uTetris.dat");
	FILE *HighListFile;
	if ((HighListFile = fopen(FileName,"wb")) != NULL) {
		fwrite(Identity,7,1,HighListFile);
		fwrite(Description,sizeof(DWORD),3,HighListFile);
		fwrite(PlayerName,Lenght,1,HighListFile);
	}
	fclose(HighListFile);
}

int CTetrisGame::LoadHighList()
{
	int Lenght;
	CString Identity[1],PlayerName[1];
	CString FileName("uTetris.dat");
	DWORD Description[3];
	unsigned char Splitter = ',';
	FILE *HighListFile;
	HighListFile = fopen(FileName,"rb"); 
	if(HighListFile == 0) return 0;
	if(HighListFile != NULL) {
		fread(Identity,7,1,HighListFile);
		fread(Description,sizeof(DWORD),3,HighListFile);
		Lenght = Description[2];
		fread(PlayerName,Lenght,1,HighListFile);
	}
	if (Identity[0] != "uTetris") return 1;
	uHighLines = Description[1];
	uHighScore = Description[0];
	uHighPlayerName = PlayerName[0];
	return 0;
}

///////////////////////////CShape class
WORD CShape::LoadShape(int Shape,int Direction)
{
	uShape MyShape[7];
	// 1_Shape
	MyShape[0].Position[0] = 0x0660; //0000 0110 0110 0000
	MyShape[0].Position[1] = 0x0660; //0000 0110 0110 0000
	MyShape[0].Position[2] = 0x0660; //0000 0110 0110 0000
	MyShape[0].Position[3] = 0x0660; //0000 0110 0110 0000
	// 2_Shape
	MyShape[1].Position[0] = 0x2222; //0010 0010 0010 0010
	MyShape[1].Position[1] = 0x00F0; //0000 1111 0000 0000
	MyShape[1].Position[2] = 0x2222; 
	MyShape[1].Position[3] = 0x00F0; //0000 1111 0000 0000
	// 3_Shape
	MyShape[2].Position[0] = 0x0226; //0010 0010 0010 0010
	MyShape[2].Position[1] = 0x00E2; //0000 1111 0000 0000
	MyShape[2].Position[2] = 0x0644; //0010 0010 0010 0010
	MyShape[2].Position[3] = 0x002E; //0000 1111 0000 0000	
	
	return MyShape[Shape].Position[Direction]; 
}





