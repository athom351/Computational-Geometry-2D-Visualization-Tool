
//import GeometricObjects.*;

/**
 * Tests reading geometric objects from a file.
 * 
public class TestFileRead15
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
            exportedObjects[i] = gArray[i].exportGeomObject();
        }

        //Exporting array of strings to txt file
        FileUtil.exportToFile(exportedObjects, "exported_objects.txt");

        //Output Success???
        System.out.println("Geometric Objects exported to file: exported_objects.txt");

        //commented out OLD!!
        //for(GeometricObject g : gArray) {System.out.println(g);}
        
    }


}
