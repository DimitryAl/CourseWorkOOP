#include<windows.h>
#include "Classes.h"	//���������� �������
#include <ctime>


extern HDC hdc;      // �������  �������� ����������
// ������ ��� �������� ��������� ���������� � �� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)



/*------------------------------------------*/
/*        ������ ������ Map                */
/*----------------------------------------*/

Map::Map(int width, int length, int x, int y,int side)
{
	Width = width;
	Length = length;
	X0 = x;
	Y0 = y;
	Side = side;
}

Map::~Map()
{

}

void Map::Create()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));		// ������� ���� � ���� ���� - ������
	SelectObject(hdc, Pen);									//������� ���� ��������
	for (int i = 0; i < Length; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			Rectangle(hdc, X0 + j * Side, Y0 + i * Side, X0 + (j + 1) * Side, Y0 + (i + 1) * Side);		//������ �������
		}
	}
}


/*------------------------------------------*/
/*        ������ ������ Location           */
/*----------------------------------------*/

Location::Location(int l, int r, int t, int b, int x, int y, int delta)
{
	Delta = delta;
	X = x + delta;
	Y = y + delta;
	Left = l;
	Right = r;
	Top = t;
	Bottom = b;
};
 
Location::~Location(void)  
{
};

int Location::GetX(void)		 //������� X ���������� 
{
	return X;
};	

int Location::GetY(void)		//������� Y ���������� 
{
	return Y;
}; 


/*------------------------------------------*/
/*        ������ ������ Point             */
/*----------------------------------------*/

Point::Point(int l, int r, int t, int b, int x, int y, int delta) : Location(l, r, t, b, x, y, delta)
{

}

Point::~Point(void)   
{

}

void Point::Show(void)
{
	SetPixel(hdc, X, Y, RGB(255, 0, 0));	
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

void Point::Hide(void)
{
	SetPixel(hdc, X, Y, RGB(255, 255, 255));
	SetPixel(hdc, X + 1, Y, RGB(255, 255, 255));
	SetPixel(hdc, X, Y + 1, RGB(255, 255, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 255, 255));
}

void Point::MoveTo(int NewX, int NewY)
{
	Hide();
	X = NewX;	
	Y = NewY;
	Show();
};

void Point::Drag(int Step)    
{
	int FigX, FigY;   
	int Sleeptime = 250;
	FigX = GetX();			//�������� ������� ���������� X
	FigY = GetY();			//�������� ������� ���������� Y

	while (1)	
	{
		if (KEY_DOWN(VK_ESCAPE))     //����� ������ 27
			break;

		//����������� �������� �������
		if (KEY_DOWN(VK_LEFT)) //������� �����  37
		{
			if ((FigX - Step) > Left)		//���� ����� ���������� �� ������� �� ������� �����
			{
				FigX -= Step;				
				MoveTo(FigX, FigY);
			}
			Sleep(Sleeptime);
		}

		if (KEY_DOWN(VK_RIGHT)) //������� ������  39
		{
			if ((FigX + Step) < Right)		//���� ����� ���������� �� ������� �� ������� �����
			{
				FigX += Step;
				MoveTo(FigX, FigY);
			}
			Sleep(Sleeptime);
		}

		if (KEY_DOWN(VK_DOWN)) //������� ����  40
		{
			if ((FigY + Step) < Bottom)		//���� ����� ���������� �� ������� �� ������� �����
			{
				FigY += Step;
				MoveTo(FigX, FigY);
			}
			Sleep(Sleeptime);
		}

		if (KEY_DOWN(VK_UP)) //������� �����  38
		{
			if ((FigY - Step) > Top)		//���� ����� ���������� �� ������� �� ������� �����
			{
				FigY -= Step;
				MoveTo(FigX, FigY);
			}
			Sleep(Sleeptime);
		}
		break;
	}   
}


/*------------------------------------------------------*/
/*        ������ ������ Human                          */
/*----------------------------------------------------*/

Human::Human(int l, int r, int t, int b, int x, int y, int delta, int m) : Point(l, r, t, b, x, y, delta)
{
	Rings = m;
}

Human:: ~Human(void)
{
}

void Human::Show(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));		
	SelectObject(hdc, Pen);								
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y - Delta / 4);					//������ ������� �������� ����
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y + Delta / 4);					//������ ������ �������� ����
	MoveToEx(hdc, X, Y + Delta / 4, NULL);
	LineTo(hdc, X + Delta / 4, Y + Delta / 1.5);	//������ ����
	MoveToEx(hdc, X, Y + Delta / 4, NULL);
	LineTo(hdc, X - Delta / 4, Y + Delta / 1.5);	//����� ����
	MoveToEx(hdc, X, Y - Delta / 4, NULL);
	LineTo(hdc, X + Delta / 3, Y + Delta / 3);		//������ ������  ����
	MoveToEx(hdc, X, Y - Delta / 4, NULL);
	LineTo(hdc, X - Delta / 3, Y + Delta / 3);		 //������ ����� ����
	MoveToEx(hdc, X, Y - Delta / 4, NULL);
	Ellipse(hdc, X - Delta / 4, Y - Delta / 2, X + Delta / 4, Y);	//������ ������
	DeleteObject(Pen);
}

