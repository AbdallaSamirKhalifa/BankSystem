#pragma once
#include <iostream>
#include "clsPeriod.h"

using namespace std;

class clsUtility
{



public:

	static string numberToText(long long  number) {

		if (number == 0)
			return "";

		if (number >= 1 && number <= 19) {
			string arr[] = { "", "One" ,"Two" ,"Three" ,"Four" ,"Five"
				,"Six" ,"Seven" ,"Eight" ,"Nine" ,"Ten" ,"Eleven" ,
				"Twelve" ,"Thirteen" ,"Fourteen" ,"Fifteen"
				,"Sixteen" ,"Seventeen ","Eighteen" ,"Nineteen" };
			return arr[number] + " ";
		}
		if (number >= 20 && number <= 99) {
			string arr[] = { "", "" ,"Twenty" ,"Thirty" ,"Fourty" ,"Fifty"
				,"Sixty" ,"Seventy" ,"Eighty" ,"Ninety" };
			return arr[number / 10] + " " + numberToText(number % 10);
		}
		if (number >= 100 && number <= 199) {

			return  "One Hundred " + numberToText(number % 100);
		}
		if (number >= 200 && number <= 999) {

			return  numberToText(number / 100) + "Hundred " + numberToText(number % 100);
		}
		if (number >= 1000 && number <= 1999) {

			return  "One Thansand " + numberToText(number % 1000);
		}
		if (number >= 2000 && number <= 999999) {

			return  numberToText(number / 1000) + "Thousand " + numberToText(number % 1000);
		}
		if (number >= 1000000 && number <= 1999999) {

			return  "One Milion " + numberToText(number % 1000000);
		}
		if (number >= 2000000 && number <= 999999999) {

			return  numberToText(number / 1000000) + "Milion " + numberToText(number % 1000000);
		}

		if (number >= 1000000000 && number <= 1999999999) {

			return  "One Bilion " + numberToText(number % 1000000000);
		}
		else {

			return  numberToText(number / 1000000000) + "Bilion  " + numberToText(number % 1000000000);
		}
		//return "";
	}

	static void  Srand()
	{
		//Seeds the random number generator in C++, called only once
		srand((unsigned)time(NULL));
	}

	static int randomNumber(int from, int to) {
		int randomNumber = rand() % (to - from + 1) + from;
		return randomNumber;
	}

	static int reverseNumber(int Number)
	{
		int Remainder = 0, Number2 = 0;
		while (Number > 0)
		{
			Remainder = Number % 10;
			Number = Number / 10;
			Number2 = Number2 * 10 + Remainder;
		}
		return Number2;
	}

	static  void Swap(int& A, int& B)
	{
		int Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(double& A, double& B)
	{
		double Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(bool& A, bool& B)
	{
		bool Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(char& A, char& B)
	{
		char Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(string& A, string& B)
	{
		string Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(clsDate& A, clsDate& B)
	{
		clsDate::swapDates(A, B);

	}
//------------------------------------------------------------
//generating Keys and Encryption
	enum enCharType { SmallLetter = 1, CapitalLetter, Digit ,MixedChar, SpecialCharacter};

	static char getRandomCharacter(enCharType charType) {
		if (charType == MixedChar) {
			charType = (enCharType)randomNumber(1, 3);
		}
		switch (charType)
		{
		case SmallLetter:
			return char(randomNumber('a', 'z'));
		case CapitalLetter:
			return  char(randomNumber('A', 'Z'));
		case SpecialCharacter:
			return  char(randomNumber('!', '/'));
		case Digit:
			return  char(randomNumber('0', '9'));
		default:
			return  char(randomNumber('A', 'Z'));

		}

	}

	static string generateWord(short length, enCharType charType) {
		string key = "";

		for (int i = 1; i <= length; i++) {

			key += getRandomCharacter(charType);
		}
		return key;
	}
	
	static string genarateKey(enCharType charType=CapitalLetter) {
		string key = "";
		key = generateWord(4, charType) + "-";
		key = key + generateWord(4, charType) + "-";
		key = key + generateWord(4, charType) + "-";
		key = key + generateWord(4, charType);
		return key;
	}

	static void generateKeys(short NumberOfKeays, enCharType charType = CapitalLetter) {
		for (int i = 1; i <= NumberOfKeays; i++) {

			cout << "key [" << i << "] : " << genarateKey(charType) << endl;

		}
	}

	static void fillArrayWithKeys(string arr[], short arrLength,enCharType charType = CapitalLetter) {

		for (short i = 0; i < arrLength; i++)
			arr[i] = genarateKey(charType);

	}

	static string encryptText(string text, short encryptionKey=3) {

		for (int i = 0; i < text.size(); i++) {
			text[i] = (text[i] + encryptionKey);
		}
		return text;
	}

	static string decryptText(string text, short encryptionKey=3) {

		for (int i = 0; i < text.size(); i++) {
			text[i] = (text[i] - encryptionKey);
		}
		return text;
	}
//------------------------------------------------------------

	//Array Fuctions

	static void copyArray(int arrSource[], int arrDistination[], int arrLength) {

			for (int i = 0; i < arrLength; i++)
			{

				arrDistination[i] = arrSource[i];
			}
	}

	static int sumArray(int arr[], int arrLength) {

		int sum = 0;

		for (int i = 0; i < arrLength; i++)
			sum += arr[i];

		return sum;
	}
	
	static float arrayAverage(int arr[], int arrLength) {

		return(float)sumArray(arr, arrLength) / arrLength;
	}

	static void fillArrayWithRandomNumbers(int arr[], short  arrLength,short from ,short to) {

		for (short i = 0; i < arrLength; i++)
			arr[i] = randomNumber(from , to);

	}

	static void fillArrayWithRandomWords(string arr[], int arrLength, enCharType CharType, short Wordlength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = generateWord(Wordlength,CharType);

	}

	static void shuffleArray(int arr[], short arrLength) {
		
		for (short i = 0; i < arrLength; i++)
		{
			Swap(arr[randomNumber(1, arrLength) - 1], arr[randomNumber(1, arrLength) - 1]);
		}
	}

	static void shuffleArray(string arr[], short arrLength) {

		for (short i = 0; i < arrLength; i++)
		{
			Swap(arr[randomNumber(1, arrLength) - 1], arr[randomNumber(1, arrLength) - 1]);
		}
	}

	static short findNumberPositionInArray(int number, int arr[], int arrLength) {


		for (int i = 0; i < arrLength; i++)
		{
			if (arr[i] == number)
				return i;

		}
		return -1;
	}

	static bool isNumberInArray(int Number, int arr[], int arrLength)
	{
		return findNumberPositionInArray(Number, arr, arrLength) != -1;
	}

	static short timesRepeatedNumberInTheArray(int Number, int arr[], short arrLength)
	{
		int count = 0;
		for (int i = 0; i <= arrLength - 1; i++)
		{
			if (Number == arr[i])
			{
				count++;
			}
		}
		return count;
	}

	static void CopyArrayInReverseOrder(int arrSource[], int arrDestination[], short arrLength)
	{
		for (int i = 0; i < arrLength; i++)
			arrDestination[i] = arrSource[arrLength - 1 - i];
	}
//------------------------------------------------------------
	static string  Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i < NumberOfTabs; i++)
		{
			t = t + "\t";
			cout << t;
		}
		return t;

	}


};

