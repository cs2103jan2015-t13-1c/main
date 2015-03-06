//
// DayPage.xaml.cpp
// Implementation of the DayPage class
//

#include "pch.h"
#include "DayPage.xaml.h"

using namespace ComCal_v1;

using namespace Platform;
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

DayPage::DayPage()
{
	InitializeComponent();
}

void ComCal_v1::DayPage::userEnterCom(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey(VK_RETURN)){		

		userInputBox->Text = nullptr;
	}
}
