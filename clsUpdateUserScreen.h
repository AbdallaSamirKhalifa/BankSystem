#pragma once
#include "clsScreen.h"
#include "clsUsers.h"
#include "iomanip"
class clsUpdateUserScreen :
    protected clsScreen
{

 


    static int _ReadPermisionsToSet() {
        char Answer = 'n';
        int Permissions = 0;

        cout << "\nDo You Want To Give Full Access(Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            return -1;

        cout << "\nDo You Want To Give Access To :\n";
        cout << "\nShow Client List (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions += clsUsers::pListClient;

        cout << "\nAdd New Client (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions += clsUsers::pAddNewClient;

        cout << "\nDelete Client (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions += clsUsers::pDeleteClient;

        cout << "\nUpdate Client (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions += clsUsers::pUpdateClient;

        cout << "\nFind Client (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions += clsUsers::pFindClient;

        cout << "\nTransacation (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions += clsUsers::pTransactions;

        cout << "\nManage Users (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions += clsUsers::pManageUsers;

        return Permissions;

    }

    static void _ReadUserInfo(clsUsers& User) {

        User.FirstName = clsInputValidate::ReadString("\nEnter First Name: ");
        User.LastName = clsInputValidate::ReadString("\nEnter Last Name: ");
        User.Email = clsInputValidate::ReadString("\nEnter Email: ");
        User.Phone = clsInputValidate::ReadString("\nEnter Phone Number: ");
        User.Password = clsInputValidate::ReadString("\nEnter Password: ");
        User.Permissions = _ReadPermisionsToSet();

    }

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
    static void ShowUpdateUserScreen()
    {

        _DrawScreenHeader("\t Update User Screen");

        string UserName = clsInputValidate::
            ReadString("Please Enter UserName: ");
        char Answer = 'n';

        while (!clsUsers::IsUserExist(UserName))
        {
            UserName = clsInputValidate::
                ReadString("\nUser Not Found, Please Enter Another UserName: ");

        }

        clsUsers User = clsUsers::Find(UserName);
        _PrintUserCard(User);
        cout << "Are You Sure You Want To Update This User Y/N: ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')

        {
            _ReadUserInfo(User);

            clsUsers::enSaveResult SaveResult;
            SaveResult = User.Save();

            switch (SaveResult)
            {
            case clsUsers::svSucceeded:
            {
                cout << "\nUser Updated Successfully.\n";
                _PrintUserCard(User);

                break;
            }
            case clsUsers::svFailedEmptyObject:
                cout << "\nError User Was Not Saved Becouse It's Empty.\n";
                break;

            }
        }
        else {
            cout << "\nOperation Was Cancelled!"<<endl;
        }

    }
};

