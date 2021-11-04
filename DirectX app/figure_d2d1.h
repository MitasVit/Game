#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <assert.h>
#include <string>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

using namespace std;

#ifndef MAX
#define MAX 2000
#endif

#define RECTANGLE                     1
#define SQUARE                        2
#define TRIANGLE                      3
#define TRIANGLE_RIGHT_ANGLE          4
#define IMAGE                         5

#define RECTANGLE_COPYMOVE            10
#define SQUARE_COPYMOVE               20
#define TRIANGLE_COPYMOVE             30
#define TRIANGLE_RIGHT_ANGLE_COPYMOVE 40
#define IMAGE_COPYMOVE                50

typedef string Figure;
int Find_number(int p[], int n, int x);
struct TrojBody2 {
	int Ax;
	int Ay;
	int Bx;
	int By;
	int Cx;
	int Cy;
};


struct TrojBody {
	int Ax;
	int Ay;
	int Cx;
	int Cy;
};

struct FigurePart {
	int x = 0;
	int y = 0;
	int id = 0;
	int type_id = 0;
	int width = 0;
	int height = 0;
	int angle_rotate = 0;
	COLORREF out_color = 0;
	COLORREF fill_color = 0;
	bool use_color = 0;

	//Window bitmap definition
	int Ax = 0;
	int Ay = 0;
	int Bx = 0;
	int By = 0;
	int Cx = 0;
	int Cy = 0;

	bool move_plus_x;//movable on plus x -> doprava
	bool move_plus_y;//movable on plus y -> dolu
	bool move_minus_x;//movable on minus x -> doleva
	bool move_minus_y;//movable on minus y -> nahoru
	int detect_points_x[MAX];//detect points for colision objects
	int detect_points_y[MAX];//detect points for colision objects
	int num_detect_points_x;
	int num_detect_points_y;
	RECT cursor_hitbox_area;//left->x horni levy roh, top->y horni levy roh, right->x dolni pravy roh, bottom->y dolni pravy roh
	string full;
};


struct rgb {
	int red;
	int green;
	int blue;
};

rgb GetRGBfromColorref(COLORREF color) {
	rgb tmp;
	tmp.red = GetRValue(color);
	tmp.green = GetGValue(color);
	tmp.blue = GetBValue(color);
	return tmp;
}

