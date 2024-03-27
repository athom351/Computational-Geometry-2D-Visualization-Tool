#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "geo2_util.h"

namespace Geo2Util {
    /**
     * @brief Convert color to string in a form of "r, g, b, trans"
     * @param color Color object (r, b, g, trans)
     * @return A string object containing the representation of Color
     */
    std::string toString(const Color& color) {
        return std::to_string(color.r) + " "
            + std::to_string(color.g) + " "
            + std::to_string(color.b) + " "
            + std::to_string(color.trans);
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
        s << std::fixed << std::setprecision(10) << "POINT " << p.x() << " "
            << p.y() << " "
            << toString(Geo2Util::DefaultBoundaryColor) << " "
            << toString(Geo2Util::DefaultBoundaryType) << " "
            << toString(Geo2Util::DefaultInteriorColor);

        return s.str();
    }

    /**
     * @brief Convert Segment_2 object to string with its source point and target point
     * @param seg Segment_2 object
     * @return A string object containing the representation of Segment_2 object
     */
    std::string toString(const Segment_2& seg) {

        return "LINE_SEGMENT " + toString(Geo2Util::DefaultBoundaryColor) + " "
            + toString(Geo2Util::DefaultBoundaryType) + "\n"
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
        c << std::fixed << std::setprecision(10) << "CIRCLE " << raduis << " "
            << toString(Geo2Util::DefaultBoundaryColor) << " "
            << toString(Geo2Util::DefaultBoundaryType) << " "
            << toString(Geo2Util::DefaultInteriorColor) + "\n"
            << toString(circ.center());

        return c.str();
    }

    /**
     * @brief Convert Triangle_2 object to string with its three vertices
     * @param tri Triangle_2 object
     * @return A string object containing the representation of Triangle_2 object
     */
    std::string toString(const Triangle_2& tri) {

        return "TRIANGLE " + toString(Geo2Util::DefaultBoundaryColor) + " "
            + toString(Geo2Util::DefaultBoundaryType) + " "
            + toString(Geo2Util::DefaultInteriorColor) + "\n"
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

        return "RECTANGLE " + toString(Geo2Util::DefaultBoundaryColor) + " "
            + toString(Geo2Util::DefaultBoundaryType) + " "
            + toString(Geo2Util::DefaultInteriorColor) + "\n"
            + toString(rect.min()) + "\n"
            + toString(rect.max());
    }

    /**
     * @brief Convert Polygon_2 object to string with all its vertices
     * @param poly Polygon_2 object
     * @return A string object containing the representation of Polygon_2 object
     */
    std::string toString(const Polygon_2& poly) {
        std::string points_str = "";
        for (auto it = poly.begin(); it != poly.end(); ++it) {
            points_str += toString(*it);
            if (it != poly.end() - 1) points_str += "\n";
        }

        return "POLYGON " + std::to_string(poly.size()) + " "
            + toString(Geo2Util::DefaultBoundaryColor) + " "
            + toString(Geo2Util::DefaultBoundaryType) + " "
            + toString(Geo2Util::DefaultInteriorColor) + "\n"
            + points_str;
    }

    /**
     * @brief Convert Polygon_with_holes_2 object to string with all its holes and holes' vertices (the interiors of the holes are transparent and white by defalut)
     * @param poly_w_h Polygon_with_holes_2 object
     * @return A string object containing the representation of Polygon_with_holes_2 object
     */
    std::string toString(const Polygon_with_holes_2& poly_w_h) {
        std::string holes_str = "";
        for (auto it = poly_w_h.holes_begin(); it != poly_w_h.holes_end(); ++it) {
            holes_str += toString(*it, Geo2Util::DefaultBoundaryColor, Geo2Util::DefaultBoundaryType, TransparentWhite);
            if (it != poly_w_h.holes_end() - 1) holes_str += "\n";
        }

        return "POLYGON_WITH_HOLES " + std::to_string(poly_w_h.number_of_holes()) + "\n"
            + toString(poly_w_h.outer_boundary()) + "\n"
            + holes_str;
    }

    /**
     * @brief Convert Line_2 object to string based on the general equation of a line ax + by + c = 0
     * @param line Line_2 object
     * @return A string object containing the representation of Line_2 object
     */
    std::string toString(const Line_2& line) {
        
        std::ostringstream oss;

        oss << std::fixed << std::setprecision(10) << "LINE "
            << line.a() << " "
            << line.b() << " "
            << line.c() << " "
            << toString(Geo2Util::DefaultBoundaryColor) << " "
            << toString(Geo2Util::DefaultBoundaryType);

        return oss.str();
    }

