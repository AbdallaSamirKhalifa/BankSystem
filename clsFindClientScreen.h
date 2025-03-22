#pragma once
#include "clsScreen.h"
#include "clsScreen.h"
#include "clsBankClient.h"
class clsFindClientScreen :
    protected clsScreen
{
    static void _PrintClient(clsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFirstName     :" << Client.FirstName;
        cout << "\nLastName      :" << Client.LastName;
        cout << "\nFullName      :" << Client.FullName();
        cout << "\nEmail         :" << Client.Email;
        cout << "\nPhone         :" << Client.Phone;
        cout << "\nAcc. Number   :" << Client.AccountNumber();
        cout << "\nPassword      :" << Client.PinCode;
        cout << "\nBalance       :" << Client.AccountBalance;
        cout << "\n______________________\n";
    }

public:
    static void ShowFindClientScreen() {
        _DrawScreenHeader("\t  Find Client Screen");
        string AccountNumber = clsInputValidate::ReadString("Enter AccountNumber: ");
        char Answer = 'n';

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("AccountNumber Not Found, Please Enter Another AccountNumber: ");
        }
        clsBankClient Client = ::clsBankClient::Find(AccountNumber);

        if (!Client.IsEmpty()) {
            cout << "\nClient Found.\n";
            _PrintClient(Client);
        }
        else {
            cout << "\nClient Not Found!\n";
            
        }

    }
};

