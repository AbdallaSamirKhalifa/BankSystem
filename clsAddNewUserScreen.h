#pragma once
#include "clsScreen.h"
#include "clsUsers.h"
#include "iomanip"
class clsAddNewUserScreen :
    protected clsScreen
{

private:

   
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

        cout << "\nShow Login Register (Y/N)? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
            Permissions += clsUsers::pShowLoginRegister;

        return Permissions;

    }
    
    static void _ReadUserInfo(clsUsers& User) {

        User.FirstName = clsInputValidate::ReadString("\nEnter First Name: ");
        User.LastName = clsInputValidate::ReadString("\nEnter Last Name: ");
        User.Email = clsInputValidate::ReadString("\nEnter Email: ");
        User.Phone = clsInputValidate::ReadString("\nEnter Phone Number: ");
        User.Password= clsInputValidate::ReadString("\nEnter Password: ");
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
    static void ShowAddNewUserScreen() {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");
        while (clsUsers::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("\nUser Already Used, Please Enter Another UserName: ");
        }

        clsUsers NewUser = clsUsers::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUsers::enSaveResult SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case clsUsers::svFailedEmptyObject:
            cout << "\nError User Was Not Saved Becouse It's Empty.\n";
            break;
        case clsUsers::svSucceeded:
            system("cls");
            cout << "\nUser Added Successfully.\n";
            _PrintUserCard(NewUser);
            break;
        case clsUsers::svFailedAccountNumberExist:
            cout << "\nError UserName Already In Use.\n";

            break;

        }


    }
};