FigurePart ParseFigurePart(string fig_full) {
	FigurePart tmp;
	tmp.full = fig_full;
	stringstream str(fig_full);
	int id_type;
	str >> id_type;

	assert(id_type == RECTANGLE || id_type == SQUARE || id_type == RECTANGLE || id_type == SQUARE || id_type == TRIANGLE || id_type == TRIANGLE_RIGHT_ANGLE || id_type == IMAGE || id_type == RECTANGLE_COPYMOVE || id_type == SQUARE_COPYMOVE || id_type == TRIANGLE_COPYMOVE || id_type == TRIANGLE_RIGHT_ANGLE_COPYMOVE || id_type == IMAGE_COPYMOVE);
	if (id_type == RECTANGLE) {
		int id, x, y, width, height, angle_rotate, use_color;
		str >> id;
		str >> x;
		str >> y;
		str >> width;
		str >> height;
		str >> angle_rotate;
		str >> use_color;
		if (use_color == 1) {
			int r, g, b, r_f, g_f, b_f;//r,g,b -> vypln, r_f, f_f, b_f -> obrys
			str >> r;
			str >> g;
			str >> b;
			str >> r_f;
			str >> g_f;
			str >> b_f;
			COLORREF out = RGB(r_f, g_f, b_f);
			COLORREF fill = RGB(r, g, b);
			tmp.type_id = id_type;
			tmp.id = id;
			tmp.x = x;
			tmp.y = y;
			tmp.width = width;
			tmp.height = height;
			tmp.angle_rotate = angle_rotate;
			tmp.use_color = use_color;
			tmp.fill_color = fill;
			tmp.out_color = out;
			tmp.full = to_string(id_type) + to_string(id) + to_string(x) + to_string(y) + to_string(width) + to_string(height) + to_string(angle_rotate) + to_string(use_color) + to_string(r) + to_string(g) + to_string(b) + to_string(r_f) + to_string(g_f) + to_string(b_f) + "\n";

		}
		else {
			tmp.type_id = id_type;
			tmp.id = id;
			tmp.x = x;
			tmp.y = y;
			tmp.width = width;
			tmp.height = height;
			tmp.angle_rotate = angle_rotate;
			tmp.use_color = use_color;
			tmp.full = to_string(id_type) + to_string(id) + to_string(x) + to_string(y) + to_string(width) + to_string(height) + to_string(angle_rotate) + to_string(use_color) + "\n";
		}
		return tmp;
	}
	else if (id_type == SQUARE) {
		int id, x, y, width, angle_rotate, use_color;
		str >> id;
		str >> x;
		str >> y;
		str >> width;
		str >> angle_rotate;
		str >> use_color;
		if (use_color == 1) {
			int r, g, b, r_f, g_f, b_f;//r,g,b -> vypln, r_f, f_f, b_f -> obrys
			str >> r;
			str >> g;
			str >> b;
			str >> r_f;
			str >> g_f;
			str >> b_f;
			COLORREF out = RGB(r_f, g_f, b_f);
			COLORREF fill = RGB(r, g, b);
			tmp.type_id = id_type;
			tmp.id = id;
			tmp.x = x;
			tmp.y = y;
			tmp.width = width;
			tmp.angle_rotate = angle_rotate;
			tmp.use_color = use_color;
			tmp.fill_color = fill;
			tmp.out_color = out;
			tmp.full = to_string(id_type) + to_string(id) + to_string(x) + to_string(y) + to_string(width) + to_string(angle_rotate) + to_string(use_color) + to_string(r) + to_string(g) + to_string(b) + to_string(r_f) + to_string(g_f) + to_string(b_f) + "\n";
		}
		else {
			tmp.type_id = id_type;
			tmp.id = id;
			tmp.x = x;
			tmp.y = y;
			tmp.width = width;
			tmp.angle_rotate = angle_rotate;
			tmp.use_color = use_color;
			tmp.full = to_string(id_type) + to_string(id) + to_string(x) + to_string(y) + to_string(width) + to_string(angle_rotate) + to_string(use_color) + "\n";
		}
		return tmp;
	}
	else if (id_type == TRIANGLE) {
		int id, Ax, Ay, Bx, By, Cx, Cy, angle_rotate, use_color;
		str >> id;
		str >> Ax;
		str >> Ay;
		str >> Bx;
		str >> By;
		str >> Cx;
		str >> Cy;
		str >> angle_rotate;
		str >> use_color;
		if (use_color == 1) {
			int r, g, b, r_f, g_f, b_f;//r,g,b -> vypln, r_f, f_f, b_f -> obrys
			str >> r;
			str >> g;
			str >> b;
			str >> r_f;
			str >> g_f;
			str >> b_f;
			COLORREF out = RGB(r_f, g_f, b_f);
			COLORREF fill = RGB(r, g, b);
			tmp.type_id = id_type;
			tmp.id = id;
			tmp.Ax = Ax;
			tmp.Ay = Ay;
			tmp.Cx = Cx;
			tmp.Cy = Cy;
			tmp.Bx = Bx;
			tmp.By = By;
			tmp.angle_rotate = angle_rotate;
			tmp.use_color = use_color;
			tmp.fill_color = fill;
			tmp.out_color = out;
			tmp.full = to_string(id_type) + to_string(id) + to_string(Ax) + to_string(Ay) + to_string(Bx) + to_string(By) + to_string(Cx) + to_string(Cy) + to_string(angle_rotate) + to_string(use_color) + to_string(r) + to_string(g) + to_string(b) + to_string(r_f) + to_string(g_f) + to_string(b_f) + "\n";
		}
		else {
			tmp.type_id = id_type;
			tmp.id = id;
			tmp.Ax = Ax;
			tmp.Ay = Ay;
			tmp.Cx = Cx;
			tmp.Cy = Cy;
			tmp.Bx = Bx;
			tmp.By = By;
			tmp.angle_rotate = angle_rotate;
			tmp.use_color = use_color;
			tmp.full = to_string(id_type) + to_string(id) + to_string(Ax) + to_string(Ay) + to_string(Bx) + to_string(By) + to_string(Cx) + to_string(Cy) + to_string(angle_rotate) + to_string(use_color) + "\n";
		}
		return tmp;
	}
	else if (id_type == TRIANGLE_RIGHT_ANGLE) {
		int id, Ax, Ay, Bx, By, Cx, Cy, angle_rotate, use_color;
		str >> id;

		str >> Ax;
		str >> Ay;
		str >> Bx;
		str >> By;
		str >> Cx;
		str >> Cy;
		str >> angle_rotate;
		str >> use_color;
		if (use_color == 1) {
			int r, g, b, r_f, g_f, b_f;//r,g,b -> vypln, r_f, f_f, b_f -> obrys
			str >> r;
			str >> g;
			str >> b;
			str >> r_f;
			str >> g_f;
			str >> b_f;
			COLORREF out = RGB(r_f, g_f, b_f);
			COLORREF fill = RGB(r, g, b);
			tmp.type_id = id_type;
			tmp.id = id;
			tmp.Ax = Ax;
			tmp.Ay = Ay;
			tmp.Cx = Cx;
			tmp.Cy = Cy;
			tmp.Bx = Bx;
			tmp.By = By;
			tmp.angle_rotate = angle_rotate;
			tmp.use_color = use_color;
			tmp.fill_color = fill;
			tmp.out_color = out;
			tmp.full = to_string(id_type) + to_string(id) + to_string(Ax) + to_string(Ay) + to_string(Bx) + to_string(By) + to_string(Cx) + to_string(Cy) + to_string(angle_rotate) + to_string(use_color) + to_string(r) + to_string(g) + to_string(b) + to_string(r_f) + to_string(g_f) + to_string(b_f) + "\n";
		}
		else {
			tmp.type_id = id_type;
			tmp.id = id;
			tmp.Ax = Ax;
			tmp.Ay = Ay;
			tmp.Cx = Cx;
			tmp.Cy = Cy;
			tmp.Bx = Bx;
			tmp.By = By;
			tmp.angle_rotate = angle_rotate;
			tmp.use_color = use_color;
			tmp.full = to_string(id_type) + to_string(id) + to_string(Ax) + to_string(Ay) + to_string(Bx) + to_string(By) + to_string(Cx) + to_string(Cy) + to_string(angle_rotate) + to_string(use_color) + "\n";
		}
		return tmp;
	}
	else if (id_type == IMAGE) {

	}
	else if (id_type == IMAGE_COPYMOVE) {

	}
	else if (id_type == RECTANGLE_COPYMOVE) {

	}
	else if (id_type == SQUARE_COPYMOVE) {

	}
	else if (id_type == TRIANGLE_COPYMOVE) {

	}
	else if (id_type == TRIANGLE_RIGHT_ANGLE_COPYMOVE) {

	}
}

