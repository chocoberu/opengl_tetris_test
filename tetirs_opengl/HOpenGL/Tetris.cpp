#include "stdafx.h"
#include "Tetris.h"
#include <gl/GL.h>
#include <gl/glut.h>
#include "ChildView.h"
#include "MainFrm.h"
static int level_temp = 0;
//static int score = 0;

Tetris::Tetris()
{
	for (int i = 0; i<21; i++)
	{
		for (int j = 0; j<12; j++)
		{
			//�ܺ��� �ǹ��ϴ� 3�� ����
			if (i == 0 || j == 0 || j == 11)
				tetris[i][j] = 3;
			else//�� ������ �ǹ��ϴ� 0�� ����
				tetris[i][j] = 0;
		}
	}
	score = 0;
	level = 0;
}


Tetris::~Tetris()
{

}
void Tetris::Initial_board()
{
	
	/*
	for (int i = 0; i < 21; i++)
	{
		DrawCube(0.f, (float)i, 0.f);
		DrawCube(12.f, (float)i, 0.f);
	}
	for (int i = 0; i < 12; i++)
	{
		DrawCube((float)i, 0, 0);
	}
	*/
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (tetris[j][i] == 2)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glColor3f(0.5, 0.5, 0.5);
				DrawCube(i, j, 0);
			}
			if (tetris[j][i] == 3)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glColor3f(1, 1, 1);
				DrawCube(i, j, 0);
			}
		}
	}
}
bool Tetris::Check_board(int xPos, int yPos)
{
	int temp = 0;
	for (int i = 0; i < 4; i++)
	{
		// ������ ��ġ�� �ִ� ��Ʈ���� ���� ������ �о� �´�.
		temp = tetris[yPos + form[form_kind][rotate_kind][i * 2 + 1]]
			[xPos + form[form_kind][rotate_kind][i * 2]];
		//1���� ũ�� ������ �����̳� �ܺ��̴�.
		if (temp>1)
			return TRUE;
	}
	return FALSE;
}
void Tetris::Print_data()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			//������ �����̶��
			if (tetris[i][j] == 2) {
				//glColor3f(1, 1, 0);
				DrawCube(i,j, 0);
			}
			else {
				//CurrentXY(30 + j * 2, i);
				//printf(" ");
			}
		}
	}
}
void Tetris::Move_data(int row) //������ �����͸� �� �� �Ʒ��� �̵��Ѵ�
{
	for (int i = row+1 ; i <20 ; i++)
		for (int j = 1; j < 11; j++)
		{
			
			tetris[i-1][j] = tetris[i][j];
		}
}
bool Tetris::Check_line2(int row) // �� ���� á���� üũ�Ѵ�.
{
	int chk = 0;
	for (int j = 1; j<11; j++)
		chk += tetris[row][j];
	// ������ ������ �ǹ��ϴ� 2�� �� �� ���̸� ���� �� ���̴�.
	if (chk == 20)
		return TRUE;
	else
		return FALSE;
}
void Tetris::Check_line() //���� ���� �ִ��� üũ�Ѵ�.
{
	int rst;
	
	for (int i = screen_y+4; i >=screen_y ; i--) {
		// ������ á���� �����Ѵ�.
		rst = Check_line2(i);
		// �� ���� á�ٸ� ������ ���� ���ش�.
		if (rst == TRUE) {
			Move_data(i);
			Print_data();
			i++;
			level = level_temp;
			level++; score += 100;
			level_temp = level;
			//score += 100;
		}
	}
	
}
void Tetris::Write_board() // ������ ������ ���
{
	for (int i = 3; i >= 0; i--)
	{
		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]][screen_x + form[form_kind][rotate_kind][i * 2]] = 2;
	}
}
bool Tetris::Go_down()
{
	int chk2;
	chk2 = Check_board(screen_x, screen_y - 1);
	if (chk2 == TRUE)
	{
		Write_board();
		//Check_line();
		return TRUE;
	}
	Delete_form();
	screen_y--;
	Print_form();
	return FALSE;

}
void Tetris::Delete_form()
{
	for (int i = 3; i>= 0 ; i--) {
		//ȭ�� ��ġ ����
		//CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2,screen_y + form[form_kind][rotate_kind][i * 2 + 1]);
		// ������ ���ٴ� �ǹ��� 0�� tetris �迭�� ����
		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]][screen_x + form[form_kind][rotate_kind][i * 2]] = 0;
		// ȭ���� ������ ����
		//printf(" ");
	}
}
void Tetris::Print_form()
{
	for (int i = 3; i>=0; i--) {
		// ȭ�� ��ġ ����
		//CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2, screen_y + form[form_kind][rotate_kind][i * 2 + 1]);
		// �������� ���� ������  �ǹ��ϴ� 1�� tetris �迭�� ����
		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]][screen_x + form[form_kind][rotate_kind][i * 2]] = 1;
		//������ ȭ�鿡 ��� 
		//printf("��");
		DrawCube(screen_x + form[form_kind][rotate_kind][i * 2], screen_y + form[form_kind][rotate_kind][i * 2 + 1], 0 );
	}
}
void Tetris::Timing()
{
	DWORD thisTickCount;
	static DWORD lastTickCount = 0;
	DWORD delay = 300;
	thisTickCount = GetTickCount();
	while (1)
	{
		if ((thisTickCount - lastTickCount)>delay)
		{
			lastTickCount = thisTickCount;
			return;
		}
		thisTickCount = GetTickCount();
	}
}
bool Tetris::Select()
{
	int chk1;
	//	int chk2;
	int prev_rotate;
	int new_rotate;
	int rtn_value;
	if (GetAsyncKeyState(VK_LEFT))
	{
		chk1 = Check_board(screen_x - 1, screen_y);
		if (chk1 == FALSE)
		{
			Delete_form();
			screen_x--;
			Print_form();
			return TRUE;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		chk1 = Check_board(screen_x + 1, screen_y);
		if (chk1 == FALSE)
		{
			Delete_form();
			screen_x++;
			Print_form();
			return TRUE;
		}
	}
	if (GetAsyncKeyState(VK_UP))
	{
		prev_rotate = rotate_kind;
		if (rotate_kind == 3) rotate_kind = 0;
		else rotate_kind++;
		new_rotate = rotate_kind;
		chk1 = Check_board(screen_x, screen_y);
		if (chk1 == FALSE)
		{
			rotate_kind = prev_rotate;
			Delete_form();
			rotate_kind = new_rotate;
			Print_form();
			return TRUE;
		}
		else
		{
			rotate_kind = prev_rotate;
		}
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		//input_down = true;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		while (!Go_down());
		input_space = true;
		return FALSE;
	}
	rtn_value = Go_down();
	if (rtn_value == TRUE)
		return FALSE;
	else
		return TRUE;
}
void Tetris::DrawCube(float xPos, float yPos, float zPos)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);

	glBegin(GL_QUADS);
	//glColor3f(1.f, 0.f, 0.f); // red
	glVertex3f(0.5f, 0.5f, 0.5f);	// top face
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	//glColor3f(0.f, 1.f, 0.f); // green
	glVertex3f(0.5f, 0.5f, 0.5f);	// front face
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	//glColor3f(0.f, 0.f, 1.f); // blue
	glVertex3f(0.5f, 0.5f, 0.5f);	// right face
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//glColor3f(1.f, 1.f, 0.f); // yellow
	glVertex3f(-0.5f, 0.5f, 0.5f);	// left face
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	//glColor3f(1.f, 0.f, 1.f); // violet
	glVertex3f(0.5f, -0.5f, 0.5f);	// bottom face
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	//glColor3f(0.f, 1.f, 1.f); // cyan
	glVertex3f(0.5f, 0.5f, -0.5f);	// back face
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();
	glPopMatrix();
}