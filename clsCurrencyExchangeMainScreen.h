#pragma once
#include "clsScreen.h"
#include "iomanip"
#include "clsCurrency.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyExchangeMainScreen :
    protected clsScreen
{
    enum enCurrencyMenueOption{eListCurrencies=1,eFindCurrency,eUpdateCurrencyRate,eCurrencyCalculator,eMainMenue};
   
    static short _ReadCurrencyMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrenciesMenue() {

        cout << setw(37) << left << "" << "\n\t\t\t\t    Press any key to go back to Currencies Menue...\n";

        system("pause>0");
        ShowCurrenciesMenue();
    }

    static void _ShowCurrenciesListScreen() {
        //cout << "\nCurrencies List Screen Will Be Here\n";
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }
    
    static void _ShowFindCurrencyScreen() {
        //cout << "\nFind Currency Screen Will Be Here\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    
    static void _ShowUpdateRateScreen()  {
        //cout << "\nUpdate Rate Screen Will Be Here\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    
    static void _ShowCurrencyCalculatorScreen() {
        //cout << "\nCurrencies Calculator Screen Will Be Here\n";

            clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
 

    }

    static void _PerformCurrencyMenueOption(enCurrencyMenueOption CurrencyMenueOption) {
        switch (CurrencyMenueOption)
        {
        case clsCurrencyExchangeMainScreen::eListCurrencies:
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenue();
            break;
        case clsCurrencyExchangeMainScreen::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;
        case clsCurrencyExchangeMainScreen::eUpdateCurrencyRate:
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrenciesMenue();
            break;
        case clsCurrencyExchangeMainScreen::eCurrencyCalculator:
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenue();
            break;
        case clsCurrencyExchangeMainScreen::eMainMenue:
            break;
        default:
            break;
        }
    }

public:
    static void ShowCurrenciesMenue()
    {

        system("cls");
        _DrawScreenHeader("   Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t  [1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t  [2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t  [3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t  [4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t  [5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyMenueOption((enCurrencyMenueOption)_ReadCurrencyMenueOption());
    }
};