void Human::Hide(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y - Delta / 4);				//������ ������� �������� ����
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y + Delta / 4);				//������ ������ �������� ����
	MoveToEx(hdc, X, Y + Delta / 4, NULL);
	LineTo(hdc, X + Delta / 4, Y + Delta / 1.5);	//������ ����
	MoveToEx(hdc, X, Y + Delta / 4, NULL);
	LineTo(hdc, X - Delta / 4, Y + Delta / 1.5);	//����� ����
	MoveToEx(hdc, X, Y - Delta / 4, NULL);
	LineTo(hdc, X + Delta / 3, Y + Delta / 3);				//������ ������  ����
	MoveToEx(hdc, X, Y - Delta / 4, NULL);
	LineTo(hdc, X - Delta / 3, Y + Delta / 3);			//������ ����� ����
	MoveToEx(hdc, X, Y - Delta / 4, NULL);
	Ellipse(hdc, X - Delta / 4, Y - Delta / 2, X + Delta / 4, Y);	//������ ������
	DeleteObject(Pen);
}


/*------------------------------------------------------*/
/*        ������ ������ Ring                          */
/*----------------------------------------------------*/

Ring::Ring(int l, int r, int t, int b, int x, int y, int delta, int behave) : Point(l, r, t, b, x, y, delta)
{
	Behave = behave;
}

Ring:: ~Ring(void)
{

}

void Ring::Show(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(225, 225, 255));	
	SelectObject(hdc, Pen);								
	MoveToEx(hdc, X , Y, NULL);
	Ellipse(hdc, X - Delta / 3, Y - Delta / 2, X + Delta / 2, Y + Delta /2);	
	DeleteObject(Pen);
}

void Ring::Hide(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));		
	SelectObject(hdc, Pen);								
	MoveToEx(hdc, X, Y, NULL);
	Ellipse(hdc, X - Delta / 3, Y - Delta / 2, X + Delta / 2, Y + Delta / 2);
	DeleteObject(Pen);
}

void Ring::NewX(void)
{
	int newX;			//����� ����������
	int number;			

	srand(time(NULL));										//���������� ��������� ��������� �����
	number = rand() % 10;									//�������� ��������� ����� �� 0 �� 10
	if (number % 2 == 0) newX = X + number * Delta * 2;		//���� ����� ������, �� ����� ���������� ����� ������ ���� �����, ���������� �� ����� ������
	else newX = X - number * Delta * 2;						//����� ����� ���������� ����� ������ ����� �����, ���������� �� ����� ������
	while ( (newX > Right || newX < Left) && (newX != X))	//���� ����� ���������� ������� �� ������� ����� � �� ����� ������
	{
		number = rand() % 10;								
		if (number % 2 == 0) newX = X + number * Delta * 2;
		else newX = X - number * Delta * 2;
	}
	X = newX;												//���������� ����� ����������
}

