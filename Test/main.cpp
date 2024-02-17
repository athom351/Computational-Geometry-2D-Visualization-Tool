
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <string>
#include <iostream>
#include <fstream>

#include "geo2_util.h"

using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Circle_2 Circle_2;
typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef K::Triangle_2 Triangle_2;
typedef K::Segment_2 Segment_2;



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

    Point_2 s1(10, 10), s2(40, 40);
    Segment_2 seg(s1, s2);

    Point_2 p(10, 10), q(20, 15), s(10, 15);
    Triangle_2 tri(p, q, s);

    Circle_2 circ(p, 4);

    Iso_rectangle_2 rect(p, q);


    string geomObjectArray[7];
    geomObjectArray[0] = Geo2Util::toString(p0);
    geomObjectArray[1] = Geo2Util::toString(p1);
    geomObjectArray[2] = Geo2Util::toString(p2);
    geomObjectArray[3] = Geo2Util::toString(seg); 
    //geomObjectArray[4] = Geo2Util::toString(s1);
    //geomObjectArray[5] = Geo2Util::toString(s2);

    geomObjectArray[4] = Geo2Util::toString(circ);

    //geomObjectArray[6] = Geo2Util::toString(circ);
    //geomObjectArray[7] = Geo2Util::toString(p);

    geomObjectArray[5] = Geo2Util::toString(tri);

    //geomObjectArray[8] = Geo2Util::toString(tri);
    //geomObjectArray[9] = Geo2Util::toString(p);
    //geomObjectArray[10] = Geo2Util::toString(q);
    //geomObjectArray[11] = Geo2Util::toString(s);

    geomObjectArray[6] = Geo2Util::toString(rect);

    //geomObjectArray[12] = Geo2Util::toString(rect);
    //geomObjectArray[13] = Geo2Util::toString(p);
    //geomObjectArray[14] = Geo2Util::toString(q);
  
   
    Geo2Util::printToFile("test.txt", geomObjectArray, 15);

}

/*
    ofstream file("test.txt");
    
    file << toString(p0) << endl << toString(p1) << endl << toString(p2) << endl << endl;

    file.close();

    cout << "Complete" << endl;

    return 0;

    */

    /*
    string toString(Point_2 p)
    {
        return "POINT " + to_string(p.x()) +  " " +
            to_string(p.y()) + " 0 0 0 255 0 0 0 0 255";
    }
    */





