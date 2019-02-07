#include "Shape.h"

namespace gerber
{
    Shape::Shape()
    {
        //ctor
    }

    Shape::~Shape()
    {
        //dtor
    }

    Vertex::Vertex(double setX, double setY)
    {
        x = setX;
        y = setY;
    }
    Vertex::~Vertex()
    {

    }

    Line::Line(Vertex* setStart, Vertex* setEnd)
    {
        startVertex = setStart;
        endVertex = setEnd;
    }
    Line::~Line()
    {

    }

}
