
#include "gumbo.h"

struct parseTree 
{
    GumboOutput* tree;
};


static parseTree parse(char* htmlstring)
{
    return parseTree(gumbo_parse(htmlstring));
}

