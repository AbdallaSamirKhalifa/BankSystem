#pragma once
#include "clsPerson.h"
#include "clsInputValidate.h"
#include "fstream"
#include "clsUtility.h"

const string FileName = "Users.txt";
class clsUsers :
    public clsPerson
{
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkForDelete = false;

    string _PrepareLoginRecord(string seperator = "#//#") {
        string Record = "";
       
        Record += clsDate::GetSystemDateTimeString() + seperator;
        Record += UserName + seperator;
        Record += clsUtility::encryptText(Password) + seperator;
        Record += to_string(Permissions);

        return Record;
    }

    static clsUsers _ConvertLineToUserObject(string line, string sep = "#//#") {
        
        vector<string>vUserData = clsString::split(line, sep);
        
        return clsUsers(UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
            vUserData[4], clsUtility::decryptText(vUserData[5]), stoi(vUserData[6]));
    }


     struct stLoginRegisterRecord;
    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string line, string sep = "#//#") {
        
        vector<string>LoginRegisterDataLine = clsString::split(line, sep);
        stLoginRegisterRecord LoginRegisterRecord;
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtility::decryptText(LoginRegisterDataLine[2]);
        LoginRegisterRecord.Permission = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;
    }

    string _ConvertUserObjectToLine(clsUsers User, string seperator = "#//#") {
        string Line;

        Line += User.FirstName + seperator;
        Line += User.LastName + seperator;
        Line += User.Email + seperator;
        Line += User.Phone + seperator;
        Line += User.UserName + seperator;
        Line += clsUtility::encryptText(User.Password) + seperator;
        Line += to_string(User.Permissions);

        return Line;
    }

    static  vector<clsUsers> _LoadUsersDataFromFile() {
        vector<clsUsers> vUsers;

        fstream MyFile;
        string Line;

        MyFile.open(FileName, ios::in);

        if (MyFile.is_open()) {

            while (getline(MyFile, Line))
            {
                clsUsers User = _ConvertLineToUserObject(Line);

                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }

    void _SaveUsersDataToFile(vector<clsUsers>vUsers) {
        fstream MyFile;
        string Line;
        MyFile.open(FileName, ios::out);

        if (MyFile.is_open()) {

            for (clsUsers U : vUsers) {
                if (U.MarkForDelete() == false)
                {

                    Line = _ConvertUserObjectToLine(U);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update() {
        vector <clsUsers>_vUsers = _LoadUsersDataFromFile();

        for (clsUsers& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
    }

    void _AddDataLineToFile(string Line) {

        fstream MyFile;

        MyFile.open(FileName, ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << Line << endl;

            MyFile.close();
        }
    }

    void _AddNew() {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    static clsUsers _GetEmptyUserObject()
    {
        return clsUsers(EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum enPermissions {
        eAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,pShowLoginRegister=128
    };

    struct stLoginRegisterRecord {
        string DateTime;
        string UserName;
        string Password;
        int Permission;
    };

    clsUsers(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permission):
        clsPerson(FirstName,LastName,Email,Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permission;

    }

    bool IsEmpty()
    {

        return (_Mode == EmptyMode);
    }

    bool MarkForDelete() {
        return _MarkForDelete;
    }

    void SetUserNmae(string UserName) {
        _UserName = UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserNmae))string UserName;

    string GetUserName()
    {
        return _UserName;
    }

    void SetPassword(string Password)
    {
        _Password= Password;
    }
    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword))string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermission()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermission, put = SetPermissions))int Permissions;

    static clsUsers Find(string UserName) {
        //vector <clsBankClient>vClients;

        fstream MyFile;
        MyFile.open(FileName, ios::in);//readMode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUsers User = _ConvertLineToUserObject(Line);
                if (User.UserName== UserName)
                {
                    MyFile.close();
                    return User;

                }
                //vClients.push_back(Client);
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    static clsUsers Find(string UserName, string Password) {
        //vector <clsUsers>vUsers;

        fstream MyFile;
        MyFile.open(FileName, ios::in);//readMode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUsers User = _ConvertLineToUserObject(Line);

                if (User.UserName== UserName && User.Password== Password)
                {
                    MyFile.close();
                    return User;

                }
                //vUsers.push_back(User);
            }
            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResult { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExist };

    enSaveResult Save() {
        switch (_Mode)
        {
        case clsUsers::EmptyMode:
            if(IsEmpty())
            return svFailedEmptyObject;

        case clsUsers::UpdateMode:
            _Update();
            return svSucceeded;

        case AddNewMode:
            if (IsUserExist(_UserName)) {
                return svFailedAccountNumberExist;
            }
            else {
                _AddNew();
                _Mode = UpdateMode;
                return svSucceeded;
            }


        }
    }

    static clsUsers GetAddNewUserObject(string UserName)
    {
        return clsUsers(AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static bool IsUserExist(string UserName)
    {
        clsUsers User = clsUsers::Find(UserName);
        return(!User.IsEmpty());
    }

    bool Delete() {
        vector <clsUsers>vUsers = _LoadUsersDataFromFile();

        for (clsUsers& U : vUsers) {
            if (U.UserName== _UserName) {
                U._MarkForDelete = true;
                break;
            }
        }
        _SaveUsersDataToFile(vUsers);
        *this = _GetEmptyUserObject();

        return true;
    }

    static vector<clsUsers> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions permision)
    {

        if (this->Permissions== eAll)
        {
            return true;
        }

        else if ((this->Permissions & permision) == permision)
        {
            return true;
        }

            return false;
       

    }

    void RegisterLogIn() {
        string stDataLine = _PrepareLoginRecord();
        fstream MyFile;

        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

   static vector<stLoginRegisterRecord>GetLoginRegisterList() {
       fstream MyFile;
       vector<stLoginRegisterRecord>vLoginRegisterRecord;
       MyFile.open("LoginRegister.txt", ios::in);
       if (MyFile.is_open())
       {
       string Line;
           while (getline(MyFile, Line))
           {
               vLoginRegisterRecord.push_back(_ConvertLoginRegisterLineToRecord(Line));
           }
           MyFile.close();
       }
       return vLoginRegisterRecord;
   }

};

