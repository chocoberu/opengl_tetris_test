#pragma once
class Tetris
{
public:
	Tetris();
	~Tetris();
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
	int form_kind;
	// 블록의 회전 형태를 나타내는 변수
	int rotate_kind;
	//화면상에서의 좌표
	int screen_x, screen_y;
	bool input_down;
	bool input_space;
	int score; int level;
	
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
	void Timing();
};

