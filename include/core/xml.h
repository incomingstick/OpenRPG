/*
openrpg - xml.h
Created on: Sept 1, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_XML_H_
#define SRC_XML_H_

/**
 * NOTE(incomingstick): Much of this was boilerplate pulled from Lee Thomason's tinyxml2 (1). I spent
 * many hours studying the header and cpp file and hand picked what I felt we would need for this
 * project. It has been my goal to write as much of this project by hand as possible, this just
 * helped me understand DOM parsing WAY better than I did before, and gave me a good starting point
 * for what we would need.
 * 
 * This is all being used to allow importing of Character Sheets generated via the Fifth Edition
 * Character Sheet app written by Walter Kammerer (2). The app exports a charcter as an XML file to the
 * users Google Drive. I would like you to be able to download that file, and import it into our Character
 * module. I plan to pull from Burak Ogan Mancarcı's import5eChar (3) written in R. I plan to attempt to
 * convert much of that project from R to C++ by hand.
 * 
 * Source 1: https://github.com/leethomason/tinyxml2
 * Source 2: https://play.google.com/store/apps/details?id=com.wgkammerer.testgui.basiccharactersheet.app
 * Source 3: https://github.com/oganm/import5eChar
 **/

#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN
#   include "core/win32.h"
#   include "exports/core_exports.h"
#else
#   define CORE_EXPORT
#endif

#include <string>

namespace ORPG {
    namespace Core {
        class XMLNode;
        class XMLAttribute;
        class XMLElement;
        class XMLDocument;

        /**
         * XMLNode is the base class for every object in the XML Document
         * Object Model (DOM), except XMLAttributes. Nodes have siblings,
         * a parent, and children which all can be navigated.
         * A node is always in an XMLDocument.
         *
	     * A XMLDocument allocates memory for all its Nodes.
         *
	     * When the XMLDocument gets deleted, all its Nodes
	     * will also be deleted.
         **/
        class XMLNode {
            // Give private member access to the XMLDocument
            friend class XMLDocument;

        protected:
            // a const pointer to the document containing this XMLNode
            XMLDocument* document;

            XMLNode* parent;        // a pointer to the parent node that contains this XMLNode as a child
            XMLNode* firstChild;    // a pointer to the first child node of this XMLNode
            XMLNode* lastChild;     // a pointer to the last child node of this XMLNode
            XMLNode* prevSib;       // a pointer to the sibling XMLNode proceeding this node
            XMLNode* nextSib;       // a pointer to the sibling XMLBode following this node

            int lineNum;
            std::string value;
            void* data;

        public:
            XMLNode() {};

            /**
             * TODO doc comments
             **/
            XMLNode(XMLDocument* doc);

            /**
             * TODO doc comments
             **/
            ~XMLNode();

            /**
             * @desc returns a pointer to the XMLDocument that contains this XMLNode
             *
             * @return const XMLDocument* - a pointer to the XMLDocument containing this
             * XMLNode
             **/
            XMLDocument* get_document() { return document; };

            /**
             * @desc returns a const pointer to the XMLDocument that contains this XMLNode
             *
             * @return const XMLDocument* - a const pointer to the XMLDocument containing this
             * XMLNode
             **/
            const XMLDocument* get_document() const { return document; };

            /**
             * @desc returns the line number of this node, if the document was loaded
             * from a file. The line number is -1 if it was not.
             *
             * @return const int - the line number of this node, -1 if it was not loaded
             * from a file
             **/
            const int get_line_number() { return lineNum; };

            /**
             * @desc returns a pointer to the parent XMLNode of this XMLNode.
             *
             * @return XMLNode* - a pointer to this XMLNode's parent XMLNode
             **/
            XMLNode* get_parent() { return parent; };

            /**
             * @desc function that returns true if this XMLNode has a child XMLNode
             *
             * @return bool - return true if child exists, false otherwise
             **/
            bool has_children() { return firstChild != nullptr ? true : false; };

            /**
             * @desc returns a pointer to the first child node of this XMLNode
             *
             * @return XMLNode* - a pointer to the first child node of this XMLNode
             **/
            XMLNode* first_child() { return firstChild; };

            /**
             * @desc returns a pointer to the last child node of this XMLNode
             *
             * @return XMLNode* - a pointer to the last child node of this XMLNode
             **/
            XMLNode* last_child() { return lastChild; };

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
            XMLNode* add_child(XMLNode* node);

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
            XMLNode* insert_last_child(XMLNode* node);

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
            XMLNode* insert_first_child(XMLNode* node);

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
            XMLNode* insert_after_node(XMLNode* after, XMLNode* insert);

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
            XMLNode* insert_before_node(XMLNode* before, XMLNode* insert);

            /**
             * @desc deletes all child nodes of this XMLNode
             **/
            void delete_children();

            /**
             * @desc deletes the given child node from this XMLNode
             *
             * @param XMLNode* node - the node to be deleted
             **/
            void delete_child(XMLNode* node);

