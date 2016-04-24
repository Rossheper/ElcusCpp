#pragma once
#include "PzForm.h"
#include "LoadEfemForm.h"
//#include "FormManager.h"
namespace ManchesterManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::Collections::Generic;
	using namespace System::Threading::Tasks;
	using namespace ManchesterLogging;
	//using namespace ManchesterDataLoader;
	using namespace ManchesterFSM;
	using namespace System::Linq;
	//using namespace ManchesterFormManager;
	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuMain;
	protected:

	protected:
#pragma region Form Controls

	private: System::Windows::Forms::ComboBox^  currentPlate;
	private: System::Windows::Forms::GroupBox^  CmdBuGroupBox;
	private: System::Windows::Forms::GroupBox^  groupBoxExecuteCommands;
	private: System::Windows::Forms::GroupBox^  groupBoxReadyFire;



	private: System::Windows::Forms::GroupBox^  groupBoxCapturePlate;

	private: System::Windows::Forms::ToolStripMenuItem^  menuToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  LoadNewEfemsToolStripMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;

	private: System::Windows::Forms::ComboBox^  comboBoxAddressOY;

	private: System::Windows::Forms::Label^  CurrAdrOYLabel;
	private: System::Windows::Forms::ComboBox^  modeSelector;
	private: System::Windows::Forms::Label^  SelectCmdLabel;
	private: System::Windows::Forms::Label^  CapturePlateLabel;
	private: System::Windows::Forms::Label^  SetAddressOYLabel;
	private: System::Windows::Forms::Label^  SelectPlateLabel;
	private: System::Windows::Forms::Button^  ExecuteButton;
	private: System::Windows::Forms::CheckBox^  fixedCommand;
	private: System::Windows::Forms::Label^  labelMBPP;
	private: System::Windows::Forms::Label^  labelBNA;
	private: System::Windows::Forms::ComboBox^  comboBox4;
	private: System::Windows::Forms::Label^  WaitingAnswerLabel;
	private: System::Windows::Forms::DataGridView^  dataGridViewMBPP;
	private: System::Windows::Forms::DataGridView^  dataGridViewBNA;









	private: System::Windows::Forms::StatusStrip^  statusPanel;

	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagGSN;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagVM;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagBICHE;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagMBPP;
	private: System::Windows::Forms::ToolStripStatusLabel^  currTimer;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagPZ;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagHotStart;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagFIX;
	private: System::Windows::Forms::CheckBox^  Button_ReadyCheck;
	private: System::Windows::Forms::Timer^  TimerReadyCheck;
	private: System::Windows::Forms::GroupBox^  NaviGroupBox;

	private: System::Windows::Forms::GroupBox^  BnaNavGroupBox;
	private: System::Windows::Forms::Label^  bnaSumNavCount;
	private: System::Windows::Forms::Label^  bnaSumNavLabel;
	private: System::Windows::Forms::Label^  bnaNumGLOCount;
	private: System::Windows::Forms::Label^  bnaNumGPSCount;
	private: System::Windows::Forms::Label^  bnaGLOlabel;
	private: System::Windows::Forms::Label^  bnaGPSlabel;
	private: System::Windows::Forms::GroupBox^  MbppNavGroupBox;
	private: System::Windows::Forms::Label^  mbppSumNavCount;
	private: System::Windows::Forms::Label^  mbppSumNavLabel;
	private: System::Windows::Forms::Label^  mbppNumGLOCount;
	private: System::Windows::Forms::Label^  mbppNumGPSCount;
	private: System::Windows::Forms::Label^  mbppGLOlabel;
	private: System::Windows::Forms::Label^  mbppGPSlabel;









	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagRM;
	private: System::Windows::Forms::ToolStripStatusLabel^  flagRT;
	private: System::Data::DataSet^  dataSetTables;
	private: System::Data::DataTable^  dataTableMBPP;
	private: System::Data::DataColumn^  dataXm;
	private: System::Data::DataColumn^  dataYm;
	private: System::Data::DataColumn^  dataZm;
	private: System::Data::DataColumn^  dataVxm;
	private: System::Data::DataColumn^  dataVym;
	private: System::Data::DataColumn^  dataVzm;
	private: System::Data::DataColumn^  dataTrustm;
	private: System::Data::DataColumn^  dataPDOP;
	private: System::Data::DataColumn^  dataCountm;
	private: System::Data::DataTable^  dataTableBNA;
	private: System::Data::DataColumn^  dataXb;
	private: System::Data::DataColumn^  dataYb;
	private: System::Data::DataColumn^  dataZb;
	private: System::Data::DataColumn^  dataVxb;
	private: System::Data::DataColumn^  dataVyb;
	private: System::Data::DataColumn^  dataVzb;
	private: System::Data::DataColumn^  dataTrustb;
	private: System::Data::DataColumn^  dataGDOP;
	private: System::Data::DataColumn^  dataCountb;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialogXML;
	private: System::Windows::Forms::Label^  labelSettedAddr;

	private: System::ComponentModel::IContainer^  components;

