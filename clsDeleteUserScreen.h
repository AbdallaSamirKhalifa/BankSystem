#pragma once
#include "clsScreen.h"
#include "clsUsers.h"
class clsDeleteUserScreen :
    protected clsScreen
{

private:
    static void _PrintUser(clsUsers User) {
        cout << "\nUser Card:";
        cout << "\n______________________";
        cout << "\nFirstName     :" << User.FirstName;
        cout << "\nLastName      :" << User.LastName;
        cout << "\nFullName      :" << User.FullName();
        cout << "\nEmail         :" << User.Email;
        cout << "\nPhone         :" << User.Phone;
        cout << "\nAcc. Number   :" << User.UserName;
        cout << "\nPassword      :" << User.Password;
        cout << "\nBalance       :" << User.Permissions;
        cout << "\n______________________\n";
    }


public:
    static void ShowDeleteUserScreen() {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = clsInputValidate::ReadString("Enter UserName: ");
        char Answer = 'n';

        while (!clsUsers::IsUserExist(UserName))
        {
            UserName = clsInputValidate::ReadString("User Is Not Found, Please Enter Another UserName: ");
        }

        clsUsers User = clsUsers::Find(UserName);
        _PrintUser(User);

        cout << "\nAre You Sure You Want To Delete This User Y/N: ";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            if (User.Delete()) {
                cout << "\nUser Deleted Successfully." << endl;
                //_PrintUser(User);

            }
            else {
                cout << "\n Error Account Was Not Deleted Some Error Accured Please Try Again Later!" << endl;
            }
        }
    }
};

