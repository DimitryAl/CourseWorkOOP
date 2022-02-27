/**************************************************************************
*                      К  У  Р  С      О  О  П                            *
*-------------------------------------------------------------------------*
*                                                                         *
* Project Name  :           kursovaya                                     *
* Project Type  : Win32 Console application                               *
* File Name     : Main.cpp                                                *
* Language      : Visual C++           MS VS 2019                         *
* Programmer(s) : Алексеев Д.А.                                           *
* Modified By   : Алексеев Д.А.                                           *
* Created       : 28 / 04 / 2020                                          *
* Last Revision : 24 / 05 / 2020                                          *
* Comment(s)    : Курсовой проект                                         *
*                                                                         *
***************************************************************************/
#pragma once                  
#include <windows.h>
#include <iostream>
#include "Classes.h" 		//Объявление классов
#include "GetConlWin.h"		//Указатель на консольное окно

using namespace std;
//Макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

HDC hdc;	// Объявим контекст устройства
			// Контекст устройства по сути это структура,
			// содержащая описание видеокарты на вашем компьютере
			// и всех необходимых графических элементов

//Функции для сравнения координат двух объектов
void CoordinatesCheck(Ring* Ring1, Ring* Ring2);		//аргументы - 2 объекта класса Ring
void CoordinatesCheck(Ring* Ring1, Human* Human1);		//аргументы - объект класса Human и класса Ring
void CoordinatesCheck(Ring* Ring1, Human* Human1, Ring* Ring2);//аргументы - объект класса Human и 2 класса Ring

