/*
openrpg - xml.h
Created on: Sept 1, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <fstream>

#include "core/xml.h"
#include "core/utils.h"

using namespace std;
using namespace ORPG;
using namespace ORPG::Core;

/**
 * TODO doc comments
 **/
XMLNode::XMLNode(XMLDocument* doc):document(doc) {
    //TODO construction
    parent = nullptr;
    firstChild = nullptr;
    lastChild = nullptr;
    prevSib = nullptr;
    nextSib = nullptr;

    lineNum = doc->currLine;

    value = "";

    data = nullptr;
}

/**
 * TODO doc comments
 **/
XMLNode::~XMLNode() {
    //TODO destruction
};

/**
 * @desc adds a node into the document as the last child
 * of this XMLNode. It will return the node argument if sucessful,
 * otherwise it will return 0. Calling this function is effectively
 * the same as calling insert_last_child()
 *
 * NOTE(incomingstick): the XMLNode will not be inserted if it is not
 * a member of this XMLDocument.
 *
 * @param XMLNode* node - a pointer to the XMLNode to be added
 *
 * @return XMLNode* - the node that was added, 0 if unsuccessful.
 **/
XMLNode* XMLNode::add_child(XMLNode* node) {
    if(last_child() == nullptr &&
       first_child() == nullptr &&
       node->document == document) {
        node->parent = this;
        firstChild = node;
        lastChild = node;
        return node;
    }

    return insert_last_child(node);
};

/**
 * @desc inserts a node into the document as the last child
 * of this XMLNode. It will return the node argument if sucessful,
 * otherwise it will return 0.
 *
 * NOTE(incomingstick): the XMLNode will not be inserted if it is not
 * a member of this XMLDocument.
 *
 * @param XMLNode* node - a pointer to the XMLNode to be added
 *
 * @return XMLNode* - the node that was added, 0 if unsuccessful.
 **/
XMLNode* XMLNode::insert_last_child(XMLNode* node) {
    return insert_after_node(last_child(), node);
}

/**
 * @desc inserts a node into the document as the last child
 * of this XMLNode. It will return the node argument if sucessful,
 * otherwise it will return 0.
 *
 * NOTE(incomingstick): the XMLNode will not be inserted if it is not
 * a member of this XMLDocument.
 *
 * @param XMLNode* node - a pointer to the XMLNode to be added
 *
 * @return XMLNode* - the node that was added, 0 if unsuccessful.
 **/
XMLNode* XMLNode::insert_first_child(XMLNode* node) {
    return insert_before_node(first_child(), node);
};

/**
 * @desc inserts a node into the document as a child of this node
 * and as a sibling following the given child XMLNode pointer after.
 * It will return the insert argument if sucessful, otherwise it will
 * return 0.
 *
 * NOTE(incomingstick): the XMLNode will not be inserted if it is not
 * a member of this XMLDocument.
 *
 * @param XMLNode* after - a pointer to the XMLNode to insert after
 * @param XMLNode* insert - a pointer to the XMLNode to be inserted
 *
 * @return XMLNode* - the node that was added, 0 if unsuccessful.
 **/
XMLNode* XMLNode::insert_after_node(XMLNode* after, XMLNode* insert) {
    if(insert == nullptr) return 0;
    if(after == nullptr) return 0;

    if(insert->get_document() != this->get_document()) return 0;
    if(after->get_document() != this->get_document()) return 0;

    if(after->nextSib == nullptr) {
        after->nextSib = insert;
        insert->prevSib = after;

        if(this->lastChild == after) {
            this->lastChild = insert;
        }
    } else {
        //TODO Query to ensure the node doesn't already exist
        //Create a temporary pointer to help with the insert
        XMLNode* tmp = after->nextSib;
        after->nextSib = insert;
        insert->nextSib = tmp;
        insert->prevSib = after;
        tmp->prevSib = insert;
    }

    insert->parent = this;

    return insert;
}

