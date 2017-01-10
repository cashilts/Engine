#pragma once
#include <string>
#include <vector>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

const std::vector<std::string> resourceStrings{ "Database","Unassigned","Level","Object" };
enum resourceType {
	DATABASE=-1, UNASSIGNED=0, LEVEL=1, OBJECT=2
};



public ref class ResourceNode : public System::Windows::Forms::TreeNode {

public:
	

	ResourceNode() : TreeNode{}, nodeType{ UNASSIGNED } {}
	ResourceNode(resourceType type) : TreeNode{}, nodeType{ type } {}

	resourceType getType() { return nodeType; }
	void setType(resourceType toSet) { nodeType = toSet; }
private:
	resourceType nodeType;

};
