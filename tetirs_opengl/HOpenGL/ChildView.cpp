
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "HOpenGL.h"
#include "ChildView.h"
//#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const  int  RED_TIMER_ID = 50;
static bool m_level_rotate = false;
static bool m_start = true;
// CChildView

//static int level = 0;
CChildView::CChildView()
{
	/*
	tet.screen_y = 19;
	tet.screen_x = 5;
	tet.form_kind = rand() % 7;
	tet.rotate_kind = 0;
//	tet.input_down = false;
//	tet.input_space = false;
	level = score = 0;
	*/
	for (int i = 0; i<21; i++)
	{
		for (int j = 0; j<12; j++)
		{
			//외벽을 의미하는 3을 저장
			if (i == 0 || j == 0 || j == 11)
				tetris[i][j] = 3;
			else//빈 도형을 의미하는 0을 저장
				tetris[i][j] = 0;
		}
	}
	srand(time(NULL));
	screen_y = 19;
	screen_x = 5;
	//form_kind = rand() % 7;
	//form_kind_next = rand() % 7;
	form_kind = form_kind_next = rand() % 7;
	form_kind_next = rand() % 7;
	rotate_kind = 0;
	level = 0; score = 0;
	m_level_rotate = false;
	
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	//init
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glColor3f(1.f, 0.f, 0.f);

	
	glTranslatef(-5, -5, 0);

	
	if(m_start)
		GameStart();
	else if (m_start == false)
	{

		glPushMatrix();
		glTranslated(5, 5, 0);
		glScalef(5, 5, 5);
		DrawPyramid();
		glPopMatrix();
		if (m_level_rotate)
			glRotatef(15, 0, 1, 0);

		//glColor3f(1.f, 0.f, 0.f);
		Initial_board();
		//glColor3f(1, 1, 1);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Print_form();
		Print_next();
		//tet.Print_data();

		chk = Check_board(screen_x, screen_y + 1);
		chk2 = Check_board(screen_x, screen_y - 1);
		if (chk == FALSE && chk2 == TRUE)
		{
			Write_board();
			Check_line();
			screen_y = 19;
			screen_x = 5;
			//form_kind = rand() % 7;
			form_kind = form_kind_next;
			form_kind_next = rand() % 7;
			rotate_kind = 0;
			//tet.tetris[20][5] = 0;
			//input_space = false;
			score += 10;
			Invalidate();
		}
		else
			if (chk == TRUE && chk2 == TRUE)
			{
				//SwapBuffers(dc.m_hDC);
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
				//Invalidate();
			}
	}
	SwapBuffers(dc.m_hDC);
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Initialize pixel format structure
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),                 // sturcture size
			1,                          // structure version number
			PFD_DRAW_TO_WINDOW |         // property flags
														PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,                             // 24-bit color+8bit  (16.7 million color)
			0,0,0,0,0,0,                 // not concerned with these
			0,0,0,0,0,0,0,              // no alpha or accumulate buffer 
			32,                            // 32-bit depth buffer (hidden surface removal)
			0,0,                           // no stencil or aux buffer
			PFD_MAIN_PLANE,      // Main layer type
			0,                             // reserved
			0,0,0                       // Unsupported
	};
	// Set the pixel format
	CClientDC dc(this);
	int pixelFormat = ChoosePixelFormat(dc.m_hDC, &pfd);  // pixel format index returned
	BOOL success = SetPixelFormat(dc.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(dc.m_hDC);  // Create RC compatible with the given DC
	wglMakeCurrent(dc.m_hDC, m_hRC); // Make the RC current (bind RC to DC)

	m_nTimer = SetTimer(RED_TIMER_ID, 1000 / 30, 0); //Timer 시작
	
	

	return 0;
}


