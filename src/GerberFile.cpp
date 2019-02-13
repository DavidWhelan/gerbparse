#include "GerberFile.h"
#include <fstream>
#include <iostream>

namespace gerber
{
    GerberFile::GerberFile()
    {
        fileState = graphicsState(4, 6, false, 0, 0, false, 1);
        syntaxReader = GerberSyntaxReader(&fileState);
    }

    GerberFile::~GerberFile()
    {

    }

    void GerberFile::execute(std::string filePath, bool boardOutline)
    {
        std::ifstream fileInput;
        fileInput.open(filePath);

        std::string commandString;

        while(std::getline(fileInput, commandString))
        {
            int parsedCommandIdentifier = syntaxReader.parseCommandID(commandString);

            switch(parsedCommandIdentifier)
            {
                case FS:
                {
                    formatSpecification tempCommand = syntaxReader.returnFormat(commandString);
                    fileState.numberOfIntegerDigits = tempCommand.numberOfIntegerDigits;
                    fileState.numberOfDecimalDigits = tempCommand.numberOfDecimalDigits;
                    break;
                }

                case MO:
                {
                    unitMode tempCommand = syntaxReader.returnUnit(commandString);
                    fileState.unit = tempCommand.unitType;
                    break;
                }

                case AD:
                {
                    apertureDefine tempCommand = syntaxReader.returnApertureDefine(commandString);
                    if(tempCommand.apertureTemplate == "R")
                    {
                        apertureLibrary.emplace_back(new rectangleAperture(tempCommand.dCodeIdentifier, tempCommand.modfierList.at(0), tempCommand.modfierList.at(1)));
                    }
                    else if(tempCommand.apertureTemplate == "C")
                    {
                        apertureLibrary.emplace_back(new circleAperture(tempCommand.dCodeIdentifier, tempCommand.modfierList.at(0)));
                    }
                    break;
                }

                case DSET:
                {
                    setCurrentAperture tempCommand = syntaxReader.returnApertureSet(commandString);
                    for(unsigned int i = 0; i<apertureLibrary.size(); i++)
                    {
                        if(apertureLibrary[i]->dCommandReferenceNumber == tempCommand.dCodeNumber)
                        {
                            fileState.currentAperture = i;
                        }
                    }
                    break;
                }

                case DCOMMAND:
                {
                    operation tempCommand = syntaxReader.returnOperation(commandString);
                    if(boardOutline)
                    {
                        if(tempCommand.operationType == 1)
                        {
                            tempShapeOutline.listOfVerticies.push_back(Vertex(tempCommand.xCoordinate, tempCommand.yCoordinate));
                        }
                        break;
                    }
                    if(tempCommand.operationType == 1)
                    {
                        Shape returnShape;
                        double angle = atan2(tempCommand.yCoordinate - fileState.yCoordinate, tempCommand.xCoordinate - fileState.xCoordinate) * (180 / 3.14159);
                        angle = angle - 90;

                        double radius = apertureLibrary.at(fileState.currentAperture)->returnRadius();
                        int resolutionDegrees = 45;

                        for(int i = 0; i<=(180/resolutionDegrees); i++)
                        {
                            double tempAngle = angle + resolutionDegrees*i;
                            double xCoord = radius * cos((tempAngle)*(3.14159265/180.0)) + tempCommand.xCoordinate;
                            double yCoord = radius * sin((tempAngle)*(3.14159265/180.0)) + tempCommand.yCoordinate;
                            returnShape.listOfVerticies.push_back(Vertex(xCoord, yCoord));
                        }
                        angle += 180;
                        for(int i = 0; i<(180/resolutionDegrees); i++)
                        {
                            double tempAngle = angle + resolutionDegrees*i;
                            double xCoord = radius * cos((tempAngle)*(3.14159265/180.0)) + fileState.xCoordinate;
                            double yCoord = radius * sin((tempAngle)*(3.14159265/180.0)) + fileState.yCoordinate;
                            returnShape.listOfVerticies.push_back(Vertex(xCoord, yCoord));
                        }

                        fileState.xCoordinate = tempCommand.xCoordinate;
                        fileState.yCoordinate = tempCommand.yCoordinate;

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

                        shapeList.push_back(returnShape);

                    }

                    else if(tempCommand.operationType == 2)
                    {
                        fileState.xCoordinate = tempCommand.xCoordinate;
                        fileState.yCoordinate = tempCommand.yCoordinate;
                    }
                    else if(tempCommand.operationType == 3)
                    {
                        shapeList.push_back(apertureLibrary[fileState.currentAperture]->generateShape(tempCommand.xCoordinate, tempCommand.yCoordinate));
                        fileState.xCoordinate = tempCommand.xCoordinate;
                        fileState.yCoordinate = tempCommand.yCoordinate;
                    }
                    break;
                }

                case LP:
                {
                    loadPolarity tempCommand = syntaxReader.returnPolarity(commandString);
                    fileState.interpolationState = tempCommand.polarity;
                    break;
                }

                case GSET:
                {
                    setInterpolationMode tempCommand = syntaxReader.returnInterpolation(commandString);
                    fileState.interpolationState = tempCommand.interpolationMode;
                    break;

                }
                default:
                {
                    syntaxReader.returnUnknown(commandString);
                    break;
                }
            }
        }
        if(boardOutline)
        {
            shapeList.push_back(tempShapeOutline);
        }
        fileInput.close();
    }

    void GerberFile::clean()
    {
       shapeList.clear();
       apertureLibrary.clear();
    }
}
