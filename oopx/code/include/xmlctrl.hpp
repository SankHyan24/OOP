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
            int res = doc_->LoadFile(xmlPath_.c_str());
            if (res != 0)
            {
                std::cout << "load xml file failed" << std::endl;
                // return res;
            }
        }
        ~SerialCtrl()
        {
            delete doc_;
        }
        // int InsertXMLNode(const std::string &nodeName, const std::string &nodeValue)
        // {
        //     int res = doc_->LoadFile(xmlPath_.c_str());
        //     if (res != 0)
        //     {
        //         std::cout << "load xml file failed" << std::endl;
        //         return res;
        //     }
        //     XMLElement *root = doc_->RootElement();
        //     XMLElement *node = doc_->NewElement(nodeName.c_str());
        //     node->SetAttribute("value", nodeValue.c_str());
        //     node->InsertEndChild(doc_->NewText("??"));
        //     doc_->InsertEndChild(node);

        //     return doc_->SaveFile(xmlPath_.c_str());
        // }
        XMLElement *GetRoot()
        {
            return doc_->RootElement();
        }
        // 在root节点上插入一个子节点，并把子节点返回
        int InsertNode(const std::string &nodeName, const std::string &nodeValue, XMLElement *root, XMLElement *&child)
        {
            child = doc_->NewElement(nodeName.c_str());
            if (nodeValue != "")
                AddAttribute(child, "value", nodeValue);
            // child->SetAttribute("value", nodeValue.c_str());
            root->InsertEndChild(child);
            return 0;
        }
        void AddAttribute(XMLElement *node, const std::string &attributeName, const std::string &attributeValue)
        {
            node->SetAttribute(attributeName.c_str(), attributeValue.c_str());
        }

        XMLDocument *doc_;
        std::string xmlPath_;

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
    };
}