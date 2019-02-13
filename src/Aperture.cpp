//This file defines the aperture that gerber uses. ONLY THE PRIMITIVE APERTURES ARE DEINFED
//This is geared toward kiCad and it only uses circles and rectangles AFIK

#include "Aperture.h"
#include <iostream>
#include <math.h>
namespace gerber
{

    aperturePrimitive::aperturePrimitive(int dCommandNumber, apertureTypes tempType)
    {
        dCommandReferenceNumber = dCommandNumber;
        type = tempType;
    }

    aperturePrimitive::aperturePrimitive()
    {
        dCommandReferenceNumber = 10;
        type = REC;
    }

    Shape aperturePrimitive::generateShape(double x, double y)
    {
        return Shape();
    }

    double aperturePrimitive::returnRadius()
    {
        return 1.0;
    }

    rectangleAperture::rectangleAperture(int dCommandNumber, double parsedLength, double parsedWidth)
        :aperturePrimitive(dCommandNumber, REC)
    {
        length = parsedLength;
        width = parsedWidth;
    }

    Shape rectangleAperture::generateShape(double x, double y)
    {
        Shape returnShape;

        Vertex bottomLeft(x-length/2.0, y-width/2.0);
        returnShape.listOfVerticies.push_back(bottomLeft);

        Vertex topLeft(x-length/2.0, y+width/2.0);
        returnShape.listOfVerticies.push_back(topLeft);

        Vertex topRight(x+length/2.0, y+width/2.0);
        returnShape.listOfVerticies.push_back(topRight);

        Vertex bottomRight(x+length/2.0, y-width/2.0);
        returnShape.listOfVerticies.push_back(bottomRight);

        for(unsigned int i = 0; i<returnShape.listOfVerticies.size(); i++)
        {
            if(i == returnShape.listOfVerticies.size()-1)
            {
                Line tempLine(&returnShape.listOfVerticies.at(i), &returnShape.listOfVerticies.at(0));
                returnShape.listOfLines.push_back(tempLine);
            }
            else
            {
                Line tempLine(&returnShape.listOfVerticies.at(i), &returnShape.listOfVerticies.at(i+1));
                returnShape.listOfLines.push_back(tempLine);
            }
        }

        return returnShape;
    }

    double rectangleAperture::returnRadius()
    {
        return sqrt((length*length)+(width*width));
    }


    circleAperture::circleAperture(int dCommandNumber, double parsedDiameter)
        :aperturePrimitive(dCommandNumber, CIRC)
    {
        diameter = parsedDiameter;
    }

    Shape circleAperture::generateShape (double x, double y)
    {
        Shape returnShape;
        double radius = diameter/2.0;
        int resolutionDegrees = 45;
        for(int i = 0; i<(360/resolutionDegrees); i++)
        {
            double xCoord = radius * cos((resolutionDegrees*i)*(3.14159265/180.0)) + x;
            double yCoord = radius * sin((resolutionDegrees*i)*(3.14159265/180.0)) + y;
            returnShape.listOfVerticies.push_back(Vertex(xCoord, yCoord));
        }

        for(unsigned int i = 0; i<returnShape.listOfVerticies.size(); i++)
        {
            if(i == returnShape.listOfVerticies.size()-1)
            {
                Line tempLine(&returnShape.listOfVerticies.at(i), &returnShape.listOfVerticies.at(0));
                returnShape.listOfLines.push_back(tempLine);
            }
            else
            {
                Line tempLine(&returnShape.listOfVerticies.at(i), &returnShape.listOfVerticies.at(i+1));
                returnShape.listOfLines.push_back(tempLine);
            }
        }
        return returnShape;
    }

    double circleAperture::returnRadius()
    {
        return diameter/(double)2;
    }
}

