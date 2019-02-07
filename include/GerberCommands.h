#ifndef GERBERCOMMANDS_H_INCLUDED
#define GERBERCOMMANDS_H_INCLUDED

#include <string>
#include <vector>

namespace gerber
{

    enum typesOfCommands
    {
        FS,
        MO,
        AD,
        DSET,
        DCOMMAND,
        LP,
        GSET,
        UNK
    };

    class commandBaseClass
    {
        public:
            int commandType;
            commandBaseClass(typesOfCommands);
            ~commandBaseClass();
    };

    class formatSpecification : public commandBaseClass

    {
        public:
            int numberOfIntegerDigits;
            int numberOfDecimalDigits;

            formatSpecification(int, int);
            formatSpecification();
            ~formatSpecification();
    };

    class unitMode : public commandBaseClass
    {
        public:

            bool unitType;

            unitMode(bool);
            ~unitMode();
    };

    class apertureDefine : public commandBaseClass
    {
        public:

            int dCodeIdentifier;
            std::string apertureTemplate;
            std::vector<double> modfierList;

            apertureDefine(int, std::string, std::vector<double>);
            ~apertureDefine();
    };

    class setCurrentAperture : public commandBaseClass
    {
        public:

            int dCodeNumber;

            setCurrentAperture(int);
            ~setCurrentAperture();
    };

    class operation : public commandBaseClass
    {
        public:

            int operationType;
            double xCoordinate;
            double yCoordinate;

            operation(int, double, double);
            ~operation();
    };

    class loadPolarity : public commandBaseClass
    {
        public:

            bool polarity;

            loadPolarity(bool);
            ~loadPolarity();
    };

    class setInterpolationMode : public commandBaseClass
    {
        public:

            int interpolationMode;

            setInterpolationMode(int);
            ~setInterpolationMode();
    };

    class unknownCommand : public commandBaseClass
    {
        public:
            std::string commandString;

            unknownCommand(std::string);
            ~unknownCommand();
    };

}


#endif // GERBERCOMMANDS_H_INCLUDED
