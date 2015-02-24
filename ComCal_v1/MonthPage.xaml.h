//
// MonthPage.xaml.h
// Declaration of the MonthPage class
//

#pragma once

#include "MonthPage.g.h"
#include <time.h>
#include "ComCalManager.h"

namespace ComCal_v1
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MonthPage sealed
	{
	public:
		MonthPage();
		void setCalendarDate_MonthPage(void);
		

	private:
		ComCalManager^ StartComCal;

		const static int MAX_ASCTIME_S = 26;
		const static int DAYS_IN_WEEK = 7;
		const static int MONTHS_IN_YEAR = 12;
		const static int MAX_DAYS_IN_MONTH = 31;

		Platform::Collections::Vector<Windows::UI::Xaml::Controls::TextBlock^> monthDateVec;
		Platform::Collections::Vector<Windows::UI::Xaml::Controls::TextBlock^> monthTasksVec;

		void defaultView(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		bool isLeapYear(int);
		void storeDateTextBlockInVec();
		void storeTasksTextBlockInVec();
		Platform::String^ incrementStringDate(Platform::String^, int);
		void userEnterCom(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
		void MarshalstrToStr(Platform::String^, std::string&);
		Platform::String^ setMonthPageTitle(tm*);
		std::wstring getMonthStr(int);

	};
} 