int GetFigurePartsCount(Figure fig) {
	stringstream str(fig);
	int tmp;
	str >> tmp;
	return tmp;
}

FigurePart GetFigurePart(Figure fig, int part_pos) {
	istringstream str(fig);
	int tmp;
	string parts[MAX];
	str >> tmp;
	for (int i = 0; i < tmp; i++) {
		str >> parts[i];
	}
	return ParseFigurePart(parts[part_pos]);
}
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
void SaveFigurePart(FigurePart figp, string filename) {
	ofstream out(filename.c_str());
	out << figp.full;
	out.close();
}
void SaveFigurePartW(FigurePart figp, const wstring filename) {
	wofstream out(filename.c_str());
	std::wstring stemp = s2ws(figp.full);
	LPCWSTR result = stemp.c_str();
	out << result;
	out.close();
}

void SaveFigure(Figure fig, string filename) {
	ofstream out(filename.c_str());
	out << fig;
	out.close();
}


Figure GetFigureFromFile(string filename) {
	Figure fig;
	ifstream in(filename.c_str());
	int tmp;
	in >> tmp;
	for (int i = 0; i < tmp; i++) {
		string n;
		getline(in, n);
		fig = fig + n;
	}
	return fig;
}

Figure CreateFigureFromFigureParts(FigurePart parts[MAX], int count) {
	Figure tmp = to_string(count) + "\n";
	for (int i = 0; i < count; i++) {
		tmp = tmp + parts[i].full;
	}
	return tmp;
}

