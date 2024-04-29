
//import GeometricObjects.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Utilities to read from file a set of geometric objects.
 */
public class FileUtil
{
    /**
     * Reads geometric objects from given file into an array.
     * 
     * @param filename given filename
     * @return array of geometric objects
     */
    public static GeometricObject[] readGeometricObjectsFromFile(String filename)
    {
        ArrayList<GeometricObject> gList = new ArrayList<>();
        
        File file = new File(filename);
        try
        {
            Scanner in = new Scanner(file);

            int[] g;

            while(in.hasNextLine())
            {
                String str = in.nextLine();
                
                //tokens[0]: object type (POINT, LINE, ...), tokens[1]: parameters
                String[] tokens = str.split(" ", 2);

                switch (tokens[0])
                {
                    case "POLYGON":

                        Polygon poly = parsePolygon(str,in);
                        gList.add(poly);

                        break;
                    case "CIRCLE":

                        Circle circle = parseCircle(str,in);

                        if(circle != null){
                            gList.add(circle);
                        }

                        break;
                    case "LINE":

                        Line line = parseLine(str);
                        gList.add(line);
                        
                        break;

                    case "POINT":
                        Point point = parsePoint(str);
                        gList.add(point);
                        
                        break;

                    case "RECTANGLE":
                        //read parameters that define the geometric object
                         g = parseGeometricObject(tokens[1]);

                        //read points that define the rectangle
                        Point begin = parsePoint(in.nextLine());
                        Point end   = parsePoint(in.nextLine());

                        Rectangle rect = new Rectangle(begin, end);
                        rect.setBoundaryColor(new Color(g[0], g[1], g[2], g[3]));
                        rect.setBoundaryType((g[4]));
                        rect.setInteriorColor(new Color(g[5], g[6], g[7], g[8]));

                        gList.add(rect);

                        break;

                    case "TRIANGLE":

                         g = parseGeometricObject(tokens[1]);

                        //read points that define the triangle
                        Point p1 = parsePoint(in.nextLine());
                        Point p2 = parsePoint(in.nextLine());
                        Point p3 = parsePoint(in.nextLine());

                        Triangle tri = new Triangle(p1,p2,p3);
                        tri.setBoundaryColor(new Color(g[0], g[1], g[2], g[3]));
                        tri.setBoundaryType((g[4]));
                        tri.setInteriorColor(new Color(g[5],g[6],g[7],g[8]));

                        gList.add(tri);

                        break;

                    case "RAY":

                        g = parseGeometricObject(tokens[1]);

                        Point ray_point = parsePoint(in.nextLine());
                        Point direction = parsePoint(in.nextLine());

                        Ray ray = new Ray(ray_point,direction);
                        ray.setBoundaryColor(new Color(g[0], g[1], g[2], g[3]));
                        ray.setBoundaryType((g[4]));


                        gList.add(ray);

                        break;

                    case "SEGMENT":

                        g = parseGeometricObject(tokens[1]);

                        Point endPoint1 = parsePoint(in.nextLine());
                        Point endPoint2 = parsePoint(in.nextLine());

                        LineSegment seg = new LineSegment(endPoint1,endPoint2);
                        seg.setBoundaryColor(new Color(g[0], g[1], g[2], g[3]));
                        seg.setBoundaryType((g[4]));

                        gList.add(seg);

                        break;



                }
            }

            in.close();
        } catch (FileNotFoundException e)
        {
            System.out.println("File not found!");
        }
        
        GeometricObject[] gArray = new GeometricObject[gList.size()];
        gArray = gList.toArray(gArray);
        
        return gArray;
    }
    
