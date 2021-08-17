#include <fstream>
#include <string>
#include "gumbo.h"

static void traverse_and_print(GumboNode* node, std::ostream& outputfile)
{
    if (node->type != GUMBO_NODE_ELEMENT) return;

}


static void htmltohipe(std::string& htmlstring, std::ostream& outputfile)
{
    outputfile << htmlstring;

    GumboOutput* gumbo_output = gumbo_parse(htmlstring.c_str());

    
    // An array relating to the DOM's document
    GumboNode* gumbo_document = gumbo_output->document;


    // Open an output file

    // Loops through the parse tree 
        // for each tag convert it to appropriate hipe text

    // Close file and finish


    gumbo_destroy_output(&kGumboDefaultOptions, gumbo_output);

}

