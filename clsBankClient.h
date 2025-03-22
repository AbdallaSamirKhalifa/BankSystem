#pragma once
#include "clsPerson.h"
#include "clsInputValidate.h"
#include "fstream"

class clsBankClient:public clsPerson
{
    private:

	enum enMode{EmptyMode=0,UpdateMode=1,AddNew};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
    bool _MarkForDelete = false;
    struct stTransferLogRecord;

     string _PrepareTransferRecord(clsBankClient DestinationClient,float TransferAmount,string seperator = "#//#") {
        string Record;
        Record =  clsDate::GetSystemDateTimeString() + seperator;
        Record += AccountNumber() + seperator;
        Record += DestinationClient.AccountNumber() + seperator;
        Record += to_string(TransferAmount) + seperator;
        Record += to_string(AccountBalance) + seperator;
        Record += to_string(DestinationClient.AccountBalance) + seperator;
        Record += CurrentUser.UserName;
        return Record;

    }

     void _RegisterTransferLog(clsBankClient DestinationClient, float TransferAmount) {
         fstream MyFile;
         MyFile.open("TransferLog.txt", ios::out | ios::app);

         if (MyFile.is_open()) {

             MyFile << _PrepareTransferRecord(DestinationClient, TransferAmount) << endl;

             MyFile.close();
         }
     }
     static stTransferLogRecord _ConvertTransferLogLineToRecord(string line, string sep = "#//#") {

         vector<string>TransferRegisterDataLine = clsString::split(line, sep);
         stTransferLogRecord TransferRegisterRecord;
         TransferRegisterRecord.DateTime = TransferRegisterDataLine[0];
         TransferRegisterRecord.SourceAccountNumber = TransferRegisterDataLine[1];
         TransferRegisterRecord.DestinationAccountNumber= TransferRegisterDataLine[2];
         TransferRegisterRecord.TransferAmount= stoi(TransferRegisterDataLine[3]);
         TransferRegisterRecord.SrcBalanceAfter= stof(TransferRegisterDataLine[4]);
         TransferRegisterRecord.DesBalanceAfter= stof(TransferRegisterDataLine[5]);
         TransferRegisterRecord.UserName= TransferRegisterDataLine[6];

         return TransferRegisterRecord;
     }

