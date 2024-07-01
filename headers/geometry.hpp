#include <iostream>
#include <cmath>
#include <vector>

class Vec {
    public:
        double x,y;
        Vec(double x, double y);       

        double mag();

        Vec translate(double dx, double dy);
        Vec rotate(double angle);
        Vec rotate_around(double angle, Vec p);

        friend Vec operator+(const Vec& u, const Vec& v);
        friend Vec operator-(const Vec& u, const Vec& v);

        friend Vec operator*(const double a, const Vec& v);
        friend Vec operator*(const Vec& v, const double a);
        friend Vec operator/(const Vec& v, const double a);
        friend bool operator==(const Vec & u, const Vec & v);
        
        Vec operator=(const Vec& v);
        Vec operator+=(const Vec& v);
        Vec operator-=(const Vec& v);
        Vec operator*=(const double a);
        Vec operator/=(const double a);

        friend std::ostream& operator<<(std::ostream& os, const Vec& obj);
 

};

class Particle {
public:
    Vec x, v;
    Vec next_x;
    double m, density, pressure;

    Particle(Vec x, double m);
    void swap_x();
};

using Segment = std::pair<Vec, Vec>;
using Point = Vec;

class Box {

    std::vector<Segment> segments;

public:
    Box();
    std::vector<Segment> get_segments();
    static Box square(Point center, int size);
    Box & add_segment(Point p1, Point p2);
    std::pair<bool, Point> point_outside(Point p, Segment s);
    std::pair<bool, Point>point_outside_box(Point p);
};
