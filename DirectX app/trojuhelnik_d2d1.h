#pragma once

#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "figure_d2d1.h"

using namespace std;



class Trojuhelnik : public Objekt {
public:
	Trojuhelnik() {
		figp.type_id = TRIANGLE;
	}
	Trojuhelnik(ID2D1HwndRenderTarget* _new, TrojBody troj) {
		figp.type_id = TRIANGLE;
		figp.Ax = troj.Ax;
		m_target = _new;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Cx;
		figp.By = troj.Ay;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}
	Trojuhelnik(ID2D1HwndRenderTarget* _new, TrojBody troj, int _id) {
		figp.type_id = TRIANGLE;
		id = _id;
		figp.id = id;
		m_target = _new;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Cx;
		figp.By = troj.Ay;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}
	Trojuhelnik(ID2D1HwndRenderTarget* _new, TrojBody2 troj) {
		figp.type_id = TRIANGLE;
		m_target = _new;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Bx;
		figp.By = troj.By;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}//ID2D1SolidColorBrush
	Trojuhelnik(ID2D1HwndRenderTarget* _new, TrojBody2 troj, int _id) {
		figp.type_id = TRIANGLE;
		m_target = _new;
		id = _id;
		figp.id = id;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Bx;
		figp.By = troj.By;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}
	Trojuhelnik(ID2D1HwndRenderTarget* _new, ID2D1SolidColorBrush* _newb, TrojBody2 troj, int _id) {
		figp.type_id = TRIANGLE;
		m_target = _new;
		m_brush = _newb;
		id = _id;
		figp.id = id;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Bx;
		figp.By = troj.By;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}
	Trojuhelnik(ID2D1HwndRenderTarget* _new, ID2D1SolidColorBrush* _newb, TrojBody troj, int _id) {
		figp.type_id = TRIANGLE;
		id = _id;
		figp.id = id;
		m_target = _new;
		m_brush = _newb;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Cx;
		figp.By = troj.Ay;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}
	Trojuhelnik(TrojBody2 troj, int _id) {
		figp.type_id = TRIANGLE;
		id = _id;
		figp.id = id;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Bx;
		figp.By = troj.By;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}
	Trojuhelnik& operator() (ID2D1HwndRenderTarget* _new, TrojBody2 troj, int _id) {
		figp.type_id = TRIANGLE;
		m_target = _new;
		id = _id;
		figp.id = id;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Bx;
		figp.By = troj.By;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
		return *this;
	}
	void SetAll(ID2D1HwndRenderTarget* _new, TrojBody troj) {
		m_target = _new;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Cx;
		figp.By = troj.Ay;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}
	void SetAll2(ID2D1HwndRenderTarget* _new, TrojBody2 troj) {
		m_target = _new;
		figp.Ax = troj.Ax;
		figp.Ay = troj.Ay;
		figp.Bx = troj.Bx;
		figp.By = troj.By;
		figp.Cx = troj.Cx;
		figp.Cy = troj.Cy;
	}
	~Trojuhelnik() {
		id = NULL;
		hdc = NULL;
		figp.Ax = NULL;
		figp.Ay = NULL;
		figp.Bx = NULL;
		figp.By = NULL;
		figp.Cx = NULL;
		figp.Cy = NULL;
	}
	void Draw() {
		if (figp.out_color == 0) {
			figp.out_color = RGB(0, 0, 0);
		}
		if (figp.fill_color == 0) {
			figp.fill_color = RGB(255, 255, 255);
		}
		figp.use_color = true;
		rgb out = GetRGBfromColorref(figp.out_color);
		rgb fill = GetRGBfromColorref(figp.fill_color);

		figp.full = to_string(figp.type_id) + " " + to_string(figp.id) + " " + to_string(figp.Ax) + " " + to_string(figp.Ay) + " " + to_string(figp.Bx) + " " + to_string(figp.By) + " " + to_string(figp.Cx) + " " + to_string(figp.Cy) + " " + to_string(figp.angle_rotate) + " " + to_string(figp.use_color) + " " + to_string(fill.red) + " " + to_string(fill.green) + " " + to_string(fill.blue) + " " + to_string(out.red) + " " + to_string(out.green) + " " + to_string(out.blue);
		//MoveToEx(hdc, figp.Ax, figp.Ay, NULL);
		D2D1_POINT_2F B, C, A;
		B.x = figp.Bx;
		B.y = figp.By;
		A.x = figp.Ax;
		A.y = figp.Ay;
		C.x = figp.Cx;
		C.y = figp.Cy;
		m_target->DrawLine(A, B, m_brush);
		m_target->DrawLine(B, C, m_brush);
		m_target->DrawLine(C, A, m_brush);
	}

