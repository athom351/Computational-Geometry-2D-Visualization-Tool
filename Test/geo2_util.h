#pragma once
#include <string>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>

namespace Geo2Util {
    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef K::Point_2 Point_2;
    typedef K::Circle_2 Circle_2;
    typedef K::Iso_rectangle_2 Iso_rectangle_2;
    typedef K::Triangle_2 Triangle_2;
    typedef K::Segment_2 Segment_2;
    typedef K::Line_2 Line_2;
    typedef K::Ray_2 Ray_2;
    typedef CGAL::Polygon_2<K> Polygon_2;
    typedef CGAL::Polygon_with_holes_2<K> Polygon_with_holes_2;

    struct Color {
        short r;
        short g;
        short b;
        short trans = 255;
    };

    enum class BoundaryType : short {
        Solid = 0,
        Dotted = 1,
        Dashed = 2
    };

    // Default Visual Setting
    const Color DefaultBoundaryColor = { 0, 0, 0, 255 };
    const Color DefaultInteriorColor = { 0, 0, 0, 255 };
    const Color TransparentWhite = { 255, 255, 255, 0 };
    const BoundaryType DefaultBoundaryType = BoundaryType::Solid;

    // Visual Properties toString
    std::string toString(const Color& color);
    std::string toString(const BoundaryType& bt);

    // Default toString
    std::string toString(const Point_2& p);
    std::string toString(const Segment_2& seg);
    std::string toString(const Circle_2& circ);
    std::string toString(const Triangle_2& tri);
    std::string toString(const Iso_rectangle_2& rect);
    std::string toString(const Polygon_2 & poly);
    std::string toString(const Polygon_with_holes_2 & poly_w_h);
    std::string toString(const Line_2& line);
    std::string toString(const Ray_2& ray);

    // Customized toString
    //! Underlying points of all objects (except Point_2) have the same color (boundary color and interior color) as its boundary color
    //! Underlying points of all objects have the same boundary type as the objects themselves
    std::string toString(const Point_2& p, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor);
    std::string toString(const Segment_2& seg, const Color& boundaryColor, const BoundaryType btype);
    std::string toString(const Circle_2& circ, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor);
    std::string toString(const Triangle_2& tri, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor);
    std::string toString(const Iso_rectangle_2& rect, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor);
    std::string toString(const Polygon_2& poly, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor);
    std::string toString(const Polygon_with_holes_2& poly_w_h, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor);
    std::string toString(const Line_2& line, const Color& boundaryColor, const BoundaryType btype);
    std::string toString(const Ray_2& ray, const Color& boundaryColor, const BoundaryType btype);
    
    // Export CGAL 2D Geometry Object to File
    void printToFile(const std::string& filename, const std::vector<std::string>& geo2_Objects);


    // Import CGAL 2D Geometry Object from file; visual information will be ignored
    std::vector<Point_2> getPoints(const std::string& filename); 
    std::vector<Line_2> getLines(const std::string& filename); 
    std::vector<Circle_2> getCircles(const std::string& filename); 
    std::vector<Iso_rectangle_2> getRectangles(const std::string& filename); 
    std::vector<Triangle_2> getTriangles(const std::string& filename); 
    std::vector<Segment_2> getSegments(const std::string& filename);
    std::vector<Ray_2> getRays(const std::string& filename); 
    std::vector<Polygon_2> getPolygons(const std::string& filename); 
}