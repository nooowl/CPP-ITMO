#ifndef _CLASS_H_
#define _CLASS_H_
#include <string>
#include <algorithm>
#include <vector>
#include <map>

class Point{
public:
	double x, y;
	void drawPoint();
};

class GeoFig{
public:
	virtual double square() = 0;
	virtual double perimeter() = 0;
protected:
	double length(Point a, Point b);
};

class PhysObject {
public:
	virtual double mass() const = 0;
	virtual Point position() = 0;
	virtual bool operator == (const PhysObject& ob) const = 0;
	virtual bool operator < (const PhysObject& ob) const = 0;
};

class Printable {
public:
	virtual void draw() = 0;
};

class DialogInitiable {
	virtual void initFromDialog() = 0;
};

class BaseCObject {
protected:
	const char* name;
public:
	virtual const char* classname() = 0;
	virtual unsigned int size() = 0;
};

class Figure : public virtual GeoFig, public virtual PhysObject, public virtual Printable, public virtual DialogInitiable, public virtual BaseCObject{
};

class Interval : public Figure{
private:
	Point a, b;
	double _mass;
public:
	Interval::Interval();
	Interval(Point p, Point q, double m);
	virtual double square();
	double perimeter();
	double mass() const;
	Point position();
	bool operator == (const PhysObject& ob) const;
	bool operator < (const PhysObject& ob) const;
	void draw();
	void initFromDialog();
	const char* classname();
	unsigned int size();
};

class Trapeze : public Figure {
private:
	Point a, b, c, d;
	double _mass;
	double h;
	double sumBases;
public:
	Trapeze::Trapeze();
	Trapeze(Point p, Point q, Point r, Point w, double m);
	virtual double square();
	double perimeter();
	double mass() const;
	Point position();
	bool operator == (const PhysObject& ob) const;
	bool operator < (const PhysObject& ob) const;
	void draw();
	void initFromDialog();
	const char* classname();
	unsigned int size();
};

class Storage{
private:
	std::vector<Figure*> array;
	Point _positionAll;
	double _squareAllFig;
	double _perimetrAllFig;
	unsigned int _sizeAll;
public:
	Storage();
	void update(Figure* a);
	void addFig();
	void printAllFig();
	double squareAllFig();
	double perimeterAllFig();
	Point positionAll();
	void sortFig();
	unsigned int sizeAll();
};

class Menu{
public:
	Menu();
	void start();
};

#endif