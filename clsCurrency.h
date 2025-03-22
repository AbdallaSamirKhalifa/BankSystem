#pragma once
#include"clsUtility.h"
#include"clsString.h"
#include"fstream"
const string CFile = "Currencies.txt";
class clsCurrency
{
	enum enMode{EmptyMode=0,UpdateMode=1};
	enMode _Mode;

	string _CountryName;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string seperator = "#//#") {
		string Record = Currency.Country() + seperator;
		Record += Currency.CurrencyCode () + seperator;
		Record += Currency.CurrencyName() + seperator;
		Record += to_string(Currency.Rate());

		return Record;
	}

	static clsCurrency _ConcvertLineToCurrencyObject(string Line, string sep = "#//#") {
		vector<string>vCurrency = clsString::split(Line,sep);
		return clsCurrency(UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
	}

	static vector<clsCurrency> _LoadCurrencysDataFromFile() {
		vector<clsCurrency>vCurrencyRecord;
		string Line;

		fstream MyFile;
		MyFile.open(CFile, ios::in);

		if (MyFile.is_open()) {

			while (getline(MyFile, Line)) {
				vCurrencyRecord.push_back(_ConcvertLineToCurrencyObject(Line));
			}
			MyFile.close();
		}

		return vCurrencyRecord;
	}

	static void _SaveCurrenciyDataToFile(vector<clsCurrency>vCurrencyRecord) {
		fstream MyFile;

		MyFile.open(CFile, ios::out);

		if (MyFile.is_open()) {
			for (clsCurrency C : vCurrencyRecord) {
				MyFile << _ConvertCurrencyObjectToLine(C) << endl;
			}
			MyFile.close();

		}
	}

	void _Update() {
		vector<clsCurrency>_vCurrencys = _LoadCurrencysDataFromFile();

		for (clsCurrency& C : _vCurrencys) {
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}

		}
		_SaveCurrenciyDataToFile(_vCurrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_CountryName = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty() {
		return _Mode == EmptyMode;
	}

	string Country() {
		return _CountryName;
	}

	string CurrencyCode() {
		return _CurrencyCode;
	}

	string CurrencyName() {
		return _CurrencyName;
	}

	void UpdateRate(float Rate) {
		_Rate = Rate;
		_Update();
	}

	float Rate() {
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode) {

		CurrencyCode = clsString::upperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open(CFile, ios::in);

		if (MyFile.is_open()) {
	
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConcvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}

			}
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {

		Country = clsString::upperAllString(Country);

		fstream MyFile;
		MyFile.open(CFile, ios::in);

		if (MyFile.is_open()) {
	
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConcvertLineToCurrencyObject(Line);
				if (clsString::upperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}

			}
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {
		clsCurrency C = clsCurrency::FindByCode(CurrencyCode);
		return (!C.IsEmpty());
	}

	static vector<clsCurrency>GetCurrenciesList() {
		
		return _LoadCurrencysDataFromFile();
	}

	float ConvertToUSD(float Amount) {
		return Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {
		
		float AmountInUSD = ConvertToUSD(Amount);
		
		if (Currency2.CurrencyCode() == "USD")
			return AmountInUSD;

		return AmountInUSD* Currency2.Rate();
	}

};