#pragma endregion
	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>

	public:

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuMain = (gcnew System::Windows::Forms::MenuStrip());
			this->menuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LoadNewEfemsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->currentPlate = (gcnew System::Windows::Forms::ComboBox());
			this->CmdBuGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->fixedCommand = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxExecuteCommands = (gcnew System::Windows::Forms::GroupBox());
			this->ExecuteButton = (gcnew System::Windows::Forms::Button());
			this->comboBoxAddressOY = (gcnew System::Windows::Forms::ComboBox());
			this->CurrAdrOYLabel = (gcnew System::Windows::Forms::Label());
			this->modeSelector = (gcnew System::Windows::Forms::ComboBox());
			this->SelectCmdLabel = (gcnew System::Windows::Forms::Label());
			this->groupBoxReadyFire = (gcnew System::Windows::Forms::GroupBox());
			this->Button_ReadyCheck = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxCapturePlate = (gcnew System::Windows::Forms::GroupBox());
			this->labelSettedAddr = (gcnew System::Windows::Forms::Label());
			this->CapturePlateLabel = (gcnew System::Windows::Forms::Label());
			this->SetAddressOYLabel = (gcnew System::Windows::Forms::Label());
			this->SelectPlateLabel = (gcnew System::Windows::Forms::Label());
			this->labelMBPP = (gcnew System::Windows::Forms::Label());
			this->labelBNA = (gcnew System::Windows::Forms::Label());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->WaitingAnswerLabel = (gcnew System::Windows::Forms::Label());
			this->dataGridViewMBPP = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewBNA = (gcnew System::Windows::Forms::DataGridView());
			this->statusPanel = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagGSN = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagVM = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagMBPP = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagBICHE = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagRM = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagRT = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->currTimer = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagPZ = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagHotStart = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->flagFIX = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->TimerReadyCheck = (gcnew System::Windows::Forms::Timer(this->components));
			this->NaviGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->BnaNavGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->bnaSumNavCount = (gcnew System::Windows::Forms::Label());
			this->bnaSumNavLabel = (gcnew System::Windows::Forms::Label());
			this->bnaNumGLOCount = (gcnew System::Windows::Forms::Label());
			this->bnaNumGPSCount = (gcnew System::Windows::Forms::Label());
			this->bnaGLOlabel = (gcnew System::Windows::Forms::Label());
			this->bnaGPSlabel = (gcnew System::Windows::Forms::Label());
			this->MbppNavGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->mbppSumNavCount = (gcnew System::Windows::Forms::Label());
			this->mbppSumNavLabel = (gcnew System::Windows::Forms::Label());
			this->mbppNumGLOCount = (gcnew System::Windows::Forms::Label());
			this->mbppNumGPSCount = (gcnew System::Windows::Forms::Label());
			this->mbppGLOlabel = (gcnew System::Windows::Forms::Label());
			this->mbppGPSlabel = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->dataSetTables = (gcnew System::Data::DataSet());
			this->dataTableMBPP = (gcnew System::Data::DataTable());
			this->dataXm = (gcnew System::Data::DataColumn());
			this->dataYm = (gcnew System::Data::DataColumn());
			this->dataZm = (gcnew System::Data::DataColumn());
			this->dataVxm = (gcnew System::Data::DataColumn());
			this->dataVym = (gcnew System::Data::DataColumn());
			this->dataVzm = (gcnew System::Data::DataColumn());
			this->dataTrustm = (gcnew System::Data::DataColumn());
			this->dataPDOP = (gcnew System::Data::DataColumn());
			this->dataCountm = (gcnew System::Data::DataColumn());
			this->dataTableBNA = (gcnew System::Data::DataTable());
			this->dataXb = (gcnew System::Data::DataColumn());
			this->dataYb = (gcnew System::Data::DataColumn());
			this->dataZb = (gcnew System::Data::DataColumn());
			this->dataVxb = (gcnew System::Data::DataColumn());
			this->dataVyb = (gcnew System::Data::DataColumn());
			this->dataVzb = (gcnew System::Data::DataColumn());
			this->dataTrustb = (gcnew System::Data::DataColumn());
			this->dataGDOP = (gcnew System::Data::DataColumn());
			this->dataCountb = (gcnew System::Data::DataColumn());
			this->saveFileDialogXML = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuMain->SuspendLayout();
			this->CmdBuGroupBox->SuspendLayout();
			this->groupBoxExecuteCommands->SuspendLayout();
			this->groupBoxReadyFire->SuspendLayout();
			this->groupBoxCapturePlate->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewMBPP))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewBNA))->BeginInit();
			this->statusPanel->SuspendLayout();
			this->NaviGroupBox->SuspendLayout();
			this->BnaNavGroupBox->SuspendLayout();
			this->MbppNavGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSetTables))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTableMBPP))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTableBNA))->BeginInit();
			this->SuspendLayout();
			// 
			// menuMain
			// 
			this->menuMain->BackColor = System::Drawing::SystemColors::Highlight;
			this->menuMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->menuToolStripMenuItem });
			this->menuMain->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->menuMain->Location = System::Drawing::Point(0, 0);
			this->menuMain->Name = L"menuMain";
			this->menuMain->Size = System::Drawing::Size(968, 24);
			this->menuMain->TabIndex = 1;
			this->menuMain->Text = L"menuStrip1";
			// 
			// menuToolStripMenuItem
			// 
			this->menuToolStripMenuItem->BackColor = System::Drawing::SystemColors::Highlight;
			this->menuToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->LoadNewEfemsToolStripMenuItem,
					this->saveToolStripMenuItem, this->clearToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->menuToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Bold));
			this->menuToolStripMenuItem->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->menuToolStripMenuItem->Name = L"menuToolStripMenuItem";
			this->menuToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->menuToolStripMenuItem->Text = L"Меню";
			// 
			// LoadNewEfemsToolStripMenuItem
			// 
			this->LoadNewEfemsToolStripMenuItem->BackColor = System::Drawing::SystemColors::HotTrack;
			this->LoadNewEfemsToolStripMenuItem->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->LoadNewEfemsToolStripMenuItem->Name = L"LoadNewEfemsToolStripMenuItem";
			this->LoadNewEfemsToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->LoadNewEfemsToolStripMenuItem->Text = L"Загрузить эфемериды";
			this->LoadNewEfemsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::LoadNewEfemsToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->BackColor = System::Drawing::SystemColors::HotTrack;
			this->saveToolStripMenuItem->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->saveToolStripMenuItem->Text = L"Сохранить";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveToolStripMenuItem_Click);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->BackColor = System::Drawing::SystemColors::HotTrack;
			this->clearToolStripMenuItem->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->clearToolStripMenuItem->Text = L"Очистить";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::clearToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->BackColor = System::Drawing::SystemColors::HotTrack;
			this->exitToolStripMenuItem->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(215, 22);
			this->exitToolStripMenuItem->Text = L"Выход";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// currentPlate
			// 
			this->currentPlate->BackColor = System::Drawing::SystemColors::Window;
			this->currentPlate->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->currentPlate->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->currentPlate->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->currentPlate->FormattingEnabled = true;
			this->currentPlate->Location = System::Drawing::Point(89, 26);
			this->currentPlate->Name = L"currentPlate";
			this->currentPlate->Size = System::Drawing::Size(42, 21);
			this->currentPlate->TabIndex = 2;
			this->currentPlate->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::currentPlate_SelectedIndexChanged);
			// 
			// CmdBuGroupBox
			// 
			this->CmdBuGroupBox->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->CmdBuGroupBox->BackColor = System::Drawing::Color::LightYellow;
			this->CmdBuGroupBox->Controls->Add(this->fixedCommand);
			this->CmdBuGroupBox->Cursor = System::Windows::Forms::Cursors::Default;
			this->CmdBuGroupBox->Enabled = false;
			this->CmdBuGroupBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CmdBuGroupBox->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CmdBuGroupBox->Location = System::Drawing::Point(728, 127);
			this->CmdBuGroupBox->Name = L"CmdBuGroupBox";
			this->CmdBuGroupBox->Size = System::Drawing::Size(231, 34);
			this->CmdBuGroupBox->TabIndex = 3;
			this->CmdBuGroupBox->TabStop = false;
			this->CmdBuGroupBox->Text = L"Команды БУ";
			this->CmdBuGroupBox->Visible = false;
			// 
			// fixedCommand
			// 
			this->fixedCommand->AutoSize = true;
			this->fixedCommand->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->fixedCommand->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->fixedCommand->Location = System::Drawing::Point(6, 13);
			this->fixedCommand->Name = L"fixedCommand";
			this->fixedCommand->Size = System::Drawing::Size(129, 17);
			this->fixedCommand->TabIndex = 1;
			this->fixedCommand->Text = L"Фиксация спутников";
			this->fixedCommand->UseVisualStyleBackColor = false;
			this->fixedCommand->CheckedChanged += gcnew System::EventHandler(this, &MainForm::fixedCommand_CheckedChanged);
			// 
			// groupBoxExecuteCommands
			// 
			this->groupBoxExecuteCommands->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->groupBoxExecuteCommands->BackColor = System::Drawing::Color::LightYellow;
			this->groupBoxExecuteCommands->Controls->Add(this->ExecuteButton);
			this->groupBoxExecuteCommands->Controls->Add(this->comboBoxAddressOY);
			this->groupBoxExecuteCommands->Controls->Add(this->CurrAdrOYLabel);
			this->groupBoxExecuteCommands->Controls->Add(this->modeSelector);
			this->groupBoxExecuteCommands->Controls->Add(this->SelectCmdLabel);
			this->groupBoxExecuteCommands->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->groupBoxExecuteCommands->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBoxExecuteCommands->Location = System::Drawing::Point(500, 27);
			this->groupBoxExecuteCommands->Name = L"groupBoxExecuteCommands";
			this->groupBoxExecuteCommands->Size = System::Drawing::Size(222, 134);
			this->groupBoxExecuteCommands->TabIndex = 4;
			this->groupBoxExecuteCommands->TabStop = false;
			this->groupBoxExecuteCommands->Text = L"Выполнение указанной команды";
			// 
			// ExecuteButton
			// 
			this->ExecuteButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->ExecuteButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->ExecuteButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->ExecuteButton->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ExecuteButton->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->ExecuteButton->Location = System::Drawing::Point(9, 72);
			this->ExecuteButton->Name = L"ExecuteButton";
			this->ExecuteButton->Size = System::Drawing::Size(204, 53);
			this->ExecuteButton->TabIndex = 8;
			this->ExecuteButton->Text = L"Выполнить";
			this->ExecuteButton->UseVisualStyleBackColor = false;
			this->ExecuteButton->Click += gcnew System::EventHandler(this, &MainForm::ExecuteButton_Click);
			// 
			// comboBoxAddressOY
			// 
			this->comboBoxAddressOY->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBoxAddressOY->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->comboBoxAddressOY->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBoxAddressOY->FormattingEnabled = true;
			this->comboBoxAddressOY->Location = System::Drawing::Point(159, 44);
			this->comboBoxAddressOY->Name = L"comboBoxAddressOY";
			this->comboBoxAddressOY->Size = System::Drawing::Size(54, 21);
			this->comboBoxAddressOY->TabIndex = 8;
			this->comboBoxAddressOY->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox3_SelectedIndexChanged);
			// 
			// CurrAdrOYLabel
			// 
			this->CurrAdrOYLabel->AutoSize = true;
			this->CurrAdrOYLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CurrAdrOYLabel->Location = System::Drawing::Point(156, 29);
			this->CurrAdrOYLabel->Name = L"CurrAdrOYLabel";
			this->CurrAdrOYLabel->Size = System::Drawing::Size(60, 13);
			this->CurrAdrOYLabel->TabIndex = 8;
			this->CurrAdrOYLabel->Text = L"Адрес ОУ:";
			// 
			// modeSelector
			// 
			this->modeSelector->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->modeSelector->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->modeSelector->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->modeSelector->FormattingEnabled = true;
			this->modeSelector->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Установить адрес", L"Ввод задания", L"Ввод задания + ГС" });
			this->modeSelector->Location = System::Drawing::Point(9, 43);
			this->modeSelector->Name = L"modeSelector";
			this->modeSelector->Size = System::Drawing::Size(121, 21);
			this->modeSelector->TabIndex = 9;
			this->modeSelector->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::mode_SelectedIndexChanged);
			// 
			// SelectCmdLabel
			// 
			this->SelectCmdLabel->AutoSize = true;
			this->SelectCmdLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SelectCmdLabel->Location = System::Drawing::Point(6, 29);
			this->SelectCmdLabel->Name = L"SelectCmdLabel";
			this->SelectCmdLabel->Size = System::Drawing::Size(91, 13);
			this->SelectCmdLabel->TabIndex = 8;
			this->SelectCmdLabel->Text = L"Выбор команды:";
			// 
			// groupBoxReadyFire
			// 
			this->groupBoxReadyFire->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->groupBoxReadyFire->BackColor = System::Drawing::Color::LightYellow;
			this->groupBoxReadyFire->Controls->Add(this->Button_ReadyCheck);
			this->groupBoxReadyFire->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->groupBoxReadyFire->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBoxReadyFire->Location = System::Drawing::Point(363, 27);
			this->groupBoxReadyFire->Name = L"groupBoxReadyFire";
			this->groupBoxReadyFire->Size = System::Drawing::Size(131, 134);
			this->groupBoxReadyFire->TabIndex = 5;
			this->groupBoxReadyFire->TabStop = false;
			this->groupBoxReadyFire->Text = L"Разрешение пуска";
			// 
			// Button_ReadyCheck
			// 
			this->Button_ReadyCheck->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Button_ReadyCheck->Appearance = System::Windows::Forms::Appearance::Button;
			this->Button_ReadyCheck->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Button_ReadyCheck->FlatAppearance->BorderSize = 0;
			this->Button_ReadyCheck->FlatAppearance->CheckedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(123)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(223)));
			this->Button_ReadyCheck->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Button_ReadyCheck->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->Button_ReadyCheck->ForeColor = System::Drawing::Color::White;
			this->Button_ReadyCheck->Location = System::Drawing::Point(6, 19);
			this->Button_ReadyCheck->Name = L"Button_ReadyCheck";
			this->Button_ReadyCheck->Size = System::Drawing::Size(119, 109);
			this->Button_ReadyCheck->TabIndex = 8;
			this->Button_ReadyCheck->Text = L"Запустить";
			this->Button_ReadyCheck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Button_ReadyCheck->UseVisualStyleBackColor = false;
			this->Button_ReadyCheck->Click += gcnew System::EventHandler(this, &MainForm::Button_ReadyCheck_Click);
			// 
			// groupBoxCapturePlate
			// 
			this->groupBoxCapturePlate->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->groupBoxCapturePlate->BackColor = System::Drawing::Color::LightYellow;
			this->groupBoxCapturePlate->Controls->Add(this->labelSettedAddr);
			this->groupBoxCapturePlate->Controls->Add(this->CapturePlateLabel);
			this->groupBoxCapturePlate->Controls->Add(this->SetAddressOYLabel);
			this->groupBoxCapturePlate->Controls->Add(this->SelectPlateLabel);
			this->groupBoxCapturePlate->Controls->Add(this->currentPlate);
			this->groupBoxCapturePlate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->groupBoxCapturePlate->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBoxCapturePlate->Location = System::Drawing::Point(12, 27);
			this->groupBoxCapturePlate->Name = L"groupBoxCapturePlate";
			this->groupBoxCapturePlate->Size = System::Drawing::Size(276, 134);
			this->groupBoxCapturePlate->TabIndex = 6;
			this->groupBoxCapturePlate->TabStop = false;
			this->groupBoxCapturePlate->Text = L"Захват платы";
			// 
			// labelSettedAddr
			// 
			this->labelSettedAddr->AutoSize = true;
			this->labelSettedAddr->Location = System::Drawing::Point(154, 66);
			this->labelSettedAddr->Name = L"labelSettedAddr";
			this->labelSettedAddr->Size = System::Drawing::Size(59, 13);
			this->labelSettedAddr->TabIndex = 8;
			this->labelSettedAddr->Text = L"NumAddr";
			// 
			// CapturePlateLabel
			// 
			this->CapturePlateLabel->AutoSize = true;
			this->CapturePlateLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold));
			this->CapturePlateLabel->Location = System::Drawing::Point(39, 87);
			this->CapturePlateLabel->Name = L"CapturePlateLabel";
			this->CapturePlateLabel->Size = System::Drawing::Size(68, 19);
			this->CapturePlateLabel->TabIndex = 7;
			this->CapturePlateLabel->Text = L"Захват";
			// 
			// SetAddressOYLabel
			// 
			this->SetAddressOYLabel->AutoSize = true;
			this->SetAddressOYLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SetAddressOYLabel->Location = System::Drawing::Point(6, 66);
			this->SetAddressOYLabel->Name = L"SetAddressOYLabel";
			this->SetAddressOYLabel->Size = System::Drawing::Size(142, 13);
			this->SetAddressOYLabel->TabIndex = 7;
			this->SetAddressOYLabel->Text = L"Установленный адрес ОУ:";
			// 
			// SelectPlateLabel
			// 
			this->SelectPlateLabel->AutoSize = true;
			this->SelectPlateLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SelectPlateLabel->Location = System::Drawing::Point(6, 29);
			this->SelectPlateLabel->Name = L"SelectPlateLabel";
			this->SelectPlateLabel->Size = System::Drawing::Size(78, 13);
			this->SelectPlateLabel->TabIndex = 0;
			this->SelectPlateLabel->Text = L"Выбор платы:";
			// 
			// labelMBPP
			// 
			this->labelMBPP->AutoSize = true;
			this->labelMBPP->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold));
			this->labelMBPP->ForeColor = System::Drawing::Color::Purple;
			this->labelMBPP->Location = System::Drawing::Point(191, 164);
			this->labelMBPP->Name = L"labelMBPP";
			this->labelMBPP->Size = System::Drawing::Size(58, 19);
			this->labelMBPP->TabIndex = 11;
			this->labelMBPP->Text = L"МБПП";
			// 
			// labelBNA
			// 
			this->labelBNA->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->labelBNA->AutoSize = true;
			this->labelBNA->Font = (gcnew System::Drawing::Font(L"Tahoma", 12, System::Drawing::FontStyle::Bold));
			this->labelBNA->ForeColor = System::Drawing::Color::Purple;
			this->labelBNA->Location = System::Drawing::Point(669, 164);
			this->labelBNA->Name = L"labelBNA";
			this->labelBNA->Size = System::Drawing::Size(44, 19);
			this->labelBNA->TabIndex = 12;
			this->labelBNA->Text = L"БНА";
			// 
			// comboBox4
			// 
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Location = System::Drawing::Point(294, 34);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(63, 21);
			this->comboBox4->TabIndex = 13;
			this->comboBox4->Visible = false;
			// 
			// WaitingAnswerLabel
			// 
			this->WaitingAnswerLabel->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->WaitingAnswerLabel->AutoSize = true;
			this->WaitingAnswerLabel->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->WaitingAnswerLabel->Location = System::Drawing::Point(406, 164);
			this->WaitingAnswerLabel->Name = L"WaitingAnswerLabel";
			this->WaitingAnswerLabel->Size = System::Drawing::Size(158, 17);
			this->WaitingAnswerLabel->TabIndex = 14;
			this->WaitingAnswerLabel->Text = L"Ожидание отправки";
			// 
			// dataGridViewMBPP
			// 
			this->dataGridViewMBPP->AllowUserToAddRows = false;
			this->dataGridViewMBPP->AllowUserToDeleteRows = false;
			this->dataGridViewMBPP->AllowUserToResizeColumns = false;
			this->dataGridViewMBPP->AllowUserToResizeRows = false;
			this->dataGridViewMBPP->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridViewMBPP->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridViewMBPP->BackgroundColor = System::Drawing::Color::Ivory;
			this->dataGridViewMBPP->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridViewMBPP->Location = System::Drawing::Point(9, 201);
			this->dataGridViewMBPP->Name = L"dataGridViewMBPP";
			this->dataGridViewMBPP->ReadOnly = true;
			this->dataGridViewMBPP->RowHeadersWidth = 20;
			this->dataGridViewMBPP->Size = System::Drawing::Size(470, 289);
			this->dataGridViewMBPP->TabIndex = 17;
			this->dataGridViewMBPP->RowsAdded += gcnew System::Windows::Forms::DataGridViewRowsAddedEventHandler(this, &MainForm::dataGridViewBNA_RowsAdded);
			// 
			// dataGridViewBNA
			// 
			this->dataGridViewBNA->AllowUserToAddRows = false;
			this->dataGridViewBNA->AllowUserToDeleteRows = false;
			this->dataGridViewBNA->AllowUserToResizeColumns = false;
			this->dataGridViewBNA->AllowUserToResizeRows = false;
			this->dataGridViewBNA->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridViewBNA->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridViewBNA->BackgroundColor = System::Drawing::Color::Ivory;
			this->dataGridViewBNA->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridViewBNA->Location = System::Drawing::Point(489, 201);
			this->dataGridViewBNA->Name = L"dataGridViewBNA";
			this->dataGridViewBNA->ReadOnly = true;
			this->dataGridViewBNA->RowHeadersWidth = 20;
			this->dataGridViewBNA->Size = System::Drawing::Size(470, 289);
			this->dataGridViewBNA->TabIndex = 18;
			this->dataGridViewBNA->RowsAdded += gcnew System::Windows::Forms::DataGridViewRowsAddedEventHandler(this, &MainForm::dataGridViewBNA_RowsAdded);
			this->dataGridViewBNA->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::dataGridViewBNA_KeyDown);
			// 
			// statusPanel
			// 
			this->statusPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(202)),
				static_cast<System::Int32>(static_cast<System::Byte>(65)));
			this->statusPanel->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
				this->toolStripStatusLabel1,
					this->flagGSN, this->flagVM, this->flagMBPP, this->flagBICHE, this->flagRM, this->flagRT, this->currTimer, this->flagPZ, this->flagHotStart,
					this->flagFIX
			});
			this->statusPanel->Location = System::Drawing::Point(0, 493);
			this->statusPanel->Name = L"statusPanel";
			this->statusPanel->Size = System::Drawing::Size(968, 26);
			this->statusPanel->SizingGrip = false;
			this->statusPanel->TabIndex = 19;
			this->statusPanel->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->toolStripStatusLabel1->ForeColor = System::Drawing::Color::Black;
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(150, 21);
			this->toolStripStatusLabel1->Text = L"Флаги и состояния:";
			// 
			// flagGSN
			// 
			this->flagGSN->BackColor = System::Drawing::Color::Red;
			this->flagGSN->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagGSN->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagGSN->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagGSN->ForeColor = System::Drawing::Color::White;
			this->flagGSN->Name = L"flagGSN";
			this->flagGSN->Size = System::Drawing::Size(41, 21);
			this->flagGSN->Text = L"ГСН";
			// 
			// flagVM
			// 
			this->flagVM->ActiveLinkColor = System::Drawing::Color::Red;
			this->flagVM->BackColor = System::Drawing::Color::Red;
			this->flagVM->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagVM->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagVM->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagVM->ForeColor = System::Drawing::Color::White;
			this->flagVM->Name = L"flagVM";
			this->flagVM->Size = System::Drawing::Size(34, 21);
			this->flagVM->Text = L"ВМ";
			// 
			// flagMBPP
			// 
			this->flagMBPP->ActiveLinkColor = System::Drawing::Color::Fuchsia;
			this->flagMBPP->BackColor = System::Drawing::Color::Red;
			this->flagMBPP->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->flagMBPP->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagMBPP->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagMBPP->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->flagMBPP->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagMBPP->ForeColor = System::Drawing::Color::White;
			this->flagMBPP->Name = L"flagMBPP";
			this->flagMBPP->Size = System::Drawing::Size(56, 21);
			this->flagMBPP->Text = L"МБПП";
			// 
			// flagBICHE
			// 
			this->flagBICHE->BackColor = System::Drawing::Color::Red;
			this->flagBICHE->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagBICHE->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagBICHE->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagBICHE->ForeColor = System::Drawing::Color::White;
			this->flagBICHE->Name = L"flagBICHE";
			this->flagBICHE->Size = System::Drawing::Size(53, 21);
			this->flagBICHE->Text = L"БИЧЭ";
			// 
			// flagRM
			// 
			this->flagRM->BackColor = System::Drawing::Color::Red;
			this->flagRM->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagRM->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagRM->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagRM->ForeColor = System::Drawing::Color::White;
			this->flagRM->Name = L"flagRM";
			this->flagRM->Size = System::Drawing::Size(34, 21);
			this->flagRM->Text = L"RM";
			// 
			// flagRT
			// 
			this->flagRT->BackColor = System::Drawing::Color::Red;
			this->flagRT->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagRT->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagRT->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagRT->ForeColor = System::Drawing::Color::White;
			this->flagRT->Name = L"flagRT";
			this->flagRT->Size = System::Drawing::Size(31, 21);
			this->flagRT->Text = L"RT";
			// 
			// currTimer
			// 
			this->currTimer->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->currTimer->ForeColor = System::Drawing::Color::Black;
			this->currTimer->Name = L"currTimer";
			this->currTimer->Size = System::Drawing::Size(202, 21);
			this->currTimer->Spring = true;
			this->currTimer->Text = L"Таймер";
			// 
			// flagPZ
			// 
			this->flagPZ->BackColor = System::Drawing::Color::Red;
			this->flagPZ->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagPZ->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagPZ->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagPZ->ForeColor = System::Drawing::Color::White;
			this->flagPZ->Name = L"flagPZ";
			this->flagPZ->Size = System::Drawing::Size(74, 21);
			this->flagPZ->Text = L"Задание";
			// 
			// flagHotStart
			// 
			this->flagHotStart->BackColor = System::Drawing::Color::Red;
			this->flagHotStart->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagHotStart->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagHotStart->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagHotStart->ForeColor = System::Drawing::Color::White;
			this->flagHotStart->Name = L"flagHotStart";
			this->flagHotStart->Size = System::Drawing::Size(116, 21);
			this->flagHotStart->Text = L"Горячий старт";
			// 
			// flagFIX
			// 
			this->flagFIX->BackColor = System::Drawing::Color::Red;
			this->flagFIX->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right)
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->flagFIX->BorderStyle = System::Windows::Forms::Border3DStyle::Adjust;
			this->flagFIX->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->flagFIX->ForeColor = System::Drawing::Color::White;
			this->flagFIX->Name = L"flagFIX";
			this->flagFIX->Size = System::Drawing::Size(162, 21);
			this->flagFIX->Text = L"Фиксация спутников";
			// 
			// TimerReadyCheck
			// 
			this->TimerReadyCheck->Interval = 1000;
			this->TimerReadyCheck->Tick += gcnew System::EventHandler(this, &MainForm::TimerReadyCheck_Tick);
			// 
			// NaviGroupBox
			// 
			this->NaviGroupBox->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->NaviGroupBox->BackColor = System::Drawing::Color::LightYellow;
			this->NaviGroupBox->Controls->Add(this->BnaNavGroupBox);
			this->NaviGroupBox->Controls->Add(this->MbppNavGroupBox);
			this->NaviGroupBox->Font = (gcnew System::Drawing::Font(L"Tahoma", 8.25F, System::Drawing::FontStyle::Bold));
			this->NaviGroupBox->Location = System::Drawing::Point(728, 27);
			this->NaviGroupBox->Name = L"NaviGroupBox";
			this->NaviGroupBox->Size = System::Drawing::Size(231, 100);
			this->NaviGroupBox->TabIndex = 20;
			this->NaviGroupBox->TabStop = false;
			this->NaviGroupBox->Text = L"Данные о навигации";
			// 
			// BnaNavGroupBox
			// 
			this->BnaNavGroupBox->Controls->Add(this->bnaSumNavCount);
			this->BnaNavGroupBox->Controls->Add(this->bnaSumNavLabel);
			this->BnaNavGroupBox->Controls->Add(this->bnaNumGLOCount);
			this->BnaNavGroupBox->Controls->Add(this->bnaNumGPSCount);
			this->BnaNavGroupBox->Controls->Add(this->bnaGLOlabel);
			this->BnaNavGroupBox->Controls->Add(this->bnaGPSlabel);
			this->BnaNavGroupBox->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->BnaNavGroupBox->ForeColor = System::Drawing::Color::Purple;
			this->BnaNavGroupBox->Location = System::Drawing::Point(118, 13);
			this->BnaNavGroupBox->Name = L"BnaNavGroupBox";
			this->BnaNavGroupBox->Size = System::Drawing::Size(106, 81);
			this->BnaNavGroupBox->TabIndex = 1;
			this->BnaNavGroupBox->TabStop = false;
			this->BnaNavGroupBox->Text = L"БНА";
			// 
			// bnaSumNavCount
			// 
			this->bnaSumNavCount->AutoSize = true;
			this->bnaSumNavCount->ForeColor = System::Drawing::Color::Red;
			this->bnaSumNavCount->Location = System::Drawing::Point(70, 55);
			this->bnaSumNavCount->Name = L"bnaSumNavCount";
			this->bnaSumNavCount->Size = System::Drawing::Size(17, 17);
			this->bnaSumNavCount->TabIndex = 5;
			this->bnaSumNavCount->Text = L"0";
			// 
			// bnaSumNavLabel
			// 
			this->bnaSumNavLabel->AutoSize = true;
			this->bnaSumNavLabel->ForeColor = System::Drawing::Color::Black;
			this->bnaSumNavLabel->Location = System::Drawing::Point(6, 55);
			this->bnaSumNavLabel->Name = L"bnaSumNavLabel";
			this->bnaSumNavLabel->Size = System::Drawing::Size(61, 17);
			this->bnaSumNavLabel->TabIndex = 4;
			this->bnaSumNavLabel->Text = L"Сумма:";
			// 
			// bnaNumGLOCount
			// 
			this->bnaNumGLOCount->AutoSize = true;
			this->bnaNumGLOCount->ForeColor = System::Drawing::Color::Red;
			this->bnaNumGLOCount->Location = System::Drawing::Point(70, 35);
			this->bnaNumGLOCount->Name = L"bnaNumGLOCount";
			this->bnaNumGLOCount->Size = System::Drawing::Size(17, 17);
			this->bnaNumGLOCount->TabIndex = 3;
			this->bnaNumGLOCount->Text = L"0";
			// 
			// bnaNumGPSCount
			// 
			this->bnaNumGPSCount->AutoSize = true;
			this->bnaNumGPSCount->ForeColor = System::Drawing::Color::Red;
			this->bnaNumGPSCount->Location = System::Drawing::Point(25, 35);
			this->bnaNumGPSCount->Name = L"bnaNumGPSCount";
			this->bnaNumGPSCount->Size = System::Drawing::Size(17, 17);
			this->bnaNumGPSCount->TabIndex = 2;
			this->bnaNumGPSCount->Text = L"0";
			// 
			// bnaGLOlabel
			// 
			this->bnaGLOlabel->AutoSize = true;
			this->bnaGLOlabel->ForeColor = System::Drawing::Color::Black;
			this->bnaGLOlabel->Location = System::Drawing::Point(64, 19);
			this->bnaGLOlabel->Name = L"bnaGLOlabel";
			this->bnaGLOlabel->Size = System::Drawing::Size(37, 17);
			this->bnaGLOlabel->TabIndex = 1;
			this->bnaGLOlabel->Text = L"GLO";
			// 
			// bnaGPSlabel
			// 
			this->bnaGPSlabel->AutoSize = true;
			this->bnaGPSlabel->ForeColor = System::Drawing::Color::Black;
			this->bnaGPSlabel->Location = System::Drawing::Point(16, 19);
			this->bnaGPSlabel->Name = L"bnaGPSlabel";
			this->bnaGPSlabel->Size = System::Drawing::Size(36, 17);
			this->bnaGPSlabel->TabIndex = 0;
			this->bnaGPSlabel->Text = L"GPS";
			// 
			// MbppNavGroupBox
			// 
			this->MbppNavGroupBox->Controls->Add(this->mbppSumNavCount);
			this->MbppNavGroupBox->Controls->Add(this->mbppSumNavLabel);
			this->MbppNavGroupBox->Controls->Add(this->mbppNumGLOCount);
			this->MbppNavGroupBox->Controls->Add(this->mbppNumGPSCount);
			this->MbppNavGroupBox->Controls->Add(this->mbppGLOlabel);
			this->MbppNavGroupBox->Controls->Add(this->mbppGPSlabel);
			this->MbppNavGroupBox->Font = (gcnew System::Drawing::Font(L"Tahoma", 10, System::Drawing::FontStyle::Bold));
			this->MbppNavGroupBox->ForeColor = System::Drawing::Color::Purple;
			this->MbppNavGroupBox->Location = System::Drawing::Point(6, 13);
			this->MbppNavGroupBox->Name = L"MbppNavGroupBox";
			this->MbppNavGroupBox->Size = System::Drawing::Size(106, 81);
			this->MbppNavGroupBox->TabIndex = 0;
			this->MbppNavGroupBox->TabStop = false;
			this->MbppNavGroupBox->Text = L"МБПП";
			// 
			// mbppSumNavCount
			// 
			this->mbppSumNavCount->AutoSize = true;
			this->mbppSumNavCount->ForeColor = System::Drawing::Color::Red;
			this->mbppSumNavCount->Location = System::Drawing::Point(70, 54);
			this->mbppSumNavCount->Name = L"mbppSumNavCount";
			this->mbppSumNavCount->Size = System::Drawing::Size(17, 17);
			this->mbppSumNavCount->TabIndex = 5;
			this->mbppSumNavCount->Text = L"0";
			// 
			// mbppSumNavLabel
			// 
			this->mbppSumNavLabel->AutoSize = true;
			this->mbppSumNavLabel->ForeColor = System::Drawing::Color::Black;
			this->mbppSumNavLabel->Location = System::Drawing::Point(6, 54);
			this->mbppSumNavLabel->Name = L"mbppSumNavLabel";
			this->mbppSumNavLabel->Size = System::Drawing::Size(61, 17);
			this->mbppSumNavLabel->TabIndex = 4;
			this->mbppSumNavLabel->Text = L"Сумма:";
			// 
			// mbppNumGLOCount
			// 
			this->mbppNumGLOCount->AutoSize = true;
			this->mbppNumGLOCount->ForeColor = System::Drawing::Color::Red;
			this->mbppNumGLOCount->Location = System::Drawing::Point(70, 34);
			this->mbppNumGLOCount->Name = L"mbppNumGLOCount";
			this->mbppNumGLOCount->Size = System::Drawing::Size(17, 17);
			this->mbppNumGLOCount->TabIndex = 3;
			this->mbppNumGLOCount->Text = L"0";
			// 
			// mbppNumGPSCount
			// 
			this->mbppNumGPSCount->AutoSize = true;
			this->mbppNumGPSCount->ForeColor = System::Drawing::Color::Red;
			this->mbppNumGPSCount->Location = System::Drawing::Point(25, 34);
			this->mbppNumGPSCount->Name = L"mbppNumGPSCount";
			this->mbppNumGPSCount->Size = System::Drawing::Size(17, 17);
			this->mbppNumGPSCount->TabIndex = 2;
			this->mbppNumGPSCount->Text = L"0";
			// 
			// mbppGLOlabel
			// 
			this->mbppGLOlabel->AutoSize = true;
			this->mbppGLOlabel->ForeColor = System::Drawing::Color::Black;
			this->mbppGLOlabel->Location = System::Drawing::Point(64, 18);
			this->mbppGLOlabel->Name = L"mbppGLOlabel";
			this->mbppGLOlabel->Size = System::Drawing::Size(37, 17);
			this->mbppGLOlabel->TabIndex = 1;
			this->mbppGLOlabel->Text = L"GLO";
			// 
			// mbppGPSlabel
			// 
			this->mbppGPSlabel->AutoSize = true;
			this->mbppGPSlabel->ForeColor = System::Drawing::Color::Black;
			this->mbppGPSlabel->Location = System::Drawing::Point(17, 18);
			this->mbppGPSlabel->Name = L"mbppGPSlabel";
			this->mbppGPSlabel->Size = System::Drawing::Size(36, 17);
			this->mbppGPSlabel->TabIndex = 0;
			this->mbppGPSlabel->Text = L"GPS";
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Location = System::Drawing::Point(294, 58);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(63, 103);
			this->panel1->TabIndex = 21;
			this->panel1->Visible = false;
			// 
			// dataSetTables
			// 
			this->dataSetTables->DataSetName = L"NewDataSet";
			this->dataSetTables->Tables->AddRange(gcnew cli::array< System::Data::DataTable^  >(2) { this->dataTableMBPP, this->dataTableBNA });
			// 
			// dataTableMBPP
			// 
			this->dataTableMBPP->Columns->AddRange(gcnew cli::array< System::Data::DataColumn^  >(9) {
				this->dataXm, this->dataYm, this->dataZm,
					this->dataVxm, this->dataVym, this->dataVzm, this->dataTrustm, this->dataPDOP, this->dataCountm
			});
			this->dataTableMBPP->TableName = L"TableMBPP";
			// 
			// dataXm
			// 
			this->dataXm->ColumnName = L"X";
			this->dataXm->ReadOnly = true;
			// 
			// dataYm
			// 
			this->dataYm->ColumnName = L"Y";
			this->dataYm->ReadOnly = true;
			// 
			// dataZm
			// 
			this->dataZm->ColumnName = L"Z";
			this->dataZm->ReadOnly = true;
			// 
			// dataVxm
			// 
			this->dataVxm->ColumnName = L"Vx";
			this->dataVxm->ReadOnly = true;
			// 
			// dataVym
			// 
			this->dataVym->ColumnName = L"Vy";
			this->dataVym->ReadOnly = true;
			// 
			// dataVzm
			// 
			this->dataVzm->ColumnName = L"Vz";
			this->dataVzm->ReadOnly = true;
			// 
			// dataTrustm
			// 
			this->dataTrustm->ColumnName = L"Trust";
			this->dataTrustm->MaxLength = 40;
			this->dataTrustm->ReadOnly = true;
			// 
			// dataPDOP
			// 
			this->dataPDOP->ColumnName = L"PDOP";
			this->dataPDOP->MaxLength = 40;
			this->dataPDOP->ReadOnly = true;
			// 
			// dataCountm
			// 
			this->dataCountm->ColumnName = L"Count";
			this->dataCountm->MaxLength = 40;
			this->dataCountm->ReadOnly = true;
			// 
			// dataTableBNA
			// 
			this->dataTableBNA->Columns->AddRange(gcnew cli::array< System::Data::DataColumn^  >(9) {
				this->dataXb, this->dataYb, this->dataZb,
					this->dataVxb, this->dataVyb, this->dataVzb, this->dataTrustb, this->dataGDOP, this->dataCountb
			});
			this->dataTableBNA->TableName = L"TableBNA";
			// 
			// dataXb
			// 
			this->dataXb->ColumnName = L"X";
			this->dataXb->ReadOnly = true;
			// 
			// dataYb
			// 
			this->dataYb->ColumnName = L"Y";
			this->dataYb->ReadOnly = true;
			// 
			// dataZb
			// 
			this->dataZb->ColumnName = L"Z";
			this->dataZb->ReadOnly = true;
			// 
			// dataVxb
			// 
			this->dataVxb->ColumnName = L"Vx";
			this->dataVxb->ReadOnly = true;
			// 
			// dataVyb
			// 
			this->dataVyb->ColumnName = L"Vy";
			this->dataVyb->ReadOnly = true;
			// 
			// dataVzb
			// 
			this->dataVzb->ColumnName = L"Vz";
			this->dataVzb->ReadOnly = true;
			// 
			// dataTrustb
			// 
			this->dataTrustb->ColumnName = L"Trust";
			this->dataTrustb->ReadOnly = true;
			// 
			// dataGDOP
			// 
			this->dataGDOP->ColumnName = L"GDOP";
			this->dataGDOP->ReadOnly = true;
			// 
			// dataCountb
			// 
			this->dataCountb->ColumnName = L"Count";
			this->dataCountb->ReadOnly = true;
			// 
			// saveFileDialogXML
			// 
			this->saveFileDialogXML->FileName = L"ready_log";
			this->saveFileDialogXML->Filter = L"XML files (*.xml)|*.xml;";
			this->saveFileDialogXML->RestoreDirectory = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Ivory;
			this->ClientSize = System::Drawing::Size(968, 519);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->NaviGroupBox);
			this->Controls->Add(this->statusPanel);
			this->Controls->Add(this->dataGridViewBNA);
			this->Controls->Add(this->dataGridViewMBPP);
			this->Controls->Add(this->WaitingAnswerLabel);
			this->Controls->Add(this->comboBox4);
			this->Controls->Add(this->labelBNA);
			this->Controls->Add(this->labelMBPP);
			this->Controls->Add(this->groupBoxCapturePlate);
			this->Controls->Add(this->groupBoxReadyFire);
			this->Controls->Add(this->groupBoxExecuteCommands);
			this->Controls->Add(this->CmdBuGroupBox);
			this->Controls->Add(this->menuMain);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuMain;
			this->MinimumSize = System::Drawing::Size(892, 477);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"МКИО";
			this->Load += gcnew System::EventHandler(this, &MainForm::MyForm1_Load);
			this->Resize += gcnew System::EventHandler(this, &MainForm::MyForm1_Resize);
			this->menuMain->ResumeLayout(false);
			this->menuMain->PerformLayout();
			this->CmdBuGroupBox->ResumeLayout(false);
			this->CmdBuGroupBox->PerformLayout();
			this->groupBoxExecuteCommands->ResumeLayout(false);
			this->groupBoxExecuteCommands->PerformLayout();
			this->groupBoxReadyFire->ResumeLayout(false);
			this->groupBoxCapturePlate->ResumeLayout(false);
			this->groupBoxCapturePlate->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewMBPP))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewBNA))->EndInit();
			this->statusPanel->ResumeLayout(false);
			this->statusPanel->PerformLayout();
			this->NaviGroupBox->ResumeLayout(false);
			this->BnaNavGroupBox->ResumeLayout(false);
			this->BnaNavGroupBox->PerformLayout();
			this->MbppNavGroupBox->ResumeLayout(false);
			this->MbppNavGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSetTables))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTableMBPP))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTableBNA))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		delegate void DelegateUpdataForms();
		FiniteStateMachine ^stateMachine;
		Mutex^ MutexReadyCheck;
		Thread^ ThreadReadyCheck;
		DelegateUpdataForms^ DelegateForms;
		ManualResetEvent ^resetEvent;
		Task ^tasks;
		DateTime oldTime;
		StringBuilder ^stringBuilder;
		Logging ^logs;
		int timeSpent;
		bool lockedFix;
		bool locked;
		short oldCountMbpp;
		void MyForm1_Resize(System::Object^  sender, System::EventArgs^  e);
		void MyForm1_Load(System::Object^  sender, System::EventArgs^  e);
		void currentPlateSelect(System::Object^  sender);
		void currentPlate_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void mode_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void comboBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void Button_ReadyCheck_Click(System::Object^  sender, System::EventArgs^  e);
		void ExecuteButton_Click(System::Object^  sender, System::EventArgs^  e);
		void fixedCommand_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
		void TimerReadyCheck_Tick(System::Object^  sender, System::EventArgs^  e);
		void dataGridViewBNA_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
		void LoadNewEfemsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void dataGridViewBNA_RowsAdded(System::Object^  sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^  e);
		void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void InitThreading();
		void InitControls();
		void UpdateDataGrids();
		void RunReadyCheck(Object ^ time);
		void SetsFlagsStatus(unsigned int state);
		void NavStatus(short mbppGLO, short mbppGPS, short bnaGLO, short bnaGPS);
		void StatusMbpp(short newCount);
		void StatusAnswerMbpp(unsigned int state);
		void EnableControlsArbitration(bool enabled);
		int GLGPC(int currGLC, int currGPS, int time);
		void EnabledControlsAfterCheckCapturePlate(bool enabled);
	};

	public  ref class ColorTable : ProfessionalColorTable
	{
	public:
		property  Color  MenuItemPressedGradientBegin {
			virtual Color get() override {
				return SystemColors::HotTrack;
			}
		}
		property Color MenuItemPressedGradientEnd {
			virtual Color get()  override {
				return SystemColors::HotTrack;
			}
		}

		property  Color  MenuItemSelectedGradientBegin {
			virtual Color get() override {
				return SystemColors::HotTrack;
			}
		}
		property Color MenuItemSelectedGradientEnd {
			virtual Color get()  override {
				return SystemColors::HotTrack;
			}
		}

		property  Color  ToolStripDropDownBackground {
			virtual Color get() override {
				return SystemColors::HotTrack;
			}
		}
		property  Color  MenuItemSelected {
			virtual Color get() override {
				return SystemColors::Highlight;
			}
		}
		
			
	};
}
