#ifndef GERBERGRAPHICSSTATE_H_INCLUDED
#define GERBERGRAPHICSSTATE_H_INCLUDED

namespace gerber
{
    class graphicsState
    {
        public:

            //variable that stores the coordinate format. False:mm True:inches
            bool unit;
            bool polarity; //false = dark, true = clear

            int numberOfIntegerDigits;
            int numberOfDecimalDigits;
            double xCoordinate;
            double yCoordinate;
            int currentAperture;
            int interpolationState;
            graphicsState();
            graphicsState(int, int, bool, double, double, int, bool, int);
            ~graphicsState();

        private:

        protected:

    };
}

#endif // GERBERGRAPHICSSTATE_H_INCLUDED
