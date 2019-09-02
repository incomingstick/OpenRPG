/*
openrpg - xml.h
Created on: Sept 1, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/

#include "core/xml.h"

using namespace std;
using namespace ORPG;
using namespace ORPG::Core;

/**
 * TODO doc comments
 **/
XMLNode::XMLNode(XMLDocument* doc):document(doc) {
    //TODO construction
}

XMLNode::~XMLNode() {
    //TODO destruction
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
    //TODO implementation
    return node;
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
    //TODO implementation
    return node;
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
    //TODO implementation
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
    //TODO implementation
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
XMLAttribute::XMLAttribute() {
    //TODO construciton
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
XMLElement::XMLElement(XMLDocument* doc) {
    //TODO construciton
}

/**
 * TODO doc comments
 **/
XMLElement::~XMLElement() {
    //TODO destruciton
}

/**
 * TODO doc comments
 **/
XMLDocument::XMLDocument() {
    //TODO construciton
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
    return true;
}