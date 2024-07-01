#include "geometry.hpp"

Vec::Vec(double x, double y): x{x}, y{y} {}

double Vec::mag() {
    return sqrt(x*x + y*y);
}

Vec Vec::translate(double dx, double dy) {
    return Vec (x+dx,y+dy);
}

Vec Vec::rotate(double angle) {
    return Vec(x*cos(angle)  -y*sin(angle), x*sin(angle) + y*cos(angle));
}

Vec Vec::rotate_around(double angle, Vec p) {
    Vec v(x,y);
    v -= p;
    v = v.rotate(angle);
    v += p;

    return v;
}

Vec operator+(const Vec& u, const Vec& v) {
    return Vec(u.x + v.x, u.y + v.y);
}
Vec operator-(const Vec& u, const Vec& v) {
    return Vec(u.x - v.x, u.y - v.y);
}

Vec operator*(const double a, const Vec& v) {
    return Vec(v.x*a, v.y*a);
}
Vec operator*(const Vec& v, const double a) {
    return Vec(v.x*a, v.y*a);
}
Vec operator/(const Vec& v, const double a) {
    return Vec(v.x/a, v.y/a);
}
bool operator==(const Vec & u, const Vec & v) {
    double threshold = 0.001f;
    return abs(u.x - v.x) <= threshold && abs(u.y - v.y) <= threshold;
}

Vec Vec::operator=(const Vec& v) {
    x = v.x;
    y = v.y;
    return *this;
}

Vec Vec::operator+=(const Vec& v) {
    *this = *this + v;
    return *this;
}
Vec Vec::operator*=(const double a) {
    *this = *this * a;
    return *this;
}
Vec Vec::operator-=(const Vec& v) {
    *this = *this - v;
    return *this;
}
Vec Vec::operator/=(const double a) {
    *this = *this / a;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vec& obj) {

    return os << "<"<<obj.x<<","<<obj.y<<">";
}