/*
void SaveFigureToSvg(Figure fig, string filename);
void SaveFigureToHtml(Figure fig, string filename);*/
void SaveFigurePartToSvg(FigurePart figp, string filename) {
	int id_type = figp.type_id;
	assert(id_type == RECTANGLE || id_type == SQUARE || id_type == RECTANGLE || id_type == SQUARE || id_type == TRIANGLE || id_type == TRIANGLE_RIGHT_ANGLE || id_type == IMAGE || id_type == RECTANGLE_COPYMOVE || id_type == SQUARE_COPYMOVE || id_type == TRIANGLE_COPYMOVE || id_type == TRIANGLE_RIGHT_ANGLE_COPYMOVE || id_type == IMAGE_COPYMOVE);
	ofstream out(filename.c_str());
	out << "<?xml version = \"1.0\" encoding = \"utf-8\" ?>" << endl;
	out << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
	out << "<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\" width = \"1000\" height = \"1000\"  xml:space = \"preserve\" > " << endl;
	if (figp.type_id == RECTANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << "	<rect width=\"" + to_string(figp.width) + "\" height=\"" + to_string(figp.height) + "\" style=\"fill:rgb(" + to_string(fill.red) + "," + to_string(fill.green) + to_string(fill.blue) + "); stroke-width:3; stroke:rgb(" + to_string(figp.height) + "\" style=\"fill:rgb(" + to_string(outc.red) + "," + to_string(outc.green) + "," + to_string(outc.blue) + ")\" />\n";
		out << "</svg>";
		out.close();
	}
	else if (figp.type_id == SQUARE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << "	<rect width=\"" + to_string(figp.width) + "\" height=\"" + to_string(figp.width) + "\" style=\"fill:rgb(" + to_string(fill.red) + "," + to_string(fill.green) + to_string(fill.blue) + "); stroke-width:3; stroke:rgb(" + to_string(figp.height) + "\" style=\"fill:rgb(" + to_string(outc.red) + "," + to_string(outc.green) + "," + to_string(outc.blue) + ")\" />\n";
		out << "</svg>";
		out.close();
	}
	else if (figp.type_id == TRIANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << "	<polygon points=\"" + to_string(figp.Ax) + "," + to_string(figp.Ay) + " " + to_string(figp.Bx) + "," + to_string(figp.By) + " " + to_string(figp.Cx) + "," + to_string(figp.Cy) + "\" style=\"fill:rgb(" + to_string(fill.red) + "," + to_string(fill.green) + "," + to_string(fill.blue) + "); stroke-width:1; stroke:rgb(" + to_string(outc.red) + "," + to_string(outc.green) + "," + to_string(outc.blue) + ")\" />\n";
		out << "</svg>";
	}
	else if (figp.type_id == TRIANGLE_RIGHT_ANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << "	<polygon points=\"" + to_string(figp.Ax) + "," + to_string(figp.Ay) + " " + to_string(figp.Bx) + "," + to_string(figp.By) + " " + to_string(figp.Cx) + "," + to_string(figp.Cy) + "\" style=\"fill:rgb(" + to_string(fill.red) + "," + to_string(fill.green) + "," + to_string(fill.blue) + "); stroke-width:3; stroke:rgb(" + to_string(outc.red) + "," + to_string(outc.green) + "," + to_string(outc.blue) + ")\" />\n";
		out << "</svg>";
	}
	out.close();
}

void SaveFigurePartToHtml(FigurePart figp, string filename) {
	int id_type = figp.type_id;
	assert(id_type == RECTANGLE || id_type == SQUARE || id_type == RECTANGLE || id_type == SQUARE || id_type == TRIANGLE || id_type == TRIANGLE_RIGHT_ANGLE || id_type == IMAGE || id_type == RECTANGLE_COPYMOVE || id_type == SQUARE_COPYMOVE || id_type == TRIANGLE_COPYMOVE || id_type == TRIANGLE_RIGHT_ANGLE_COPYMOVE || id_type == IMAGE_COPYMOVE);
	ofstream out(filename.c_str());
	out << "<hmtl>" << endl;
	out << "<head>" << endl;
	out << "<title> Figure to html </title>" << endl;
	out << "</head>" << endl;
	out << "<body>" << endl;
	out << "<svg width=\"10000\" height=\"10000\">\n";
	if (figp.type_id == RECTANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << "	<rect width=\"" + to_string(figp.width) + "\" height=\"" + to_string(figp.height) + "\" style=\"fill:rgb(" + to_string(fill.red) + "," + to_string(fill.green) + to_string(fill.blue) + "); stroke-width:3; stroke:rgb(" + to_string(figp.height) + "\" style=\"fill:rgb(" + to_string(outc.red) + "," + to_string(outc.green) + "," + to_string(outc.blue) + ")\" />\n";
		out << "</svg>";
		out.close();
	}
	else if (figp.type_id == SQUARE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << "	<rect width=\"" + to_string(figp.width) + "\" height=\"" + to_string(figp.width) + "\" style=\"fill:rgb(" + to_string(fill.red) + "," + to_string(fill.green) + to_string(fill.blue) + "); stroke-width:3; stroke:rgb(" + to_string(figp.height) + "\" style=\"fill:rgb(" + to_string(outc.red) + "," + to_string(outc.green) + "," + to_string(outc.blue) + ")\" />\n";
		out << "</svg>";
		out.close();
	}
	else if (figp.type_id == TRIANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << "	<polygon points=\"" + to_string(figp.Ax) + "," + to_string(figp.Ay) + " " + to_string(figp.Bx) + "," + to_string(figp.By) + " " + to_string(figp.Cx) + "," + to_string(figp.Cy) + "\" style=\"fill:rgb(" + to_string(fill.red) + "," + to_string(fill.green) + "," + to_string(fill.blue) + "); stroke-width:3; stroke:rgb(" + to_string(outc.red) + "," + to_string(outc.green) + "," + to_string(outc.blue) + ")\" />\n";
		out << "</svg>";
	}
	else if (figp.type_id == TRIANGLE_RIGHT_ANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << "	<polygon points=\"" + to_string(figp.Ax) + "," + to_string(figp.Ay) + " " + to_string(figp.Bx) + "," + to_string(figp.By) + " " + to_string(figp.Cx) + "," + to_string(figp.Cy) + "\" style=\"fill:rgb(" + to_string(fill.red) + "," + to_string(fill.green) + "," + to_string(fill.blue) + "); stroke-width:3; stroke:rgb(" + to_string(outc.red) + "," + to_string(outc.green) + "," + to_string(outc.blue) + ")\" />\n";
		out << "</svg>";
	}
	out << "</body>" << endl;
	out << "</html>";
	out.close();
}

