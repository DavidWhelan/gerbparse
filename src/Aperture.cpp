//This file defines the aperture that gerber uses. ONLY THE PRIMITIVE APERTURES ARE DEINFED
//This is geared toward kiCad and it only uses circles and rectangles AFIK

#include "Aperture.h"
namespace gerber
{

    aperturePrimitive::aperturePrimitive(int dCommandNumber)
    {
        dCommandReferenceNumber = dCommandNumber;
    }

    rectangleAperture::rectangleAperture(int dCommandNumber, double parsedLength, double parsedWidth)
        :aperturePrimitive(dCommandNumber)
    {
        length = parsedLength;
        width = parsedWidth;
    }


    circleAperture::circleAperture(int dCommandNumber, double parsedDiameter)
        :aperturePrimitive(dCommandNumber)
    {
        diameter = parsedDiameter;
    }

}

