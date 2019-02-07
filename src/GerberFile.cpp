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
                    if(tempCommand.operationType == 1)
                    {

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
        fileInput.close();
    }

    void GerberFile::clean()
    {
       shapeList.clear();
       apertureLibrary.clear();
    }
}
