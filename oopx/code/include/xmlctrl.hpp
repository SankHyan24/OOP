#pragma once

#include <iostream>
#include <fstream>
#include <tinyxml2.h>
using namespace tinyxml2;
namespace XMLSerial
{
    class SerialCtrl
    {
    public:
        SerialCtrl(const std::string &xmlPath, const std::string &rootName, const std::string &version, const std::string &encoding) : xmlPath_(xmlPath)
        {
            doc_ = new XMLDocument();
            if (doc_->LoadFile(xmlPath_.c_str()) != 0)
                CreateXML(rootName, version, encoding);
            else
                std::cout << "load xml file failed" << std::endl;
        }
        ~SerialCtrl() { delete doc_; }
        // Get
        XMLElement *GetRoot() { return doc_->RootElement(); }
        XMLDocument *GetDoc() { return doc_; }
        std::string GetXMLPath() { return xmlPath_; }
        // XML control
        int InsertNode(const std::string &nodeName, const std::string &nodeValue, XMLElement *root, XMLElement *&child)
        {
            child = doc_->NewElement(nodeName.c_str());
            if (nodeValue != "")
                AddAttribute(child, "value", nodeValue);
            // InsertText(child, nodeValue);
            root->InsertEndChild(child);
            return 0;
        }
        void AddAttribute(XMLElement *node, const std::string &attributeName, const std::string &attributeValue)
        {
            node->SetAttribute(attributeName.c_str(), attributeValue.c_str());
        }
        void InsertText(XMLElement *node, const std::string &textContent)
        {
            node->InsertEndChild(doc_->NewText(textContent.c_str()));
        }

    private:
        int CreateXML(const std::string &rootName, const std::string &version, const std::string &encoding)
        {
            std::string declaration = "<?xml version=\"" + version + "\" encoding=\"" + encoding + "\" standalone=\"no\"?>";
            doc_->Parse(declaration.c_str());
            XMLElement *root = doc_->NewElement(rootName.c_str());
            doc_->InsertEndChild(root);
            return doc_->SaveFile(xmlPath_.c_str());
        }

        XMLElement *root_;
        XMLElement *node_;
        XMLDocument *doc_;
        std::string xmlPath_;
    };
}