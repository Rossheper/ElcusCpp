#pragma once
#include "Description.h"
//#include "FormManager.h"

namespace ManchesterManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;
	using namespace System::Threading;
	using namespace System::Linq;
	using namespace System::Data::Linq;
	using namespace System::Xml;
	using namespace System::Xml::Linq;
	using namespace ManchesterTask;
	using namespace ManchesterDataLoader;
	using namespace ManchesterLogging;
	using namespace ManchesterEnumerableMethods;

	//using namespace ManchesterFormManager;
	/// <summary>
	/// Сводка для PzForm
	/// </summary>
	private enum class FlagsComboBoxes {
		Pg = 0,
		FTM = 1, 
		Edited = 2, 
		NotEdited = 3
	};

	public ref class PzForm : public System::Windows::Forms::Form {
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  PZFiledsNotEdited;
	public:
		PzForm(void)
		{
			InitializeComponent();
			this->KeyPreview = true;
			this->EditedPZGrid->BorderStyle = BorderStyle::None;
			this->PM24->BorderStyle = BorderStyle::None;
			this->PM25->BorderStyle = BorderStyle::None;
			this->NotEditedPZGrid->BorderStyle = BorderStyle::None;
			collectData = gcnew CollectDataPz();
			pz = gcnew PZ();
			//
			//TODO: добавьте код конструктора
			//
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~PzForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::Label^  PL24;
	private: System::Windows::Forms::Label^  PL25;
	private: System::Windows::Forms::DataGridView^  PM24;
	private: System::Windows::Forms::DataGridView^  PM25;
	private: System::Windows::Forms::DataGridView^  NotEditedPZGrid;
	private: System::Windows::Forms::Button^  ButtonCalcPZ;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  OK_button;
	private: System::Windows::Forms::DataGridView^  EditedPZGrid;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  описаниеToolStripMenuItem;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  PZFieldsEdited;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
		PZ ^ pz;
		Logging ^logs;
		XDocument ^xmlDoc;
		ResXResourceReader ^_resDescription;
		CollectDataPz ^ collectData;
		//System::Collections::Generic::IEnumerable<DictionaryEntry>^ _resourceEnumerator;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle8 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle9 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle11 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle10 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle12 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle13 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PzForm::typeid));
			this->PL24 = (gcnew System::Windows::Forms::Label());
			this->PL25 = (gcnew System::Windows::Forms::Label());
			this->PM24 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PM25 = (gcnew System::Windows::Forms::DataGridView());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->NotEditedPZGrid = (gcnew System::Windows::Forms::DataGridView());
			this->PZFiledsNotEdited = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ButtonCalcPZ = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->OK_button = (gcnew System::Windows::Forms::Button());
			this->EditedPZGrid = (gcnew System::Windows::Forms::DataGridView());
			this->PZFieldsEdited = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->описаниеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PM24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PM25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NotEditedPZGrid))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EditedPZGrid))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// PL24
			// 
			this->PL24->AutoSize = true;
			this->PL24->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PL24->Location = System::Drawing::Point(511, 31);
			this->PL24->Name = L"PL24";
			this->PL24->Size = System::Drawing::Size(41, 19);
			this->PL24->TabIndex = 23;
			this->PL24->Text = L"П24";
			// 
			// PL25
			// 
			this->PL25->AutoSize = true;
			this->PL25->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PL25->Location = System::Drawing::Point(511, 154);
			this->PL25->Name = L"PL25";
			this->PL25->Size = System::Drawing::Size(41, 19);
			this->PL25->TabIndex = 24;
			this->PL25->Text = L"П25";
			// 
			// PM24
			// 
			this->PM24->AllowUserToAddRows = false;
			this->PM24->AllowUserToDeleteRows = false;
			this->PM24->AllowUserToResizeColumns = false;
			this->PM24->AllowUserToResizeRows = false;
			this->PM24->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->PM24->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->PM24->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->PM24->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->PM24->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Column1, this->Column2,
					this->Column3
			});
			this->PM24->GridColor = System::Drawing::SystemColors::ButtonFace;
			this->PM24->Location = System::Drawing::Point(398, 53);
			this->PM24->Name = L"PM24";
			this->PM24->ReadOnly = true;
			this->PM24->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->PM24->RowHeadersWidth = 20;
			this->PM24->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->PM24->Size = System::Drawing::Size(270, 95);
			this->PM24->TabIndex = 60;
			// 
			// Column1
			// 
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->Column1->DefaultCellStyle = dataGridViewCellStyle2;
			this->Column1->HeaderText = L"1";
			this->Column1->MaxInputLength = 9;
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column1->Width = 80;
			// 
			// Column2
			// 
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->Column2->DefaultCellStyle = dataGridViewCellStyle3;
			this->Column2->HeaderText = L"2";
			this->Column2->MaxInputLength = 9;
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column2->Width = 80;
			// 
			// Column3
			// 
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->Column3->DefaultCellStyle = dataGridViewCellStyle4;
			this->Column3->HeaderText = L"3";
			this->Column3->MaxInputLength = 9;
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column3->Width = 80;
			// 
			// PM25
			// 
			this->PM25->AllowUserToAddRows = false;
			this->PM25->AllowUserToDeleteRows = false;
			this->PM25->AllowUserToResizeColumns = false;
			this->PM25->AllowUserToResizeRows = false;
			this->PM25->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->PM25->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle5->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->PM25->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle5;
			this->PM25->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->PM25->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Column4, this->Column5,
					this->Column6
			});
			this->PM25->GridColor = System::Drawing::SystemColors::ButtonFace;
			this->PM25->Location = System::Drawing::Point(398, 176);
			this->PM25->Name = L"PM25";
			this->PM25->ReadOnly = true;
			this->PM25->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->PM25->RowHeadersWidth = 20;
			this->PM25->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->PM25->Size = System::Drawing::Size(270, 95);
			this->PM25->TabIndex = 61;
			// 
			// Column4
			// 
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->Column4->DefaultCellStyle = dataGridViewCellStyle6;
			this->Column4->HeaderText = L"1";
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			this->Column4->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column4->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column4->Width = 80;
			// 
			// Column5
			// 
			dataGridViewCellStyle7->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->Column5->DefaultCellStyle = dataGridViewCellStyle7;
			this->Column5->HeaderText = L"2";
			this->Column5->Name = L"Column5";
			this->Column5->ReadOnly = true;
			this->Column5->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column5->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column5->Width = 80;
			// 
			// Column6
			// 
			dataGridViewCellStyle8->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->Column6->DefaultCellStyle = dataGridViewCellStyle8;
			this->Column6->HeaderText = L"3";
			this->Column6->Name = L"Column6";
			this->Column6->ReadOnly = true;
			this->Column6->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Column6->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column6->Width = 80;
			// 
			// NotEditedPZGrid
			// 
			this->NotEditedPZGrid->AllowUserToAddRows = false;
			this->NotEditedPZGrid->AllowUserToDeleteRows = false;
			this->NotEditedPZGrid->AllowUserToResizeColumns = false;
			this->NotEditedPZGrid->AllowUserToResizeRows = false;
			this->NotEditedPZGrid->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->NotEditedPZGrid->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			dataGridViewCellStyle9->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle9->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle9->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle9->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle9->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle9->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle9->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->NotEditedPZGrid->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle9;
			this->NotEditedPZGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->NotEditedPZGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->PZFiledsNotEdited });
			this->NotEditedPZGrid->GridColor = System::Drawing::SystemColors::ButtonFace;
			this->NotEditedPZGrid->Location = System::Drawing::Point(12, 54);
			this->NotEditedPZGrid->Name = L"NotEditedPZGrid";
			this->NotEditedPZGrid->ReadOnly = true;
			this->NotEditedPZGrid->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle11->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle11->BackColor = System::Drawing::Color::Coral;
			dataGridViewCellStyle11->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle11->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle11->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle11->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle11->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->NotEditedPZGrid->RowHeadersDefaultCellStyle = dataGridViewCellStyle11;
			this->NotEditedPZGrid->RowHeadersWidth = 80;
			this->NotEditedPZGrid->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->NotEditedPZGrid->Size = System::Drawing::Size(187, 432);
			this->NotEditedPZGrid->TabIndex = 62;
			// 
			// PZFiledsNotEdited
			// 
			dataGridViewCellStyle10->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			this->PZFiledsNotEdited->DefaultCellStyle = dataGridViewCellStyle10;
			this->PZFiledsNotEdited->HeaderText = L"Значение";
			this->PZFiledsNotEdited->Name = L"PZFiledsNotEdited";
			this->PZFiledsNotEdited->ReadOnly = true;
			this->PZFiledsNotEdited->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->PZFiledsNotEdited->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// ButtonCalcPZ
			// 
			this->ButtonCalcPZ->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->ButtonCalcPZ->FlatAppearance->BorderSize = 0;
			this->ButtonCalcPZ->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->ButtonCalcPZ->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ButtonCalcPZ->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Bold));
			this->ButtonCalcPZ->ForeColor = System::Drawing::SystemColors::Window;
			this->ButtonCalcPZ->Location = System::Drawing::Point(398, 277);
			this->ButtonCalcPZ->Name = L"ButtonCalcPZ";
			this->ButtonCalcPZ->Size = System::Drawing::Size(123, 46);
			this->ButtonCalcPZ->TabIndex = 63;
			this->ButtonCalcPZ->Text = L"Рассчитать полетное задание";
			this->ButtonCalcPZ->UseVisualStyleBackColor = false;
			this->ButtonCalcPZ->Click += gcnew System::EventHandler(this, &PzForm::Calc_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label1->Location = System::Drawing::Point(140, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(132, 19);
			this->label1->TabIndex = 64;
			this->label1->Text = L"Параметры ПЗ";
			// 
			// OK_button
			// 
			this->OK_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->OK_button->Enabled = false;
			this->OK_button->FlatAppearance->BorderSize = 0;
			this->OK_button->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(79)),
				static_cast<System::Int32>(static_cast<System::Byte>(141)), static_cast<System::Int32>(static_cast<System::Byte>(244)));
			this->OK_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->OK_button->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OK_button->ForeColor = System::Drawing::SystemColors::Window;
			this->OK_button->Location = System::Drawing::Point(547, 277);
			this->OK_button->Name = L"OK_button";
			this->OK_button->Size = System::Drawing::Size(121, 46);
			this->OK_button->TabIndex = 65;
			this->OK_button->Text = L"ОК";
			this->OK_button->UseVisualStyleBackColor = false;
			this->OK_button->Click += gcnew System::EventHandler(this, &PzForm::OK_button_Click);
			// 
			// EditedPZGrid
			// 
			this->EditedPZGrid->AllowUserToAddRows = false;
			this->EditedPZGrid->AllowUserToDeleteRows = false;
			this->EditedPZGrid->AllowUserToResizeColumns = false;
			this->EditedPZGrid->AllowUserToResizeRows = false;
			this->EditedPZGrid->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->EditedPZGrid->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			dataGridViewCellStyle12->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle12->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle12->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle12->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle12->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle12->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle12->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->EditedPZGrid->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle12;
			this->EditedPZGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->EditedPZGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) { this->PZFieldsEdited });
			this->EditedPZGrid->GridColor = System::Drawing::SystemColors::ButtonFace;
			this->EditedPZGrid->Location = System::Drawing::Point(205, 54);
			this->EditedPZGrid->Name = L"EditedPZGrid";
			this->EditedPZGrid->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->EditedPZGrid->RowHeadersWidth = 80;
			this->EditedPZGrid->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->EditedPZGrid->Size = System::Drawing::Size(187, 432);
			this->EditedPZGrid->TabIndex = 66;
			this->EditedPZGrid->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &PzForm::EditedPZGrid_CellEndEdit);
			this->EditedPZGrid->CellValidating += gcnew System::Windows::Forms::DataGridViewCellValidatingEventHandler(this, &PzForm::EditedPZGrid_CellValidating);
			this->EditedPZGrid->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &PzForm::EditedPZGrid_CellValueChanged);
			// 
			// PZFieldsEdited
			// 
			dataGridViewCellStyle13->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			this->PZFieldsEdited->DefaultCellStyle = dataGridViewCellStyle13;
			this->PZFieldsEdited->HeaderText = L"Значение";
			this->PZFieldsEdited->Name = L"PZFieldsEdited";
			this->PZFieldsEdited->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->PZFieldsEdited->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Highlight;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->описаниеToolStripMenuItem });
			this->menuStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->menuStrip1->Size = System::Drawing::Size(681, 24);
			this->menuStrip1->TabIndex = 67;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// описаниеToolStripMenuItem
			// 
			this->описаниеToolStripMenuItem->BackColor = System::Drawing::SystemColors::Highlight;
			this->описаниеToolStripMenuItem->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->описаниеToolStripMenuItem->Name = L"описаниеToolStripMenuItem";
			this->описаниеToolStripMenuItem->Size = System::Drawing::Size(74, 20);
			this->описаниеToolStripMenuItem->Text = L"Описание";
			this->описаниеToolStripMenuItem->Click += gcnew System::EventHandler(this, &PzForm::descriptionToolStripMenuItem_Click);
			// 
			// PzForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(681, 498);
			this->Controls->Add(this->EditedPZGrid);
			this->Controls->Add(this->OK_button);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ButtonCalcPZ);
			this->Controls->Add(this->NotEditedPZGrid);
			this->Controls->Add(this->PM25);
			this->Controls->Add(this->PM24);
			this->Controls->Add(this->PL25);
			this->Controls->Add(this->PL24);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"PzForm";
			this->Text = L"Расчет полетного задания";
			this->Load += gcnew System::EventHandler(this, &PzForm::PzForm_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &PzForm::PzForm_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PM24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PM25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NotEditedPZGrid))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EditedPZGrid))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion


	private: 
		DataGridViewComboBoxCell^ CreateComboBoxCell(FlagsComboBoxes boxes);
		List<String^>^ CreatingHeadersCellNames(FlagsComboBoxes boxes);
		array<array<int>^>^ GetMpnFromGrids(DataGridView ^currGridView);
		Dictionary<String^,String^>^ GetDataFromGrids(DataGridView ^currGridView);
		CollectDataPz ^ GetCollectionGridsData();
		System::Void InitNotEditedGrid(String^ name, List<String^> ^headersNotEditingCell);
		System::Void InitEditedGrid(String^ name, List<String^> ^headersEditingCell);
		System::Void InitPMs();
		System::Void Load_Mpn(CollectDataPz^ calcPz);
		System::Void Load_CalcPz(CollectDataPz^ calcPz);
		System::Void PzToXml(CollectDataPz^ dataList);

		System::Void PzForm_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void descriptionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void Calc_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void EditedPZGrid_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e);
		System::Void EditedPZGrid_CellValidating(System::Object^  sender, System::Windows::Forms::DataGridViewCellValidatingEventArgs^  e);
		System::Void EditedPZGrid_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e);
		System::Void PzForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		System::Void OK_button_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
