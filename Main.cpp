/**************************************************************************
*                      �  �  �  �      �  �  �                            *
*-------------------------------------------------------------------------*
*                                                                         *
* Project Name  :           kursovaya                                     *
* Project Type  : Win32 Console application                               *
* File Name     : Main.cpp                                                *
* Language      : Visual C++           MS VS 2019                         *
* Programmer(s) : �������� �.�.                                           *
* Modified By   : �������� �.�.                                           *
* Created       : 28 / 04 / 2020                                          *
* Last Revision : 24 / 05 / 2020                                          *
* Comment(s)    : �������� ������                                         *
*                                                                         *
***************************************************************************/
#pragma once                  
#include <windows.h>
#include <iostream>
#include "Classes.h" 		//���������� �������
#include "GetConlWin.h"		//��������� �� ���������� ����

using namespace std;
//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

HDC hdc;	// ������� �������� ����������
			// �������� ���������� �� ���� ��� ���������,
			// ���������� �������� ���������� �� ����� ����������
			// � ���� ����������� ����������� ���������

//������� ��� ��������� ��������� ���� ��������
void CoordinatesCheck(Ring* Ring1, Ring* Ring2);		//��������� - 2 ������� ������ Ring
void CoordinatesCheck(Ring* Ring1, Human* Human1);		//��������� - ������ ������ Human � ������ Ring
void CoordinatesCheck(Ring* Ring1, Human* Human1, Ring* Ring2);//��������� - ������ ������ Human � 2 ������ Ring

