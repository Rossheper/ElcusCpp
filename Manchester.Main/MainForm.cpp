
#include "MainForm.h"
//#include "PzForm.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace ManchesterManager;
using namespace std;


[STAThread]
void Main(array<String^>^args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ManchesterManager::MainForm mainForm;
	Application::Run(%mainForm);
}

void MainForm::InitThreading() {
	tasks = gcnew Task(gcnew Action<Object^>(this, &MainForm::RunReadyCheck), 100);
	resetEvent = gcnew ManualResetEvent(true);
	MutexReadyCheck = gcnew Mutex();
}
void MainForm::InitControls() {
	menuMain->Renderer = gcnew ToolStripProfessionalRenderer(gcnew ColorTable());
	labelSettedAddr->Text = "";
	CapturePlateLabel->Text = "";
	CapturePlateLabel->ForeColor = Color::Black;
	CapturePlateLabel->Text = "Плата не захвачена!";

	comboBoxAddressOY->Items->Add(10);
	for (int i = 1; i < 7; i++)
		comboBoxAddressOY->Items->Add(i);

	for (int i = 0; i < 8; i++)
		currentPlate->Items->Add(i);

	currentPlate->SelectedIndex = 0;
	modeSelector->SelectedIndex = 0;
	comboBoxAddressOY->SelectedIndex = 0;
}
void MainForm::TimerReadyCheck_Tick(System::Object^  sender, System::EventArgs^  e) {
	timeSpent++;
	currTimer->Text = DateTime((DateTime::Now - oldTime).Ticks).ToString("mm:ss", CultureInfo::InvariantCulture);
}
void MainForm::MyForm1_Resize(System::Object^  sender, System::EventArgs^  e) {
	dataGridViewBNA->Top = 200;
	dataGridViewBNA->Left = this->Width / 2;
	dataGridViewBNA->Width = this->Width / 2 - 20;

	dataGridViewMBPP->Top = 200;
	dataGridViewMBPP->Left = 8;
	dataGridViewMBPP->Width = this->Width / 2 - 20;

	this->WaitingAnswerLabel->Top = 165;
	this->WaitingAnswerLabel->Left = this->Width / 2 - 86;

	labelMBPP->Left = dataGridViewMBPP->Width / 2 - labelMBPP->Width;
	labelBNA->Left = dataGridViewBNA->Left + dataGridViewBNA->Width / 2 - labelBNA->Width;
}
void MainForm::MyForm1_Load(System::Object^  sender, System::EventArgs^  e) {
	stateMachine = gcnew FiniteStateMachine();
	FormManager::pathApp = Directory::GetCurrentDirectory();
	lockedFix = false;
	locked = false;
	stringBuilder = gcnew StringBuilder();
	oldCountMbpp = 0;
	InitThreading();
	InitControls();

	dataGridViewBNA->DataSource = dataSetTables->Tables["TableBNA"];
	dataGridViewMBPP->DataSource = dataSetTables->Tables["TableMBPP"];

	NaviStatus::GLC = false; // true - user, false - admin
}
void MainForm::exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}
void MainForm::currentPlateSelect(System::Object^  sender) {
	if (!comboBoxAddressOY->Focused)
		comboBoxAddressOY->Focus();
	stateMachine->NumPlate = Convert::ToInt32(((ComboBox^)sender)->Text);
	stateMachine->ProcessEvent(FiniteStateMachine::Events::CapturePlate);
	if (stateMachine->State == FiniteStateMachine::States::ErrorCapture) {
		CapturePlateLabel->Text = "Плата не захвачена!";
		CapturePlateLabel->ForeColor = Color::Red;
		//EnabledControlsAfterCheckCapturePlate(false);
	}
	else {
		CapturePlateLabel->Text = "Плата захвачена!";
		CapturePlateLabel->ForeColor = Color::Green;
		//EnabledControlsAfterCheckCapturePlate(true);
	}
}
void MainForm::currentPlate_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	currentPlateSelect(sender);
}
void MainForm::mode_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	if (modeSelector->SelectedIndex > 0) {
		PzForm ^p = gcnew PzForm();
		p->ShowDialog();
	}
}
void MainForm::LoadNewEfemsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	LoadEfemForm ^lf = gcnew LoadEfemForm();
	lf->ShowDialog();
}
void MainForm::comboBox3_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	stateMachine->Address = Convert::ToInt32(((ComboBox^)sender)->Text);
}
void MainForm::dataGridViewBNA_RowsAdded(System::Object^  sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^  e) {
	((DataGridView^)sender)->FirstDisplayedScrollingRowIndex = e->RowIndex;
}
//Обновление таблицы
void MainForm::UpdateDataGrids() {
	if (stateMachine->State == FiniteStateMachine::States::ErrorSend) {
		WaitingAnswerLabel->ForeColor = Color::Red;
		WaitingAnswerLabel->Text = "Отправка не успешна";
	}
	else {
		WaitingAnswerLabel->ForeColor = Color::Green;
		WaitingAnswerLabel->Text = "Отправка успешна";
		stringBuilder = gcnew StringBuilder();
		DataRow ^rowMbpp = dataSetTables->Tables["TableMBPP"]->NewRow();
		DataRow ^rowBna = dataSetTables->Tables["TableBNA"]->NewRow();
		for (int i = 0; i < stateMachine->LengthDataMass / 2 + 1; i++) {
			if (i < 6) {
				rowMbpp[i] = (int)stateMachine->ResponseMass[i];	//X Y Z Vx Vy Vz MBPP
				rowBna[i] = (int)stateMachine->ResponseMass[i + 9];	//X Y Z Vx Vy Vz BNA
			}
			else if (i == 6) {
				rowMbpp[i] = stateMachine->ResponseMass[i] & 0x000f;	  //Trust MBPP
				rowBna[i] = (stateMachine->ResponseMass[i] & 0xf000) >> 12; //Trust BNA
				SetsFlagsStatus(stateMachine->ResponseMass[i]);
			}
			else if (i == 7) {
				rowMbpp[i] = ((stateMachine->ResponseMass[i + 1] & 0xff00) >> 8) / 8;    //PDOP
				rowBna[i] = ((stateMachine->ResponseMass[i + 8] & 0xff00) >> 8) / 8;	 //GDOP
				NaviStatus::gloMbpp = (stateMachine->ResponseMass[i + 1] & 0xf);
				NaviStatus::gpsMbpp = (stateMachine->ResponseMass[i + 1] & 0xf0) >> 4;
				NaviStatus::gloBna = (stateMachine->ResponseMass[i + 8] & 0xf);
				NaviStatus::gpsBna = (stateMachine->ResponseMass[i + 8] & 0xf0) >> 4;
				if (NaviStatus::GLC) {
					NaviStatus::gloMbpp = GLGPC(NaviStatus::gloMbpp, NaviStatus::gpsMbpp, timeSpent);
					NaviStatus::gloBna = GLGPC(NaviStatus::gloBna, NaviStatus::gpsBna, timeSpent);
				}
				NavStatus(NaviStatus::gloMbpp, NaviStatus::gpsMbpp, NaviStatus::gloBna, NaviStatus::gpsBna);
				StatusAnswerMbpp(stateMachine->ResponseMass[i] & 0x00C0);
			}
			else if (i == 8) {
				rowMbpp[i] = oldCountMbpp;		//Count MBPP
				rowBna[i] = (stateMachine->ResponseMass[i - 1] & 0x3f00) >> 8;    //Count BNA
				StatusMbpp(stateMachine->ResponseMass[i - 1] & 0x003f);
			}
		}
		dataSetTables->Tables["TableMBPP"]->Rows->Add(rowMbpp);
		dataSetTables->Tables["TableBNA"]->Rows->Add(rowBna);
		dataGridViewMBPP->DataSource = dataSetTables->Tables["TableMBPP"];
		dataGridViewBNA->DataSource = dataSetTables->Tables["TableBNA"];
		logs->ToReadyCheckLog(dataSetTables, true, NaviStatus::gloMbpp, NaviStatus::gpsMbpp, NaviStatus::gloBna, NaviStatus::gpsBna);
	}
}
void MainForm::StatusMbpp(short newCount) {
	if (oldCountMbpp == newCount)
		flagMBPP->BackColor = Color::Red;
	else
		flagMBPP->BackColor = Color::Green;
	oldCountMbpp = newCount;
}
void MainForm::StatusAnswerMbpp(unsigned int state) {
	//RM
	if (((state & 0x0080) >> 7) == 0)
		flagRM->BackColor = Color::Green;
	else
		flagRM->BackColor = Color::Red;
	//RT
	if (((state & 0x0040) >> 6) == 0)
		flagRT->BackColor = Color::Green;
	else
		flagRT->BackColor = Color::Red;
}
void MainForm::EnableControlsArbitration(bool enabled) {
	groupBoxCapturePlate->Enabled = enabled;
	groupBoxExecuteCommands->Enabled = enabled;
	CmdBuGroupBox->Enabled = !enabled;
	menuMain->Enabled = enabled;
}
void MainForm::EnabledControlsAfterCheckCapturePlate(bool enabled)
{
	groupBoxExecuteCommands->Enabled = enabled;
	groupBoxReadyFire->Enabled = enabled;
	menuMain->Enabled = enabled;
	CmdBuGroupBox->Enabled = !enabled;
}
void MainForm::Button_ReadyCheck_Click(System::Object^  sender, System::EventArgs^  e) {
	if (Button_ReadyCheck->Checked) {
		logs = gcnew Logging("ReadyLog.txt");
		logs->WriteHeaders(dataSetTables);
		oldTime = DateTime::Now;
		timeSpent = 0;
		dataSetTables->Tables["TableMBPP"]->Rows->Clear();
		dataSetTables->Tables["TableBNA"]->Rows->Clear();
		EnableControlsArbitration(Button_ReadyCheck->Checked);
		TimerReadyCheck->Start();
		stateMachine->SetReadyConfig();
		if (tasks->Status == TaskStatus::RanToCompletion) {
			InitThreading();
			tasks->Start();
		}
		else if (tasks->Status == TaskStatus::Created)
			tasks->Start();
		else
			resetEvent->Set();
		((CheckBox^)sender)->Text = "Остановить";
	}
	else {
		try {
			Monitor::Enter(stateMachine, locked);
			resetEvent->Reset();
			((CheckBox^)sender)->Text = "Запустить";
		}
		finally{
			if (locked) {
				Monitor::Exit(stateMachine);
				locked = false;
			}
			logs->~Logging();
		}
		TimerReadyCheck->Stop();
		EnableControlsArbitration(Button_ReadyCheck->Checked);
	}
}
void MainForm::RunReadyCheck(Object ^ time) {
	MutexReadyCheck->WaitOne();
	while (true) {
		stateMachine->ProcessEvent(FiniteStateMachine::Events::ReadyOn);
		try {
			this->Invoke(gcnew DelegateUpdataForms(this, &MainForm::UpdateDataGrids));
		}
		catch (...) {
		}
		if (stateMachine->State == FiniteStateMachine::States::ErrorSend) {
			resetEvent->Reset();
			break;
		}
		Thread::Sleep((int)time);
		resetEvent->WaitOne();
	}
	MutexReadyCheck->ReleaseMutex();
}
void MainForm::ExecuteButton_Click(System::Object^  sender, System::EventArgs^  e) {
	//	if(stateMachine->State != FiniteStateMachine::States::ErrorCapture){
	switch (modeSelector->SelectedIndex) {
	case 0:
	{
		stateMachine->ProcessEvent(FiniteStateMachine::Events::SetAddr);
		break;
	}
	case 1:
	{
		stateMachine->ProcessEvent(FiniteStateMachine::Events::CalcPZ);
		break;
	}
	case 2:
	{
		stateMachine->ProcessEvent(FiniteStateMachine::Events::CalcPZ_Ef);
		if (stateMachine->State == FiniteStateMachine::States::EnterPZ_EF)
			flagHotStart->BackColor = Color::Green;
		else
			flagHotStart->BackColor = Color::Red;
		break;
	}
	}

	//	}
	if (stateMachine->State == FiniteStateMachine::States::ErrorSend || stateMachine->State == FiniteStateMachine::States::ErrorCapture) {
		WaitingAnswerLabel->ForeColor = Color::Red;
		WaitingAnswerLabel->Text = "Отправка не успешна";
	}
	else {
		WaitingAnswerLabel->ForeColor = Color::Green;
		WaitingAnswerLabel->Text = "Отправка успешна";
	}

}
void MainForm::saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Stream ^myStream;
	if (dataSetTables->IsInitialized) {
		if (saveFileDialogXML->ShowDialog() == ::DialogResult::OK) {
			if ((myStream = saveFileDialogXML->OpenFile()) != nullptr)
			{
				dataSetTables->WriteXml(myStream);
				myStream->Close();
			}
		}
	}
	else {
		MessageBox::Show(this, "Объект с данными поврежден или не инициализировался", "Ошибка!", MessageBoxButtons::OK);
	}
}
void MainForm::fixedCommand_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (fixedCommand->Checked) {
		try {
			Monitor::Enter(stateMachine, lockedFix);
			stateMachine->Fixed(6, FiniteStateMachine::Events::FixedOn);
		}
		finally{
			Monitor::Exit(stateMachine);
			lockedFix = false;
		}
	}
	else {
		try {
			Monitor::Enter(stateMachine, lockedFix);
			stateMachine->Fixed(5, FiniteStateMachine::Events::FixedOff);
		}
		finally{
			Monitor::Exit(stateMachine);
			lockedFix = false;
		}
	}
}

