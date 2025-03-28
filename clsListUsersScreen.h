#pragma once
#include "clsScreen.h"
#include "clsUsers.h"
#include "iomanip"
class clsListUsersScreen :
    protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUsers User) {
        cout << setw(8) << left << "" << "| " << setw(15) << left << User.UserName
            << "| " << setw(20) << left << User.FullName()
            << "| " << setw(12) << left << User.Phone
            << "| " << setw(20) << left << User.Email
            << "| " << setw(10) << left << User.Password
            << "| " << setw(12) << left << User.Permissions;
    }

public:
    static void ShowUsersList() {

        vector<clsUsers> vUsers;
        vUsers = clsUsers::GetUsersList();
        string Title = "\t  Users List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUsers User : vUsers)
            {

                _PrintUserRecordLine(User);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

    }

};

