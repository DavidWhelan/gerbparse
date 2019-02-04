#ifndef GERBERSYNTAXREADER_H
#define GERBERSYNTAXREADER_H

#include <string>
#include <regex>
#include "Aperture.h"
#include "GerberCommands.h"
#include "GerberGraphicsState.h"

namespace gerber
{

class GerberSyntaxReader
{
    public:
        /** Default constructor */
        GerberSyntaxReader();
        GerberSyntaxReader(graphicsState *pointerToGraphicsState);

        gerber::graphicsState *graphicsStateForParsing;

        commandBaseClass parseCommand(std::string);

        std::regex FSCommand;
        std::regex MOCommand;
        std::regex ADDCommand;
        std::regex setAperture;
        std::regex DOperation;
        std::regex LPCommand;
        std::regex setInterpolation;

        /** Default destructor */
        virtual ~GerberSyntaxReader();

    protected:

    private:
};
}
#endif // GERBERSYNTAXREADER_H