void MainForm::dataGridViewBNA_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->Control && e->KeyCode == Keys::U)
		CmdBuGroupBox->Visible = true;
	else if (e->Control && e->KeyCode == Keys::L)
		CmdBuGroupBox->Visible = false;
}

void MainForm::clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	dataSetTables->Tables["TableMBPP"]->Rows->Clear();
	dataSetTables->Tables["TableBNA"]->Rows->Clear();
}
void MainForm::SetsFlagsStatus(unsigned int st) {
	//FIX
	if (((st & 0x0800) >> 11) == 0)
		flagFIX->BackColor = Color::Green;
	else
		flagFIX->BackColor = Color::Red;
	//PZ
	if (((st & 0x0400) >> 10) == 0)
		flagPZ->BackColor = Color::Green;
	else
		flagPZ->BackColor = Color::Red;
	//GSN
	if (((st & 0x0200) >> 9) == 0)
		flagGSN->BackColor = Color::Green;
	else
		flagGSN->BackColor = Color::Red;
	//VM
	if (((st & 0x0100) >> 8) == 0)
		flagVM->BackColor = Color::Green;
	else
		flagVM->BackColor = Color::Red;
	//БИЧЭ
	if (((st & 0x00F0) >> 4) == 0)
		flagBICHE->BackColor = Color::Green;
	else
		flagBICHE->BackColor = Color::Red;
}
void MainForm::NavStatus(short mbppGLO, short mbppGPS, short bnaGLO, short bnaGPS) {
	NaviStatus::sumNaviBna = bnaGLO + bnaGPS;
	NaviStatus::sumNaviMbpp = mbppGLO + mbppGPS;

	mbppNumGLOCount->Text = Convert::ToString(mbppGLO);
	mbppNumGPSCount->Text = Convert::ToString(mbppGPS);

	bnaNumGLOCount->Text = Convert::ToString(bnaGLO);
	bnaNumGPSCount->Text = Convert::ToString(bnaGPS);

	mbppSumNavCount->Text = Convert::ToString(NaviStatus::sumNaviMbpp);
	bnaSumNavCount->Text = Convert::ToString(NaviStatus::sumNaviBna);

	if (mbppGLO > 0)
		mbppNumGLOCount->ForeColor = Color::Green;
	else
		mbppNumGLOCount->ForeColor = Color::Red;
	if (mbppGPS > 0)
		mbppNumGPSCount->ForeColor = Color::Green;
	else
		mbppNumGPSCount->ForeColor = Color::Red;

	if (bnaGLO > 0)
		bnaNumGLOCount->ForeColor = Color::Green;
	else
		bnaNumGLOCount->ForeColor = Color::Red;
	if (bnaGPS > 0)
		bnaNumGPSCount->ForeColor = Color::Green;
	else
		bnaNumGPSCount->ForeColor = Color::Red;

	if (NaviStatus::sumNaviMbpp >= 10)
		mbppSumNavCount->ForeColor = Color::Green;
	else
		mbppSumNavCount->ForeColor = Color::Red;
	if (NaviStatus::sumNaviBna >= 10)
		bnaSumNavCount->ForeColor = Color::Green;
	else
		bnaSumNavCount->ForeColor = Color::Red;
}
int MainForm::GLGPC(int currGLC, int currGPS, int time) {
	if (currGLC > 3) {
		return currGLC;
	}
	else {
		if (currGPS > 3) {
			if (time < 40) { //c
				return 1;
			}
			else if (time > 39 && time < 50) {
				return 2;
			}
			else if (time > 49 && time < 70) {
				return 3;
			}
			else if (time > 69 && time < 80) {
				return (4 + (gcnew Random())->Next(2));
			}
			else
				return 5;
		}
		else
			return 0;
	}

}