void main()
{
	//���������� � ������������� ����������
	int x0 = 200, y0 = 200;				//��������� ���������� �����
	int Col = 5, Row = 4;				//���-�� ��������, ���-�� �����
	int Side = 40;						//������ ��������
	int StartRings = 1, EndRings = 10;	//��������� ���-�� �����, �������� ���-�� �����
	
	//��� ����������� ���������
	setlocale(LC_ALL, "rus");

	//������� ���������� ����������� ����
	HWND hwnd = GetConcolWindow();

	//���� ���������� ���������� - ����� ��������
	if (hwnd != NULL)
	{
		//������� �������� ���������� ��� ����������� ����
		hdc = GetWindowDC(hwnd);

		//���� �������� ���������� - ����� ��������
		if (hdc != 0)
		{
			cout << "�������:\n";
			cout << "����������� ��������� �����, ����, ������, �����.\n";
			cout << "��� ��������� �������(����� ���������� � ���� ������� � �������) " << EndRings - StartRings << " ����� �����.\n";
			cout << "��� ������ �������� ������, ���������� ��������� ����� ������������ �� 1.\n";
			
			//������ ���� �� �������� ����� �������������
			Map* AMap = new Map(Col, Row, x0, y0, Side);											//������ ��������� �� ������ ������ Map
			AMap->Create();																			//������ � ���� �����
			
			//������ ���������, ������� ����� ���������
			Human* AHuman = new Human(x0, x0 + Side * Col, y0, y0 + Side * Row, x0, y0, Side / 2, StartRings);	//������ ������ ������ Human
			AHuman->Show();																			//������ � ���� �������� 
			AHuman->Rings = StartRings;																		//��������� ������ �������� ������������ � ����

			//������ ������� ������, ������� ���� ����� ���������
			Ring* AGRing;
			GRing AGoodRing(x0, x0 + Side * Col, y0, y0 + Side * Row, x0 + Side, y0 + Side, Side / 2, 1);	//������ ������ ������ GRing
			AGRing = &AGoodRing;
			AGRing->NewX();																		//���������� ����� ���������� X ������ 
			AGRing->NewY();																		//���������� ����� ���������� Y ������ 
			CoordinatesCheck(AGRing, AHuman);													//����� ������  � ������� �� ��������� � ����� �����
			AGRing->Show();																		//������ � ���� ������

			//������ ������ ������, ������� �� ���� ����� ���������
			Ring* ABRing;
			BRing ABadRing(x0, x0 + Side * Col, y0, y0 + Side * Row, x0 + Side, y0 + Side, Side / 2, -1);	//������ ������ ������ GRing
			ABRing = &ABadRing;
			ABRing->NewX();																		//���������� ����� ���������� X ������ 
			ABRing->NewY();																		//���������� ����� ���������� Y ������ 
			CoordinatesCheck(ABRing, AGRing);													//����� ������ ������ �� ���� � ����� ����� � ��������� � ������� �������
			ABRing->Show();																		//������ � ���� ������
			
			Ring* AGRing2;
			GRing2 Ring2(x0, x0 + Side * Col, y0, y0 + Side * Row, x0 + Side, y0 + Side, Side / 2, 2);
			AGRing2 = &Ring2;
			AGRing2->NewX();
			AGRing2->NewY();
		
			CoordinatesCheck(AGRing2, AGRing);
			AGRing2->Show();

			//������� ������� ��������� �����
			cout << "��������� ������:\t" << AHuman->Rings;
			
			while(1)													
			{
				Sleep(250);
				AHuman->Drag(Side);																	//���������� �������� 
				if (AHuman->GetX() == AGRing->GetX() && AHuman->GetY() == AGRing->GetY())		//���� ���������� �������� � �������� ������ ���������(�.�. ������� � ������ � ����� ��������)
				{
					AGRing->Hide();																	//�������� ������ 
					AHuman->Show();																	//������ �������� 
					AGRing->NewX();																	//���������� ����� ���������� X ������ 
					AGRing->NewY();																	//���������� ����� ���������� Y ������ 
					CoordinatesCheck(AGRing, AHuman, ABRing);										//����� ������� ������ �� ��������� � ����� ����� � ��������� � ������ �������
					AHuman->Rings += AGRing->Behave;												//����������� ���-�� ��������� ����� �� ����	
					if (AHuman->Rings != EndRings) AGRing->Show();									//���� ���-�� ��������� ����� ������� ���������, �� ������ ����� ������
					else { cout << "\b\b " << AHuman->Rings; break; }								//����� ���� �����������
					cout << "\b\b " << AHuman->Rings;
				}

				if (AHuman->GetX() == ABRing->GetX() && AHuman->GetY() == ABRing->GetY())		//���� ���������� �������� � ������� ������ ���������(�.�. ������� � ������ � ����� ��������)
				{
					ABRing->Hide();																	//�������� ������ 
					AHuman->Show();																	//������ �������� 
					ABRing->NewX();																	//���������� ����� ���������� X ������ 
					ABRing->NewY();																	//���������� ����� ���������� Y ������ 
					CoordinatesCheck(ABRing, AHuman, AGRing);										//����� ������ ������ �� ��������� � ����� ����� � ��������� � ������� �������
					ABRing->Show();																	//������ ����� ������
					AHuman->Rings += ABRing->Behave;												//��������� ���-�� ��������� ����� �� ����	
					cout << "\b\b " << AHuman->Rings;
				}
				ABRing->Hide();																	//�������� ������ 
				ABRing->NewX();																	//���������� ����� ���������� X ������ 
				ABRing->NewY();																	//���������� ����� ���������� Y ������ 
				CoordinatesCheck(ABRing, AHuman, AGRing);										//����� ������ ������ �� ��������� � ����� ����� � ��������� � ������� �������
				CoordinatesCheck(ABRing, AGRing2);
				ABRing->Show();

				if (AHuman->GetX() == AGRing2->GetX() && AHuman->GetY() == AGRing2->GetY())		//���� ���������� �������� � �������� ������ ���������(�.�. ������� � ������ � ����� ��������)
				{
					AGRing2->Hide();																	//�������� ������ 
					AHuman->Show();																	//������ �������� 
					AGRing2->NewX();																	//���������� ����� ���������� X ������ 
					AGRing2->NewY();																	//���������� ����� ���������� Y ������ 
					CoordinatesCheck(AGRing2, AHuman, ABRing);										//����� ������� ������ �� ��������� � ����� ����� � ��������� � ������ �������
					CoordinatesCheck(AGRing2, AGRing);
					AHuman->Rings *= AGRing2->Behave;												//����������� ���-�� ��������� ����� �� ����	
					if (AHuman->Rings < EndRings) AGRing2->Show();									//���� ���-�� ��������� ����� ������� ���������, �� ������ ����� ������
					else { cout << "\b\b " << AHuman->Rings; break; }								//����� ���� �����������
					cout << "\b\b " << AHuman->Rings;
				}

			}// end while(1)
		}// end if(hdc!=0) 
	}//end if(hwnd != NULL)
}//end main

void CoordinatesCheck(Ring* Ring1, Ring* Ring2)
{
	while (Ring1->GetX() == Ring2->GetX() && Ring1->GetY() == Ring2->GetY())		//���� � ����� �� ����� ������ ����������
	{ 
		Ring1->NewX();																//���������� ����� X ���������� 
		Ring1->GetY();																//���������� ����� Y ���������� 
	}
}

void CoordinatesCheck(Ring* Ring1, Human* Human1)
{
	//���� � ������ ���������� �� ����� ���������� �� ��������� ��������
	while (Ring1->GetX() == Human1->GetX() && Ring1->GetY() == Human1->GetY())
	{
		Ring1->NewX();																//���������� ����� X ���������� ������
		Ring1->GetY();																//���������� ����� Y ���������� ������
	}
}

void CoordinatesCheck(Ring* Ring1, Human* Human1, Ring* Ring2)
{
	//���� � ������� ������ ���������� �� ����� ���������� �� ��������� �������� � ��������� ������� ������
	while ( (Ring1->GetX() == Human1->GetX() && Ring1->GetY() == Human1->GetY()) || (Ring1->GetX() == Ring2->GetX() && Ring1->GetY() == Ring2->GetY()) )
	{
		Ring1->NewX();																//���������� ����� X ���������� ������
		Ring1->GetY();																//���������� ����� Y ���������� ������
	}
	//cout << Ring1->GetX() << "\t" << Ring2->GetY() << endl;
}