void Ring::NewY(void)
{
	int newY;						//����� ����������
	int number;

	//srand(time(NULL));										//���������� ��������� ��������� �����
	number = rand() % 10;									//�������� ��������� ����� �� 0 �� 10
	if (number % 2 == 0) newY = Y + number * Delta * 2;		//���� ����� ������, �� ����� ���������� ����� ������ ���� �����, ���������� �� ����� ������
	else newY = Y - number * Delta * 2;						//����� ����� ���������� ����� ������ ����� �����, ���������� �� ����� ������
	while ( (newY < Top || newY > Bottom) && (newY != Y))	//���� ����� ���������� ������� �� ������� ����� �  ����� ������
	{
		number = rand() & 10;
		if (number % 2 == 0) newY = Y + number * Delta * 2;
		else newY = Y - number * Delta * 2;
	}
	Y = newY;												//���������� ����� ����������
}

/*------------------------------------------------------*/
/*        ������ ������ GRing                          */
/*----------------------------------------------------*/

GRing::GRing(int l, int r, int t, int b, int x, int y, int delta, int behave) : Ring(l, r, t, b, x, y, delta, behave)
{
	Behave = behave;
}

GRing:: ~GRing(void)
{

}

void GRing::Show(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 216, 0));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, X, Y, NULL);
	Ellipse(hdc, X - Delta / 3, Y - Delta / 2, X + Delta / 2, Y + Delta / 2);
	DeleteObject(Pen);
}

void GRing::Hide(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, X, Y, NULL);
	Ellipse(hdc, X - Delta / 3, Y - Delta / 2, X + Delta / 2, Y + Delta / 2);
	DeleteObject(Pen);
}

void GRing::NewX(void)
{
	int newX;			//����� ����������
	int number;

	//srand(time(NULL));										//���������� ��������� ��������� �����
	number = rand() % 10;									//�������� ��������� ����� �� 0 �� 10
	if (number % 2 == 0) newX = X + number * Delta * 2;		//���� ����� ������, �� ����� ���������� ����� ������ ���� �����, ���������� �� ����� ������
	else newX = X - number * Delta * 2;						//����� ����� ���������� ����� ������ ����� �����, ���������� �� ����� ������
	while ((newX > Right || newX < Left) && (newX != X))	//���� ����� ����������  ������� �� ������� ����� �  ����� ������
	{
		number = rand() % 10;
		if (number % 2 == 0) newX = X + number * Delta * 2;
		else newX = X - number * Delta * 2;
	}
	X = newX;												//���������� ����� ����������
}

void GRing::NewY(void)
{
	int newY;						//����� ����������
	int number;

	//srand(time(NULL));										//���������� ��������� ��������� �����
	number = rand() % 10;									//�������� ��������� ����� �� 0 �� 10
	if (number % 2 == 0) newY = Y + number * Delta * 2;		//���� ����� ������, �� ����� ���������� ����� ������ ���� �����, ���������� �� ����� ������
	else newY = Y - number * Delta * 2;						//����� ����� ���������� ����� ������ ����� �����, ���������� �� ����� ������
	while ((newY < Top || newY > Bottom) && (newY != Y))	//���� ����� ����������  ������� �� ������� ����� �  ����� ������
	{
		number = rand() & 10;
		if (number % 2 == 0) newY = Y + number * Delta * 2;
		else newY = Y - number * Delta * 2;
	}
	Y = newY;												//���������� ����� ����������
}

/*------------------------------------------------------*/
/*        ������ ������ GRing2                          */
/*----------------------------------------------------*/

GRing2::GRing2(int l, int r, int t, int b, int x, int y, int delta, int behave) : GRing(l, r, t, b, x, y, delta, behave)
{
	Behave = behave;
}

GRing2:: ~GRing2(void)
{

}

void GRing2::Show(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(65, 105, 255));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, X, Y, NULL);
	Ellipse(hdc, X - Delta / 3, Y - Delta / 2, X + Delta / 2, Y + Delta / 2);
	DeleteObject(Pen);
}

void GRing2::Hide(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, X, Y, NULL);
	Ellipse(hdc, X - Delta / 3, Y - Delta / 2, X + Delta / 2, Y + Delta / 2);
	DeleteObject(Pen);
}

