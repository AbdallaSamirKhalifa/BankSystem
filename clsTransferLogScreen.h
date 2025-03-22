#pragma once
#include "clsScreen.h"
#include "iomanip"
#include "clsBankClient.h"
class clsTransferLogScreen :
    protected clsScreen
{
private:
    static void _PrintTransferRecordLine(clsBankClient::stTransferLogRecord LogRecord) {

        cout << setw(8) << left << "" << "| " << setw(23) << left << LogRecord.DateTime
            << "| " << setw(10) << left << LogRecord.SourceAccountNumber
            << "| " << setw(10) << left << LogRecord.DestinationAccountNumber
            << "| " << setw(10) << left << LogRecord.TransferAmount
            << "| " << setw(10) << left << LogRecord.SrcBalanceAfter
            << "| " << setw(10) << left << LogRecord.DesBalanceAfter
            << "| " << setw(10) << left << LogRecord.UserName;
    }

public:
    static void ShowTransferLogScreen() {

        vector<clsBankClient::stTransferLogRecord> vTransferLogRecord;
        vTransferLogRecord = clsBankClient::GetTransferLogList();

        string Title = "\t  Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Acct";
        cout << "| " << left << setw(10) << "D.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
            {

                _PrintTransferRecordLine(Record);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

    }
};

