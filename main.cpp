#include <fstream>
#include <iostream>
#include "HtmlToHipe/src/HtmlToHipe.h"
#include "CssToHipe/src/CssToHipe.h"
// Expects a filename to be passed into this function
int main(int argc, char* arcv[])
{
    if (argc > 1)
    {
        char* htmlfilename = arcv[1];
        char* cssfilename = arcv[2];

        // create output file
        std::ofstream outputFile("output.txt");

        // read htmlfile & css
        std::ifstream htmlFile(htmlfilename);
        std::ifstream cssFile(cssfilename);

        // pass in htmlfilename to html to hipe && output file
        
        // pass css file into html to hipe && output file
        
        return 0;
    }

    return 1;
}