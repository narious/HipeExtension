#include "attr.h"


static void traverse_and_print(GumboNode* node, std::ostream& outputfile)
{
    if (node->type != GUMBO_NODE_ELEMENT) return;
    printf("%s", node->v.text);
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; i ++) {
        (GumboNode*)children[i]->v.text;
    }

}