void SaveFigurePartToSvgW(FigurePart figp, const wstring filename) {
	int id_type = figp.type_id;
	assert(id_type == RECTANGLE || id_type == SQUARE || id_type == RECTANGLE || id_type == SQUARE || id_type == TRIANGLE || id_type == TRIANGLE_RIGHT_ANGLE || id_type == IMAGE || id_type == RECTANGLE_COPYMOVE || id_type == SQUARE_COPYMOVE || id_type == TRIANGLE_COPYMOVE || id_type == TRIANGLE_RIGHT_ANGLE_COPYMOVE || id_type == IMAGE_COPYMOVE);
	wofstream out(filename.c_str());
	out << L"<?xml version = \"1.0\" encoding = \"utf-8\" ?>" << endl;
	out << L"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
	out << L"<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\" width = \"1000\" height = \"1000\"  xml:space = \"preserve\" > " << endl;
	if (figp.type_id == RECTANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << L"	<rect width=\"" + to_wstring(figp.width) + L"\" height=\"" + to_wstring(figp.height) + L"\" style=\"fill:rgb(" + to_wstring(fill.red) + L"," + to_wstring(fill.green) + to_wstring(fill.blue) + L"); stroke-width:3; stroke:rgb(" + to_wstring(figp.height) + L"\" style=\"fill:rgb(" + to_wstring(outc.red) + L"," + to_wstring(outc.green) + L"," + to_wstring(outc.blue) + L")\" />\n";
		out << L"</svg>";
		out.close();
	}
	else if (figp.type_id == SQUARE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << L"	<rect width=\"" + to_wstring(figp.width) + L"\" style=\"fill:rgb(" + to_wstring(fill.red) + L"," + to_wstring(fill.green) + to_wstring(fill.blue) + L"); stroke-width:3; stroke:rgb(" + to_wstring(figp.height) + L"\" style=\"fill:rgb(" + to_wstring(outc.red) + L"," + to_wstring(outc.green) + L"," + to_wstring(outc.blue) + L")\" />\n";
		out << L"</svg>";
		out.close();
	}
	else if (figp.type_id == TRIANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << L"	<polygon points=\"" + to_wstring(figp.Ax) + L"," + to_wstring(figp.Ay) + L" " + to_wstring(figp.Bx) + L"," + to_wstring(figp.By) + L" " + to_wstring(figp.Cx) + L"," + to_wstring(figp.Cy) + L"\" style=\"fill:rgb(" + to_wstring(fill.red) + L"," + to_wstring(fill.green) + L"," + to_wstring(fill.blue) + L"); stroke-width:1; stroke:rgb(" + to_wstring(outc.red) + L"," + to_wstring(outc.green) + L"," + to_wstring(outc.blue) + L")\" />\n";
		out << L"</svg>";
	}
	else if (figp.type_id == TRIANGLE_RIGHT_ANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << L"	<polygon points=\"" + to_wstring(figp.Ax) + L"," + to_wstring(figp.Ay) + L" " + to_wstring(figp.Bx) + L"," + to_wstring(figp.By) + L" " + to_wstring(figp.Cx) + L"," + to_wstring(figp.Cy) + L"\" style=\"fill:rgb(" + to_wstring(fill.red) + L"," + to_wstring(fill.green) + L"," + to_wstring(fill.blue) + L"); stroke-width:1; stroke:rgb(" + to_wstring(outc.red) + L"," + to_wstring(outc.green) + L"," + to_wstring(outc.blue) + L")\" />\n";
		out << L"</svg>";
	}
	out.close();
}

