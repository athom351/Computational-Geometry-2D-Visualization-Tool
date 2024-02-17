#include <string>
#include <iostream>
#include <fstream>

#include "geo2_util.h"

std::string Geo2Util::Black() {
    static std::string black(" 0 0 0 255");
    return black;
}
//Setcolor
std::string Geo2Util::SolidBoundary() {
    static std::string solidBoundary(" 0");
    return solidBoundary;
}

std::string Geo2Util::DottedBoundary() {
    static std::string dottedBoundary(" 1");
    return dottedBoundary;
}

std::string Geo2Util::DashedBoundary() {
    static std::string dashedBoundary(" 2");
    return dashedBoundary;
}

std::string Geo2Util::toString(Point_2 p) {

    std::ostringstream s;
    s << std::fixed << std::setprecision(10) << "POINT " << p.x() << " " << p.y() << Black() + SolidBoundary() + Black();

    return s.str();
}

std::string Geo2Util::toString(Segment_2 seg) {

    return "LINE_SEGMENT" + Black() + DottedBoundary();
}

std::string Geo2Util::toString(Circle_2 circ) {


    double raduis = std::sqrt(circ.squared_radius());


    std::ostringstream c;
    c << std::fixed << std::setprecision(10) << "CIRCLE " << raduis << Black() << DashedBoundary() << Black();

    return c.str();
}


std::string Geo2Util::toString(Triangle_2 tri) {

    return "TRIANGLE" + Black() + DottedBoundary() + Black();
}

std::string Geo2Util::toString(Iso_rectangle_2 rect) {

    return "RECTANGLE" + Black() + DottedBoundary() + Black();
}

void Geo2Util::printToFile(std::string filename, std::string p[], int total) {

    std::ofstream output(filename);
    output << std::fixed << std::setprecision(10);
    for (int i = 0; i < total; i++) {
        output << p[i] << std::endl;
    }
    output.close();

}