    /**
     * @brief Convert Ray_2 object to string with source() and point(1)
     * @param ray Ray_2 object
     * @return A string object containing the representation of Ray_2 object
     */
    std::string toString(const Ray_2& ray) {

        return "RAY " + toString(Geo2Util::DefaultBoundaryColor) + " "
            + toString(Geo2Util::DefaultBoundaryType) + "\n"
            + toString(ray.source()) + " " + "\n"
            + toString(ray.point(1));
    }

    // Customized toString
    //! Underlying points of all objects (except Point_2) have the same color (boundary color and interior color) as its boundary color
    //! Underlying points of all objects have the same boundary type as the objects themselves
    std::string toString(const Point_2& p, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {
        std::ostringstream s;
        s << std::fixed << std::setprecision(10) << "POINT " << p.x() << " "
            << p.y() << " "
            << toString(boundaryColor) << " "
            << toString(btype) << " "
            << toString(interiorColor);

        return s.str();
    }

    std::string toString(const Segment_2& seg, const Color& boundaryColor, const BoundaryType btype) {

        return "LINE_SEGMENT " + toString(boundaryColor) + " "
            + toString(btype) + "\n"
            + toString(seg.source(), boundaryColor, btype, boundaryColor) + "\n"
            + toString(seg.target(), boundaryColor, btype, boundaryColor);
    }

    std::string toString(const Circle_2& circ, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {

        double raduis = std::sqrt(circ.squared_radius());

        std::ostringstream c;
        c << std::fixed << std::setprecision(10) << "CIRCLE " << raduis << " "
            << toString(boundaryColor) << " "
            << toString(interiorColor) << " "
            << toString(btype) + "\n"
            << toString(circ.center(), boundaryColor, btype, boundaryColor);

        return c.str();
    }

    std::string toString(const Triangle_2& tri, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {

        return "TRIANGLE " + toString(boundaryColor) + " "
            + toString(btype) + " "
            + toString(interiorColor) + "\n"
            + toString(tri[0], boundaryColor, btype, boundaryColor) + "\n"
            + toString(tri[1], boundaryColor, btype, boundaryColor) + "\n"
            + toString(tri[2], boundaryColor, btype, boundaryColor);
    }

    std::string toString(const Iso_rectangle_2& rect, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {

        return "RECTANGLE " + toString(boundaryColor) + " "
            + toString(btype) + " "
            + toString(interiorColor) + "\n"
            + toString(rect.min(), boundaryColor, btype, boundaryColor) + "\n"
            + toString(rect.max(), boundaryColor, btype, boundaryColor);
    }

    std::string toString(const Polygon_2& poly, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {
        std::string points_str = "";
        for (auto it = poly.begin(); it != poly.end(); ++it) {
            points_str += toString(*it, boundaryColor, btype, boundaryColor);
            if (it != poly.end() - 1) points_str += "\n";
        }

        return "POLYGON " + std::to_string(poly.size()) + " "
            + toString(boundaryColor) + " "
            + toString(btype) + " "
            + toString(interiorColor) + "\n"
            + points_str;
    }

    std::string toString(const Polygon_with_holes_2& poly_w_h, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {
        std::string holes_str = "";
        for (auto it = poly_w_h.holes_begin(); it != poly_w_h.holes_end(); ++it) {
            holes_str += toString(*it, boundaryColor, btype, TransparentWhite);
            if (it != poly_w_h.holes_end() - 1) holes_str += "\n";
        }

        return "POLYGON_WITH_HOLES " + std::to_string(poly_w_h.number_of_holes()) + "\n"
            + toString(poly_w_h.outer_boundary(), boundaryColor, btype, interiorColor) + "\n"
            + holes_str;
    }

    std::string toString(const Line_2& line, const Color& boundaryColor, const BoundaryType btype) {

        std::ostringstream oss;

        oss << std::fixed << std::setprecision(10) << "LINE "
            << line.a() << " "
            << line.b() << " "
            << line.c() << " "
            << toString(boundaryColor) << " "
            << toString(btype);

        return oss.str();
    }

    std::string toString(const Ray_2& ray, const Color& boundaryColor, const BoundaryType btype) {
        return "RAY " + toString(boundaryColor) + " "
            + toString(btype) + "\n"
            + toString(ray.source(), boundaryColor, btype, boundaryColor) + "\n"
            + toString(ray.point(1), boundaryColor, btype, boundaryColor);
    }

    /**
     * @brief Export a collect of 2D geometry objects to a file
     * @param filename Export target file
     * @param geo2_Objects String representations of a collection of 2D geometry objects
     */
    void printToFile(const std::string& filename, const std::vector<std::string>& geo2_Objects) {

        std::ofstream output(filename);
        output << std::fixed << std::setprecision(10);
        for (int i = 0; i < geo2_Objects.size(); i++) {
            output << geo2_Objects[i] << std::endl;
        }
        output.close();
    }
}