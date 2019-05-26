#ifndef _CLASS_H_
#define _CLASS_H_
#include <vector>

class vechile {
public:
	struct point{
		double x, y, z;
		point(){
			x = 0;
			y = 0;
			z = 0;
		}
		point(double newX, double newY, double newZ) {
			x = newX;
			y = newY;
			z = newZ;
		}
	};
	vechile();
	void setDirection(double x, double y, double z);
	virtual void move(int n) = 0;
	void on(int n);
	void off();
	std::vector<point> getWay();
protected:
	void doMove(int n);
	double distance();
private:
	double dirX, dirY, dirZ;
	bool record;
	int freq;
	int time;
	point curPos;
	std::vector<point> way;
	void updatePos(double x, double y, double z);
};

class car : public vechile{
private:
	double petrol;
	bool enoughPetrol();
	double consumption;
public:
	car();
	double getPetrol();
	void addPetrol(double k);
	void setConsumption(double k);
	void move(int n);
};

#endif