            /**
             * @desc returns the string value contained within this XMLNode
             *
             * @return std::string - returns the stored string value
             **/
            std::string get_value() { return value; };

            /**
             * @desc sets the string value of this XMLNode to the given string newValue.
             *
             * @param std::string newValue - the string for the new value of this XMLNode
             **/
            void set_value(std::string newValue) { value = newValue; };

            /**
             * @desc returns a pointer to the data contained within this XMLNode
             *
             * @return void* - returns a pointer to the data
             **/
            void* get_data() { return data; };

            /**
             * @desc sets the data pointer of this XMLNode to the given pointer newData.
             *
             * @param void* newData - the pointer to the new data of this XMLNode
             **/
            void set_data(void* newData) { data = newData; };

            /**
             * @desc compares this XMLNode to the given XMLNode pointer. If
             * the given node is the same as this node, it returns true, otherwise
             * it returns false.
             *
             * @param XMLNode* node - the XMLNode to compare against
             *
             * @return bool - returns true if the nodes are the same, false otherwise
             **/
            bool equal_to(XMLNode* node);
        };

        /** An attribute is a name-value pair. Elements have an arbitrary
	     * number of attributes, each with a unique name.
	     * NOTE(incomingstick): Attributes are NOT XMLNodes. You may only query the
	     * next() attribute in a list.
         **/
        class XMLAttribute {
            // Give private member access to the XMLElement
            friend class XMLElement;

        private:
            std::string name;
            std::string value;
            int lineNum;

            XMLAttribute* next;
        public:
            /**
             * TODO doc comments
             **/
            XMLAttribute(std::string attrName, std::string val, int line);

            /**
             * TODO doc comments
             **/
            ~XMLAttribute();

            /**
             * TODO doc comments
             **/
            XMLAttribute* get_next() { return next; };

            /**
             * TODO doc comments
             **/
            const std::string get_name() { return name; };

            /**
             * TODO doc comments
             **/
            const std::string get_value() { return value; };

            /**
             * TODO doc comments
             **/
            void set_value(std::string val) { value = val; };

            /**
             * @desc returns the line number of this attribute, if the document was loaded
             * from a file. The line number is -1 if it was not.
             *
             * @return const int - the line number of this attribute, -1 if it was not loaded
             * from a file
             **/
            const int get_line_number() { return lineNum; };
        };

        /**
         * This enum allows for canonical checking of an XMLElements tag type:
         *      OPEN        i.e <foo>
         *      CLOSED      i.e <foo/>
         *      CLOSING     i.e </foo>
         **/
        enum XMLElementClosingType {
            OPEN,		// <foo>
            CLOSED,		// <foo/>
            CLOSING		// </foo>
        };

        /**
         * An XMLElement is a container class. It has a value, the element name,
	     * and can contain other elements, text, comments, etc.
	     * Elements also contain an arbitrary number of attributes.
         **/
        class XMLElement : public XMLNode {
            // Give private member access to these classes
            friend class XMLDocument;
            friend class XMLNode;

        private:
            /**
             * The attribute list is ordered; there is no 'last_attribute()'
             * because the list needs to be scanned for dupes before adding
             * a new attribute.
             **/
            XMLAttribute* root;

            /**
             * closingType allows for canonical checking of an XMLElements tag type:
             *      OPEN        i.e <foo>
             *      CLOSED      i.e <foo/>
             *      CLOSING     i.e </foo>
             **/
            XMLElementClosingType closingType;

        public:
            /**
             * TODO doc comments
             **/
            XMLElement(XMLDocument* doc);

            /**
             * TODO doc comments
             **/
            ~XMLElement();

            /* Get the name of an element (which is the Value() of the node.) */
            std::string get_name() { return get_value(); }

            /* Set the name of an element (which is the Value() of the node.) */
            void set_name(std::string name) { set_value(name.c_str()); };

            /**
             * @desc Adds the attribute to the list if it does not already exist. If
             * the attribute already exists, the value is over written.
             *
             * @param std::string name - the name of the attribute to add
             * @param std::string value - the value to set the attribute to
             * @param int line - the line number of this attribute
             **/
            void add_attribute(std::string name, std::string value, int line);

            /**
             * TODO doc comments
             **/
            const XMLElementClosingType closing_type() { return closingType; };
        };

        /**
         * An XMLDocument allows for direct access of a loaded XML file.
     	 * It can be saved, loaded, and printed to the screen.
	     * All Nodes are connected and allocated to a Document.
	     * If the Document is deleted, all its Nodes are also deleted.
         **/
        class CORE_EXPORT XMLDocument {
            // Give private member access to XMLNode
            friend class XMLNode;
        private:
            XMLElement* root;
            int currLine = 0;
        public:
            /**
             * TODO doc comments
             **/
            XMLDocument();

            /**
             * TODO doc comments
             **/
            ~XMLDocument();

            /**
             * TODO doc comments
             **/
            bool load_file(std::string filename);
        };
    }
}

#endif /* SRC_XML_H_ */