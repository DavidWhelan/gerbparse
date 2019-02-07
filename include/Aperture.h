#ifndef APERTURE_H_INCLUDED
#define APERTURE_H_INCLUDED

#include "Shape.h"

namespace gerber
{
    enum apertureTypes
    {
        CIRC,
        REC
    };

    class aperturePrimitive
    {
        public:

            aperturePrimitive(int, apertureTypes);
            aperturePrimitive();

            virtual Shape generateShape(double, double);
            virtual double returnRadius();

            int dCommandReferenceNumber;
            apertureTypes type;

        private:

        protected:
    };

    class rectangleAperture : public aperturePrimitive
    {
        public:

            rectangleAperture(int, double, double);

            Shape generateShape(double, double);
            double returnRadius();

            double length;
            double width;
    };

    class circleAperture : public aperturePrimitive
    {
        public:

            circleAperture(int, double);

            Shape generateShape(double, double);
            double returnRadius();

            double diameter;
    };

}

#endif // APERTURE_H_INCLUDED
