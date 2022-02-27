#pragma once

/*----------------------------  Класс Map -----------------------------*/
class Map
{
protected:
	int Width;				//Кол-во столбцов
	int Length;				//Кол-во строк
	int X0;					//Стартовая координата по X
	int Y0;					//Стартовая координата по Y
	int Side;				//Длина стороны квадрата
public:
	Map(int width, int length, int x, int y, int side);			//Конструктор 
	~Map();														//Деструктор
	void Create();												//Рисует в окне
};

/*-----------------------Интерфейс Base------------------------------------*/
class Base
{
public:

	virtual ~Base() = default;
	virtual void Show() = 0;
	virtual void Hide() = 0;
};

/*-----------------------  Класс Location -------------------------*/
class Location : public Base
{
protected:
	int X;								//Координата X
	int Y;								//Координата Y
	int Left, Right, Top, Bottom;		//левая, правая, верхняя, нижняя границы карты соотвественно 
	int Delta;							//Длина клетки, делённая на  2
public:   
	Location(int l, int r,int t, int b, int x, int y, int delta);	//Конструктор
	~Location();													//Деструктор
	int GetX();														//Возвращает текущую координату X
	int GetY();														//Возвращает текущую координату Y
};

/*-----------------------  Класс Point ----------------------------------*/
class Point : public Location
{
public:
	Point(int l, int r, int t, int b, int x, int y, int delta);	//Конструктор
	~Point();													//Деструктор
	void MoveTo(int NewX, int NewY);							//Присваиваем точке новые координаты
	void Drag(int Step);										//Двигаем точку 
	virtual void Show();										//Рисуем точку
	virtual void Hide();										//Затираем точку
};

/*-----------------------  Класс Human  ----------------------------------*/
class Human : public Point
{
public:
	int Rings;												//Кол-во собранных колец
public:

	Human(int l, int r, int t, int b, int x, int y, int delta, int m);	//Конструктор
	~Human();															//Деструктор
	void Show();														//Рисуем человека
	void Hide();														//Затираем человека
};

/*-----------------------  Класс Ring  ----------------------------------*/
class Ring : public Point
{
public:
	int Behave;
public:
	Ring(int l, int r, int t, int b, int x, int y, int delta, int behave);	//Конструктор
	~Ring();																		//Деструктор
	virtual void NewX();																	//Генерация новой координаты X
	virtual void NewY();																	//Генерация новой координаты Y
	virtual void Show();																	//Рисуем кольцо 
	virtual void Hide();																	//Затираем кольцо
};

/*-----------------------  Класс GRing  ----------------------------------*/
class GRing : public Ring
{
public:
	//int Behave;
public:
	GRing(int l, int r, int t, int b, int x, int y, int delta, int behave);	//Конструктор
	~GRing();																		//Деструктор
	void NewX();																	//Генерация новой координаты X
	void NewY();																	//Генерация новой координаты Y
	virtual void Show();																	//Рисуем кольцо 
	void Hide();																	//Затираем кольцо
};

//class GRing3 : public GRing
//{
//public:
//	//int Behave;
//public:
//	GRing3(int l, int r, int t, int b, int x, int y, int delta, int behave);	//Конструктор
//	~GRing3();																		//Деструктор
//	void NewX();																	//Генерация новой координаты X
//	void NewY();																	//Генерация новой координаты Y
//	void Show();																	//Рисуем кольцо 
//	void Hide();																	//Затираем кольцо
//};

class GRing2 : public GRing
{
public:
	//int Behave;
public:
	GRing2(int l, int r, int t, int b, int x, int y, int delta, int behave);	//Конструктор
	~GRing2();																		//Деструктор
	void NewX();																	//Генерация новой координаты X
	void NewY();																	//Генерация новой координаты Y
	void Show();																	//Рисуем кольцо 
	void Hide();																	//Затираем кольцо
};

/*-----------------------  Класс BRing  ----------------------------------*/
class BRing : public Ring
{
public:
	//int Behave = -1;
public:
	BRing(int l, int r, int t, int b, int x, int y, int delta, int behave);	//Конструктор
	~BRing();																		//Деструктор
	void NewX();																	//Генерация новой координаты X
	void NewY();																	//Генерация новой координаты Y
	void Show();																	//Рисуем кольцо 
	void Hide();																	//Затираем кольцо
};

