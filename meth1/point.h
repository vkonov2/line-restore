#ifndef __CLASS_POINT_H__
#define __CLASS_POINT_H__
using namespace std;

class Point{
	public:
		double x,y,z, w;
		Point();
		void equaling(Point & a);
		Point(double x, double y, double z);
		double return_x();
		double return_y();
		double return_z();
		void keyboard_put_with_weight();
		void keyboard_put_without_weight();
		void print();
		Point& operator =(const Point &a);

};

#endif 
