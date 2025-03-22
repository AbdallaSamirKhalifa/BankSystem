#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransferScreen :
    public clsScreen
{
    static void _PrintClient(clsBankClient Client) {
        cout << "\nClient Card:";
        cout << "\n______________________";
        cout << "\nFullName      :" << Client.FullName();
        cout << "\nAcc. Number   :" << Client.AccountNumber();
        cout << "\nBalance       :" << Client.AccountBalance;
        cout << "\n______________________\n";
    }

    static string _ReadAccountNumber(string Message) {
        string AccountNumber = clsInputValidate::ReadString(Message);
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client With Account Number [" << AccountNumber;
            AccountNumber = clsInputValidate::ReadString("] Does Not Exist.\nPlease Enter Another AccountNumber: ");
        }
        return AccountNumber;
    }

    static float _ReadAmount(clsBankClient SourceClient) {
        float TransferAmount = 0;
        cout << "\nPlease Enter Transfer Amount: ";
        TransferAmount = clsInputValidate::ReadFloatNumber();

        while (TransferAmount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds Avilable Balance, Enter Another Amount: ";
            TransferAmount = clsInputValidate::ReadFloatNumber();
        }
        return TransferAmount;
    }
public:
    static  void ShowTransferScreen() {

        _DrawScreenHeader("\t  Transfer Screen");
        char Answer = 'n';

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("Please Enter Account Number To Transfer From: "));
        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("Please Enter Account Number To Transfer To: "));
        _PrintClient(DestinationClient);

        float TransferAmount = _ReadAmount(SourceClient);

        cout << "\nAre You Sure You Want To Perform This Transaction (Y/N)? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            
            if (SourceClient.Transfer(TransferAmount, DestinationClient)) {
                cout << "\nAmount Transferd Succefully.\n";
            }
            else {

                cout << "\nOperation Was Not Done Amount Exceeds Balance!\n";
            }

        }
        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    }

};

