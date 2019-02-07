#include "GerberSyntaxReader.h"
#include <iostream>
namespace gerber
{

    GerberSyntaxReader::GerberSyntaxReader(graphicsState *pointerToGraphicsState)
    {
        graphicsStateForParsing = pointerToGraphicsState;

        FSCommand = std::regex("%FSLAX\\d{2}Y\\d{2}\\*%", std::regex::icase | std::regex::ECMAScript);
        MOCommand = std::regex("%MO(IN||MM)\\*%", std::regex::icase | std::regex::ECMAScript);
        ADDCommand = std::regex("%ADD\\d+(R|C|O|P)\\,(\\d*\\.?\\d*)(X\\d*\\.?\\d*)*\\*%", std::regex::icase | std::regex::ECMAScript);
        setAperture = std::regex("D[1-9][0-9]+\\*", std::regex::icase | std::regex::ECMAScript);
        DOperation = std::regex("((X(\\+|-)?\\d+)?(Y(\\+|-)?\\d+)?)?D0(1|2|3)\\*", std::regex::icase | std::regex::ECMAScript);
        LPCommand = std::regex("%LP(C|D)\\*%", std::regex::icase | std::regex::ECMAScript);
        setInterpolation = std::regex("G0(1|2|3)\\*", std::regex::icase | std::regex::ECMAScript);
    }

    GerberSyntaxReader::GerberSyntaxReader(){}

    GerberSyntaxReader::~GerberSyntaxReader()
    {
        //dtor
    }

    int GerberSyntaxReader::parseCommandID(std::string inputString)
    {

        if(std::regex_match(inputString, FSCommand))
        {
            return FS;
        }
        else if(std::regex_match(inputString, MOCommand))
        {
            return MO;
        }
        else if(std::regex_match(inputString, ADDCommand))
        {
            return AD;
        }
        else if(std::regex_match(inputString, setAperture))
        {
            return DSET;
        }
        else if(std::regex_match(inputString, DOperation))
        {
            return DCOMMAND;
        }
        else if(std::regex_match(inputString, LPCommand))
        {
            return LP;
        }
        else if(std::regex_match(inputString, setInterpolation))
        {
            return GSET;
        }

        return UNK;
    }

    formatSpecification GerberSyntaxReader::returnFormat(std::string inputString)
    {
        std::cout << "FSCommand ";
        int numInt = std::stoi(inputString.substr(6, 1));
        std::cout << "Int:" << numInt;
        int numDouble = std::stoi(inputString.substr(7, 1));
        gerber::formatSpecification returnFormatSpecification(numInt, numDouble);
        std::cout << " Double:" << numDouble << "\n";

        return returnFormatSpecification;
    }

    unitMode GerberSyntaxReader::returnUnit(std::string inputString)
    {
        std::cout << "MOCommand ";
        if(inputString.substr(3, 2) == "MM")
        {
            std::cout << "MM\n";
            gerber::unitMode returnUnitMode(false);
            return returnUnitMode;
        }
        else
        {
            std::cout << "IN\n";
            gerber::unitMode returnUnitMode(true);
            return returnUnitMode;
        }
    }

    apertureDefine GerberSyntaxReader::returnApertureDefine(std::string inputString)
    {
        std::string dCodeNumber;
        std::string apertureTemplate;
        std::string listOfModifiers;

        dCodeNumber = inputString.substr(inputString.find("D")+2, 2);
        apertureTemplate = inputString.substr(inputString.find(",")-1, 1);
        listOfModifiers = inputString.substr(inputString.find(",") + 1, inputString.find("*")-inputString.find(",")-1);
        std::cout << "Number: " << dCodeNumber << " Template: " << apertureTemplate << " Modifiers: " << listOfModifiers << "\n";

        int intDCodeNumber = std::stoi(dCodeNumber);

        std::vector<double> listOfModifiersDouble;
        std::string tempString = listOfModifiers;
        while(true)
        {
            if(tempString.find("X")!= std::string::npos)
            {
                double tempDouble;
                tempDouble = std::stod(tempString.substr(0, tempString.find("X")));
                listOfModifiersDouble.push_back(tempDouble);
                tempString = tempString.substr(tempString.find("X")+1, tempString.size()-tempString.find("X"));
            }
            else
            {
                double tempDouble = std::stod(tempString);
                listOfModifiersDouble.push_back(tempDouble);
                break;
            }
        }

        gerber::apertureDefine returnApertureDefine(intDCodeNumber, apertureTemplate, listOfModifiersDouble);
        return returnApertureDefine;

    }

