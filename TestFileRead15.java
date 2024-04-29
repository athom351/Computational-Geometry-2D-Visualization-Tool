import GeometricObjects.*;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

ublic class TestFileRead15
{
    public static void main(String[] args)
    {
        new TestFileRead15();
    }
    
    public TestFileRead15()
    {
        //testing reading from file
        System.out.println("Geometric Objects:");  //"geom objects file 01.txt" //"test.txt"
        GeometricObject[] gArray = FileUtil.readGeometricObjectsFromFile("geom objects file 01.txt");
        //in main array of string of characters created
        String[] exportedObjects = new String[gArray.length];
        //new loop
        for (int i = 0; i < gArray.length; i++) {
            //Exporting storing in the new array
            if (gArray[i] instanceof Point) {
                exportedObjects[i] = FileUtil.exportGeomObject((Point) gArray[i]);
            } else if (gArray[i] instanceof Line) {
                exportedObjects[i] = FileUtil.exportGeomObject((Line) gArray[i]);
            } else if (gArray[i] instanceof LineSegment) {
                exportedObjects[i] = FileUtil.exportGeomObject((LineSegment) gArray[i]);
            } else if (gArray[i] instanceof Ray) {
                exportedObjects[i] = FileUtil.exportGeomObject((Ray) gArray[i]);
            } else if (gArray[i] instanceof Circle) {
                exportedObjects[i] = FileUtil.exportGeomObject((Circle) gArray[i]);
            } else if (gArray[i] instanceof Triangle) {
                exportedObjects[i] = FileUtil.exportGeomObject((Triangle) gArray[i]);
            } else if (gArray[i] instanceof Rectangle) {
                exportedObjects[i] = FileUtil.exportGeomObject((Rectangle) gArray[i]);
            } else if (gArray[i] instanceof Polygon) {
                exportedObjects[i] = FileUtil.exportGeomObject((Polygon) gArray[i]);
            }

        }

        //Exporting array of strings to txt file
        FileUtil.exportToFile(exportedObjects, "exported_objects.txt");

        //Output Success???
        System.out.println("Geometric Objects exported to file: exported_objects.txt");

        
    }


}
