#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

namespace gerber
{

    class Vertex
    {
        public:
            Vertex(double, double);
            ~Vertex();
            double x;
            double y;
    };

    class Line
    {
        public:
            Line(Vertex*, Vertex*);
            ~Line();
            Vertex* startVertex;
            Vertex* endVertex;
    };

    class Shape
    {
        public:
            /** Default constructor */
            Shape();
            /** Default destructor */
            virtual ~Shape();
            std::vector<Vertex> listOfVerticies;
            std::vector<Line> listOfLines;

        protected:

        private:
    };
}


#endif // SHAPE_H
