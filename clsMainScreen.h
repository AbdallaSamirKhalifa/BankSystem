#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginScreen.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
class clsMainScreen :
    protected clsScreen
{
private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient , eDeleteClient ,
        eUpdateClient , eFindClient , eShowTransactionsMenue ,
        eManageUsers ,eLoginRegister,eCurrencyExchange, eExit 
    };

    static short _ReadMainMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }

    static void _GoBackToMainMenue() {

        cout << setw(37) << left << "" << "\n\t\t\t\t    Press any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen() {
        if (!CheckAccessRights(clsUsers::pListClient))
            return;

        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen() {
        if (!CheckAccessRights(clsUsers::pAddNewClient))
            return;
        //cout << "\nClients Lis Screen Will Be Here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen() {
        if (!CheckAccessRights(clsUsers::pDeleteClient))
            return;
        //cout << "\nDelete Client Screen Will Be Here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen() {
        if (!CheckAccessRights(clsUsers::pUpdateClient))
            return;
        //cout << "\nUpdate Client Screen Will Be Here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen() {
        if (!CheckAccessRights(clsUsers::pFindClient))
            return;
        //cout << "\nFind Client Screen Will Be Here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue() {
        if (!CheckAccessRights(clsUsers::pTransactions))
            return;
        //cout << "\nTransaactions Menue Will Be Here...\n";
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        if (!CheckAccessRights(clsUsers::pManageUsers))
            return;
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUsersScreen::ShowManageUsersMenue();

    }

    static void _ShowLoginRegisterScreen() {
        if (!CheckAccessRights(clsUsers::pShowLoginRegister))
            return;
        clsLoginRegisterScreen::ShowLogRecordScreen();
    }

    static void _ShowCurrencyExchangeScreen() {
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
    }

    static void _Logout()
    {
        //cout << "\nEnd Screen Will be here...\n";
         CurrentUser = clsUsers::Find("", "");
        
        //Then It Will Go Back To Main Function

    }


    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case clsMainScreen::eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eAddNewClient:
            system("cls");
            _ShowAddNewClientScreen();
            _GoBackToMainMenue(); 
            break;
        case clsMainScreen::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eCurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenue();
            break;
        case clsMainScreen::eExit:
            system("cls");
            _Logout();

            break;

        }
    }

public:


    static void ShowMainMenue()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }

};



