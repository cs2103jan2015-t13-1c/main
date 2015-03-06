//
// MonthPage.xaml.cpp
// Implementation of the MonthPage class
//

#include "pch.h"
#include "MonthPage.xaml.h"
#include <time.h>
#include <string>
#include "ComCalManager.h"
#include <wchar.h>
#include <sstream>
#include <fstream>

using namespace ComCal_v1;

using namespace Platform;
using namespace Platform::Runtime::InteropServices;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MonthPage::MonthPage()
{
	InitializeComponent();

	storeDateTextBlockInVec();
	storeTasksTextBlockInVec();

	StartComCal = ref new ComCalManager();
	defaultView(nullptr, nullptr);
}

void ComCal_v1::MonthPage::setCalendarDate_MonthPage(void){
	struct tm * newtime = new tm();
	__time32_t * long_time = new __time32_t();

	String^ dateNum = "1";
	std::string monthTitleStr;
	int daysInMonth[MONTHS_IN_YEAR] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	_time32(long_time);
	_localtime32_s(newtime, long_time);

	newtime->tm_mday = 1;;
	mktime(newtime);

	//set the title
	MonthPageTitle->Text = setMonthPageTitle(newtime);

	//February has 29 days during a leap year
	if ((newtime->tm_mon == 1) && isLeapYear(newtime->tm_year + 1900)){
		daysInMonth[1] = 29;
	}

	//sets remaining dates on the month grid
	for (int i = newtime->tm_wday; i < (newtime->tm_wday + daysInMonth[newtime->tm_mon]); ++i){
		monthDateVec.GetAt(i)->Text = dateNum;

		dateNum = incrementStringDate(dateNum, 1);
	}

}

String^ MonthPage::incrementStringDate(String^ dateNum, int incrementSize){
	std::wstring dateNumStr(dateNum->Data());
	std::wstringstream convert;

	int dateNumInt;

	convert << dateNumStr;
	convert >> dateNumInt;

	dateNumInt += incrementSize;
	dateNum = dateNumInt.ToString();

	return dateNum;
}


bool ComCal_v1::MonthPage::isLeapYear(int year)
{
	bool isLeap = false;

	if (year % 4 != 0){
		isLeap = false;
	}
	else{
		if (year % 100 != 0){
			isLeap = true;
		}
		else{
			if (year % 400 != 0){
				isLeap = false;
			}
			else{
				isLeap = true;
			}
		}
	}

	return isLeap;
}

Platform::String^ MonthPage::setMonthPageTitle(tm * newtime){
	int currentYear = newtime->tm_year + 1900;
	std::wstring yearStr;
	std::wstring title;

	std::wstringstream convert;
	convert << currentYear;
	yearStr = convert.str();

	title += getMonthStr(newtime->tm_mon);
	title += L" ";
	title += yearStr;

	Platform::String^ titleStr = ref new String(title.c_str());

	return titleStr;
}

void ComCal_v1::MonthPage::defaultView(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	setCalendarDate_MonthPage();
}

std::wstring ComCal_v1::MonthPage::getMonthStr(int iter){
	const static std::wstring MONTHS[MONTHS_IN_YEAR] = { L"January", L"February", L"March", L"April", L"May", 
	L"June", L"July", L"August", L"September", L"October", L"November", L"December" };

	return MONTHS[iter];
}

void ComCal_v1::MonthPage::userEnterCom(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey(VK_RETURN)){
		StartComCal->deduceCommand(userInputBox->Text);

		userInputBox->Text = nullptr;
	}
}

