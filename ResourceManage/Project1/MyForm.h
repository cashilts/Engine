#pragma once
#include "rapidxml.hpp"
#include "ResourceNode.h"
#include "ResourceFile.h"
#include <iostream>
namespace Project1 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TreeView^  treeView1;
	 System::Windows::Forms::MenuStrip^  menuStrip1;
	 System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	 System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	 System::ComponentModel::Container ^components;
	 System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
			 ResourceNode ^currentlySelected;
			 TreeNode ^ dragged;
			 TreeNode ^ hovered;
	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Button^  dependancyAdd;
			 bool dragging = false;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->dependancyAdd = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// treeView1
			// 
			this->treeView1->Location = System::Drawing::Point(12, 41);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(121, 508);
			this->treeView1->TabIndex = 0;
			this->treeView1->ItemDrag += gcnew System::Windows::Forms::ItemDragEventHandler(this, &MyForm::treeView1_ItemDrag);
			this->treeView1->NodeMouseHover += gcnew System::Windows::Forms::TreeNodeMouseHoverEventHandler(this, &MyForm::treeView1_NodeMouseHover);
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MyForm::treeView1_AfterSelect_1);
			this->treeView1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::treeView1_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1007, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->newToolStripMenuItem,
					this->loadToolStripMenuItem, this->saveAsToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::newToolStripMenuItem_Click);
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->loadToolStripMenuItem->Text = L"Load";
			this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveAsToolStripMenuItem_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(162, 526);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"New Resource";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"None", L"Level", L"Object" });
			this->comboBox1->Location = System::Drawing::Point(258, 94);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 3;
			this->comboBox1->Visible = false;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(159, 97);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Resource type";
			this->label1->Visible = false;
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"xml";
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveFileDialog1_FileOk);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(151, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Database Name";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(258, 41);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(121, 20);
			this->textBox1->TabIndex = 6;
			this->textBox1->Text = L"New Database";
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox1_KeyDown);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(556, 41);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(381, 95);
			this->listBox1->TabIndex = 7;
			this->listBox1->Visible = false;
			// 
			// dependancyAdd
			// 
			this->dependancyAdd->Location = System::Drawing::Point(556, 158);
			this->dependancyAdd->Name = L"dependancyAdd";
			this->dependancyAdd->Size = System::Drawing::Size(141, 23);
			this->dependancyAdd->TabIndex = 8;
			this->dependancyAdd->Text = L"Add New Dependancy";
			this->dependancyAdd->UseVisualStyleBackColor = true;
			this->dependancyAdd->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1007, 597);
			this->Controls->Add(this->dependancyAdd);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->treeView1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		TreeNode^  treeNode2 = (gcnew ResourceNode{ resourceType::DATABASE });
		treeNode2->Name = L"";
		treeNode2->Text = L"New Document";
		this->treeView1->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode2 });
	}
	private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
		
	}
	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
	}
	private: System::Void treeView1_AfterSelect_1(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
		currentlySelected = dynamic_cast<ResourceNode^>(e->Node);
		if (currentlySelected->getType() >= resourceType::UNASSIGNED) {
			this->label1->Visible = true;
			this->comboBox1->Visible = true;
			this->listBox1->Visible = true;
			this->dependancyAdd->Visible = true;
			this->label2->Text = "Resource Name";
		}
		else {
			this->label1->Visible = false;
			this->comboBox1->Visible = false;
			this->listBox1->Visible = false;
			this->dependancyAdd->Visible = false;
			this->label2->Text = "Database Name";
		}
		this->textBox1->Text = currentlySelected->Text;
		this->comboBox1->SelectedIndex = currentlySelected->getType();
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		ResourceNode^ toAdd = gcnew ResourceNode{};
		toAdd->Text = "New Resource";
		currentlySelected->Nodes->Add(toAdd);
	}
	
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		currentlySelected->setType((resourceType)this->comboBox1->SelectedIndex);
	}
	private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		saveFileDialog1->ShowDialog();
	}
	private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		std::string url = marshal_as<std::string>(saveFileDialog1->FileName);
		ResourceFile::treeToXmlDoc(this->treeView1, url);
	}
	
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		
	}
	private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if(e->KeyCode == System::Windows::Forms::Keys::Enter) currentlySelected->Text = textBox1->Text;
	}
	private: System::Void treeView1_ItemDrag(System::Object^  sender, System::Windows::Forms::ItemDragEventArgs^  e) {
		dragged = reinterpret_cast<TreeNode^>(e->Item);
		dragging = true;
		hovered = dragged;
	}
	private: System::Void treeView1_NodeMouseHover(System::Object^  sender, System::Windows::Forms::TreeNodeMouseHoverEventArgs^  e) {
		if (dragging) {
			hovered = e->Node;
		}
	}
	private: System::Void treeView1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (dragging) {
			dragging = false;
			if (hovered != dragged) {
				if (hovered->Level > dragged->Level) {
					TreeNode^ levelCheck = hovered->Parent;
					while (true) {
						if (levelCheck->Level == dragged->Level) {
							if (dragged == levelCheck) return;
							break;
						}
						levelCheck = levelCheck->Parent;
					}
				}
				dragged->Parent->Nodes->Remove(dragged);
				hovered->Nodes->Add(dragged);
				
			}
		}
	}
	private: System::Void loadToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog1->ShowDialog();
	}
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		ResourceNode^ newHead = ResourceFile::xmlToTree(marshal_as<std::string>(this->openFileDialog1->FileName));
		this->treeView1->Nodes->Clear();
		this->treeView1->Nodes->Add(newHead);
	}
};
}