    /**
     * Parse the given string into the components of a geometric object; no 
     * validation is performed on the string.
     * 
     * @param str string formatted as "r g b alpha beta r g b alpha" or
     *            as "r g b alpha beta"
     * 
     * @return an int array with the parsed values
     */
    private static int[] parseGeometricObject(String str)
    {
        int[] g;

        String[] features = str.split(" ");

        //there are two possibilities for the input string:
        // "r g b alpha beta r g b alpha" or "r g b alpha beta"
        if (features.length == 9) //input string: "r g b alpha beta r g b alpha"
        {
            g = new int[9];

            //red component of the boundary color
            g[0] = Integer.parseInt(features[0]);

            //green component of the boundary color
            g[1] = Integer.parseInt(features[1]);

            //blue component of the boundary color
            g[2] = Integer.parseInt(features[2]);

            //alpha component of the boundary color
            g[3] = Integer.parseInt(features[3]);

            //beta component of the boundary, i.e., the boundary type
            g[4] = Integer.parseInt(features[4]);

            //red component of the interior color
            g[5] = Integer.parseInt(features[5]);

            //green component of the interior color
            g[6] = Integer.parseInt(features[6]);

            //blue component of the interior color
            g[7] = Integer.parseInt(features[7]);

            //alpha component of the interior color
            g[8] = Integer.parseInt(features[8]);
        }
        else //input string: "r g b alpha beta"
        {
            g = new int[5];

            //red component of the boundary color
            g[0] = Integer.parseInt(features[0]);

            //green component of the boundary color
            g[1] = Integer.parseInt(features[1]);

            //blue component of the boundary color
            g[2] = Integer.parseInt(features[2]);

            //alpha component of the boundary color
            g[3] = Integer.parseInt(features[3]);

            //beta component of the boundary, i.e., the boundary type
            g[4] = Integer.parseInt(features[4]);
        }

        return g;
    }

    /**
     * Parse the given string into the components of a lineInfo; no validation
     * is performed on the string.
     * 
     * @param str string formatted as "POINT x y r g b alpha beta r g b alpha"
     * 
     * @return corresponding Point object
     */
    public static Point parsePoint(String str)
    {
        //separates str into 4 strings: POINT, x, y, and the rest (r g b ...)
        String[] pointInfo = str.split(" ", 4);

        //parses the value of x and y
        double x = Double.parseDouble(pointInfo[1]);
        double y = Double.parseDouble(pointInfo[2]);
        
        //parses the geometric info portion
        int[] g = parseGeometricObject(pointInfo[3]);
        
        //defines colors and boundary type
        Color boundaryColor = new Color(g[0], g[1], g[2], g[3]);
        int boundaryType = g[4];
        Color interiorColor = new Color(g[5], g[6], g[7], g[8]);
        
        //defines lineInfo properties with the information just parsed
        Point p = new Point(x, y);
        p.setBoundaryColor(boundaryColor);
        p.setBoundaryType(boundaryType);
        p.setInteriorColor(interiorColor);
        
        return p;
    }

    /**
     * Parse the given string into the components of a lineInfo; no validation 
     * is performed on the string.
     * 
     * @param str string formatted as "LINE a b c r g b alpha beta"
     * 
     * @return corresponding Line object
     */
    public static Line parseLine(String str)
    {
        //separates str into 5 strings: LINE, a, b, c, and the rest (r g b ...)
        String[] lineInfo = str.split(" ", 5);

        //parses the value of a, b, and c
        double a = Double.parseDouble(lineInfo[1]);
        double b = Double.parseDouble(lineInfo[2]);
        double c = Double.parseDouble(lineInfo[3]);
        
        //parses the geometric info portion
        int[] g = parseGeometricObject(lineInfo[4]);
        
        //defines colors and boundary type
        Color boundaryColor = new Color(g[0], g[1], g[2], g[3]);
        int boundaryType = g[4];
        
        //defines lineInfo properties with the information just parsed
        Line line = new Line(a, b, c);
        line.setBoundaryColor(boundaryColor);
        line.setBoundaryType(boundaryType);
        
        return line;
    }