void SaveFigurePartToHtmlW(FigurePart figp,const wstring filename) {
	int id_type = figp.type_id;
	assert(id_type == RECTANGLE || id_type == SQUARE || id_type == RECTANGLE || id_type == SQUARE || id_type == TRIANGLE || id_type == TRIANGLE_RIGHT_ANGLE || id_type == IMAGE || id_type == RECTANGLE_COPYMOVE || id_type == SQUARE_COPYMOVE || id_type == TRIANGLE_COPYMOVE || id_type == TRIANGLE_RIGHT_ANGLE_COPYMOVE || id_type == IMAGE_COPYMOVE);
	wofstream out(filename.c_str());
	out << L"<hmtl>" << endl;
	out << L"<head>" << endl;
	out << L"<title> Figure to html </title>" << endl;
	out << L"</head>" << endl;
	out << L"<body>" << endl;
	out << L"<svg width=\"10000\" height=\"10000\">\n";
	if (figp.type_id == RECTANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << L"	<rect width=\"" + to_wstring(figp.width) + L"\" height=\"" + to_wstring(figp.height) + L"\" style=\"fill:rgb(" + to_wstring(fill.red) + L"," + to_wstring(fill.green) + to_wstring(fill.blue) + L"); stroke-width:3; stroke:rgb(" + to_wstring(figp.height) + L"\" style=\"fill:rgb(" + to_wstring(outc.red) + L"," + to_wstring(outc.green) + L"," + to_wstring(outc.blue) + L")\" />\n";
		out << L"</svg>";
		out.close();
	}
	else if (figp.type_id == SQUARE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << L"	<rect width=\"" + to_wstring(figp.width) + L"\" style=\"fill:rgb(" + to_wstring(fill.red) + L"," + to_wstring(fill.green) + to_wstring(fill.blue) + L"); stroke-width:3; stroke:rgb(" + to_wstring(figp.height) + L"\" style=\"fill:rgb(" + to_wstring(outc.red) + L"," + to_wstring(outc.green) + L"," + to_wstring(outc.blue) + L")\" />\n";
		out << L"</svg>";
		out.close();
	}
	else if (figp.type_id == TRIANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << L"	<polygon points=\"" + to_wstring(figp.Ax) + L"," + to_wstring(figp.Ay) + L" " + to_wstring(figp.Bx) + L"," + to_wstring(figp.By) + L" " + to_wstring(figp.Cx) + L"," + to_wstring(figp.Cy) + L"\" style=\"fill:rgb(" + to_wstring(fill.red) + L"," + to_wstring(fill.green) + L"," + to_wstring(fill.blue) + L"); stroke-width:1; stroke:rgb(" + to_wstring(outc.red) + L"," + to_wstring(outc.green) + L"," + to_wstring(outc.blue) + L")\" />\n";
		out << L"</svg>";
	}
	else if (figp.type_id == TRIANGLE_RIGHT_ANGLE) {
		rgb fill = GetRGBfromColorref(figp.fill_color);
		rgb outc = GetRGBfromColorref(figp.out_color);
		out << L"	<polygon points=\"" + to_wstring(figp.Ax) + L"," + to_wstring(figp.Ay) + L" " + to_wstring(figp.Bx) + L"," + to_wstring(figp.By) + L" " + to_wstring(figp.Cx) + L"," + to_wstring(figp.Cy) + L"\" style=\"fill:rgb(" + to_wstring(fill.red) + L"," + to_wstring(fill.green) + L"," + to_wstring(fill.blue) + L"); stroke-width:1; stroke:rgb(" + to_wstring(outc.red) + L"," + to_wstring(outc.green) + L"," + to_wstring(outc.blue) + L")\" />\n";
		out << L"</svg>";
	}
	out << L"</body>" << endl;
	out << L"</html>";
	out.close();
}
#define PLUS 0
#define MINUS 1

