## Import Data from File (C++)

### Terminology

Object Data (example)
> "POLYGON" numVertices <boundaryColor> boundaryType <interiorColor> \
"POINT" ... \
"POINT" ... \
...

Object **Header**: the first line
> "POLYGON" numVertices <boundaryColor> boundaryType <interiorColor>

Object **Details**: the rest of lines
> "POINT" ... \
"POINT" ... \
...

### Parsing

1. Parse the header into string vector
2. Check object type by comparing 0th index of string vector from step 1
    - 2a. filter/skip content if object type does not match
3. Parse object data

### Filter

Ignore certain amount of lines of content/details:
- "POINT"                   : 0
- "LINE_SEGMENT"            : 2
- "CIRCLE"                  : 1
- "TRIANGLE"                : 3
- "RECTANGLE"               : 2
- "LINE"                    : 0
- "RAY"                     : 2
- "POLYGON"                 : numPoint
- "POLYGON_WITH_HOLES"      : (Not yet decided)


## Object Format

### Point_2
"POINT" x y <boundaryColor> boundaryType <interiorColor>


### Segment_2
"LINE_SEGMENT" <boundaryColor> boundaryType <interiorColor> \
SourceVertex \
TargetVertex


### Circle_2
"CIRCLE" radius <boundaryColor> boundaryType <interiorColor> \
CenterVertex


### Triangle_2
"TRIANGLE" <boundaryColor> boundaryType <interiorColor> \
0thVertex \
1stVertex \
2ndVertex


### Iso_rectangle_2
"RECTANGLE" <boundaryColor> boundaryType <interiorColor> \
LowerLeftVertex \
HigherRightVertex


### Polygon_2
"POLYGON" numVertices <boundaryColor> boundaryType <interiorColor> // numVertices: the # of vertices is going to be read \
"POINT" ... \
"POINT" ... \
...


### Polygon_with_holes_2 (polygon with inner polygons)
"POLYGON_WITH_HOLES" numHoles                                      // numHoles: the # of holes(sub polygon) \
"POLYGON" numVertices <boundaryColor> boundaryType <interiorColor> // outer polygon \
"POINT" ... \
"POINT" ... \
... \
"POLYGON" numVertices <boundaryColor> boundaryType <interiorColor> // hole1 \
"POINT" ... \
"POINT" ... \
... \
"POLYGON" numVertices <boundaryColor> boundaryType <interiorColor> // hole2 \
"POINT" ... \
"POINT" ... \
... \
"POLYGON" ...                                                      // holeX \
...


### Line_2
"LINE" a b c <boundaryColor> boundaryType


### Ray_2
"Ray" <boundaryColor> boundaryType
SourceVertex ... \
DirectionPoint/point(1) ... // see CGAL Ray_2::point(const Kernel::FT i)
