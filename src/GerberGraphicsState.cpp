#include "GerberGraphicsState.h"
namespace gerber
{


    graphicsState::graphicsState(int integerDigits, int decimalDigits, bool unitValue,
                  double startX, double startY, bool polaritySet, int setInterpolation)
    {
        currentAperture = 0;
        unit = unitValue;
        numberOfIntegerDigits = integerDigits;
        numberOfDecimalDigits = decimalDigits;
        xCoordinate = startX;
        yCoordinate = startY;
        polarity = polaritySet;
        interpolationState = setInterpolation;
    }

    graphicsState::graphicsState(){}

    graphicsState::~graphicsState(){}

}
