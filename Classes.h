#pragma once

/*----------------------------  ����� Map -----------------------------*/
class Map
{
protected:
	int Width;				//���-�� ��������
	int Length;				//���-�� �����
	int X0;					//��������� ���������� �� X
	int Y0;					//��������� ���������� �� Y
	int Side;				//����� ������� ��������
public:
	Map(int width, int length, int x, int y, int side);			//����������� 
	~Map();														//����������
	void Create();												//������ � ����
};

/*-----------------------��������� Base------------------------------------*/
class Base
{
public:

	virtual ~Base() = default;
	virtual void Show() = 0;
	virtual void Hide() = 0;
};

/*-----------------------  ����� Location -------------------------*/
class Location : public Base
{
protected:
	int X;								//���������� X
	int Y;								//���������� Y
	int Left, Right, Top, Bottom;		//�����, ������, �������, ������ ������� ����� ������������� 
	int Delta;							//����� ������, ������� ��  2
public:   
	Location(int l, int r,int t, int b, int x, int y, int delta);	//�����������
	~Location();													//����������
	int GetX();														//���������� ������� ���������� X
	int GetY();														//���������� ������� ���������� Y
};

/*-----------------------  ����� Point ----------------------------------*/
class Point : public Location
{
public:
	Point(int l, int r, int t, int b, int x, int y, int delta);	//�����������
	~Point();													//����������
	void MoveTo(int NewX, int NewY);							//����������� ����� ����� ����������
	void Drag(int Step);										//������� ����� 
	virtual void Show();										//������ �����
	virtual void Hide();										//�������� �����
};

/*-----------------------  ����� Human  ----------------------------------*/
class Human : public Point
{
public:
	int Rings;												//���-�� ��������� �����
public:

	Human(int l, int r, int t, int b, int x, int y, int delta, int m);	//�����������
	~Human();															//����������
	void Show();														//������ ��������
	void Hide();														//�������� ��������
};

/*-----------------------  ����� Ring  ----------------------------------*/
class Ring : public Point
{
public:
	int Behave;
public:
	Ring(int l, int r, int t, int b, int x, int y, int delta, int behave);	//�����������
	~Ring();																		//����������
	virtual void NewX();																	//��������� ����� ���������� X
	virtual void NewY();																	//��������� ����� ���������� Y
	virtual void Show();																	//������ ������ 
	virtual void Hide();																	//�������� ������
};

/*-----------------------  ����� GRing  ----------------------------------*/
class GRing : public Ring
{
public:
	//int Behave;
public:
	GRing(int l, int r, int t, int b, int x, int y, int delta, int behave);	//�����������
	~GRing();																		//����������
	void NewX();																	//��������� ����� ���������� X
	void NewY();																	//��������� ����� ���������� Y
	virtual void Show();																	//������ ������ 
	void Hide();																	//�������� ������
};

//class GRing3 : public GRing
//{
//public:
//	//int Behave;
//public:
//	GRing3(int l, int r, int t, int b, int x, int y, int delta, int behave);	//�����������
//	~GRing3();																		//����������
//	void NewX();																	//��������� ����� ���������� X
//	void NewY();																	//��������� ����� ���������� Y
//	void Show();																	//������ ������ 
//	void Hide();																	//�������� ������
//};

class GRing2 : public GRing
{
public:
	//int Behave;
public:
	GRing2(int l, int r, int t, int b, int x, int y, int delta, int behave);	//�����������
	~GRing2();																		//����������
	void NewX();																	//��������� ����� ���������� X
	void NewY();																	//��������� ����� ���������� Y
	void Show();																	//������ ������ 
	void Hide();																	//�������� ������
};

/*-----------------------  ����� BRing  ----------------------------------*/
class BRing : public Ring
{
public:
	//int Behave = -1;
public:
	BRing(int l, int r, int t, int b, int x, int y, int delta, int behave);	//�����������
	~BRing();																		//����������
	void NewX();																	//��������� ����� ���������� X
	void NewY();																	//��������� ����� ���������� Y
	void Show();																	//������ ������ 
	void Hide();																	//�������� ������
};

