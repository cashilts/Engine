#pragma once
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "ResourceNode.h"
#include "stdafx.h"
#include <msclr/marshal_cppstd.h>

using namespace msclr::interop;

class ResourceFile{
	 static rapidxml::xml_document<>* doc;
public:
	static void treeToXmlDoc(TreeView^ tree, std::string filename) {
		rapidxml::xml_node<>* head = constructNode(dynamic_cast<ResourceNode^>(tree->TopNode));
		doc->append_node(head);
		std::ofstream outputFile;
		outputFile.open(filename);
		outputFile << *doc;
		outputFile.close();
	}

	static ResourceNode^ xmlToTree(std::string filename) {
		rapidxml::file<> xml{ filename.c_str() };
		doc->parse<0>(xml.data());
		ResourceNode^ head = constructTree(doc->first_node());
		return head;
	}
private:

	static ResourceNode^ constructTree(rapidxml::xml_node<> *node) {
		ResourceNode^ temp = gcnew ResourceNode{};
		temp->Text = gcnew System::String{ node->first_attribute()->value() };
		node = node->first_node();
		while (true) {
			if (node && node->first_node()) {
				temp->Nodes->Add(constructTree(node));
			}
			else {
				break;
			}
			node = node->next_sibling();
		}
		return temp;
	}

	static rapidxml::xml_node<>* constructNode(ResourceNode^ base) {
		char* nodeName = doc->allocate_string(resourceStrings[base->getType() + 1].c_str());
		char* nodeValue = doc->allocate_string("none");

		rapidxml::xml_node<>* temp = doc->allocate_node(rapidxml::node_element, nodeName, nodeValue);
			char* attribName = doc->allocate_string(marshal_as<std::string>(base->Text).c_str());
			char* attribValue = doc->allocate_string("Name");
		rapidxml::xml_attribute<>* resourceKind = doc->allocate_attribute(attribValue, attribName);
		temp->append_attribute(resourceKind);
		TreeNodeCollection^ subNodes = base->Nodes;
		int sizeOfSub = subNodes->Count;
		for (int i = 0; i < sizeOfSub; i++) {
			rapidxml::xml_node<>* subTemp = constructNode(dynamic_cast<ResourceNode^>(subNodes[i]));
			temp->append_node(subTemp);
		}
		return temp;
	}
};