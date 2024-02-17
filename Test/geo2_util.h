#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <string>


namespace Geo2Util 
{
    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef K::Point_2 Point_2;
    typedef K::Circle_2 Circle_2;
    typedef K::Iso_rectangle_2 Iso_rectangle_2;
    typedef K::Triangle_2 Triangle_2;
    typedef K::Segment_2 Segment_2;

    std::string Black();
    std::string SolidBoundary();
    std::string DottedBoundary();
    std::string DashedBoundary();

    std::string toString(Point_2 p);
    std::string toString(Segment_2 seg);
    std::string toString(Circle_2 circ);
    std::string toString(Triangle_2 tri);
    std::string toString(Iso_rectangle_2 rect);

    void printToFile(std::string filename, std::string p[], int total);
}