#include <iostream>
#include <string>
#include <cmath>

#include "point.h"
using namespace std;

Point::Point()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 1;
}

void Point::equaling(Point & a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = a.w;
}


Point::Point(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Point::return_x()
{
	return this->x;
}


double Point::return_y()
{
	return this->y;
}

double Point::return_z()
{
	return this->z;
}

void Point::keyboard_put_with_weight()
{
	printf(">>>print x, y, z, w:");
    std::cin>> x >> y >> z >> w;
}

void Point::keyboard_put_without_weight()
{
	w = 1;
	printf(">>>print x, y, z:");
    std::cin>> x >> y >> z;
}

void Point::print()
{
	std::cout<<"p("<<this->x<<", "<<this->y<<", "<<this->z<<")  ";
}


Point& Point::operator =(const Point &a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = a.w;
	return *this;
}
