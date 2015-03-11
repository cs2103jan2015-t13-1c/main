#pragma once

#include <string>
#include "ComCalManager.h"

namespace ComCal_v01 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MonthForm
	/// </summary>
	public ref class MonthForm : public System::Windows::Forms::Form
	{
	public:
		MonthForm(int, array<String^>^);

	private:
		ComCalManager* _manager;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MonthForm()
		{
			if (components)
			{
				delete components;
			}

			delete _manager;
		}
		//Function to set the calendar----------------------------------------------------------------


		//--------------------------------------------------------------------------------------------

	private: System::Windows::Forms::TableLayoutPanel^  monthPanel;

	private: System::Windows::Forms::TextBox^  dayTxtBlkSun;
	private: System::Windows::Forms::TextBox^  dayTxtBlkSat;
	private: System::Windows::Forms::TextBox^  dayTxtBlkFri;
	private: System::Windows::Forms::TextBox^  dayTxtBlkThur;
	private: System::Windows::Forms::TextBox^  dayTxtBlkWed;
	private: System::Windows::Forms::TextBox^  dayTxtBlkTue;
	private: System::Windows::Forms::TextBox^  dayTxtBlkMon;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  userInputBox;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::TextBox^  textBox2;

	protected:

	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->monthPanel = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->dayTxtBlkSat = (gcnew System::Windows::Forms::TextBox());
			this->dayTxtBlkFri = (gcnew System::Windows::Forms::TextBox());
			this->dayTxtBlkThur = (gcnew System::Windows::Forms::TextBox());
			this->dayTxtBlkWed = (gcnew System::Windows::Forms::TextBox());
			this->dayTxtBlkTue = (gcnew System::Windows::Forms::TextBox());
			this->dayTxtBlkSun = (gcnew System::Windows::Forms::TextBox());
			this->dayTxtBlkMon = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->userInputBox = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->monthPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// monthPanel
			// 
			this->monthPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->monthPanel->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->monthPanel->ColumnCount = 7;
			this->monthPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28571F)));
			this->monthPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28572F)));
			this->monthPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28572F)));
			this->monthPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28572F)));
			this->monthPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28572F)));
			this->monthPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28572F)));
			this->monthPanel->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 14.28572F)));
			this->monthPanel->Controls->Add(this->dayTxtBlkSat, 6, 0);
			this->monthPanel->Controls->Add(this->dayTxtBlkFri, 5, 0);
			this->monthPanel->Controls->Add(this->dayTxtBlkThur, 4, 0);
			this->monthPanel->Controls->Add(this->dayTxtBlkWed, 3, 0);
			this->monthPanel->Controls->Add(this->dayTxtBlkTue, 2, 0);
			this->monthPanel->Controls->Add(this->dayTxtBlkSun, 0, 0);
			this->monthPanel->Controls->Add(this->dayTxtBlkMon, 1, 0);
			this->monthPanel->Controls->Add(this->textBox1, 0, 5);
			this->monthPanel->Controls->Add(this->tableLayoutPanel1, 0, 1);
			this->monthPanel->Enabled = false;
			this->monthPanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->monthPanel->Location = System::Drawing::Point(147, 31);
			this->monthPanel->Name = L"monthPanel";
			this->monthPanel->RowCount = 6;
			this->monthPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9.538284F)));
			this->monthPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 18.09234F)));
			this->monthPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 18.09234F)));
			this->monthPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 18.09234F)));
			this->monthPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 18.09234F)));
			this->monthPanel->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 18.09234F)));
			this->monthPanel->Size = System::Drawing::Size(586, 408);
			this->monthPanel->TabIndex = 0;
			// 
			// dayTxtBlkSat
			// 
			this->dayTxtBlkSat->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dayTxtBlkSat->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dayTxtBlkSat->Location = System::Drawing::Point(502, 4);
			this->dayTxtBlkSat->Name = L"dayTxtBlkSat";
			this->dayTxtBlkSat->ReadOnly = true;
			this->dayTxtBlkSat->Size = System::Drawing::Size(80, 19);
			this->dayTxtBlkSat->TabIndex = 6;
			this->dayTxtBlkSat->Text = L"Sat";
			this->dayTxtBlkSat->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// dayTxtBlkFri
			// 
			this->dayTxtBlkFri->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dayTxtBlkFri->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dayTxtBlkFri->Location = System::Drawing::Point(419, 4);
			this->dayTxtBlkFri->Name = L"dayTxtBlkFri";
			this->dayTxtBlkFri->ReadOnly = true;
			this->dayTxtBlkFri->Size = System::Drawing::Size(76, 19);
			this->dayTxtBlkFri->TabIndex = 5;
			this->dayTxtBlkFri->Text = L"Fri";
			this->dayTxtBlkFri->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->dayTxtBlkFri->TextChanged += gcnew System::EventHandler(this, &MonthForm::textBox5_TextChanged);
			// 
			// dayTxtBlkThur
			// 
			this->dayTxtBlkThur->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dayTxtBlkThur->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dayTxtBlkThur->Location = System::Drawing::Point(336, 4);
			this->dayTxtBlkThur->Name = L"dayTxtBlkThur";
			this->dayTxtBlkThur->ReadOnly = true;
			this->dayTxtBlkThur->Size = System::Drawing::Size(76, 19);
			this->dayTxtBlkThur->TabIndex = 4;
			this->dayTxtBlkThur->Text = L"Thu";
			this->dayTxtBlkThur->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// dayTxtBlkWed
			// 
			this->dayTxtBlkWed->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dayTxtBlkWed->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dayTxtBlkWed->Location = System::Drawing::Point(253, 4);
			this->dayTxtBlkWed->Name = L"dayTxtBlkWed";
			this->dayTxtBlkWed->ReadOnly = true;
			this->dayTxtBlkWed->Size = System::Drawing::Size(76, 19);
			this->dayTxtBlkWed->TabIndex = 3;
			this->dayTxtBlkWed->Text = L"Wed";
			this->dayTxtBlkWed->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// dayTxtBlkTue
			// 
			this->dayTxtBlkTue->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dayTxtBlkTue->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dayTxtBlkTue->Location = System::Drawing::Point(170, 4);
			this->dayTxtBlkTue->Name = L"dayTxtBlkTue";
			this->dayTxtBlkTue->ReadOnly = true;
			this->dayTxtBlkTue->Size = System::Drawing::Size(76, 19);
			this->dayTxtBlkTue->TabIndex = 2;
			this->dayTxtBlkTue->Text = L"Tue";
			this->dayTxtBlkTue->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// dayTxtBlkSun
			// 
			this->dayTxtBlkSun->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dayTxtBlkSun->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dayTxtBlkSun->Location = System::Drawing::Point(4, 4);
			this->dayTxtBlkSun->Name = L"dayTxtBlkSun";
			this->dayTxtBlkSun->ReadOnly = true;
			this->dayTxtBlkSun->Size = System::Drawing::Size(76, 19);
			this->dayTxtBlkSun->TabIndex = 0;
			this->dayTxtBlkSun->Text = L"Sun";
			this->dayTxtBlkSun->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->dayTxtBlkSun->TextChanged += gcnew System::EventHandler(this, &MonthForm::textBox1_TextChanged);
			// 
			// dayTxtBlkMon
			// 
			this->dayTxtBlkMon->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->dayTxtBlkMon->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->dayTxtBlkMon->Location = System::Drawing::Point(87, 4);
			this->dayTxtBlkMon->Name = L"dayTxtBlkMon";
			this->dayTxtBlkMon->ReadOnly = true;
			this->dayTxtBlkMon->Size = System::Drawing::Size(76, 19);
			this->dayTxtBlkMon->TabIndex = 1;
			this->dayTxtBlkMon->Text = L"Mon";
			this->dayTxtBlkMon->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Location = System::Drawing::Point(4, 335);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(76, 19);
			this->textBox1->TabIndex = 7;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				35.52632F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				64.47369F)));
			this->tableLayoutPanel1->Location = System::Drawing::Point(4, 43);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 31.81818F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 68.18182F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(76, 66);
			this->tableLayoutPanel1->TabIndex = 8;
			// 
			// userInputBox
			// 
			this->userInputBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(7) {
				L"add", L"edit", L"delete",
					L"show", L"redo", L"undo", L"search"
			});
			this->userInputBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Append;
			this->userInputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->userInputBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->userInputBox->Location = System::Drawing::Point(147, 482);
			this->userInputBox->Name = L"userInputBox";
			this->userInputBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->userInputBox->Size = System::Drawing::Size(586, 29);
			this->userInputBox->TabIndex = 1;
			this->userInputBox->TextChanged += gcnew System::EventHandler(this, &MonthForm::userInputBox_TextChanged);
			this->userInputBox->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MonthForm::userEnter);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Enabled = false;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->textBox2->Location = System::Drawing::Point(311, 6);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(255, 25);
			this->textBox2->TabIndex = 2;
			// 
			// MonthForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ClientSize = System::Drawing::Size(745, 523);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->userInputBox);
			this->Controls->Add(this->monthPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"MonthForm";
			this->Text = L"ComCal";
			this->monthPanel->ResumeLayout(false);
			this->monthPanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion  

	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {}
	private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {}
	private: System::Void userInputBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {}

	private: System::Void userEnter(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	}; //end MonthForm class
} //end of ComCal_v01 namespace