void main()
{
	//объявление и инициализация переменных
	int x0 = 200, y0 = 200;				//Стартовые координаты карты
	int Col = 5, Row = 4;				//Кол-во столбцов, кол-во строк
	int Side = 40;						//Размер квадрата
	int StartRings = 1, EndRings = 10;	//Начальное кол-во колец, конечное кол-во колец
	
	//Для отображения кириллицы
	setlocale(LC_ALL, "rus");

	//Получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();

	//Если дескриптор существует - можем работать
	if (hwnd != NULL)
	{
		//Получим контекст устройства для консольного окна
		hdc = GetWindowDC(hwnd);

		//Если контекст существует - можем работать
		if (hdc != 0)
		{
			cout << "Правила:\n";
			cout << "Перемещение стрелками вверх, вниз, вправо, влево.\n";
			cout << "Для окончания собрать(зайти человечком в один квадрат с кольцом) " << EndRings - StartRings << " жёлтых колец.\n";
			cout << "При взятии красного кольца, количетсво собранных колец уменьшаеться на 1.\n";
			
			//Рисуем поле по которому будем передвигаться
			Map* AMap = new Map(Col, Row, x0, y0, Side);											//Создаём указатель на объект класса Map
			AMap->Create();																			//Рисуем в окне карту
			
			//Создаём персонажа, которым будем управлять
			Human* AHuman = new Human(x0, x0 + Side * Col, y0, y0 + Side * Row, x0, y0, Side / 2, StartRings);	//Создаём объект класса Human
			AHuman->Show();																			//Рисуем в окне человека 
			AHuman->Rings = StartRings;																		//Собранные кольца человека приравниваем к нулю

			//Создаём хорошее кольцо, которое надо будет подбирать
			Ring* AGRing;
			GRing AGoodRing(x0, x0 + Side * Col, y0, y0 + Side * Row, x0 + Side, y0 + Side, Side / 2, 1);	//Создаём объект класса GRing
			AGRing = &AGoodRing;
			AGRing->NewX();																		//Генерируем новую координату X кольца 
			AGRing->NewY();																		//Генерируем новую координату Y кольца 
			CoordinatesCheck(AGRing, AHuman);													//Чтобы кольцо  и человек не появились в одном месте
			AGRing->Show();																		//Рисуем в окне кольцо

			//Создаём плохое кольцо, которое не надо будет подбирать
			Ring* ABRing;
			BRing ABadRing(x0, x0 + Side * Col, y0, y0 + Side * Row, x0 + Side, y0 + Side, Side / 2, -1);	//Создаём объект класса GRing
			ABRing = &ABadRing;
			ABRing->NewX();																		//Генерируем новую координату X кольца 
			ABRing->NewY();																		//Генерируем новую координату Y кольца 
			CoordinatesCheck(ABRing, AGRing);													//Чтобы плохое кольцо не было в одном месте с человеком и хорошим кольцом
			ABRing->Show();																		//Рисуем в окне кольцо
			
			Ring* AGRing2;
			GRing2 Ring2(x0, x0 + Side * Col, y0, y0 + Side * Row, x0 + Side, y0 + Side, Side / 2, 2);
			AGRing2 = &Ring2;
			AGRing2->NewX();
			AGRing2->NewY();
		
			CoordinatesCheck(AGRing2, AGRing);
			AGRing2->Show();

			//Выводим счетчик собранных колец
			cout << "Собранные кольца:\t" << AHuman->Rings;
			
			while(1)													
			{
				Sleep(250);
				AHuman->Drag(Side);																	//Перемещаем человека 
				if (AHuman->GetX() == AGRing->GetX() && AHuman->GetY() == AGRing->GetY())		//Если координаты человека и хорошего кольца совпадают(т.е. человек и кольцо в одном квадрате)
				{
					AGRing->Hide();																	//Затираем кольцо 
					AHuman->Show();																	//Рисуем человека 
					AGRing->NewX();																	//Генерируем новую координату X кольца 
					AGRing->NewY();																	//Генерируем новую координату Y кольца 
					CoordinatesCheck(AGRing, AHuman, ABRing);										//Чтобы хорошее кольцо не появилось в одном месте с человеком и плохим кольцом
					AHuman->Rings += AGRing->Behave;												//Увеличиваем кол-во собранных колец на одно	
					if (AHuman->Rings != EndRings) AGRing->Show();									//Если кол-во собранных колец неравно конечному, то рисуем новое кольцо
					else { cout << "\b\b " << AHuman->Rings; break; }								//Иначе цикл завершается
					cout << "\b\b " << AHuman->Rings;
				}

				if (AHuman->GetX() == ABRing->GetX() && AHuman->GetY() == ABRing->GetY())		//Если координаты человека и плохого кольца совпадают(т.е. человек и кольцо в одном квадрате)
				{
					ABRing->Hide();																	//Затираем кольцо 
					AHuman->Show();																	//Рисуем человека 
					ABRing->NewX();																	//Генерируем новую координату X кольца 
					ABRing->NewY();																	//Генерируем новую координату Y кольца 
					CoordinatesCheck(ABRing, AHuman, AGRing);										//Чтобы плохое кольцо не появилось в одном месте с человеком и хорошим кольцом
					ABRing->Show();																	//Рисуем новое кольцо
					AHuman->Rings += ABRing->Behave;												//Уменьшаем кол-во собранных колец на одно	
					cout << "\b\b " << AHuman->Rings;
				}
				ABRing->Hide();																	//Затираем кольцо 
				ABRing->NewX();																	//Генерируем новую координату X кольца 
				ABRing->NewY();																	//Генерируем новую координату Y кольца 
				CoordinatesCheck(ABRing, AHuman, AGRing);										//Чтобы плохое кольцо не появилось в одном месте с человеком и хорошим кольцом
				CoordinatesCheck(ABRing, AGRing2);
				ABRing->Show();

				if (AHuman->GetX() == AGRing2->GetX() && AHuman->GetY() == AGRing2->GetY())		//Если координаты человека и хорошего кольца совпадают(т.е. человек и кольцо в одном квадрате)
				{
					AGRing2->Hide();																	//Затираем кольцо 
					AHuman->Show();																	//Рисуем человека 
					AGRing2->NewX();																	//Генерируем новую координату X кольца 
					AGRing2->NewY();																	//Генерируем новую координату Y кольца 
					CoordinatesCheck(AGRing2, AHuman, ABRing);										//Чтобы хорошее кольцо не появилось в одном месте с человеком и плохим кольцом
					CoordinatesCheck(AGRing2, AGRing);
					AHuman->Rings *= AGRing2->Behave;												//Увеличиваем кол-во собранных колец на одно	
					if (AHuman->Rings < EndRings) AGRing2->Show();									//Если кол-во собранных колец неравно конечному, то рисуем новое кольцо
					else { cout << "\b\b " << AHuman->Rings; break; }								//Иначе цикл завершается
					cout << "\b\b " << AHuman->Rings;
				}

			}// end while(1)
		}// end if(hdc!=0) 
	}//end if(hwnd != NULL)
}//end main

void CoordinatesCheck(Ring* Ring1, Ring* Ring2)
{
	while (Ring1->GetX() == Ring2->GetX() && Ring1->GetY() == Ring2->GetY())		//Пока у колец не будут разные координаты
	{ 
		Ring1->NewX();																//Генерируем новые X координаты 
		Ring1->GetY();																//Генерируем новые Y координаты 
	}
}

void CoordinatesCheck(Ring* Ring1, Human* Human1)
{
	//Пока у кольца координаты не будут отличаться от координат человека
	while (Ring1->GetX() == Human1->GetX() && Ring1->GetY() == Human1->GetY())
	{
		Ring1->NewX();																//Генерируем новые X координаты кольца
		Ring1->GetY();																//Генерируем новые Y координаты кольца
	}
}

void CoordinatesCheck(Ring* Ring1, Human* Human1, Ring* Ring2)
{
	//Пока у первого кольца координаты не будут отличаться от координат человека и координат второго кольца
	while ( (Ring1->GetX() == Human1->GetX() && Ring1->GetY() == Human1->GetY()) || (Ring1->GetX() == Ring2->GetX() && Ring1->GetY() == Ring2->GetY()) )
	{
		Ring1->NewX();																//Генерируем новые X координаты кольца
		Ring1->GetY();																//Генерируем новые Y координаты кольца
	}
	//cout << Ring1->GetX() << "\t" << Ring2->GetY() << endl;
}