#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionsScreen :
    protected clsScreen
{
    enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw, eShowTotalBalance, eTransfer,eTransferLog, eShowMainMenue};

    static short _ReadTransactionsMenueOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowDepositScreen() {
        //cout << "\nDeposit Screen Will Be Here.\n";
        clsDepositScreen::ShowDepositScreen();
    }
    
    static void _ShowWithdrawScreen() {
        //cout << "\nWithdraw Screen Will Be Here.\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    
    static void _ShowTotalBalanceScreen() {
        //cout << "\nBalance List Screen Will Be Here.\n";
        clsTotalBalanceScreen::ShowTotalBalances();
    }

    static void _ShowTrasferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();

    }



    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions traOptions) {
        
            switch (traOptions)
            {
            case eDeposit:
                system("cls");
                _ShowDepositScreen();
                _GoBackToTransactionsMenue();
                break;
            case eWithdraw:
                system("cls");
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenue();
                break;
            case eShowTotalBalance:
                system("cls");
                _ShowTotalBalanceScreen();
                _GoBackToTransactionsMenue();
                break;
            case eTransfer:
                system("cls");
                _ShowTrasferScreen();
                _GoBackToTransactionsMenue();
            case eTransferLog:
                system("cls");
                _ShowTransferLogScreen();
                _GoBackToTransactionsMenue();
            case eShowMainMenue:
                //clsMainScreen::ShowMainMenue();
                //Do Nothing The Main Menue Will handle it
                break;
            }
        }
public:
    static void ShowTransactionsMenue() {

        system("cls");
        _DrawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());
    }
};

