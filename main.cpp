#include <fstream>
#include <iostream>
#include <string>

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

        // Read html and css into a string 
        // see: https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
        std::string htmlstring( (std::istreambuf_iterator<char>(htmlFile)),
        std::istreambuf_iterator<char>());

        std::string cssstring((std::istreambuf_iterator<char>(cssFile)),
        std::istreambuf_iterator<char>());

        // pass in htmlfilename to html to hipe && output file
        htmltohipe(htmlstring, outputFile);

        // pass css file into html to hipe && output file
        csstohipe(cssstring, outputFile);

        return 0;
    }

    return 1;
}