struct colision_detect {
	bool in_colision_x;
	bool in_colision_y;
	bool axis1_x;/* INFO: FOR COLISION OBJ1, viz definitions(PLUS,MINUS)*/
	bool axis1_y;/* INFO: FOR COLISION OBJ1, viz definitions(PLUS,MINUS)*/
};

colision_detect Colision(FigurePart fig1, FigurePart fig2) {
	colision_detect test;
	int copy1x[MAX], copy2x[MAX], copy1y[MAX], copy2y[MAX];
	for (int i = 0; i < fig1.num_detect_points_x; i++) {
		copy1x[i] = fig1.detect_points_x[i];
	}
	for (int i = 0; i < fig2.num_detect_points_x; i++) {
		copy2x[i] = fig2.detect_points_x[i];
	}
	for (int i = 0; i < fig1.num_detect_points_y; i++) {
		copy1y[i] = fig1.detect_points_y[i];
	}
	for (int i = 0; i < fig2.num_detect_points_y; i++) {
		copy2y[i] = fig2.detect_points_y[i];
	}
	/*sort(copy1x[0], copy1x[MAX]);
	sort(copy1y[0], copy1y[MAX]);
	sort(copy2x[0], copy2x[MAX]);
	sort(copy2y[0], copy2y[MAX]);*/
	for (int i = 0; i < fig2.num_detect_points_x; i++) {
		int tmp = Find_number(copy2x, MAX, copy1x[i]);
		if (tmp != copy2x[MAX]) {
			test.in_colision_x = true;
			if (copy1x[i] > copy2x[tmp]) {
				test.axis1_x = PLUS;
			}
			else {
				test.axis1_x = MINUS;
			}
		}
	}
	for (int i = 0; i < fig1.num_detect_points_x; i++) {
		int tmp = Find_number(copy1x, MAX, copy2x[i]);
		if (tmp != copy1x[MAX]) {
			test.in_colision_x = true;
			if (copy2x[i] > copy1x[tmp]) {
				test.axis1_x = MINUS;
			}
			else {
				test.axis1_x = PLUS;
			}
		}
	}
	for (int i = 0; i < fig2.num_detect_points_y; i++) {
		int tmp = Find_number(copy2y, MAX, copy1y[i]);
		if (tmp != copy2y[MAX]) {
			test.in_colision_y = true;
			if (copy1x[i] > copy2x[tmp]) {
				test.axis1_y = PLUS;
			}
			else {
				test.axis1_y = MINUS;
			}
		}
	}
	for (int i = 0; i < fig1.num_detect_points_y; i++) {
		int tmp = Find_number(copy1y, MAX, copy2y[i]);
		if (tmp != copy1y[MAX]) {
			test.in_colision_y = true;
			if (copy2y[i] > copy1y[tmp]) {
				test.axis1_y = MINUS;
			}
			else {
				test.axis1_y = PLUS;
			}
		}
	}
	return test;
}



int FindMax(int p[], int n) {
		int i;
		int max = p[0];
		for (i = 1; i < n; i++)
			if (p[i] > max)
				max = p[i];
		return max;
	
}
int FindMin(int p[], int n)
{
	int i, min, imin;
	min = p[0]; imin = 0;
	for (i = 1; i < n; i++)
		if (p[i] < min)
		{
			min = p[i]; imin = i;
		}
	return imin; 
}

int Find_number(int p[], int n, int x)
{
	int i;
	for (i = 0; i < n; i++)
		if (x == p[i]) return i;
	return -1;                  /* hledaný prvek v poli není */
}

