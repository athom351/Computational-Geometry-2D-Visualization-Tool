#include <string>
#include <iostream>
#include <fstream>

#include "geo2_util.h"

namespace Geo2Util
{
    std::string Black() {
        static std::string black(" 0 0 0 255");
        return black;
    }
    //Setcolor
    std::string SolidBoundary() {
        static std::string solidBoundary(" 0");
        return solidBoundary;
    }

    std::string DottedBoundary() {
        static std::string dottedBoundary(" 1");
        return dottedBoundary;
    }

    std::string DashedBoundary() {
        static std::string dashedBoundary(" 2");
        return dashedBoundary;
    }

    std::string toString(Point_2 p) {

        std::ostringstream s;
        s << std::fixed << std::setprecision(10) << "POINT " << p.x() << " " << p.y() << Black() + SolidBoundary() + Black();

        return s.str();
    }

    std::string toString(Segment_2 seg) {

        return "LINE_SEGMENT" + Black() + DottedBoundary() + "\n"
                + toString(seg.source()) + "\n"
                + toString(seg.target());
    }

    std::string toString(Circle_2 circ) {


        double raduis = std::sqrt(circ.squared_radius());


        std::ostringstream c;
        c << std::fixed << std::setprecision(10) << "CIRCLE " << raduis << Black() << DashedBoundary() << Black() + "\n"
            << toString(circ.center());

        return c.str();
    }


    std::string toString(Triangle_2 tri) {

        return "TRIANGLE" + Black() + DottedBoundary() + Black() + "\n"
                + toString(tri[0]) + "\n"
                + toString(tri[1]) + "\n"
                + toString(tri[2]);
    }

    std::string toString(Iso_rectangle_2 rect) {

        return "RECTANGLE" + Black() + DottedBoundary() + Black() + "\n"
                + toString(rect.min()) + "\n"
                + toString(rect.max());
    }

    void printToFile(std::string filename, std::string p[], int total) {

        std::ofstream output(filename);
        output << std::fixed << std::setprecision(10);
        for (int i = 0; i < total; i++) {
            output << p[i] << std::endl;
        }
        output.close();
    }
}