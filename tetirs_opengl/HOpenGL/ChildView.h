
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include <gl/GL.h>
#include <gl/glut.h>
#include "Tetris.h"
// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();
	char form[7][4][8] = {
		{ { 1,0,1,1,1,2,1,3 },{ 0,1,1,1,2,1,3,1 },{ 1,0,1,1,1,2,1,3 },{ 0,1,1,1,2,1,3,1 } }, // 작대기(ㅣ)
	{ { 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 } }, // ㅁ
	{ { 2,1,0,2,1,2,1,1 },{ 1,0,2,1,1,1,2,2 },{ 2,1,0,2,1,2,1,1 },{ 1,0,2,1,1,1,2,2 } }, // 
	{ { 0,1,1,1,1,2,2,2 },{ 2,0,2,1,1,1,1,2 },{ 0,1,1,1,1,2,2,2 },{ 2,0,2,1,1,1,1,2 } }, //
	{ { 1,0,1,1,1,2,2,2 },{ 0,1,1,1,2,1,0,2 },{ 1,0,2,0,2,1,2,2 },{ 2,1,2,2,1,2,0,2 } },
	{ { 2,0,2,1,2,2,1,2 },{ 0,1,0,2,1,2,2,2 },{ 1,0,2,0,1,1,1,2 },{ 0,1,1,1,2,1,2,2 } },
	{ { 0,1,1,1,2,1,1,2 },{ 2,0,2,1,2,2,1,1 },{ 1,1,1,2,0,2,2,2 },{ 1,0,1,1,1,2,2,1 } },
	};
	// 테트리스 도형
	// 테트리스 보드판 배열
	int tetris[21][12];
	//블록의 종류를 나타내는 변수
	int form_kind; int form_kind_next;
	// 블록의 회전 형태를 나타내는 변수
	int rotate_kind;
	//화면상에서의 좌표
	int screen_x, screen_y;
	//static bool m_level_rotate;
	

	void Initial_board(); // 게임보드 초기화
	void DrawCube(float xPos, float yPos, float zPos);
	void Delete_form();
	bool Check_board(int xPos, int yPos);
	void Print_form();
	void Print_data();
	void Move_data(int row);
	bool Check_line2(int row);
	void Check_line();
	void Write_board();
	bool Go_down();
	bool Select();
	void Print_next();
// 특성입니다.
public:
	int m_nTimer;
	HGLRC m_hRC;
	//Tetris tet;
// 작업입니다.
public:
	bool chk, chk2;
	int level, score;
// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void GameStart();
	void DrawPyramid();
};

