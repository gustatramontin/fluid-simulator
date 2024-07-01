
#include "geometry.hpp"

Box::Box() {}

Box Box::square(Point center, int size) {
    Box b;

    Point corner1 = center + Point(-size/2, +size/2);
    Point corner2 =  corner1 + Point(size, 0);
    Point corner3 =  corner2 + Point(0, -size);
    Point corner4 =  corner1 + Point(0, -size);


    b
    .add_segment(corner1, corner2)
    .add_segment(corner3, corner4)
    .add_segment(corner4, corner1)
    .add_segment(corner2, corner3);

    return b;
}

Box & Box::add_segment(Point p1, Point p2) {
    Segment s = std::make_pair(p1, p2);
    segments.push_back(s);
    return *this;
}

std::vector<Segment> Box::get_segments() {
    return segments;
}

std::pair<bool, Point> Box::point_outside(Point p, Segment s) {
    double right_angle = M_PI/4;

    Point center = (s.first + s.second) / 2;
    Vec s_vec = s.second - s.first;
    Vec s_vec_per = s_vec.rotate(right_angle);
    double angle = atan2(s_vec_per.y, s_vec_per.x);
    

    Point upward_s1 = s.first.rotate_around(right_angle - angle, center);
    Point upward_s2 = s.second.rotate_around(right_angle - angle, center);
    Point rotated_p = p.rotate_around(right_angle - angle, center);

    bool p_in_segment_x_axis = rotated_p.x >= upward_s1.x && rotated_p.x <= upward_s2.x;
    bool p_in_segment_y_axis = rotated_p.y <= upward_s1.y;
    
    bool is_point_outside = p_in_segment_x_axis && !p_in_segment_y_axis;
    Point relocate = Point(rotated_p.x,upward_s1.y).rotate_around(- (right_angle-angle), center);

    return std::make_pair(is_point_outside, relocate);
}

std::pair<bool, Point> Box::point_outside_box(Point p) {
    for (Segment s : segments) {
        auto ps = point_outside(p,s);
        if (ps.first) return ps;
    }
    return std::make_pair(false, Vec(0,0));
}
