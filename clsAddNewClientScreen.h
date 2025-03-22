#pragma once
#include "clsScreen.h"
#include "iomanip"
#include "clsBankClient.h"
class clsAddNewClientScreen:protected clsScreen
{
private:
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



public:
   static void ShowAddNewClientScreen() {

       _DrawScreenHeader("\t  Add New Client Screen");

        string AccontNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");
        while (clsBankClient::IsClientExist(AccontNumber)) {
            AccontNumber = clsInputValidate::ReadString("\nAccount Already Used, Please Enter Another Account Number: ");
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccontNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResult SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::svFailedEmptyObject:
            cout << "\nError Account Was Not Saved Becouse It's Empty.\n";
            break;
        case clsBankClient::svSucceeded:
            system("cls");
            cout << "\nAccount Added Successfully.\n";
            _PrintClientCard(NewClient);
            break;
        case clsBankClient::svFailedAccountNumberExist:
            cout << "\nError Account Already In Use.\n";

            break;

        }


    }

};