    public static Circle parseCircle(String str, Scanner in){

        String[] circleInfo = str.split(" ",3);
        double radius = Double.parseDouble(circleInfo[1]);
        //parses that geometric info portion
        int[] g = parseGeometricObject(circleInfo[2]);

        Color boundaryColor = new Color(g[0],g[1],g[2],g[3]);
        int boundaryType = g[4];
        Color interiorColor = new Color(g[5], g[6], g[7], g[8]);

        if(in.hasNextLine()){
            String pointStr = in.nextLine();
            Point center = parsePoint(pointStr);

            Circle circle = new Circle(radius,center);
            circle.setBoundaryColor(boundaryColor);
            circle.setBoundaryType(boundaryType);
            circle.setInteriorColor(interiorColor);


            return circle;
        }
        else{
            System.out.println("Missing point information of circle");
            return null;
        }

    }

    public static Polygon parsePolygon(String str, Scanner in){

        String[] polygonInfo = str.split(" ", 3);

        int numVertices =  Integer.parseInt(polygonInfo[1]); //gets number of vertices
        int[] g = parseGeometricObject(polygonInfo[2]);      // parses polygons geometric information

        //defines colors and boundary type
        Color boundaryColor = new Color(g[0],g[1],g[2],g[3]);
        int boundaryType = g[4];
        Color interiorColor = new Color(g[5], g[6], g[7], g[8]);

        Point[] points = new Point[numVertices]; //Array of points to create polygon

        int ctr = 0; //counter to check how many points have been added

        for(int i =0; i<numVertices; i++){

            String pointStr = in.nextLine();
            Point p = parsePoint(pointStr);

            points[ctr++] = p;
        }

        Polygon polygon = new Polygon(points);
        polygon.setBoundaryColor(boundaryColor);
        polygon.setBoundaryType(boundaryType);
        polygon.setInteriorColor(interiorColor);


        return polygon;
    }


    public static String exportGeomObject(Point p) {
        return "POINT " + p.getX() + " " + p.getY() + " " + p.toString();
    }

    public static String exportGeomObject(Line line) {
        return "LINE " + line.getA() + " " + line.getB() + " " + line.getC() + " " + line.toString();
    }

    public static String exportGeomObject(LineSegment lineSegment) {
        return "LINE_SEGMENT " + lineSegment.getBegin().getX() + " " + lineSegment.getBegin().getY() + " " +
                lineSegment.getEnd().getX() + " " + lineSegment.getEnd().getY() + " " + lineSegment.toString();
    }

    public static String exportGeomObject(Ray ray) {
        return "RAY " + ray.getSource().getX() + " " + ray.getSource().getY() + " " +
                ray.getDirection().getX() + " " + ray.getDirection().getY() + " " + ray.toString();
    }

    public static String exportGeomObject(Circle c) {
        return "CIRCLE " + c.getRadius() + " " + c.getCenter().getX() + " " + c.getCenter().getY() + " " + c.toString();
    }

    public static String exportGeomObject(Triangle t) {
        return "TRIANGLE " + t.getBegin().getX() + " " + t.getBegin().getY() + " " +
                t.getMiddle().getX() + " " + t.getMiddle().getY() + " " +
                t.getEnd().getX() + " " + t.getEnd().getY() + " " + t.toString();
    }

    public static String exportGeomObject(Rectangle rectangle) {
        return "RECTANGLE " + rectangle.getBegin().getX() + " " + rectangle.getBegin().getY() + " " +
                rectangle.getEnd().getX() + " " + rectangle.getEnd().getY() + " " + rectangle.toString();
    }

    public static String exportGeomObject(Polygon polygon) {
    StringBuilder sb = new StringBuilder();
    sb.append("POLYGON ").append(polygon.getNumberOfVertices()).append("\n");
    Point[] vertices = polygon.getVertices();
        for (Point vertex : vertices) {
        sb.append(vertex.getX()).append(" ").append(vertex.getY()).append("\n");
        }
    return sb.toString();
    }

    public static void exportToFile(String[] exportedObjects, String filename) {
        try {
            FileWriter writer = new FileWriter(filename);
            for (String object : exportedObjects) {
                writer.write(object + "\n"); // Write each object followed by a newline
            }
            writer.close();
            System.out.println("Export successful to file: " + filename);
        } catch (IOException e) {
            System.out.println("Error exporting to file: " + e.getMessage());
        }
    }

}