void ComCal_v1::MonthPage::storeDateTextBlockInVec(){
	int i = 0;

	monthDateVec.InsertAt(i, monthDate_grid11);
	monthDateVec.InsertAt(++i, monthDate_grid12);
	monthDateVec.InsertAt(++i, monthDate_grid13);
	monthDateVec.InsertAt(++i, monthDate_grid14);
	monthDateVec.InsertAt(++i, monthDate_grid15);
	monthDateVec.InsertAt(++i, monthDate_grid16);
	monthDateVec.InsertAt(++i, monthDate_grid17);

	monthDateVec.InsertAt(++i, monthDate_grid21);
	monthDateVec.InsertAt(++i, monthDate_grid22);
	monthDateVec.InsertAt(++i, monthDate_grid23);
	monthDateVec.InsertAt(++i, monthDate_grid24);
	monthDateVec.InsertAt(++i, monthDate_grid25);
	monthDateVec.InsertAt(++i, monthDate_grid26);
	monthDateVec.InsertAt(++i, monthDate_grid27);

	monthDateVec.InsertAt(++i, monthDate_grid31);
	monthDateVec.InsertAt(++i, monthDate_grid32);
	monthDateVec.InsertAt(++i, monthDate_grid33);
	monthDateVec.InsertAt(++i, monthDate_grid34);
	monthDateVec.InsertAt(++i, monthDate_grid35);
	monthDateVec.InsertAt(++i, monthDate_grid36);
	monthDateVec.InsertAt(++i, monthDate_grid37);

	monthDateVec.InsertAt(++i, monthDate_grid41);
	monthDateVec.InsertAt(++i, monthDate_grid42);
	monthDateVec.InsertAt(++i, monthDate_grid43);
	monthDateVec.InsertAt(++i, monthDate_grid44);
	monthDateVec.InsertAt(++i, monthDate_grid45);
	monthDateVec.InsertAt(++i, monthDate_grid46);
	monthDateVec.InsertAt(++i, monthDate_grid47);

	monthDateVec.InsertAt(++i, monthDate_grid51);
	monthDateVec.InsertAt(++i, monthDate_grid52);
	monthDateVec.InsertAt(++i, monthDate_grid53);
	monthDateVec.InsertAt(++i, monthDate_grid54);
	monthDateVec.InsertAt(++i, monthDate_grid55);
	monthDateVec.InsertAt(++i, monthDate_grid56);
	monthDateVec.InsertAt(++i, monthDate_grid57);
}

void ComCal_v1::MonthPage::storeTasksTextBlockInVec(){
	int i = 0;

	monthTasksVec.InsertAt(i, date_tasks11);
	monthTasksVec.InsertAt(++i, date_tasks12);
	monthTasksVec.InsertAt(++i, date_tasks13);
	monthTasksVec.InsertAt(++i, date_tasks14);
	monthTasksVec.InsertAt(++i, date_tasks15);
	monthTasksVec.InsertAt(++i, date_tasks16);
	monthTasksVec.InsertAt(++i, date_tasks17);

	monthTasksVec.InsertAt(++i, date_tasks21);
	monthTasksVec.InsertAt(++i, date_tasks22);
	monthTasksVec.InsertAt(++i, date_tasks23);
	monthTasksVec.InsertAt(++i, date_tasks24);
	monthTasksVec.InsertAt(++i, date_tasks25);
	monthTasksVec.InsertAt(++i, date_tasks26);
	monthTasksVec.InsertAt(++i, date_tasks27);

	monthTasksVec.InsertAt(++i, date_tasks31);
	monthTasksVec.InsertAt(++i, date_tasks32);
	monthTasksVec.InsertAt(++i, date_tasks33);
	monthTasksVec.InsertAt(++i, date_tasks34);
	monthTasksVec.InsertAt(++i, date_tasks35);
	monthTasksVec.InsertAt(++i, date_tasks36);
	monthTasksVec.InsertAt(++i, date_tasks37);

	monthTasksVec.InsertAt(++i, date_tasks41);
	monthTasksVec.InsertAt(++i, date_tasks42);
	monthTasksVec.InsertAt(++i, date_tasks43);
	monthTasksVec.InsertAt(++i, date_tasks44);
	monthTasksVec.InsertAt(++i, date_tasks45);
	monthTasksVec.InsertAt(++i, date_tasks46);
	monthTasksVec.InsertAt(++i, date_tasks47);

	monthTasksVec.InsertAt(++i, date_tasks51);
	monthTasksVec.InsertAt(++i, date_tasks52);
	monthTasksVec.InsertAt(++i, date_tasks53);
	monthTasksVec.InsertAt(++i, date_tasks54);
	monthTasksVec.InsertAt(++i, date_tasks55);
	monthTasksVec.InsertAt(++i, date_tasks56);
	monthTasksVec.InsertAt(++i, date_tasks57);
}
