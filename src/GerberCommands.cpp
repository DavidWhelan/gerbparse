#include <string>
#include <vector>

#include "GerberCommands.h"

namespace gerber
{
    commandBaseClass::commandBaseClass(typesOfCommands tempType)
    {
        commandType = tempType;
    }

    commandBaseClass::~commandBaseClass(){}

    formatSpecification::formatSpecification(int integerDigits, int decimalDigits)
        :commandBaseClass(FS)
    {
        numberOfIntegerDigits = integerDigits;
        numberOfDecimalDigits = decimalDigits;
    }
    formatSpecification::formatSpecification():commandBaseClass(FS){}
    formatSpecification::~formatSpecification(){}

    unitMode::unitMode(bool setUnitType)
        :commandBaseClass(MO)
    {
        unitType = setUnitType;
    }

    unitMode::~unitMode(){}

    apertureDefine::apertureDefine(int dCode, std::string primitiveTemplate, std::vector<double> modifiers)
        :commandBaseClass(AD)
    {
        dCodeIdentifier = dCode;
        apertureTemplate = primitiveTemplate;
        for(unsigned int i = 0; i < modifiers.size(); i++)
        {
            modfierList.push_back(modifiers.at(i));
        }
    }

    apertureDefine::~apertureDefine(){}

    setCurrentAperture::setCurrentAperture(int dCode)
        :commandBaseClass(DSET)
    {
        dCodeNumber = dCode;
    }

    setCurrentAperture::~setCurrentAperture(){}

    operation::operation(int operation, double x, double y)
        :commandBaseClass(DCOMMAND)
    {
        operationType = operation;
        xCoordinate = x;
        yCoordinate = y;
    }

    operation::~operation(){}

    loadPolarity::loadPolarity(bool parsedPolarity)
        :commandBaseClass(LP)
    {
        polarity = parsedPolarity;
    }

    loadPolarity::~loadPolarity(){}

    setInterpolationMode::setInterpolationMode(int setMode)
        :commandBaseClass(GSET)
    {
        interpolationMode = setMode;
    }

    setInterpolationMode::~setInterpolationMode(){}

    unknownCommand::unknownCommand(std::string unknownCommandString)
        :commandBaseClass(UNK)
    {
        commandString = unknownCommandString;
    }

    unknownCommand::~unknownCommand(){}
}