	void Rotate(float alfa, bool psi = FALSE) {
		D2D1_POINT_2F B, C, A;
		B.x = figp.Bx;
		B.y = figp.By;
		A.x = figp.Ax;
		A.y = figp.Ay;
		C.x = figp.Cx;
		C.y = figp.Cy;
		D2D1_POINT_2F n1, n2, n3;
		n1 = RotatePrimka2(A, B, alfa,true);
		n2 = RotatePrimka2(B, C, alfa,true);
		n3 = RotatePrimka2(A, C, alfa,true);
		figp.Bx = n2.x;
		figp.By=n2.y;
		figp.Ax=n3.x;
		figp.Ay=n3.y;
		figp.Cx=n1.x;
		figp.Cy=n1.y;
		Draw();
	}

	void SetColor2(COLORREF new_fill) {
		figp.fill_color = new_fill;
	}
	void SetBrush(ID2D1SolidColorBrush* _new) {
		m_brush = _new;
	}
	void Erase() {
		D2D1_POINT_2F B, C, A;
		B.x = figp.Bx;
		B.y = figp.By;
		A.x = figp.Ax;
		A.y = figp.Ay;
		C.x = figp.Cx;
		C.y = figp.Cy;
		D2D1_COLOR_F color, prev;
		prev = m_brush->GetColor();
		color.a = 255;
		color.g = 255;
		color.b = 255;
		color.r = 255;
		m_brush->SetColor(color);
		m_target->DrawLine(A, B, m_brush);
		m_target->DrawLine(B, C, m_brush);
		m_target->DrawLine(C, A, m_brush);
		color.a = 255;
		color.g = 255;
		color.b = 255;
		color.r = 255;
		m_brush->SetColor(prev);
	}
	void ChangePoints(TrojBody troj) {
		figp.Ax = troj.Ax;
		figp.Bx = troj.Cx;
		figp.Cx = troj.Cx;
		figp.Ay = troj.Ay;
		figp.By = troj.Ay;
		figp.Cy = troj.Cy;
	}
	void ChangePoints2(TrojBody2 troj) {
		figp.Ax = troj.Ax;
		figp.Bx = troj.Bx;
		figp.Cx = troj.Cx;
		figp.Ay = troj.Ay;
		figp.By = troj.By;
		figp.Cy = troj.Cy;
	}
	void InitDetectionPoints() {
		//A-B
		int max_AB_y = 0;
		int min_AB_y = 0;
		int max_AB_x = 0;
		int min_AB_x = 0;
		if (figp.Ay > figp.By) {
			max_AB_y = figp.Ay;
			min_AB_y = figp.By;
			if (figp.Ax > figp.Bx) {
				max_AB_x = figp.Ax;
				min_AB_x = figp.Bx;
			}
			else if (figp.Ax < figp.Bx) {
				max_AB_x = figp.Bx;
				min_AB_x = figp.Ax;
			}
		}
		else if (figp.Ay < figp.By) {
			max_AB_y = figp.By;
			min_AB_y = figp.Ay;
			if (figp.Ax > figp.Bx) {
				max_AB_x = figp.Ax;
				min_AB_x = figp.Bx;
			}
			else if (figp.Ax < figp.Bx) {
				max_AB_x = figp.Bx;
				min_AB_x = figp.Ax;
			}
		}
		figp.num_detect_points_x = max_AB_x - min_AB_x;
		figp.num_detect_points_y = max_AB_y - min_AB_y;
		for (int x = max_AB_x; x > min_AB_x; x--) {
			figp.detect_points_x[x - max_AB_x] = x;
		}
		for (int y = max_AB_y; y > min_AB_y; y--) {
			figp.detect_points_y[y - max_AB_y] = y;
		}
		//B-C
		int max_BC_y = 0;
		int min_BC_y = 0;
		int max_BC_x = 0;
		int min_BC_x = 0;
		if (figp.Cy > figp.By) {
			max_BC_y = figp.Cy;
			min_BC_y = figp.By;
			if (figp.Cx > figp.Bx) {
				max_BC_x = figp.Cx;
				min_BC_x = figp.Bx;
			}
			else if (figp.Cx < figp.Bx) {
				max_BC_x = figp.Bx;
				min_BC_x = figp.Cx;
			}
		}
		else if (figp.Cy < figp.By) {
			max_BC_y = figp.By;
			min_BC_y = figp.Cy;
			if (figp.Cx > figp.Bx) {
				max_BC_x = figp.Cx;
				min_BC_x = figp.Cx;
			}
			else if (figp.Cx < figp.Bx) {
				max_BC_x = figp.Bx;
				min_BC_x = figp.Cx;
			}
		}
		figp.num_detect_points_x = figp.num_detect_points_x + (max_BC_x - min_BC_x);
		figp.num_detect_points_y = figp.num_detect_points_y + (max_BC_y - min_BC_y);
		for (int x = max_BC_x; x > min_BC_x; x--) {
			figp.detect_points_x[x - max_BC_x] = x;
		}
		for (int y = max_BC_y; y > min_BC_y; y--) {
			figp.detect_points_y[y - max_BC_y] = y;
		}
		//A-C
		int max_AC_y = 0;
		int min_AC_y = 0;
		int max_AC_x = 0;
		int min_AC_x = 0;
		if (figp.Cy > figp.Ay) {
			max_AC_y = figp.Cy;
			min_AC_y = figp.Ay;
			if (figp.Cx > figp.Ax) {
				max_AC_x = figp.Cx;
				min_AC_x = figp.Ax;
			}
			else if (figp.Cx < figp.Ax) {
				max_AC_x = figp.Ax;
				min_AC_x = figp.Cx;
			}
		}
		else if (figp.Cy < figp.Ay) {
			max_AC_y = figp.Ay;
			min_AC_y = figp.Cy;
			if (figp.Cx > figp.Ax) {
				max_AC_x = figp.Cx;
				min_AC_x = figp.Cx;
			}
			else if (figp.Cx < figp.Ax) {
				max_AC_x = figp.Ax;
				min_AC_x = figp.Cx;
			}
		}
		figp.num_detect_points_x = figp.num_detect_points_x + (max_AC_x - min_AC_x);
		figp.num_detect_points_y = figp.num_detect_points_y + (max_AC_y - min_AC_y);
		for (int x = max_AC_x; x > min_AC_x; x--) {
			figp.detect_points_x[x - max_AC_x] = x;
		}
		for (int y = max_AC_y; y > min_AC_y; y--) {
			figp.detect_points_y[y - max_AC_y] = y;
		}

	}

