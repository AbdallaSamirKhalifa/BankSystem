#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsDeleteClientScreen :
    protected clsScreen
{
private:
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
    static void ShowDeleteClientScreen() {

        _DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = clsInputValidate::ReadString("Enter AccountNumber: ");
        char Answer = 'n';

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("AccountNumber Does Not Exist, Please Enter Another AccountNumber: ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nAre You Sure You Want To Delete This Client Y/N: ";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            if (Client.Delete()) {
                cout << "\nAccount Deleted Successfully " << endl;
                _PrintClient(Client);

            }
            else {
                cout << "\n Error Account Was Not Deleted Some Error Accured Please Try Again Later!" << endl;
            }
        }
    }
};


