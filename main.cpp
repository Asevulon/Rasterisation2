#include<afxwin.h>


void DrawLineBrezenham(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
	int x = x1;
	int y = y1;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	int incx(1), incy(1);
	if (x2 < x1)incx = -1;
	if (y2 < y1)incy = -1;
	double c = 0;
	if (dx >= dy)
	{
		if (x2 >= x1)
		{
			c = double(dy) / dx - 0.5;
			while (x <= x2)
			{
				SetPixel(hdc, x, y, color);

				if (c >= 0)
				{
					y+=incy;
					c -= 1;
				}
				x+=incx;
				c += (double)dy / dx;
			}
		}
		else
		{
			c = double(dy) / dx - 0.5;
			while (x >= x2)
			{
				SetPixel(hdc, x, y, color);

				if (c >= 0)
				{
					y += incy;
					c -= 1;
				}
				x += incx;
				c += (double)dy / dx;
			}
		}
	}
	else
	{
		c = double(dx) / dy - 0.5;
		if (y2 >= y1)
		{
			while (y <= y2)
			{
				SetPixel(hdc, x, y, color);

				if (c >= 0)
				{
					x += incx;
					c -= 1;
				}
				y += incy;
				c += (double)dx / dy;
			}
		}
		else
		{
			while (y >= y2)
			{
				SetPixel(hdc, x, y, color);

				if (c >= 0)
				{
					x += incx;
					c -= 1;
				}
				y += incy;
				c += (double)dx / dy;
			}
		}
	}

}

void DiagonalStep(int& x, int& y, int& c)
{
	x++;
	y--;
	c += 2 * (x - y + 1);
}


void HorisontalStep(int& x, int& c)
{
	x++;
	c += 2 * x + 1;
}

void VerticalStep(int& y, int& c)
{
	y--;
	c -= 2 * y - 1;
}


void DrawCircleBrezenhem(HDC hdc,int x1, int y1, int R, COLORREF color)
{
	int x = x1;
	int y = R + y1;
	int c = 2 * (1 - R);
	while (y > y1)
	{
		SetPixel(hdc, x, y, color);
		if (c == 0)DiagonalStep(x, y, c);
		else
			if (c < 0)
				if (2 * (c + y) - 1 <= 0)HorisontalStep(x, c);
				else DiagonalStep(x, y, c);
			else
				if (2 * (c - x) - 1 <= 0)DiagonalStep(x, y, c);
				else VerticalStep(y, c);
	}

}






class App :public CWinApp
{

public:
	virtual BOOL InitInstance();
};

App app;

class Win : public CFrameWnd
{

public:
	CPoint m1, m2;
	bool draw;
	Win();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

BOOL App::InitInstance()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	m_pMainWnd = new Win;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return CWinApp::InitInstance();
}
BEGIN_MESSAGE_MAP(Win, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void Win::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �������� ���� ��� ����������� ���������
					   // �� �������� CFrameWnd::OnPaint() ��� ��������� ���������

	DrawLineBrezenham(dc, m1.x, m1.y, m2.x, m2.y, RGB(0, 255, 0));
	DrawCircleBrezenhem(dc, m1.x, m1.y, sqrt((m2.x - m1.x) * (m2.x - m1.x) + (m2.y - m1.y) * (m2.y - m1.y)), RGB(255, 0, 0));
}


Win::Win()
{
	draw = false;
	Create(NULL, L"Rasterisation");
}

void Win::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	draw = true;
	m1 = point;
	CFrameWnd::OnLButtonDown(nFlags, point);
}


void Win::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	draw = false;
	CFrameWnd::OnLButtonUp(nFlags, point);
}


void Win::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	if (draw)
	{
		m2 = point;
		Invalidate();
	}
	CFrameWnd::OnMouseMove(nFlags, point);
}
