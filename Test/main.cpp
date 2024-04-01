
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "geo2_util.h"

using namespace std;
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



//std::string Black() {
//    static std::string black(" 0 0 0 255");
//    return black;
//}
////Setcolor
//std::string SolidBoundary() {
//    static std::string solidBoundary(" 0");
//    return solidBoundary;
//}
//
//std::string DottedBoundary() {
//    static std::string dottedBoundary(" 1");
//    return dottedBoundary;
//}
//
//std::string DashedBoundary() {
//    static std::string dashedBoundary(" 2");
//    return dashedBoundary;
//}
//
//string toString(Point_2 p) {
//
//    ostringstream s;
//    s << fixed << setprecision(10) << "POINT " << p.x() << " " << p.y() << Black() + SolidBoundary() + Black() ;
//    
//    return s.str();
//}
//
//string toString(Segment_2 seg) {
//
//    return "LINE_SEGMENT" + Black() + DottedBoundary();
//}
//
//string toString(Circle_2 circ) {
//
//    
//    double raduis = std::sqrt(circ.squared_radius());
//   
//
//    ostringstream c;
//    c << fixed << setprecision(10) << "CIRCLE " << raduis << Black() << DashedBoundary() << Black();
//
//        return c.str();
//}
//
//
//string toString(Triangle_2 tri) {
//
//    return "TRIANGLE" + Black() + DottedBoundary() + Black();
//}
//
//string toString(Iso_rectangle_2 rect) {
//
//    return "RECTANGLE" + Black() + DottedBoundary() + Black();
//}
//
//void printToFile(string filename, string p[], int total) {
//
//    ofstream output(filename);
//    output << fixed << setprecision(10);
//    for (int i = 0; i < total; i++) {
//        output << p[i] << endl;
//     }
//    output.close();
//
//}


int main()
{
    Point_2 p0(12, -15), p1(-10, -25.3), p2(-0.01, 0.2);

    Point_2 s1(20, 10), s2(40, 40);
    Segment_2 seg(s1, s2);

    Point_2 p(10, 10), q(20, 15), s(10, 15);

    Triangle_2 tri(p, q, s);

    Circle_2 circ(p, 4);

    Iso_rectangle_2 rect(p, q);


    std::vector<std::string> geomObjectArray;

    geomObjectArray.push_back(Geo2Util::toString(p0));
    geomObjectArray.push_back(Geo2Util::toString(p1));
    geomObjectArray.push_back(Geo2Util::toString(p2));
    geomObjectArray.push_back(Geo2Util::toString(seg));

    geomObjectArray.push_back(Geo2Util::toString(circ));

    geomObjectArray.push_back(Geo2Util::toString(tri));

    geomObjectArray.push_back(Geo2Util::toString(rect));
  
    // create a polygon with three holes
    Polygon_2 poly;
    poly.push_back(Point_2(0, 0)); poly.push_back(Point_2(9, 0));
    poly.push_back(Point_2(6, 8)); poly.push_back(Point_2(5, 3));
    poly.push_back(Point_2(2, 8)); poly.push_back(Point_2(0, 8));

    geomObjectArray.push_back(Geo2Util::toString(poly));

    std::vector<Polygon_2> holes(3);
    holes[0].push_back(Point_2(6, 2)); holes[0].push_back(Point_2(7, 1));
    holes[0].push_back(Point_2(7, 3)); holes[0].push_back(Point_2(6, 3));
    holes[0].push_back(Point_2(5, 2));
    holes[1].push_back(Point_2(2, 1)); holes[1].push_back(Point_2(3, 1));
    holes[1].push_back(Point_2(3, 3)); holes[1].push_back(Point_2(2, 2));
    holes[1].push_back(Point_2(1, 2));
    holes[2].push_back(Point_2(1, 4)); holes[2].push_back(Point_2(2, 4));
    holes[2].push_back(Point_2(2, 5)); holes[2].push_back(Point_2(3, 5));
    holes[2].push_back(Point_2(3, 6)); holes[2].push_back(Point_2(1, 6));

    Polygon_with_holes_2 poly_w_h(poly, holes.begin(), holes.end());

    geomObjectArray.push_back(Geo2Util::toString(poly_w_h, Geo2Util::Color{ 159,246,37,100 }, Geo2Util::BoundaryType::Dotted, Geo2Util::Color{ 200,200,200,5 }));

    double a = 3.14159265390;
    double b = 6.14159265390;
    double c = 7.14159265390;
    Line_2 line(a, b, c);
    geomObjectArray.push_back(Geo2Util::toString(line));

    Ray_2 ray(q, s);
    geomObjectArray.push_back(Geo2Util::toString(ray, Geo2Util::Color{ 157,246,42,30 }, Geo2Util::BoundaryType::Dotted));

    Geo2Util::printToFile("test.txt", geomObjectArray);


    {   // import test

        // lambda function for printing objects (for testing)
        auto printObjects = [](auto objs) {
            for (auto& obj : objs) {
                std::cout << Geo2Util::toString(obj) << '\n';
            }
        };

        std::vector<Point_2> points = Geo2Util::getPoints("test.txt");
        printObjects(points);

        std::vector<Segment_2> segs = Geo2Util::getSegments("test.txt");
        printObjects(segs);

        std::vector<Line_2> lines = Geo2Util::getLines("test.txt");
        printObjects(lines);

        std::vector<Iso_rectangle_2> rects = Geo2Util::getRectangles("test.txt");
        printObjects(rects);

        std::vector<Circle_2> circles = Geo2Util::getCircles("test.txt");
        printObjects(circles);

        std::vector<Triangle_2> triangles = Geo2Util::getTriangles("test.txt");
        printObjects(triangles);

        std::vector<Ray_2> rays = Geo2Util::getRays("test.txt");
        printObjects(rays);

        std::vector<Polygon_2> polygons = Geo2Util::getPolygons("test.txt");
        printObjects(polygons);
    }
}
