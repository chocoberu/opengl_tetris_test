#pragma once
class Tetris
{
public:
	Tetris();
	~Tetris();
	char form[7][4][8] = {
		{ { 1,0,1,1,1,2,1,3 },{ 0,1,1,1,2,1,3,1 },{ 1,0,1,1,1,2,1,3 },{ 0,1,1,1,2,1,3,1 } }, // �۴��(��)
	{ { 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 },{ 1,1,2,1,1,2,2,2 } }, // ��
	{ { 2,1,0,2,1,2,1,1 },{ 1,0,2,1,1,1,2,2 },{ 2,1,0,2,1,2,1,1 },{ 1,0,2,1,1,1,2,2 } }, // 
	{ { 0,1,1,1,1,2,2,2 },{ 2,0,2,1,1,1,1,2 },{ 0,1,1,1,1,2,2,2 },{ 2,0,2,1,1,1,1,2 } }, //
	{ { 1,0,1,1,1,2,2,2 },{ 0,1,1,1,2,1,0,2 },{ 1,0,2,0,2,1,2,2 },{ 2,1,2,2,1,2,0,2 } },
	{ { 2,0,2,1,2,2,1,2 },{ 0,1,0,2,1,2,2,2 },{ 1,0,2,0,1,1,1,2 },{ 0,1,1,1,2,1,2,2 } },
	{ { 0,1,1,1,2,1,1,2 },{ 2,0,2,1,2,2,1,1 },{ 1,1,1,2,0,2,2,2 },{ 1,0,1,1,1,2,2,1 } },
	};
	// ��Ʈ���� ����
	// ��Ʈ���� ������ �迭
	int tetris[21][12];
	//����� ������ ��Ÿ���� ����
	int form_kind;
	// ����� ȸ�� ���¸� ��Ÿ���� ����
	int rotate_kind;
	//ȭ��󿡼��� ��ǥ
	int screen_x, screen_y;
	bool input_down;
	bool input_space;
	int score; int level;
	
	void Initial_board(); // ���Ӻ��� �ʱ�ȭ
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

