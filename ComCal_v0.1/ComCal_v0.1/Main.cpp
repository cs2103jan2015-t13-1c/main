#include "MonthForm.h"

using namespace ComCal_v01;
using namespace System;
using namespace System::Windows::Forms;

int main (array<String^>^ fileNames) {
	int numOfSpecifiedFiles = fileNames->Length;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MonthForm form(numOfSpecifiedFiles, fileNames);
	Application::Run(%form);

	return 0;
}