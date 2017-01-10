#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


enum resourceType {
	DATABASE, UNASSIGNED
};

public ref class ResourceNode : public System::Windows::Forms::TreeNode {

public:
	

	ResourceNode() : TreeNode{} {
		nodeType = UNASSIGNED;
	}

private:
	resourceType nodeType;

};
