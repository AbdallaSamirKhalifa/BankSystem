#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
class clsCurrencyCalculatorScreen :
    protected clsScreen
{
    static string _ReadCurrencyCode(string message) {
        string Code = clsInputValidate::ReadString(message);
        while (!clsCurrency::IsCurrencyExist(clsString::upperAllString(Code))) {

            cout << "Currency Not Found,";
            Code = clsInputValidate::ReadString("Please Enter Another Currency Code: ");

        }
        return Code;
    }

    static void _PrintCurrency(clsCurrency Currency,string Message)
    {

        cout << Message;
        cout << "\n______________________";
        cout << "\nCountry   :" << Currency.Country();
        cout << "\nCode      :" << Currency.CurrencyCode();
        cout << "\nName      :" << Currency.CurrencyName();
        cout << "\nRate(1$)  :" << Currency.Rate();
        cout << "\n______________________\n";


    }

    static float _ReadExchangeAmount() {

        cout << "\nEnter Amount To Exchange: ";
        float NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;


    }

    static clsCurrency _GetCurrency(string Message) {
        string Code = clsString::upperAllString(_ReadCurrencyCode(Message));

        clsCurrency Currency = clsCurrency::FindByCode(Code);
        return Currency;
    }

    static void _PrinCalculatioResult(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo) {
           

        _PrintCurrency(CurrencyFrom, "\nConvert From:");

        float AmountToUSD = CurrencyFrom.ConvertToUSD(Amount);

        cout << endl << Amount << " " << CurrencyFrom.CurrencyCode()<< 
            " = " << AmountToUSD << " " << "USD" << endl;

        if (CurrencyTo.CurrencyCode() == "USD") 
            return;

        _PrintCurrency(CurrencyTo, "\nConverting From USD To:");
        cout << endl << Amount << " " << CurrencyFrom.CurrencyCode() << " = " <<
            CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo) << " " << CurrencyTo.CurrencyCode() << endl;

        
    }

public:
    
    static void ShowCurrencyCalculatorScreen() {
        char Continue = 'Y';

        while(toupper(Continue)=='Y')
        {
            system("cls");
            _DrawScreenHeader("\tCurrency Calculator Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadExchangeAmount();

            _PrinCalculatioResult(Amount, CurrencyFrom, CurrencyTo);

            cout << "\nDo You Want To Perform Another Calculation Y/N: ";
            cin >> Continue;
        }


    }

};

