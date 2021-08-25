#include "attr.h"
#include <stdio.h>
#include "string.h"
#include "gumbo.h"

void mygumbo_write_attr(GumboNode *root, int fd) {
  traverse(root, fd);
}

/*
Traverses the tree and sends the attributes
*/
static void traverse(GumboNode* node, int fd)
{

  // special case the document node
  if (node->type == GUMBO_NODE_DOCUMENT) {
    traverse_attrs(node, fd);
  }
    
    const char * tagname = get_tag_name(node);

    // Iterators through current node and sends attributes 
    const GumboVector * attribs = &node->v.element.attributes;
    for (int i=0; i< attribs->length; ++i) {
      // NOTE: casting can fail at run time
        GumboAttribute* at = (GumboAttribute*)(attribs->data[i]); 
        hipe_build_attrs(at, "not loc supplied", fd);
    }

    // Traverses down the children
    traverse_attrs(node, fd);
}


static void traverse_attrs(GumboNode* node, int fd)
{

  const char * tagname = get_tag_name(node);

  GumboVector* children = &node->v.element.children;

  for (unsigned int i = 0; i < children->length; ++i) {
    GumboNode* child = (GumboNode*)(children->data[i]);
    if ((child->type == GUMBO_NODE_ELEMENT) || (child->type == GUMBO_NODE_TEMPLATE)) {
      traverse(child, fd);
    } 
    else if (child->type == GUMBO_NODE_WHITESPACE) {} 
    else if (child->type != GUMBO_NODE_COMMENT) {} 
    else if (child->type == GUMBO_NODE_TEXT) {}

  }
}

/*
Takes an attribute, determines the location and adds it to the file
hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, mantissa, 2, "colspan", "4");
*/
static void hipe_build_attrs(GumboAttribute* at, const char * hipeLoc, int fd)
{

  const char * attrname = at->name;
  const char * attrvalue = at->value;
  dprintf(fd, "\thipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, %s, 2, \"%s\", \"%s\");\n", 
  hipeLoc, attrname, attrvalue);

}

// From a node get the tagname
static const char * get_tag_name(GumboNode *node)
{
  const char * tagname;
  // work around lack of proper name for document node
  if (node->type == GUMBO_NODE_DOCUMENT) {
    tagname = "document";
  } else {
    tagname = gumbo_normalized_tagname(node->v.element.tag);
  }
  if (*tagname == 0) {
    tagname = handle_unknown_tag(&node->v.element.original_tag);
  }
  return tagname;
}

// Guesses the tag name
static const char * handle_unknown_tag(GumboStringPiece *text)
{
  char * tagname = "";
  if (text->data == NULL) {
    return tagname;
  }
  // work with copy GumboStringPiece to prevent asserts 
  // if try to read same unknown tag name more than once
  GumboStringPiece gsp = *text;
  gumbo_tag_from_original_text(&gsp);
  //tagname = std::string(gsp.data, gsp.length);
  return tagname; 
}
