#include <fstream>
#include <string>
#include "gumbo.h"

static void htmltohipe(std::string& htmlstring, std::ostream& outputfile)
{
    outputfile << htmlstring;

    GumboOutput* myoutput = gumbo_parse(htmlstring.c_str());

    // Opens up the file into a varaible

    // Sends it to htmlparser to pasrse and gets the parseTree

    // Open an output file

    // Loops through the parse tree 
        // for each tag convert it to appropriate hipe text

    // Close file and finish


    gumbo_destroy_output(&kGumboDefaultOptions, myoutput);

}