/**
 * @desc inserts a node into the document as a child of this node
 * and as a sibling proceeding the given child XMLNode pointer before.
 * It will return the insert argument if sucessful, otherwise it will
 * return 0.
 *
 * NOTE(incomingstick): the XMLNode will not be inserted if it is not
 * a member of this XMLDocument.
 *
 * @param XMLNode* before - a pointer to the XMLNode to insert before
 * @param XMLNode* insert - a pointer to the XMLNode to be inserted
 *
 * @return XMLNode* - the node that was added, 0 if unsuccessful.
 **/
XMLNode* XMLNode::insert_before_node(XMLNode* before, XMLNode* insert) {
    if(insert == nullptr) return 0;
    if(before == nullptr) return 0;

    if(insert->get_document() != this->get_document()) return 0;
    if(before->get_document() != this->get_document()) return 0;

    if(before->nextSib == nullptr) {
        before->nextSib = insert;
    } else {
        //TODO Query to ensure the node doesn't already exist
        //Create a temporary pointer to help with the insert
        XMLNode* tmp = before->prevSib;
        before->prevSib = insert;
        insert->prevSib = tmp;
    }

    return insert;
}

/**
 * @desc deletes all child nodes of this XMLNode
 **/
void XMLNode::delete_children() {
    //TODO implementation
}

/**
 * @desc deletes the given child node from this XMLNode
 *
 * @param XMLNode* node - the node to be deleted
 **/
void XMLNode::delete_child(XMLNode* node) {
    //TODO implementation
}

/**
 * TODO doc comments
 **/
XMLAttribute::XMLAttribute(std::string attrName, std::string val, int line):
    name(attrName), value(val), lineNum(line) {
    
    next = nullptr;
}

/**
 * TODO doc comments
 **/
XMLAttribute::~XMLAttribute() {
    //TODO destruciton
}

/**
 * TODO doc comments
 **/
XMLElement::XMLElement(XMLDocument* doc):XMLNode(doc) {
    //TODO construciton
    root = nullptr;
}

/**
 * TODO doc comments
 **/
XMLElement::~XMLElement() {
    //TODO destruciton
}

/**
 * @desc Adds the attribute to the list if it does not already exist. If
 * the attribute already exists, the value is over written.
 *
 * @param std::string name - the name of the attribute to add
 * @param std::string value - the value to set the attribute to
 * @param int line - the line number of this attribute
 **/
void XMLElement::add_attribute(std::string name, std::string value, int line) {
    if(root == nullptr) {
        root = new XMLAttribute(name, value, line);
    } else {
        XMLAttribute* curr = root;
        while(curr != nullptr) {
            if(curr->get_name() != name) {
                // we made it to the end of the attribute list and did not find
                // a match, so lets add it to the list
                if(curr->get_next() == nullptr) {
                    curr->next = new XMLAttribute(name, value, line);
                    break;
                }

                curr = curr->get_next();
            } else {
                // found it
                //TODO(incomingstick): update line number?
                curr->set_value(value);
                break;
            }
        }
    }
}

/**
 * TODO doc comments
 **/
XMLDocument::XMLDocument() {
    //TODO construciton
    root = nullptr;
}

/**
 * TODO doc comments
 **/
XMLDocument::~XMLDocument() {
    //TODO destruciton
}

/**
 * TODO doc comments
 **/
