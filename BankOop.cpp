
#include <iostream>
#include "clsLoginScreen.h"
#include "clsCurrency.h"

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

int main()
{
    //clsCurrency Currency = Currency.FindByCode("jod");

    //if (Currency.IsEmpty()) {
    //    cout << "\nCurrency Is Not Found!\n";
    //}
    //else {
    //    _PrintCurrency(Currency);
    //}

    //clsCurrency Currency2 = Currency2.FindByCountry("Egypt");

    //if (Currency2.IsEmpty()) {
    //    cout << "\nCurrency Is Not Found!\n";
    //}
    //else {
    //    _PrintCurrency(Currency2);
    //}

    //    cout << "\nCurrency After Updating Rate\n";
    //    Currency2.UpdateRate(50);
    //    _PrintCurrency(Currency2);

    //
    while (clsLoginScreen::ShowLoginScreen())
    {
        continue;
    }
    system("pause>0");
}



