﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class TextBlock;
                ref class Grid;
                ref class TextBox;
            }
        }
    }
}

namespace ComCal_v1
{
    partial ref class MonthPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::TextBlock^ MonthPageTitle;
        private: ::Windows::UI::Xaml::Controls::Grid^ MonthGrid;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ helperBlock;
        private: ::Windows::UI::Xaml::Controls::TextBox^ userInputBox;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ feedbackBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ commandHelpSheet;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthPage_Day1;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthPage_Day2;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthPage_Day3;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthPage_Day4;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthPage_Day5;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthPage_Day6;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthPage_Day7;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid11;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid12;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid13;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid14;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid15;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid16;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid17;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid21;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid22;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid23;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid24;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid25;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid26;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid27;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid31;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid32;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid33;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid34;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid35;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid36;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid37;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid41;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid42;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid43;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid44;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid45;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid46;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid47;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid51;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid52;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid53;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid54;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid55;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid56;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ monthDate_grid57;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks11;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks12;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks13;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks14;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks15;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks16;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks17;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks21;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks22;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks23;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks24;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks25;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks26;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks27;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks31;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks32;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks33;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks34;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks35;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks36;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks37;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks41;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks42;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks43;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks44;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks45;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks46;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks47;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks51;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks52;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks53;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks54;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks55;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks56;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ date_tasks57;
    };
}