	void Move2(int plus_x, int plus_y, bool create_copy) {
		if (!create_copy) {
			Erase();
		}
		figp.Ay = figp.Ay + plus_y;
		figp.By = figp.By + plus_y;
		figp.Cy = figp.Cy + plus_y;
		figp.Ax = figp.Ax + plus_x;
		figp.Bx = figp.Bx + plus_x;
		figp.Cx = figp.Cx + plus_x;
		Draw();
	}
	void Move_math(int plus_x, int plus_y) {
		MessageBox(NULL, L"Move_math()", L"Move_math()", MB_OK);
		figp.Ay = figp.Ay + plus_y;
		figp.By = figp.By + plus_y;
		figp.Cy = figp.Cy + plus_y;
		figp.Ax = figp.Ax + plus_x;
		figp.Bx = figp.Bx + plus_x;
		figp.Cx = figp.Cx + plus_x;
	}
	void Move(int plus_x, int plus_y, bool create_copy) {
		if (!create_copy) {
			Erase();
		}
		if (plus_y > 0) {
			if (figp.move_plus_y == true) {
				figp.Ay = figp.Ay + plus_y;
				figp.By = figp.By + plus_y;
				figp.Cy = figp.Cy + plus_y;
			}
			else {
				//nic
			}
		}
		else if (plus_y < 0) {
			if (figp.move_minus_y == true) {
				figp.Ay = figp.Ay + plus_y;
				figp.By = figp.By + plus_y;
				figp.Cy = figp.Cy + plus_y;
			}
			else {
				//nic
			}
		}
		else if (plus_x > 0) {
			if (figp.move_plus_x == true) {
				figp.Ax = figp.Ax + plus_x;
				figp.Bx = figp.Bx + plus_x;
				figp.Cx = figp.Cx + plus_x;
			}
			else {
				//nic
			}
		}
		else if (plus_x < 0) {
			if (figp.move_minus_x == true) {
				figp.Ax = figp.Ax + plus_x;
				figp.Bx = figp.Bx + plus_x;
				figp.Cx = figp.Cx + plus_x;
			}
			else {
				//nic
			}
		}
		Draw();
	}
	void Zoom(int percent_x, int percent_y) {
		figp.Ax = (figp.Ax / 100) * percent_x;
		figp.Bx = (figp.Bx / 100) * percent_x;
		figp.Cx = (figp.Cx / 100) * percent_x;
		figp.Ay = (figp.Ay / 100) * percent_y;
		figp.By = (figp.By / 100) * percent_y;
		figp.Cy = (figp.Cy / 100) * percent_y;
		Draw();
	}
	void Zoom_math(int percent_x, int percent_y) {
		figp.Ax = (figp.Ax / 100) * percent_x;
		figp.Bx = (figp.Bx / 100) * percent_x;
		figp.Cx = (figp.Cx / 100) * percent_x;
		figp.Ay = (figp.Ay / 100) * percent_y;
		figp.By = (figp.By / 100) * percent_y;
		figp.Cy = (figp.Cy / 100) * percent_y;
	}
	//need win for GetWindowRect()
	bool CurorOn(HWND win) {
		RECT pos;
		POINT cursor;
		pos.left = 0;
		pos.bottom = 0;
		pos.right = 0;
		pos.top = 0;
		cursor.x = 0;
		cursor.y = 0;

		GetCursorPos(&cursor);
		GetWindowRect(win, &pos);
		if (use_own_points == false) {
			int x_ar[3] = { figp.Ax, figp.Bx, figp.Cx };//0,1,2
			int y_ar[3] = { figp.Ay, figp.By, figp.Cy };
			int min_x = FindMin(x_ar, 3);
			int max_x = FindMax(x_ar, 3);
			int min_y = FindMin(y_ar, 3);
			int max_y = FindMax(y_ar, 3);
			figp.cursor_hitbox_area.left = min_x;
			figp.cursor_hitbox_area.top = min_y;
			figp.cursor_hitbox_area.right = max_x;
			figp.cursor_hitbox_area.bottom = max_y;
			//y horni roh, x horni roh, y pravy dolni, x pravy dolni
			if (cursor.y > (pos.top + min_y + 40) && cursor.x > (pos.left + min_x) && cursor.y < (pos.top + max_y + 40) && cursor.x < (pos.left + max_x)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (cursor.y > (pos.top + figp.cursor_hitbox_area.top + 40) && cursor.x > (pos.left + figp.cursor_hitbox_area.left) && cursor.y < (pos.top + figp.cursor_hitbox_area.bottom + 40) && cursor.x < (pos.left + figp.cursor_hitbox_area.right)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	Trojuhelnik* clone() {
		return this;
	}
	Trojuhelnik* copy() {
		return this;
	}

};

