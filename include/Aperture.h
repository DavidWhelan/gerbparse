#ifndef APERTURE_H_INCLUDED
#define APERTURE_H_INCLUDED

namespace gerber
{
    class aperturePrimitive
    {
        public:

            aperturePrimitive(int);
            int dCommandReferenceNumber;

        private:

        protected:
    };

    class rectangleAperture : public aperturePrimitive
    {
        public:

            rectangleAperture(int, double, double);

            double length;
            double width;
    };

    class circleAperture : public aperturePrimitive
    {
        public:

            circleAperture(int, double);

            double diameter;
    };

}

#endif // APERTURE_H_INCLUDED
