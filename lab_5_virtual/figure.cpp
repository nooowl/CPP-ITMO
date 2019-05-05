#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "class.h"


double GeoFig::length(Point a, Point b){
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Point::drawPoint(){
	std::cout << '(' << x << ", " << y << ')';
}

Interval::Interval(){};

Interval::Interval(Point p, Point q, double m){
	a = p;
	b = q;
	name = "Interval";
	_mass = m;
}

double Interval::square(){
	return 0;
};

double Interval::perimeter(){
	return length(a, b);
}

Point Interval::position(){
	Point center;
	center.x = (a.x + b.x) / 2;
	center.y = (a.y + b.y) / 2;
	return center;
}

double Interval::mass() const{
	return _mass;
}

bool Interval::operator == (const PhysObject& ob) const{
	return (ob.mass() == mass());
}

bool Interval::operator < (const PhysObject& ob) const{
	return (mass() < ob.mass());
}

void Interval::draw(){
	std::cout << name << std::endl;
	a.drawPoint();
	b.drawPoint();
}

void Interval::initFromDialog(){
	Point p, q;
	double m;
	std::cin >> p.x >> p.y >> q.x >> q.y >> m;
	Interval newInterval = Interval(p, q, m);
	a = p;
	b = q;
	name = "Interval";
	_mass = m;
}

const char* Interval::classname(){
	return name;
}

unsigned int Interval::size(){
	return sizeof(Interval);
}

Trapeze::Trapeze(){};

Trapeze::Trapeze(Point p, Point q, Point r, Point w, double m){
	a = p;
	b = q;
	c = r;
	d = w;
	name = "Trapeze";
	_mass = m;
	Point e;
	e.x = b.x;
	e.y = a.y;
	h = length(b, e);
	sumBases = length(a, d) + length(b, c);
}

double Trapeze::square(){
	return sumBases / 2 * h;
};

double Trapeze::perimeter(){
	return length(a, b) + length(b, c) + length(c, d) + length(d, a);
}

Point Trapeze::position(){
	Point center;
	center.x = (a.x + d.x) / 2;
	center.y = a.y + (h / 3) * (sumBases + length(a, d)) / sumBases;
	return center;
}

double Trapeze::mass() const{
	return _mass;
}

bool Trapeze::operator == (const PhysObject& ob) const{
	return (ob.mass() == mass());
}

bool Trapeze::operator < (const PhysObject& ob) const{
	return (mass() < ob.mass());
}

void Trapeze::draw(){
	std::cout << name << std::endl;
	a.drawPoint();
	b.drawPoint();
	c.drawPoint();
	d.drawPoint();
}

void Trapeze::initFromDialog(){
	Point p, q, r, w;
	double m;
	std::cin >> p.x >> p.y >> q.x >> q.y >> r.x >> r.y >> w.x >> w.y >> m;
	a = p;
	b = q;
	c = r;
	d = w;
	name = "Trapeze";
	_mass = m;
	Point e;
	e.x = b.x;
	e.y = a.y;
	h = length(b, e);
	sumBases = length(a, d) + length(b, c);
}

const char* Trapeze::classname(){
	return name;
}

unsigned int Trapeze::size(){
	return sizeof(Trapeze);
}

Storage::Storage(){
	_positionAll.x = 0;
	_positionAll.y = 0;
	_squareAllFig = 0;
	_perimetrAllFig = 0;
	_sizeAll = 0;
}

void Storage::update(Figure* a){
	_squareAllFig += a->square();
	_perimetrAllFig += a->perimeter();
	_sizeAll += a->size();
	Point pos = a->position();
	_positionAll.x = (_positionAll.x * array.size() + pos.x) / (array.size() + 1);
	_positionAll.y = (_positionAll.y * array.size() + pos.y) / (array.size() + 1);
}

void Storage::addFig(){
	std::string name;
	std::cin >> name;
	if (name == "Interval"){
		Interval *l = new Interval();
		l->initFromDialog();
		update(l);
		array.push_back(l);
	}
	else if (name == "Trapeze"){
		Trapeze* t = new Trapeze();
		t->initFromDialog();
		update(t);
		array.push_back(t);
	} 
	else std::cout << "ERROR!!!" << std::endl;
}

void Storage::printAllFig(){
	for (int i = 0; i < array.size(); i++){
		array[i]->draw();
		std::cout << std::endl;
	}
}

double Storage::squareAllFig(){
	return _squareAllFig;
}

double Storage::perimeterAllFig(){
	return _perimetrAllFig;
}

Point Storage::positionAll(){
	return _positionAll;
}

unsigned int Storage::sizeAll(){
	return _sizeAll;
}

bool cmp(Figure* a, Figure* b){
	return a->mass() < b->mass();
}

void Storage::sortFig(){
	std::sort(array.begin(), array.end(), cmp);
}

Menu::Menu(){};

void Menu::start(){
	std::string s;
	Storage st = Storage();
	while (s != "--end"){
		std::cin >> s;
		if (s == "--addFigure")
			st.addFig();
		else if (s == "--printFigures")
			st.printAllFig();
		else if (s == "--square")
			std::cout << st.squareAllFig();
		else if (s == "--perimeter")
			std::cout << st.perimeterAllFig();
		else if (s == "--centerOfMass")
			st.positionAll().drawPoint();
		else if (s == "--size")
			std::cout << st.sizeAll();
		else if (s == "--sort")
			st.sortFig();
		else if(s != "--end") 
			std::cout << "Use other commands";
		std::cout << std::endl;
	}
}