void CChildView::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(m_nTimer);   // Timer 끝

	CClientDC dc(this);
	wglMakeCurrent(dc.m_hDC, NULL);  // Maket the RC not current (unbind RC to DC)
	wglDeleteContext(m_hRC);
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (cy == 0) cy = 1;

	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_PROJECTION); // change the Matrix Mode
	glLoadIdentity();

	gluPerspective(45.0f, 1.0f*cx / cy, 1.0f, 1000.0f);

	// camera view configuration 
	gluLookAt(0.f, 0.f, 40.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

	glMatrixMode(GL_MODELVIEW);  // go back to the default
	glLoadIdentity();
	
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (score >= 1000 && score < 2000)
	{
		level = 1;
		m_level_rotate = false;
	}
	else if (score >= 2000 && score < 3000)
	{
		level = 2;
		m_level_rotate = false;
	}
	else if (score >= 3000 && score < 4000)
	{
		level = 3;
		m_level_rotate = false;
	}
	else if (score >= 4000 && score < 5000)
	{
		level = 4;
		m_level_rotate = false;
	}
	else if (score >= 5000)
	{
		level = 5;
		m_level_rotate = TRUE;
	}
	
	switch (nIDEvent)
	{
	case RED_TIMER_ID:

		if (level == 0)
			Sleep(250);
		else if (level == 1)
			Sleep(200);
		else if (level == 2)
			Sleep(150);
		else
			Sleep(100);

		//Sleep(200);
		if(!m_start)
		Select();
		Invalidate();
	}
	
	//CWnd::OnTimer(nIDEvent);
}

void CChildView::Initial_board()
{
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

void CChildView::DrawCube(float xPos, float yPos, float zPos)
{
	// TODO: 여기에 구현 코드 추가.
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

void CChildView::Delete_form()
{
	for (int i = 3; i >= 0; i--) {
		//화면 위치 지정
		//CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2,screen_y + form[form_kind][rotate_kind][i * 2 + 1]);
		// 도형이 없다는 의미인 0을 tetris 배열에 저장
		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]][screen_x + form[form_kind][rotate_kind][i * 2]] = 0;
		// 화면의 도형을 삭제
		//printf(" ");
	}
}

bool CChildView::Check_board(int xPos, int yPos)
{
	int temp = 0;
	for (int i = 0; i < 4; i++)
	{
		// 현재의 위치에 있는 테트리스 도형 정보를 읽어 온다.
		temp = tetris[yPos + form[form_kind][rotate_kind][i * 2 + 1]]
			[xPos + form[form_kind][rotate_kind][i * 2]];
		//1보다 크면 착지한 도형이나 외벽이다.
		if (temp>1)
			return TRUE;
	}
	return FALSE;
}

void CChildView::Print_form()
{
	for (int i = 3; i >= 0; i--) {
		// 화면 위치 지정
		//CurrentXY(30 + (screen_x + form[form_kind][rotate_kind][i * 2]) * 2, screen_y + form[form_kind][rotate_kind][i * 2 + 1]);
		// 착지하지 않은 도형을  의미하는 1을 tetris 배열애 저장
		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]][screen_x + form[form_kind][rotate_kind][i * 2]] = 1;
		//도형을 화면에 출력 
		//printf("□");
		DrawCube(screen_x + form[form_kind][rotate_kind][i * 2], screen_y + form[form_kind][rotate_kind][i * 2 + 1], 0);
	}
}

void CChildView::Print_data()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			//착지한 도형이라면
			if (tetris[i][j] == 2) {
				//glColor3f(1, 1, 0);
				DrawCube(i, j, 0);
			}
			else {
				//CurrentXY(30 + j * 2, i);
				//printf(" ");
			}
		}
	}
}

void CChildView::Move_data(int row)
{
	for (int i = row + 1; i <20; i++)
		for (int j = 1; j < 11; j++)
		{

			tetris[i - 1][j] = tetris[i][j];
		}
}

bool CChildView::Check_line2(int row)
{
	int chk = 0;
	for (int j = 1; j<11; j++)
		chk += tetris[row][j];
	// 착지한 도형을 의미하는 2가 열 개 모이면 줄이 찬 것이다.
	if (chk == 20)
		return TRUE;
	else
		return FALSE;
}