void GRing2::NewX(void)
{
	int newX;			//����� ����������
	int number;

	//srand(time(NULL));										//���������� ��������� ��������� �����
	number = rand() % 10;									//�������� ��������� ����� �� 0 �� 10
	if (number % 2 == 0) newX = X + number * Delta * 2;		//���� ����� ������, �� ����� ���������� ����� ������ ���� �����, ���������� �� ����� ������
	else newX = X - number * Delta * 2;						//����� ����� ���������� ����� ������ ����� �����, ���������� �� ����� ������
	while ((newX > Right || newX < Left) && (newX != X))	//���� ����� ����������  ������� �� ������� ����� �  ����� ������
	{
		number = rand() % 10;
		if (number % 2 == 0) newX = X + number * Delta * 2;
		else newX = X - number * Delta * 2;
	}
	X = newX;												//���������� ����� ����������
}

void GRing2::NewY(void)
{
	int newY;						//����� ����������
	int number;

	//srand(time(NULL));										//���������� ��������� ��������� �����
	number = rand() % 10;									//�������� ��������� ����� �� 0 �� 10
	if (number % 2 == 0) newY = Y + number * Delta * 2;		//���� ����� ������, �� ����� ���������� ����� ������ ���� �����, ���������� �� ����� ������
	else newY = Y - number * Delta * 2;						//����� ����� ���������� ����� ������ ����� �����, ���������� �� ����� ������
	while ((newY < Top || newY > Bottom) && (newY != Y))	//���� ����� ����������  ������� �� ������� ����� �  ����� ������
	{
		number = rand() & 10;
		if (number % 2 == 0) newY = Y + number * Delta * 2;
		else newY = Y - number * Delta * 2;
	}
	Y = newY;												//���������� ����� ����������
}

/*------------------------------------------------------*/
/*        ������ ������ BRing                          */
/*----------------------------------------------------*/

BRing::BRing(int l, int r, int t, int b, int x, int y, int delta, int behave) : Ring(l, r, t, b, x, y, delta, behave)
{
	Behave = behave;
}

BRing:: ~BRing(void)
{

}

void BRing::Show(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(225, 0, 0));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, X, Y, NULL);
	Ellipse(hdc, X - Delta / 3, Y - Delta / 2, X + Delta / 2, Y + Delta / 2);
	DeleteObject(Pen);
}

void BRing::Hide(void)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, X, Y, NULL);
	Ellipse(hdc, X - Delta / 3, Y - Delta / 2, X + Delta / 2, Y + Delta / 2);
	DeleteObject(Pen);
}

void BRing::NewX(void)
{
	int newX;			//����� ����������
	int number;

	//srand(time(NULL));										//���������� ��������� ��������� �����
	number = rand() % 10;									//�������� ��������� ����� �� 0 �� 10
	if (number % 2 == 0) newX = X + number * Delta * 2;		//���� ����� ������, �� ����� ���������� ����� ������ ���� �����, ���������� �� ����� ������
	else newX = X - number * Delta * 2;						//����� ����� ���������� ����� ������ ����� �����, ���������� �� ����� ������
	while ((newX > Right || newX < Left) && (newX != X))	//���� ����� ����������  ������� �� ������� ����� �  ����� ������
	{
		number = rand() % 10;
		if (number % 2 == 0) newX = X + number * Delta * 2;
		else newX = X - number * Delta * 2;
	}
	X = newX;												//���������� ����� ����������
}

void BRing::NewY(void)
{
	int newY;						//����� ����������
	int number;

	//srand(time(NULL));										//���������� ��������� ��������� �����
	number = rand() % 10;									//�������� ��������� ����� �� 0 �� 10
	if (number % 2 == 0) newY = Y + number * Delta * 2;		//���� ����� ������, �� ����� ���������� ����� ������ ���� �����, ���������� �� ����� ������
	else newY = Y - number * Delta * 2;						//����� ����� ���������� ����� ������ ����� �����, ���������� �� ����� ������
	while ((newY < Top || newY > Bottom) && (newY != Y))	//���� ����� ����������  ������� �� ������� ����� �  ����� ������
	{
		number = rand() & 10;
		if (number % 2 == 0) newY = Y + number * Delta * 2;
		else newY = Y - number * Delta * 2;
	}
	Y = newY;												//���������� ����� ����������
}
