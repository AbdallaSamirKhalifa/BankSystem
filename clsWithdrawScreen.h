#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsWithdrawScreen :
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

    static string _ReadAccountNumber() {
        string AccountNumber = clsInputValidate::ReadString("Enter AccountNumber: ");
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client With Account Number [" << AccountNumber;
            AccountNumber = clsInputValidate::ReadString("] Does Not Exist.\nPlease Enter Another AccountNumber: ");
        }
        return AccountNumber;
    }




public:

    static  void ShowWithdrawScreen() {

        _DrawScreenHeader("\t   Withdraw Screen");
        char Answer = 'n';

        string AccountNumber = _ReadAccountNumber();

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        float WithdrawAmount = 0;
        cout << "\nPlease Enter Withdraw Amount: ";
        WithdrawAmount = clsInputValidate::ReadFloatNumber();

        while (WithdrawAmount > Client.AccountBalance) {
            cout << "\nThe Amount Exceeds Your Balance, You Can Only Withdraw Up To :" << Client.AccountBalance << endl;
            cout << "\nPlease Enter Withdraw Amount: ";
            WithdrawAmount = clsInputValidate::ReadFloatNumber();
        }

        cout << "\nAre You Sure You Want To Perform This Transaction (Y/N)? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            if(Client.Withdraw(WithdrawAmount))
            {
                cout << "\nAmount Withdrawed Succefully.\n";
                cout << "\nNew Balance Is: " << Client.AccountBalance;
            }
            else {
                cout << "\nCannot Withdraw, Insuffecient Balance!\n";
                cout << "\nAmount To Withdraw Is: " << WithdrawAmount;
                cout << "\nAccount Balance Is: " <<Client.AccountBalance;

            }

        }
        else {
            cout << "\nOperation Was Cancelled!\n";

        }
    }

};

