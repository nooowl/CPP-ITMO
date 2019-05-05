#include <vector>
#include <iostream>
#include "class.h"

void vechile::updatePos(double x, double y, double z){
	curPos.x += x;
	curPos.y += y;
	curPos.z += z;
}

vechile::vechile(){
	dirX = 0;
	dirY = 0;
	dirZ = 0;
	record = false;
	curPos = point();
}

void vechile::setDirection(double x, double y, double z){
	dirX = x;
	dirY = y;
	dirZ = z;
}

void vechile::doMove(int n){
	if (record && time == 0){
		way.push_back(curPos);
	}
	for (int i = 0; i < n; i++){
		time++;
		updatePos(dirX / n, dirY / n, dirZ / n);
		if (record && time % freq == 0)
			way.push_back(curPos);
	}
}

void vechile::move(int n){
	doMove(n);
}

void vechile::on(int n){
	time = 0;
	record = true;
	freq = n;
}

void vechile::off(){
	record = false;
}

std::vector<vechile::point> vechile::getWay(){
	return way;
}

car::car() : vechile(){
	consumption = 1;
	petrol = 0;
}

double vechile::distance(){
	return sqrt(dirX*dirX + dirY*dirY + dirZ*dirZ);
}

bool car::enoughPetrol(){
	if (distance()*consumption <= petrol)
		return true;
	std::cout << "Not enough petrol!" << std::endl;
	return false;
}

double car::getPetrol(){
	return petrol;
}

void car::addPetrol(double k){
	petrol += k;
}

void car::setConsumption(double k){
	consumption = k;
}

void car::move(int n){
	if (enoughPetrol())
		doMove(n);
}