bool XMLDocument::load_file(string filename) {
    //TODO load file
    ifstream xml(filename);

    if(xml.is_open()) {
        string buffer;

        XMLElementClosingType closeType;
        XMLElement* currElement = root;

        currLine = 0;

        // begin parsing the XML document one line at a time
        while(Utils::safeGetline(xml, buffer)) {
            string tag = "";

            currLine++;

            // parse each individual character to catch special characters
            for(string::iterator ch = buffer.begin();
                ch != buffer.end();) {

                switch(*ch) {
                    // ignore whitespace
                    case ' ': {
                        ch++;
                    } break;

                    // tag and tagline opened
                    case '<': {
                        ch++;

                        if(currElement == nullptr) currElement = new XMLElement(this);

                        closeType = XMLElementClosingType::OPEN;

                        // getting the tag name here
                        while(ch != buffer.end() &&
                                *ch != ' ' &&
                                *ch != '>' &&
                                *ch != '/' &&
                                *ch != '=' &&
                                *ch != '?') {

                            tag += *ch++;
                        }

                        //FIXME if we are a "parent" here, we overwrite our name...
                        if(!tag.empty()) currElement->set_name(tag);
                    } break;

                    // tag closing
                    case '/': {
                        ch++;

                        // getting the tag name here
                        while(ch != buffer.end() &&
                                *ch != ' ' &&
                                *ch != '>' &&
                                *ch != '/' &&
                                *ch != '=' &&
                                *ch != '?') {

                            tag += *ch++;
                        }

                        //FIXME(incomingstick): this is a very rudimentary way of doing this
                        if(tag == ((XMLElement*)currElement->get_parent())->get_name()) {
                            closeType = XMLElementClosingType::CLOSING;
                        } else {
                            closeType = XMLElementClosingType::CLOSED;
                        }
                    } break;

                    // tagline closed
                    case '>': {
                        ch++;

                        /* ignore data between tags such as <tag stuff="foo bar">DATA</tag>
                          in that case DATA is added to the currElements data pointer */
                        /* TODO store this data */
                        string data = "";

                        while(ch != buffer.end() && *ch != '<') {
                            data += *ch++;
                        }

                        currElement->set_data((void*)data.c_str());

                        if(currElement != nullptr && closeType == XMLElementClosingType::OPEN) {
                            currElement->add_child(new XMLElement(this));

                            if(root == nullptr) root = currElement;

                            currElement = (XMLElement*)currElement->first_child();
                        } else if(closeType == XMLElementClosingType::CLOSING) {
                            currElement = (XMLElement*)currElement->get_parent();
                        } else if(closeType == XMLElementClosingType::CLOSED) {
                            currElement = (XMLElement*)currElement->get_parent();
                        }

                        tag = "";
                    } break;

                    // XML definition tag found
                    case '?': {
                        *ch++;

                        // getting the tag name here
                        while(ch != buffer.end() &&
                                *ch != ' ' &&
                                *ch != '>' &&
                                *ch != '/' &&
                                *ch != '=' &&
                                *ch != '?') {

                            tag += *ch++;
                        }

                        /* NOTE(incomingstick): tag == "xml" should be true here,
                            is this something we should enforce? Will it ever matter? */

                        if(!tag.empty()) currElement->set_name(tag);
                    } break;

                    // we can assume that if we reached  default, we are working with attributes
                    default: {
                        //first we get the attribute name
                        string attr = "";
                        
                        // getting the attribute name here
                        while(ch != buffer.end() &&
                                *ch != ' ' &&
                                *ch != '>' &&
                                *ch != '/' &&
                                *ch != '=' &&
                                *ch != '?') {
                        
                            attr += *ch++;
                        }

                        // this clears any whitespace until we find our first '"' 
                        while(*ch == ' ' ||
                              *ch == '=') {
                            ch++;
                        }

                        // this is a sanity check to ensure proper formatting
                        // if an incorrect format is found, we abort immediately.
                        // TODO handle this error reporting better
                        if(*ch == '/' || *ch == '>' || *ch == '<') {
                            cout << "found an unexpected " << *ch << " ";
                            cout << "aborting parse of " << attr << endl;
                            break;
                        } else if(*ch == '"' || *ch == APOSTROPHE) {
                            ch++;
                        }

                        // we are now parsing attribute data
                        string dat = "";

                        while(*ch != '"' && *ch != APOSTROPHE) {
                            dat += *ch++;
                        }

                        // check and make sure we pop off the final " or '
                        if(*ch == '"' || *ch == APOSTROPHE) {
                            ch++;
                        }

                        currElement->add_attribute(attr, dat, currLine);

                        break;
                    }
                }
            }
        }
    } else {
        return false;
    }

    return true;
}