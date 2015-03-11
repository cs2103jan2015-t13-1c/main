#include "MonthForm.h"
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal.h>

using namespace ComCal_v01;
using namespace System;
using namespace System::Windows::Forms;

MonthForm::MonthForm(int argc, array<String^>^ argv)
{
	InitializeComponent();

	_manager = new ComCalManager();
}


System::Void MonthForm::userEnter(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	String^ feedBack;

	if (e->KeyCode == Keys::Enter){
		feedBack = _manager->deduceCommand(userInputBox->Text);

		userInputBox->Text = nullptr;
	}
}
