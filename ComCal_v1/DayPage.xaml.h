//
// DayPage.xaml.h
// Declaration of the DayPage class
//

#pragma once

#include "DayPage.g.h"
#include "ComCalManager.h"

namespace ComCal_v1
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class DayPage sealed
	{
	public:
		DayPage();
	private:
		void userEnterCom(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);

	};
}
