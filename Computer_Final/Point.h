#pragma once
class Pointi {
public:
	int x, y;
public:
	Pointi(int px, int py) { x = px; y = py; }
	void SetX(int px) { x = px; }
	void SetY(int py) { y = py; }
	int GetX() { return x; }
	int GetY() { return y; }
};
class Pointd {
public:
	double x, y;
public:
	Pointd(double px, double py) { x = px; y = py; }
	void SetX(int px) { x = px; }
	void SetY(int py) { y = py; }
	double GetX() { return x; }
	double GetY() { return y; }
};