#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsUpdateCurrencyRateScreen :
    protected clsScreen
{

    static string _ReadCurrencyCode() {
        string Code = clsInputValidate::ReadString("Please Enter Currency Code: ");
        while (!clsCurrency::IsCurrencyExist(clsString::upperAllString(Code))) {

            cout << "Currency Not Found,";
            Code = clsInputValidate::ReadString("Please Enter Another Currency Code: ");

        }
        return Code;
    }

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

    static float _ReadRate() {

        cout << "\nEnter New Rate: ";
        float NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;


    }

public:

    static void ShowUpdateCurrencyRateScreen() {

        _DrawScreenHeader("\t Update Currency Screen");
        char Answer = 'n';
        string Code = _ReadCurrencyCode();

        clsCurrency Currency = clsCurrency::FindByCode(clsString::upperAllString(Code));
        _PrintCurrency(Currency);

        cout << "\nAre You Sure You Want To Update This Currency Y/N: ";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            cout << "\n\nUpdate Currency Rate:" << endl;
            cout << "________________________\n";

            Currency.UpdateRate(_ReadRate());

            cout << "\n Currency Rate Updated Successfuly \n";
            _PrintCurrency(Currency);
        }
        else {
            cout << "\nOperation Was Cancelled\n";
        }
    }

};

