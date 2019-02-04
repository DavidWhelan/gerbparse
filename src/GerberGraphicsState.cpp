#include "GerberGraphicsState.h"
namespace gerber
{


    graphicsState::graphicsState(int integerDigits, int decimalDigits, bool unitValue,
                  double startX, double startY, int defaultAperture,
                  bool polaritySet, int setInterpolation)
    {
        unit = unitValue;
        numberOfIntegerDigits = integerDigits;
        numberOfDecimalDigits = decimalDigits;
        xCoordinate = startX;
        yCoordinate = startY;
        currentAperture = defaultAperture;
        polarity = polaritySet;
        interpolationState = setInterpolation;
    }

    graphicsState::graphicsState(){}

    graphicsState::~graphicsState(){}

}
