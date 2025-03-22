#pragma once
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :
    protected clsScreen
{
   static bool _Login() {
        bool loginFailed = false;
        string UserName, Password;
        short Trials = 3;

        do {

            if (loginFailed)
            {
                cout << "\nInvalid UserName/Password!" << endl;
                cout << "You Have " << --Trials << " Trial(s).\n" << endl;

            if (Trials == 0) {
                cout << "Your Locked After 3 Failed Trials.";
                return false;
            }
            }

            cout << "Enter UserName: ";
            getline(cin >> ws, UserName);

            cout << "Enter Password: ";
            getline(cin >> ws, Password);

             CurrentUser=clsUsers::Find(UserName, Password);
             loginFailed = CurrentUser.IsEmpty();

        } while (loginFailed);
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:

    static bool ShowLoginScreen() {
    
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }

};