    setCurrentAperture GerberSyntaxReader::returnApertureSet(std::string inputString)
    {
        std::cout << "Aperture Set ";
        std::string stringSetAperture = inputString.substr(1, inputString.find("*")-1);
        int apertureNumber = std::stoi(stringSetAperture);
        std::cout << apertureNumber << "\n";
        gerber::setCurrentAperture returnSetCurrentAperture(apertureNumber);
        return returnSetCurrentAperture;
    }

    operation GerberSyntaxReader::returnOperation(std::string inputString)
    {
        int dCommandOperation;
        double x;
        double y;
        if(inputString.find("X") != std::string::npos)
        {
            int xPosStart = inputString.find("X") + 1;
            int xPosEnd;
            if(inputString.find("Y") != std::string::npos) xPosEnd = inputString.find("Y") - inputString.find("X") -1;
            else xPosEnd = (inputString.find("D")) - inputString.find("X") -1;
            std::string xNumberString = inputString.substr(xPosStart, xPosEnd);
            xNumberString = xNumberString.substr(0, xNumberString.size()-graphicsStateForParsing->numberOfDecimalDigits) + "." + xNumberString.substr(xNumberString.size()-graphicsStateForParsing->numberOfDecimalDigits, graphicsStateForParsing->numberOfDecimalDigits);
            x = std::stod(xNumberString);
        }
        else
        {
            x = graphicsStateForParsing->xCoordinate;
        }
        if(inputString.find("Y") != std::string::npos)
        {
            int yPosStart = inputString.find("Y") + 1;
            int yPosEnd = inputString.find("D") - yPosStart;
            std::string yNumberString = inputString.substr(yPosStart, yPosEnd);
            yNumberString = yNumberString.substr(0, yNumberString.size()-graphicsStateForParsing->numberOfDecimalDigits) + "." + yNumberString.substr(yNumberString.size()-graphicsStateForParsing->numberOfDecimalDigits, graphicsStateForParsing->numberOfDecimalDigits);
            y = std::stod(yNumberString);
        }
        else
        {
            y = graphicsStateForParsing->yCoordinate;
        }
        std::string dOperationString = inputString.substr(inputString.find("D") + 1, inputString.find("*") - inputString.find("D") -1);
        dCommandOperation = std::stoi(dOperationString);
        std::cout << "D Operation:" <<dCommandOperation << " X:" << x << " Y:" << y << "\n";
        gerber::operation returnOperation(dCommandOperation, x, y);
        return returnOperation;
    }

    loadPolarity GerberSyntaxReader::returnPolarity(std::string inputString)
    {
        std::cout << "LPCommand ";
        if(inputString.substr(3, 1) == "D")
        {
            std::cout << "Dark\n";
            gerber::loadPolarity returnLoadPolarity(false);
            return returnLoadPolarity;
        }
        else
        {
            std::cout << "Clear\n";
            gerber::loadPolarity returnLoadPolarity(true);
            return returnLoadPolarity;
        }
    }

    setInterpolationMode GerberSyntaxReader::returnInterpolation(std::string inputString)
    {
        std::string stringOfInterpolation = inputString.substr(1, inputString.find("*")-1);
        int interpolationNumber = std::stoi(stringOfInterpolation);
        std::cout << "Set Interpolation " << interpolationNumber << "\n";
        gerber::setInterpolationMode returnSetInterpolationMode(interpolationNumber);
        return returnSetInterpolationMode;
    }

    unknownCommand GerberSyntaxReader::returnUnknown(std::string inputString)
    {
        std::cout <<inputString << "\n";
        return unknownCommand(inputString);
    }
}
