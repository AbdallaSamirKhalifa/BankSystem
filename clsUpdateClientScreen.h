#pragma once
#include "clsScreen.h"
#include "iomanip"
#include "clsBankClient.h"
class clsUpdateClientScreen :
    protected clsScreen
{
    enum enUpdate { FirstName = 1, LastName, PhoneNumber, AccountBalance, Email, PinCode, All };
   
    static void _ShowUpdateClientMenue() {
        short what = 0;
        system("cls");
        _DrawScreenHeader("\tUpdate Client Screen");
        cout << "\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\t            Update Menue          \n\n";
        cout << "\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\t  1-FirstName" << endl;
        cout << "\t\t\t\t\t  2-LastName" << endl;
        cout << "\t\t\t\t\t  3-Phone Number" << endl;
        cout << "\t\t\t\t\t  4-AccountBalance" << endl;
        cout << "\t\t\t\t\t  5-Email" << endl;
        cout << "\t\t\t\t\t  6-PinCode" << endl;
        cout << "\t\t\t\t\t  7-All Data" << endl;
        cout << "\t\t\t\t\t______________________________________\n";




    }

   static void _ReadClientInfo(clsBankClient& Client) {
        //clsBankClient client;


        Client.FirstName = clsInputValidate::ReadString("\nEnter First Name: ");
        Client.LastName = clsInputValidate::ReadString("\nEnter Last Name: ");
        Client.Email = clsInputValidate::ReadString("\nEnter Email: ");
        Client.Phone = clsInputValidate::ReadString("\nEnter Phone Number: ");
        Client.PinCode = clsInputValidate::ReadString("\nEnter Pin Code: ");
        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();

    }

   static void _PrintClientCard(clsBankClient Client) {
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

    static void _PerformUpdateOperation(clsBankClient& Client) {

        _ShowUpdateClientMenue();
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 7]? ";
        enUpdate update = (enUpdate)clsInputValidate::ReadShortNumberBetween(1, 7, "Enter Number between 1 to 7? ");

        system("cls");
        _DrawScreenHeader("\tUpdate Client Screen");
        _PrintClientCard(Client);
        cout << "\n\nUpdate Client Info:";
        cout << "\n_____________________________\n";

        if (update == All)
        {
            _ReadClientInfo(Client);
            return;
        }
        switch (update)
        {
        case FirstName:
            Client.FirstName = clsInputValidate::ReadString("\nEnter First Name: ");
            return;
        case LastName:
            Client.LastName = clsInputValidate::ReadString("\nEnter Last Name: ");
            return;
        case PhoneNumber:
            Client.Phone = clsInputValidate::ReadString("\nEnter Phone Number: ");
            return;
        case AccountBalance:
            cout << "\nEnter Account Balance: ";
            Client.AccountBalance = clsInputValidate::ReadFloatNumber();
            return;
        case Email:
            Client.Email = clsInputValidate::ReadString("\nEnter Email: ");
            return;
        case PinCode:
            Client.PinCode = clsInputValidate::ReadString("\nEnter Pin Code: ");
            return;

        }


    }

public:
    static void ShowUpdateClientScreen()
    {

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = clsInputValidate::
            ReadString("Please Enter Client Account Number: ");
        char Answer = 'n';

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::
                ReadString("\nAccount Number Doesn't Exist Please Enter Another Account Number: ");

        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);
        cout << "Are You Sure You Want To Update This Client Y/N: ";
        cin >> Answer;

        if (toupper(Answer)=='Y')

        {
            _PerformUpdateOperation(Client);

            clsBankClient::enSaveResult SaveResult;
            SaveResult = Client.Save();

            switch (SaveResult)
            {
            case clsBankClient::svSucceeded:
            {
                cout << "\nAccount Updated Successfully.\n";
                _PrintClientCard(Client);

                break;
            }
            case clsBankClient::svFailedEmptyObject:
                cout << "\nError Account Was Not Saved Becouse It's Empty.\n";
                break;

            }
        }

    }


};

