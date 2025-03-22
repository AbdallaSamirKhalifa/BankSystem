#pragma once
#include "clsScreen.h"
#include "iomanip"
#include "clsUsers.h"
class clsLoginRegisterScreen :
    protected clsScreen
{
private:
    static void _PrintLogRecordLine(clsUsers::stLoginRegisterRecord LogRecord) {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LogRecord.DateTime
            << "| " << setw(20) << left << LogRecord.UserName
            << "| " << setw(20) << left << LogRecord.Password
            << "| " << setw(10) << left << LogRecord.Permission;
    }

public:
    static void ShowLogRecordScreen() {

        vector<clsUsers::stLoginRegisterRecord> vLogRecord;
        vLogRecord = clsUsers::GetLoginRegisterList();
        string Title = "\t  Login Register List Screen";
        string SubTitle = "\t    (" + to_string(vLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        if (vLogRecord.size() == 0)
            cout << "\t\t\t\tNo Record Available In the System!";
        else

            for (clsUsers::stLoginRegisterRecord Record : vLogRecord)
            {

                _PrintLogRecordLine(Record);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

    }
};

