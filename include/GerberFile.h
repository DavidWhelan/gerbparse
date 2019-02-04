#ifndef GERBERFILE_H
#define GERBERFILE_H

#include <string>

#include "Aperture.h"
#include "GerberCommands.h"
#include "GerberGraphicsState.h"
#include "GerberSyntaxReader.h"
#include "Shape.h"

namespace gerber
{
    class GerberFile
    {
        public:
            /** Default constructor */
            GerberFile(std::string);
            /** Default destructor */
            virtual ~GerberFile();

            std::vector<aperturePrimitive> apertureLibrary;
            std::vector<Shape> shapeList;
            std::string pathToFile;
            graphicsState fileState;
            GerberSyntaxReader syntaxReader;

            void execute();

        protected:

        private:
    };
}

#endif // GERBERFILE_H
