#pragma once

namespace ManchesterManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace ManchesterEfems;
	using namespace ManchesterDataLoader;
	/// <summary>
	/// Сводка для LoadEfemForm
	/// </summary>
	public ref class LoadEfemForm : public System::Windows::Forms::Form
	{
	public:
		LoadEfemForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~LoadEfemForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	protected: 

	private: System::Windows::Forms::ToolStripMenuItem^  OpenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ExitToolStripMenuItem;

	private: System::Windows::Forms::TreeView^  treeView1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::OpenFileDialog^  openEfemsDialog;
	private: System::Windows::Forms::StatusStrip^  statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  StatusEfemsLabel;


	private: System::Windows::Forms::ToolStripStatusLabel^  StatusLoadEfemsText;

	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;


	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LoadEfemForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OpenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ExitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->openEfemsDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->StatusEfemsLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->StatusLoadEfemsText = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menuStrip1->SuspendLayout();
			this->statusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Highlight;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->loadToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(581, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->OpenToolStripMenuItem, 
				this->ExitToolStripMenuItem});
			this->fileToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Bold));
			this->fileToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->fileToolStripMenuItem->Text = L"Файл";
			// 
			// OpenToolStripMenuItem
			// 
			this->OpenToolStripMenuItem->BackColor = System::Drawing::SystemColors::Highlight;
			this->OpenToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->OpenToolStripMenuItem->Name = L"OpenToolStripMenuItem";
			this->OpenToolStripMenuItem->Size = System::Drawing::Size(129, 22);
			this->OpenToolStripMenuItem->Text = L"Открыть";
			this->OpenToolStripMenuItem->Click += gcnew System::EventHandler(this, &LoadEfemForm::OpenToolStripMenuItem_Click);
			// 
			// ExitToolStripMenuItem
			// 
			this->ExitToolStripMenuItem->BackColor = System::Drawing::SystemColors::Highlight;
			this->ExitToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->ExitToolStripMenuItem->Name = L"ExitToolStripMenuItem";
			this->ExitToolStripMenuItem->Size = System::Drawing::Size(129, 22);
			this->ExitToolStripMenuItem->Text = L"Выход";
			this->ExitToolStripMenuItem->Click += gcnew System::EventHandler(this, &LoadEfemForm::ExitToolStripMenuItem_Click);
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->Enabled = false;
			this->loadToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Bold));
			this->loadToolStripMenuItem->ForeColor = System::Drawing::Color::White;
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(82, 20);
			this->loadToolStripMenuItem->Text = L"Загрузить";
			this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &LoadEfemForm::loadToolStripMenuItem_Click);
			// 
			// treeView1
			// 
			this->treeView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->treeView1->Location = System::Drawing::Point(12, 27);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(188, 221);
			this->treeView1->TabIndex = 1;
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &LoadEfemForm::treeView1_AfterSelect);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->richTextBox1->Location = System::Drawing::Point(206, 27);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(363, 221);
			this->richTextBox1->TabIndex = 2;
			this->richTextBox1->Text = L"";
			// 
			// openEfemsDialog
			// 
			this->openEfemsDialog->FileName = L"openEfemsDialog";
			this->openEfemsDialog->Filter = L"TXT files (*.txt)|*.txt;";
			this->openEfemsDialog->RestoreDirectory = true;
			// 
			// statusStrip
			// 
			this->statusStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(202)), 
				static_cast<System::Int32>(static_cast<System::Byte>(65)));
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->StatusEfemsLabel, 
				this->StatusLoadEfemsText});
			this->statusStrip->Location = System::Drawing::Point(0, 270);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(581, 26);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 3;
			this->statusStrip->Text = L"statusStrip1";
			// 
			// StatusEfemsLabel
			// 
			this->StatusEfemsLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->StatusEfemsLabel->Name = L"StatusEfemsLabel";
			this->StatusEfemsLabel->Size = System::Drawing::Size(140, 21);
			this->StatusEfemsLabel->Text = L"Статус эфемерид:";
			// 
			// StatusLoadEfemsText
			// 
			this->StatusLoadEfemsText->BackColor = System::Drawing::Color::Red;
			this->StatusLoadEfemsText->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->StatusLoadEfemsText->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->StatusLoadEfemsText->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->StatusLoadEfemsText->ForeColor = System::Drawing::Color::White;
			this->StatusLoadEfemsText->Name = L"StatusLoadEfemsText";
			this->StatusLoadEfemsText->Size = System::Drawing::Size(426, 21);
			this->StatusLoadEfemsText->Spring = true;
			this->StatusLoadEfemsText->Text = L"не загружены";
			// 
			// LoadEfemForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(581, 296);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->treeView1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"LoadEfemForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Загрузка эфемерид";
			this->Load += gcnew System::EventHandler(this, &LoadEfemForm::LoadEfemForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		ParseEfemsLogsVPU ^_newEf;
		List<MarkLogs^> ^_list;
		int _currNode;
		//List<ClassContainer> _list;
	private: System::Void OpenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(openEfemsDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					 _list = _newEf->ConvertEfems(openEfemsDialog->FileName);
				 for each (MarkLogs^ line in _list)
				 {
					 treeView1->Nodes->Add(line->Name);
				 }
				 //openEfemsDialog.ShowDialog();
				 //_list = _ef.ConvertEfems(openEfemsDialog.FileName, "TestEFEMS.txt");
				 //foreach (var line in _list)
				 //{
				 //    treeView1.Nodes.Add(line.Name);
				 //}
			 }
	private: System::Void LoadEfemForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 _newEf = gcnew ParseEfemsLogsVPU();
				 _currNode = 0;
			 }
	private: System::Void treeView1_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
				 if(!loadToolStripMenuItem->Enabled)
					 loadToolStripMenuItem->Enabled = true;
				 _currNode = e->Node->Index;
				 richTextBox1->Clear();
				 for each (String^ line in _list[e->Node->Index]->LoadEfems)
				 {
					 richTextBox1->Text += line;
					 richTextBox1->Text += "\n";
				 }
			 }
	private: System::Void loadToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(_newEf->InitLoadedEfems(openEfemsDialog->FileName,_currNode)){
					 StatusLoadEfemsText->Text = "успешно загружены";
					 StatusLoadEfemsText->BackColor = Color::Green;
					 FormManager::newEfems = _newEf;
				 }
				 else{
					 StatusLoadEfemsText->Text = "не загружены";
					 StatusLoadEfemsText->BackColor = Color::Red;
				 }
			 }
	private: System::Void ExitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Application::Exit();
			 }
	};
}
