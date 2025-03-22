#pragma once
#include "clsScreen.h"
#include "clsUsers.h"
#include "iomanip"
class clsFindUserScreen :
    protected clsScreen
{

    static void _PrintUserCard(clsUsers User) {
        cout << "\nUser Card:";
        cout << "\n______________________";
        cout << "\nFirstName     :" << User.FirstName;
        cout << "\nLastName      :" << User.LastName;
        cout << "\nFullName      :" << User.FullName();
        cout << "\nEmail         :" << User.Email;
        cout << "\nPhone         :" << User.Phone;
        cout << "\nUserName      :" << User.UserName;
        cout << "\nPassword      :" << User.Password;
        cout << "\nPermission    :" << User.Permissions;
        cout << "\n______________________\n";
    }


public:
    static void ShowFindUserScreen() {
        _DrawScreenHeader("\t  Find User Screen");
        string UserName = clsInputValidate::ReadString("Enter UserName: ");
        char Answer = 'n';

        while (!clsUsers::IsUserExist(UserName))
        {
            UserName = clsInputValidate::ReadString("User Not Found, Please Enter Another UserName: ");
        }
        clsUsers User = ::clsUsers::Find(UserName);

        if (!User.IsEmpty()) {
            cout << "\nUser Found.\n";
            _PrintUserCard(User);
        }
        else {
            cout << "\nUser Not Found!\n";

        }
        
    }
};

