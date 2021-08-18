

/*
 * Set all HTML tag attributes in a HTML file with hipe
 * client instructions.
 */
#ifndef ATTR_H
#define ATTR_H

#include "attr.h"
#include "gumbo.h"
#include "iostream"
#include "string"

// Forward declarations
static std::string traverse_attrs(GumboNode* node, int lvl, const std::string indent_chars);
static std::string hipe_build_attrs(GumboAttribute* at);
static std::string get_tag_name(GumboNode *node);
static std::string handle_unknown_tag(GumboStringPiece *text);

static std::string traverse(GumboNode* node, int lvl, const std::string indent_chars)
{

  // special case the document node
  if (node->type == GUMBO_NODE_DOCUMENT) {
    std::string results = "";
    results.append(traverse_attrs(node,lvl+1,indent_chars));
    return results;
  }
    
    std::string atts               = "";
    std::string tagname            = get_tag_name(node);
    std::string closeTag           = "";
    char c                         = indent_chars.at(0);
    int  n                         = indent_chars.length();

    // Create the attributes of this node
    // m: attrribute build attr string handled here
    const GumboVector * attribs = &node->v.element.attributes;
    for (int i=0; i< attribs->length; ++i) {
        GumboAttribute* at = static_cast<GumboAttribute*>(attribs->data[i]);
        atts.append(hipe_build_attrs(at));
    }

  // Recurse into the contents
     // m: incrasing indentation
    std::string indent_space = std::string((lvl-1)*n,c);

    // prettyprint your contents m: goes into and branches
    std::string contents = traverse_attrs(node, lvl+1, indent_chars);

    closeTag = "</" + tagname + ">";

        // build results
    std::string results;
    results.append(indent_space +"<"+tagname+atts+">");
    results.append("\n" + contents + "\n" + indent_space + closeTag + "\n");
    return results;
}

// traverse: does the branching step then calls the traverse
static std::string traverse_attrs(GumboNode* node, int lvl, const std::string indent_chars)
{

  std::string contents        = "";
  std::string tagname         = get_tag_name(node);
    // m:loops through the children
  GumboVector* children = &node->v.element.children;

  for (unsigned int i = 0; i < children->length; ++i) {
    GumboNode* child = static_cast<GumboNode*> (children->data[i]);
    if ((child->type == GUMBO_NODE_ELEMENT) || (child->type == GUMBO_NODE_TEMPLATE)) {
      std::string childname = get_tag_name(child);
      std::string val = traverse(child, lvl, indent_chars);
        // m" undecided whether to append the childname
      contents.append(val);
    
    } // m: just do nothng in these cases
    else if (child->type == GUMBO_NODE_WHITESPACE) {} 
    else if (child->type != GUMBO_NODE_COMMENT) {} 
    else if (child->type == GUMBO_NODE_TEXT) {}

  }

  return contents;
}


static std::string hipe_build_attrs(GumboAttribute* at)
{
  std::string atts = "";
  atts.append(" ");
  atts.append(at->name);

  // how do we want to handle attributes with empty values
  // <input type="checkbox" checked />  or <input type="checkbox" checked="" /> 

  if ( (!std::string(at->value).empty())   || 
       (at->original_value.data[0] == '"') || 
       (at->original_value.data[0] == '\'') ) {

    // determine original quote character used if it exists
    char quote = at->original_value.data[0];
    std::string qs = "";
    if (quote == '\'') qs = std::string("'");
    if (quote == '"') qs = std::string("\"");

    atts.append("=");
    atts.append(qs);
    atts.append(at->value);
    atts.append(qs);
  }
  return atts;
}

// From a node get the tagname
static std::string get_tag_name(GumboNode *node)
{
  std::string tagname;
  // work around lack of proper name for document node
  if (node->type == GUMBO_NODE_DOCUMENT) {
    tagname = "document";
  } else {
    tagname = gumbo_normalized_tagname(node->v.element.tag);
  }
  if (tagname.empty()) {
    tagname = handle_unknown_tag(&node->v.element.original_tag);
  }
  return tagname;
}

// Guesses the tag name
static std::string handle_unknown_tag(GumboStringPiece *text)
{
  std::string tagname = "";
  if (text->data == NULL) {
    return tagname;
  }
  // work with copy GumboStringPiece to prevent asserts 
  // if try to read same unknown tag name more than once
  GumboStringPiece gsp = *text;
  gumbo_tag_from_original_text(&gsp);
  tagname = std::string(gsp.data, gsp.length);
  return tagname; 
}


#endif