class Objekt{
public:
	COLORREF SetColorFromChooseColorDialog() {
		CHOOSECOLOR cc;                 // common dialog box structure 
		static COLORREF acrCustClr[16]; // array of custom colors 
		HWND hwnd = NULL;                      // owner window
		static DWORD rgbCurrent;        // initial color selection

		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = (LPDWORD)acrCustClr;
		cc.rgbResult = rgbCurrent;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;

		if (ChooseColor(&cc) == TRUE)
		{
			MessageBox(NULL, L"Do you want to use this color as outline? (No->will be used as fill color)", L"Info", MB_YESNO);
			D2D1_COLOR_F color;

			color.r = GetRValue(acrCustClr[0]);
			color.g = GetGValue(acrCustClr[0]);
			color.b = GetBValue(acrCustClr[0]);
			color.a = 255;//plná
			m_target->CreateSolidColorBrush(color, &m_brush);

			figp.out_color = acrCustClr[0];

			rgbCurrent = cc.rgbResult;
		}
		return cc.rgbResult;
	}
	void LoadFromFigurePart(FigurePart fig) {
		figp = fig;
	}
	void SetMovable(bool _move_plus_x, bool _move_minus_x, bool _move_plus_y, bool _move_minus_y) {
		figp.move_plus_x == _move_plus_x;
		figp.move_minus_x == _move_minus_x;
		figp.move_plus_y == _move_plus_y;
		figp.move_minus_y == _move_minus_y;
	}
	void SetColisionPoints(int _detect_points_x[MAX], int _detect_points_y[MAX]) {
		for (int i = 0; i < MAX; i++) {
			figp.detect_points_x[i] = _detect_points_x[i];
			figp.detect_points_y[i] = _detect_points_y[i];
		}
	}
	void SetCursorHitboxArea(int min_x, int min_y, int max_x, int max_y) {
		figp.cursor_hitbox_area.left = min_x;
		figp.cursor_hitbox_area.top = min_y;
		figp.cursor_hitbox_area.right = max_x;
		figp.cursor_hitbox_area.bottom = max_y;
		use_own_points = true;
	}
	void SetColor(COLORREF new_out) {
		figp.out_color = new_out;
		D2D1_COLOR_F color;

		color.r = GetRValue(new_out);
		color.g = GetGValue(new_out);
		color.b = GetBValue(new_out);
		color.a = 255;//plná
		m_brush->SetColor(color);
	}
	/*void SetHdc(HDC _hdc) {
		hdc = _hdc;
	}*/
	void SetID(int _id) {
		id = _id;
	}
	FigurePart GetFigurePart() {
		return figp;
	}

	bool use_own_points = false;
	int id = 0;
	HDC hdc = NULL;
	FigurePart figp;
	std::ofstream _out;
	ID2D1SolidColorBrush* m_brush;
	ID2D1HwndRenderTarget* m_target;
	
};


inline bool FileExist(const wchar_t *name) {
#pragma warning(suppress : 4996)
	if (FILE* file = _wfopen(name, L"r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

TrojBody _TrojBody(int Ax, int Ay, int Cx, int Cy) {
	TrojBody tmp;
	tmp.Ax = Ax;
	tmp.Ay = Ay;
	tmp.Cx = Cx;
	tmp.Cy = Cy;
	return tmp;
}

TrojBody2 _TrojBody2(int Ax, int Ay, int Bx, int By, int Cx, int Cy) {
	TrojBody2 tmp;
	tmp.Ax = Ax;
	tmp.Ay = Ay;
	tmp.Bx = Bx;
	tmp.By = By;
	tmp.Cx = Cx;
	tmp.Cy = Cy;
	return tmp;
}


#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461

D2D1_POINT_2F RotatePrimka(float Ax, float Ay, float Bx, float By, float alfa, bool psi = FALSE) {
	float _Ax = 0;
	float _Ay = 0;
	float rozdil_x = Ax - _Ax;
	float rozdil_y = Ay - _Ay;
	float _Bx = Bx - rozdil_x;
	float _By = By - rozdil_y;
	if (psi != FALSE) {
		psi = atan(_Bx / _By * (PI / 180));
	}
	float fi = psi + alfa;
	float r = sqrt(pow(_Bx, 2) + pow(_By, 2));
	float finX = (r * cos(fi * (PI / 180))) + rozdil_x;
	float finY = (r * sin(fi * (PI / 180))) + rozdil_y;
	D2D1_POINT_2F fin;
	fin.x = finX;
	fin.y = finY;
	return fin;
}

D2D1_POINT_2F RotatePrimka2(D2D1_POINT_2F point1, D2D1_POINT_2F point2, float alfa, bool psi = FALSE) {
	float _Ax = 0;
	float _Ay = 0;
	float rozdil_x = /*Ax*/ point1.x - _Ax;
	float rozdil_y = /*Ay*/point1.y - _Ay;
	float _Bx = /*Bx*/ point2.x - rozdil_x;
	float _By = /*By*/point2.y - rozdil_y;
	if (psi != FALSE) {
		psi = atan((_Bx /_By) * (PI / 180));
	}
	float fi = psi + alfa;
	float r = sqrt(pow(_Bx, 2) + pow(_By, 2));
	float finX = (r * cos(fi * (PI / 180))) + rozdil_x;
	float finY = (r * sin(fi * (PI / 180))) + rozdil_y;
	D2D1_POINT_2F fin;
	fin.x = finX;
	fin.y = finY;
	return fin;
}