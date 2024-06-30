#include <iostream>
#include <cmath>

class Vec {
    public:
        double x,y;
        Vec(double x, double y);       

        double mag();

        friend Vec operator+(const Vec& u, const Vec& v);
        friend Vec operator-(const Vec& u, const Vec& v);

        friend Vec operator*(const double a, const Vec& v);
        friend Vec operator*(const Vec& v, const double a);
        friend Vec operator/(const Vec& v, const double a);
        friend bool operator==(const Vec & u, const Vec & v);
        
        Vec operator=(const Vec& v);
        Vec operator+=(const Vec& v);
        Vec operator*=(const double a);

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
