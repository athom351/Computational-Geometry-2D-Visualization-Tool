#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/algorithm/string/split.hpp> // boost::split
#include <boost/algorithm/string/classification.hpp > // boost::is_any_of

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
     * @brief Convert Point_2 object to string with its x and y coordinate, with default visual setting
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
     * @brief Convert Segment_2 object to string with its source point and target point, with default visual setting
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
     * @brief Convert Circle_2 object to string with its center point and radius, with default visual setting
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
     * @brief Convert Triangle_2 object to string with its three vertices, with default visual setting
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
     * @brief Convert Iso_rectangle_2 object to string with its diagonal opposite vertices, with default visual setting
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
     * @brief Convert Polygon_2 object to string with all its vertices, with default visual setting
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
     * @brief Convert Polygon_with_holes_2 object to string with all its holes and holes' vertices (the interiors of the holes are transparent and white by defalut), with default visual setting
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
     * @brief Convert Line_2 object to string based on the general equation of a line ax + by + c = 0, with default visual setting
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
     * @brief Convert Ray_2 object to string with source() and point(1), with default visual setting
     * @param ray Ray_2 object
     * @return A string object containing the representation of Ray_2 object
     */
    std::string toString(const Ray_2& ray) {

        return "RAY " + toString(Geo2Util::DefaultBoundaryColor) + " "
            + toString(Geo2Util::DefaultBoundaryType) + "\n"
            + toString(ray.source()) + " " + "\n"
            + toString(ray.point(1));
    }

    /**
     * @brief Convert Point_2 object to string with its x and y coordinate, with customized visual setting
     * @param p Point_2 object
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @param interiorColor Interior color to be set
     * @return A string object containing the representation of Point_2 object
     */
    std::string toString(const Point_2& p, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {
        std::ostringstream s;
        s << std::fixed << std::setprecision(10) << "POINT " << p.x() << " "
            << p.y() << " "
            << toString(boundaryColor) << " "
            << toString(btype) << " "
            << toString(interiorColor);

        return s.str();
    }

    /**
     * @brief Convert Segment_2 object to string with its source point and target point, with customized visual setting
     * @param seg Segment_2 object to be set
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @return A string object containing the representation of Segment_2 object
     */
    std::string toString(const Segment_2& seg, const Color& boundaryColor, const BoundaryType btype) {

        return "LINE_SEGMENT " + toString(boundaryColor) + " "
            + toString(btype) + "\n"
            + toString(seg.source(), boundaryColor, btype, boundaryColor) + "\n"
            + toString(seg.target(), boundaryColor, btype, boundaryColor);
    }

    /**
     * @brief Convert Circle_2 object to string with its center point and radius, with customized visual setting
     * @param circ Circle_2 object
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @param interiorColor Interior color to be set
     * @return 
     */
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

    /**
     * @brief Triangle_2 object to string with its three vertices, with customized visual setting
     * @param tri Triangle_2 object
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @param interiorColor Interior color to be set
     * @return A string object containing the representation of Triangle_2 object
     */
    std::string toString(const Triangle_2& tri, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {

        return "TRIANGLE " + toString(boundaryColor) + " "
            + toString(btype) + " "
            + toString(interiorColor) + "\n"
            + toString(tri[0], boundaryColor, btype, boundaryColor) + "\n"
            + toString(tri[1], boundaryColor, btype, boundaryColor) + "\n"
            + toString(tri[2], boundaryColor, btype, boundaryColor);
    }

    /**
     * @brief Iso_rectangle_2 object to string with its diagonal opposite vertices, with customized visual setting
     * @param rect Iso_rectangle_2 object
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @param interiorColor Interior color to be set
     * @return A string object containing the representation of Iso_rectangle_2 object
     */
    std::string toString(const Iso_rectangle_2& rect, const Color& boundaryColor, const BoundaryType btype, const Color& interiorColor) {

        return "RECTANGLE " + toString(boundaryColor) + " "
            + toString(btype) + " "
            + toString(interiorColor) + "\n"
            + toString(rect.min(), boundaryColor, btype, boundaryColor) + "\n"
            + toString(rect.max(), boundaryColor, btype, boundaryColor);
    }

    /**
     * @brief Convert Polygon_2 object to string with all its vertices, with customized visual setting
     * @param poly Polygon_2 object
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @param interiorColor Interior color to be set
     * @return A string object containing the representation of Polygon_2 object
     */
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

    /**
     * @brief Convert Polygon_with_holes_2 object to string with all its holes and holes' vertices (the interiors of the holes are transparent and white by defalut), with customized visual setting
     * @param poly_w_h Polygon_with_holes_2 object
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @param interiorColor Interior color to be set
     * @return A string object containing the representation of Polygon_with_holes_2 object
     */
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

    /**
     * @brief Convert Line_2 object to string based on the general equation of a line ax + by + c = 0, with default visual setting
     * @param line Line_2 object
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @return A string object containing the representation of Line_2 object
     */
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

    /**
     * @brief Convert Ray_2 object to string with source() and point(1), with customized visual setting
     * @param ray Ray_2 object
     * @param boundaryColor Boundary color to be set
     * @param btype Boundary type to be set
     * @return A string object containing the representation of Ray_2 object
     */
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

    /**
    * The follow section includes a series of get object functions that retrieve
    * all CGAL objects of a specific type from a file.
    */

    namespace {
        // The number of lines that certain object's detail has
        const int PointDetailLength = 0;
        const int SegmentDetailLength = 2;
        const int CircleDetailLength = 1;
        const int TriangleDetailLength = 3;
        const int RectangleDetailLength = 2;
        const int LineDetailLength = 0;
        const int RayDetailLength = 2;

        /**
         * @brief This "private" function skip the object details in the input stream based on the header information that is provided.
         * @param in Input stream
         * @param header Object header
         */
        void skipObjectDetails(std::ifstream& in, std::vector<std::string>& header) {
            if (header.size() == 0) return;
            
            int num_lines = 0;
            if (header[0] == "POINT") {
                num_lines = PointDetailLength;
            }
            else if (header[0] == "LINE_SEGMENT") {
                num_lines = SegmentDetailLength;
            }
            else if (header[0] == "CIRCLE") {
                num_lines = CircleDetailLength;
            }
            else if (header[0] == "TRIANGLE") {
                num_lines = TriangleDetailLength;
            }
            else if (header[0] == "RECTANGLE") {
                num_lines = RectangleDetailLength;
            }
            else if (header[0] == "LINE") {
                num_lines = LineDetailLength;
            }
            else if (header[0] == "RAY") {
                num_lines = RayDetailLength;
            }
            else if (header[0] == "POLYGON") {
                if (header.size() < 2) // invalid data format
                    return; 
                num_lines = std::stoi(header[1]);
            }
            else {
                num_lines = 0;
            }
            
            const int max_len_per_line = 1028;
            for (int line = 0; line < num_lines; ++line) {
                in.ignore(max_len_per_line, '\n');
            }
        }
    }

    /**
     * @brief Retrieve a vector of Point_2 objects from target file.
     * @param filename Target file
     * @return A vector of Point_2 objects
     */
    std::vector<Point_2> getPoints(const std::string& filename) {
        std::ifstream in(filename);
        std::vector<Point_2> points;
        std::string content;
        while (std::getline(in, content)) {
            std::vector<std::string> header;
            boost::split(header, content, boost::is_any_of(" \n"));
            if (header[0] == "POINT") {
                double x = std::stod(header[1]);
                double y = std::stod(header[2]);

                points.push_back(Point_2(x, y));
            } 
            else {
                skipObjectDetails(in, header);
            }
        }
        in.close();
        return points;
    }

    /**
     * @brief Retrieve a vector of Line_2 objects from target file.
     * @param filename Target file
     * @return A vector of Line_2 objects
     */
    std::vector<Line_2> getLines(const std::string& filename) {
        std::ifstream in(filename);

        std::vector<Line_2> lines;
        std::string content;
        while (std::getline(in, content)) {
            std::vector<std::string> header;
            boost::split(header, content, boost::is_any_of(" \n"));
            if (header[0] == "LINE") {
                double a = std::stod(header[1]);
                double b = std::stod(header[2]);
                double c = std::stod(header[3]);

                lines.push_back(Line_2(a, b, c));
            } 
            else {
                skipObjectDetails(in, header);
            }
        }
        in.close();
        return lines;
    }

    /**
     * @brief Retrieve a vector of Circle_2 objects from target file.
     * @param filename Target file
     * @return A vector of Circle_2 objects
     */
    std::vector<Circle_2> getCircles(const std::string& filename) {
        std::ifstream in(filename);
        std::vector<Circle_2> circs;
        std::string content;
        while (std::getline(in, content)) {
            std::vector<std::string> header;
            boost::split(header, content, boost::is_any_of(" \n"));
            if (header[0] == "CIRCLE") {
                double radius = std::stod(header[1]);

                std::vector<std::string> detail;

                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x_center = std::stod(detail[1]);
                double y_center = std::stod(detail[2]);

                circs.push_back(
                    Circle_2(
                        Point_2(x_center, y_center), radius * radius
                    )
                );
            } 
            else {
                skipObjectDetails(in, header);
            }
        }
        in.close();
        return circs;
    }

    /**
     * @brief Retrieve a vector of Iso_rectangle_2 objects from target file.
     * @param filename Target file
     * @return A vector of Iso_rectangle_2 objects
     */
    std::vector<Iso_rectangle_2> getRectangles(const std::string& filename) {
        std::ifstream in(filename);
        std::vector<Iso_rectangle_2> rects;
        std::string content;
        while (std::getline(in, content)) {
            std::vector<std::string> header;
            boost::split(header, content, boost::is_any_of(" \n"));
            if (header[0] == "RECTANGLE") {
                std::vector<std::string> detail;

                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x_min = std::stod(detail[1]);
                double y_min = std::stod(detail[2]);

                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x_max = std::stod(detail[1]);
                double y_max = std::stod(detail[2]);

                rects.push_back(
                    Iso_rectangle_2(
                        Point_2(x_min, y_min), Point_2(x_max, y_max)
                    )
                );
            } 
            else {
                skipObjectDetails(in, header);
            }
        }
        in.close();
        return rects;
    }

    /**
     * @brief Retrieve a vector of Triangle_2 objects from target file.
     * @param filename Target file
     * @return A vector of Triangle_2 objects
     */
    std::vector<Triangle_2> getTriangles(const std::string& filename) {
        std::ifstream in(filename);
        std::vector<Triangle_2> tris;
        std::string content;
        while (std::getline(in, content)) {
            std::vector<std::string> header;
            boost::split(header, content, boost::is_any_of(" \n"));
            if (header[0] == "TRIANGLE") {
                std::vector<std::string> detail;
                // 0th Vertex
                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x1 = std::stod(detail[1]);
                double y1 = std::stod(detail[2]);
                // 1st Vertex
                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x2 = std::stod(detail[1]);
                double y2 = std::stod(detail[2]);
                // 2nd Vertex
                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x3 = std::stod(detail[1]);
                double y3 = std::stod(detail[2]);

                tris.push_back(
                    Triangle_2(
                        Point_2(x1, y1), Point_2(x2, y2), Point_2(x3, y3)
                    )
                );
            } 
            else {
                skipObjectDetails(in, header);
            }
        }
        in.close();
        return tris;
    }

    /**
     * @brief Retrieve a vector of Segment_2 objects from target file.
     * @param filename Target file
     * @return A vector of Segment_2 objects
     */
    std::vector<Segment_2> getSegments(const std::string& filename) {
        std::ifstream in(filename);
        std::vector<Segment_2> segs;
        std::string content;
        while (std::getline(in, content)) {
            std::vector<std::string> header;
            boost::split(header, content, boost::is_any_of(" \n"));
            if (header[0] == "LINE_SEGMENT") {
                std::vector<std::string> detail;

                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x_src = std::stod(detail[1]);
                double y_src = std::stod(detail[2]);

                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x_tar = std::stod(detail[1]);
                double y_tar = std::stod(detail[2]);

                segs.push_back(
                    Segment_2(
                        Point_2(x_src, y_src), Point_2(x_tar, y_tar)
                    )
                );
            } 
            else {
                skipObjectDetails(in, header);
            }
        }
        in.close();
        return segs;
    }

    /**
     * @brief Retrieve a vector of Ray_2 objects from target file.
     * @param filename Target file
     * @return A vector of Ray_2 objects
     */
    std::vector<Ray_2> getRays(const std::string& filename) {
        std::ifstream in(filename);
        std::vector<Ray_2> rays;
        std::string content;
        while (std::getline(in, content)) {
            std::vector<std::string> header;
            boost::split(header, content, boost::is_any_of(" \n"));
            if (header[0] == "RAY") {
                std::vector<std::string> detail;

                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x_src = std::stod(detail[1]);
                double y_src = std::stod(detail[2]);

                std::getline(in, content);
                boost::split(detail, content, boost::is_any_of(" \n"));
                double x_direct = std::stod(detail[1]);
                double y_direct = std::stod(detail[2]);

                rays.push_back(
                    Ray_2(
                        Point_2(x_src, y_src), Point_2(x_direct, y_direct)
                    )
                );
            } 
            else {
                skipObjectDetails(in, header);
            }
        }
        in.close();
        return rays;
    }

    /**
     * @brief Retrieve a vector of Polygon_2 objects from target file.
     * @param filename Target file
     * @return A vector of Polygon_2 objects
     */
    std::vector<Polygon_2> getPolygons(const std::string& filename) {
        std::ifstream in(filename);
        std::vector<Polygon_2> polygons;
        std::string content;
        while (std::getline(in, content)) {
            std::vector<std::string> header;
            boost::split(header, content, boost::is_any_of(" \n"));
            if (header[0] == "POLYGON") {
                int numVertices = std::stoi(header[1]);

                Polygon_2 poly;
                std::vector<std::string> detail;

                for (int i = 0; i < numVertices; ++i) {
                    std::getline(in, content);
                    boost::split(detail, content, boost::is_any_of(" \n"));
                    double x = std::stod(detail[1]);
                    double y = std::stod(detail[2]);

                    poly.push_back(Point_2(x, y));
                }
                polygons.push_back(poly);
            } 
            else {
                skipObjectDetails(in, header);
            }
        }
        in.close();
        return polygons;
    }
}