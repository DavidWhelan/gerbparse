#ifndef GERBERFILE_H
#define GERBERFILE_H

#include <string>

#include "Aperture.h"
#include "GerberCommands.h"
#include "GerberGraphicsState.h"
#include "GerberSyntaxReader.h"
#include "Shape.h"
#include <memory>

namespace gerber
{
    class GerberFile
    {
        public:
            /** Default constructor */
            GerberFile();
            /** Default destructor */
            virtual ~GerberFile();

            std::vector<std::unique_ptr<aperturePrimitive>> apertureLibrary;
            std::vector<Shape> shapeList;
            graphicsState fileState;
            GerberSyntaxReader syntaxReader;

            Shape tempShapeOutline;

            void execute(std::string, bool);

            void clean();

        protected:

        private:
    };
}

#endif // GERBERFILE_H
