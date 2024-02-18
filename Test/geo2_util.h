#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <string>
#include <vector>


namespace Geo2Util {
    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef K::Point_2 Point_2;
    typedef K::Circle_2 Circle_2;
    typedef K::Iso_rectangle_2 Iso_rectangle_2;
    typedef K::Triangle_2 Triangle_2;
    typedef K::Segment_2 Segment_2;

    std::string Black();

    enum class BoundaryType : short {
        Solid = 0,
        Dotted = 1,
        Dashed = 2
    };
    std::string toString(const BoundaryType& t);

    std::string toString(const Point_2& p);
    std::string toString(const Segment_2& seg);
    std::string toString(const Circle_2& circ);
    std::string toString(const Triangle_2& tri);
    std::string toString(const Iso_rectangle_2& rect);

    void printToFile(const std::string& filename, const std::vector<std::string>& geo2_Objects);
}