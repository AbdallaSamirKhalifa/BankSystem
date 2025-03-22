#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsFindCurrencyScreen :
    protected clsScreen
{
    enum enChoice{eCode=1,eCountry};
    static void _PrintCurrency(clsCurrency Currency)
    {

        cout << "\nCurrency Card:";
        cout << "\n______________________";
        cout << "\nCountry   :" << Currency.Country();
        cout << "\nCode      :" << Currency.CurrencyCode();
        cout << "\nName      :" << Currency.CurrencyName();
        cout << "\nRate(1$)  :" << Currency.Rate();
        cout << "\n______________________\n";


    }
   
    static void _FindCurrencyByCode() {
        string CurrencyCode = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");
        
        clsCurrency Currency = clsCurrency::FindByCode(clsString::upperAllString(CurrencyCode));
        if (!Currency.IsEmpty()) {
            cout << "\nCurrency Found.\n";
            _PrintCurrency(Currency);
        }
        else {
            cout << "\nCurrency Not Found!\n";
        }
    }
  
    static void _FindCurrencyByCountry() {
        string CountryName = clsInputValidate::ReadString("\nPlease Enter Country Name: ");
        
        clsCurrency Currency = clsCurrency::FindByCountry(clsString::upperAllString(CountryName));
        if (!Currency.IsEmpty()) {
            cout << "\nCurrency Found.\n";
            _PrintCurrency(Currency);
        }
        else {
            cout << "\nCurrency Not Found!\n";
        }
    }

public:
    static void ShowFindCurrencyScreen() {

        _DrawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind Currency By: [1] Code Or [2] Country: ";

        enChoice Choice = (enChoice)clsInputValidate::ReadShortNumberBetween(1,2);

        switch (Choice)
        {
        case clsFindCurrencyScreen::eCode:
            _FindCurrencyByCode();
            break;

        case clsFindCurrencyScreen::eCountry:
            _FindCurrencyByCountry();
            break;

        }
        
    }
};

