#include "GerberFile.h"

namespace gerber
{
    GerberFile::GerberFile(std::string filePath)
    {
        fileState = graphicsState(4, 6, false, 0, 0, 10, false, 1);
        syntaxReader = GerberSyntaxReader(&fileState);
        pathToFile = filePath;
    }

    GerberFile::~GerberFile()
    {
        //dtor
    }

    void GerberFile::execute()
    {

    }

}