    static clsBankClient _ConvertLineToClientObject(string line, string sep = "#//#") {
        vector<string>vClientDate = clsString::split(line, sep);

        return clsBankClient(UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2], vClientDate[3],
            vClientDate[4], vClientDate[5], stof(vClientDate[6]));
    }

    string _ConvertClientObjectToLine(clsBankClient Client, string seperator = "#//#") {
        string Line;
        Line += Client.FirstName + seperator;
        Line += Client.LastName+ seperator;
        Line += Client.Email + seperator;
        Line += Client.Phone + seperator;
        Line += Client.AccountNumber()+seperator;
        Line += Client.PinCode+seperator;
        Line += to_string(Client.AccountBalance);

        return Line;
    }

    static  vector<clsBankClient> _LoadClientsDataFromFile() {
        vector<clsBankClient> vClient;
       
        fstream MyFile;
        string Line;
        
        MyFile.open("Clients.txt", ios::in);
        
        if (MyFile.is_open()) {
         
            while (getline(MyFile, Line))
            {
                clsBankClient client = _ConvertLineToClientObject(Line);

                vClient.push_back(client);
            }
            MyFile.close();
        }
        return vClient;
    }

    void _SaveClientsDataToFile(vector<clsBankClient>vClients) {
        fstream MyFile;
        string Line;
        MyFile.open("Clients.txt", ios::out);

        if (MyFile.is_open()) {

            for (clsBankClient C : vClients) {
                if (C.MarkForDelete() == false)
                {

                    Line = _ConvertClientObjectToLine(C);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update() {
        vector <clsBankClient>_vClients=_LoadClientsDataFromFile();

        for (clsBankClient &C:_vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    }

    void _AddDataLineToFile( string Line) {

        fstream MyFile;

        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << Line << endl;

            MyFile.close();
        }
    }

    void _AddNew() {
         _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    struct stTransferLogRecord {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float TransferAmount;
        float SrcBalanceAfter;
        float DesBalanceAfter;
        string UserName;
    };

    clsBankClient(enMode Mode,string FirstName,string LastName,string Email,string Phone,
        string AccountNumber,string PinCode ,float AccountBalance):
        clsPerson(FirstName, LastName, Email, Phone) {

        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {

        return (_Mode == EmptyMode);
    }

    bool MarkForDelete() {
        return _MarkForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

   
    //No Related UI Code Inside The Object
    //void Print() {
    //    cout << "\nClient Card:";
    //    cout << "\n______________________";
    //    cout << "\nFirstName     :" << FirstName;
    //    cout << "\nLastName      :" << LastName;
    //    cout << "\nFullName      :" << FullName();
    //    cout << "\nEmail         :" << Email;
    //    cout << "\nPhone         :" << Phone;
    //    cout << "\nAcc. Number   :" << _AccountNumber;
    //    cout << "\nPassword      :" << _PinCode;
    //    cout << "\nBalance       :" << _AccountBalance;
    //    cout << "\n______________________\n";
    //}

    void Deposit(float Amount) {
        _AccountBalance += Amount;
        Save();
    }
    
    bool Withdraw(float Amount) {

        if (Amount > _AccountBalance)
            return false;
        else
        _AccountBalance -= Amount;
        Save();
    }

    static clsBankClient Find( string AccountNumber) {
        //vector <clsBankClient>vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//readMode
        
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
               clsBankClient Client = _ConvertLineToClientObject(Line);
               if (Client.AccountNumber() == AccountNumber)
               {
                   MyFile.close();
                   return Client;

               }
                //vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find( string AccountNumber,string PinCode) {
        //vector <clsBankClient>vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//readMode
        
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
               clsBankClient Client = _ConvertLineToClientObject(Line);

               if (Client.AccountNumber() == AccountNumber&&Client.PinCode==PinCode)
               {
                   MyFile.close();
                   return Client;

               }
                //vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    enum enSaveResult{svFailedEmptyObject=0, svSucceeded=1,svFailedAccountNumberExist};

    enSaveResult Save() {
        switch (_Mode)
        {
        case clsBankClient::EmptyMode:
            return svFailedEmptyObject;

        case clsBankClient::UpdateMode:
            _Update();
            return svSucceeded;
        
        case AddNew:
            if (IsClientExist(_AccountNumber)) {
                return svFailedAccountNumberExist;
            }
            else {
                _AddNew();
                _Mode = UpdateMode;
                return svSucceeded;
            }
        

        }
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(AddNew, "", "", "", "", AccountNumber, "", 0);
    }


    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return(!Client1.IsEmpty());
    }
    
    bool Delete() {
        vector <clsBankClient>vClients = _LoadClientsDataFromFile();

        for (clsBankClient &C : vClients) {
            if (C.AccountNumber() == _AccountNumber) {
                C._MarkForDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
        *this = _GetEmptyClientObject();

        return true;
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances() {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        double TotalBalances = 0;
        for (clsBankClient C:vClients)
        {
            TotalBalances += C.AccountBalance;
        }
        return TotalBalances;
    }

    bool Transfer(float Amount, clsBankClient& DestinationClient) {
        if (Amount > AccountBalance)
            return false;

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(DestinationClient, Amount);
        return true;

    }

    static vector<stTransferLogRecord>GetTransferLogList() {
        vector<stTransferLogRecord>vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vTransferLogRecord.push_back(_ConvertTransferLogLineToRecord(Line));
            }
            MyFile.close();
        }
        return vTransferLogRecord;
    }
};

