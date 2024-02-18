#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "geo2_util.h"

namespace Geo2Util {
    std::string Black() {
        static std::string black(" 0 0 0 255");
        return black;
    }

    /**
     * @brief Convert BoundaryType string with its x and y coordinate
     * @param t Boundary Type
     * @return A string object containing the representation of BoundaryType
     */
    std::string toString(const BoundaryType& t) {
        switch (t) {
            case BoundaryType::Solid : return "0";
            case BoundaryType::Dotted : return "1";
            case BoundaryType::Dashed : return "2";
            default: return "N/A";
        }
    }

    /**
     * @brief Convert Point_2 object to string with its x and y coordinate
     * @param p Point_2 object
     * @return A string object containing the representation of Point_2 object
     */
    std::string toString(const Point_2& p) {

        std::ostringstream s;
        s << std::fixed << std::setprecision(10) << "POINT " << p.x() << " " << p.y() 
            << Black() + toString(BoundaryType::Solid) + Black();

        return s.str();
    }

    /**
     * @brief Convert Segment_2 object to string with its source point and target point
     * @param seg Segment_2 object
     * @return A string object containing the representation of Segment_2 object
     */
    std::string toString(const Segment_2& seg) {

        return "LINE_SEGMENT" + Black() + toString(BoundaryType::Dotted) + "\n"
                + toString(seg.source()) + "\n"
                + toString(seg.target());
    }

    /**
     * @brief Convert Circle_2 object to string with its center point and radius
     * @param circ Circle_2 object
     * @return A string object containing the representation of Circle_2 object
     */
    std::string toString(const Circle_2& circ) {

        double raduis = std::sqrt(circ.squared_radius());

        std::ostringstream c;
        c << std::fixed << std::setprecision(10) << "CIRCLE " << raduis 
            << Black() << toString(BoundaryType::Dashed) << Black() + "\n"
            << toString(circ.center());

        return c.str();
    }

    /**
     * @brief Convert Triangle_2 object to string with its three vertices
     * @param tri Triangle_2 object
     * @return A string object containing the representation of Triangle_2 object
     */
    std::string toString(const Triangle_2& tri) {

        return "TRIANGLE" + Black() + toString(BoundaryType::Dotted) + Black() + "\n"
                + toString(tri[0]) + "\n"
                + toString(tri[1]) + "\n"
                + toString(tri[2]);
    }

    /**
     * @brief Convert Iso_rectangle_2 object to string with its diagonal opposite vertices
     * @param rect Iso_rectangle_2 object
     * @return A string object containing the representation of Iso_rectangle_2 object
     */
    std::string toString(const Iso_rectangle_2& rect) {

        return "RECTANGLE" + Black() + toString(BoundaryType::Dotted) + Black() + "\n"
                + toString(rect.min()) + "\n"
                + toString(rect.max());
    }

    void printToFile(const std::string& filename, const std::vector<std::string>& geo2_Objects) {

        std::ofstream output(filename);
        output << std::fixed << std::setprecision(10);
        for (int i = 0; i < geo2_Objects.size(); i++) {
            output << geo2_Objects[i] << std::endl;
        }
        output.close();
    }
}