void CChildView::Check_line()
{
	int rst;

	for (int i = screen_y + 4; i >= screen_y; i--) {
		// 한줄이 찼는지 점검한다.
		rst = Check_line2(i);
		// 한 줄이 찼다면 삭제할 줄을 없앤다.
		if (rst == TRUE) {
			Move_data(i);
			Print_data();
			i++;
			//level = level_temp;
			score += 100;
			//level_temp = level;
			//score += 100;
		}
	}
}

void CChildView::Write_board()
{
	for (int i = 3; i >= 0; i--)
	{
		tetris[screen_y + form[form_kind][rotate_kind][i * 2 + 1]][screen_x + form[form_kind][rotate_kind][i * 2]] = 2;
	}
}

bool CChildView::Go_down()
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

bool CChildView::Select()
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
		return FALSE;
	}
	rtn_value = Go_down();
	if (rtn_value == TRUE)
		return FALSE;
	else
		return TRUE;
}
void CChildView::Print_next()
{
	for (int i = 3; i >= 0; i--) 
	{
		DrawCube(13 + form[form_kind_next][0][i * 2], 14 + form[form_kind_next][0][i * 2 + 1], 0);
	}
}


void CChildView::GameStart()
{
	glTranslatef(0, 5, 0);
	glPushMatrix();
	DrawCube(-5, 5, 0);
	DrawCube(-4, 5, 0);
	DrawCube(-3, 5, 0);
	DrawCube(-4, 4, 0);
	DrawCube(-4, 3, 0);
	DrawCube(-4, 2, 0); // T

	DrawCube(-1, 5, 0);
	DrawCube(0, 5, 0);
	DrawCube(1, 5, 0);
	DrawCube(-1, 4, 0);
	DrawCube(0, 3.5, 0);
	DrawCube(-1, 3, 0);
	DrawCube(-1, 2, 0); 
	DrawCube(0, 2, 0);
	DrawCube(1, 2, 0); // E

	DrawCube(3, 5, 0);
	DrawCube(4, 5, 0);
	DrawCube(5, 5, 0);
	DrawCube(4, 4, 0);
	DrawCube(4, 3, 0);
	DrawCube(4, 2, 0); // T

	DrawCube(7, 5, 0);
	DrawCube(8, 5, 0);
	DrawCube(9, 5, 0);
	DrawCube(7, 4, 0);
	DrawCube(9, 4, 0);
	DrawCube(7, 3, 0);
	DrawCube(8.5, 3, 0);
	DrawCube(7, 2, 0);
	DrawCube(9, 2, 0); // R

	DrawCube(11, 5, 0);
	DrawCube(11, 4, 0);
	DrawCube(11, 3, 0);
	DrawCube(11, 2, 0);// I

	DrawCube(13, 5, 0);
	DrawCube(14, 5, 0);
	DrawCube(15, 5, 0);
	DrawCube(13, 4, 0);
	DrawCube(14, 3.5, 0);
	DrawCube(15, 3, 0);
	DrawCube(13, 2, 0);
	DrawCube(14, 2, 0);
	DrawCube(15, 2, 0);// S
	glPopMatrix();

	if (GetAsyncKeyState(VK_RETURN))
	{
		m_start = false;
		Invalidate();
	}
}
void CChildView::DrawPyramid()
{
	// TODO: 여기에 구현 코드 추가.
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(1, 0, 0); // red
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0, 1, 0); // green
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glColor3f(0, 0, 1); // blue
	glVertex3f(0.0f, 0.0f, 1.0f);

	glColor3f(1, 0, 1); // violet
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0, 1, 1); // cyan
	glVertex3f(0.0f, 0.0f, -1.0f);

	glColor3f(0, 1, 0); // green
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(0, 0, 1); // blue
	glVertex3f(0.0f, 0.0f, 1.0f);

	glColor3f(1, 0, 1); // violet
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0, 1, 1); // cyan
	glVertex3f(0.0f, 0.0f, -1.0f);

	glColor3f(0, 1, 0); // green
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glEnd();
}