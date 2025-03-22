#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class clsString
{
	string _Value;

public:
	clsString() {
		_Value = "";
	}
	clsString(string value) {
		_Value = value;
	}

	void SetValue(string Value) {
		_Value = Value;
	}
	string GetValue() {
		return _Value;
	}
	__declspec(property(get = GetValue, put = SetValue)) string
		Value;
	static short Length(string S1)
	{
		return S1.length();
	};

	short Length()
	{
		return _Value.length();
	};

	static void printFristLetter(string str) {
		bool isFirstLetter = true;//flag

		cout << "\nFirst Letter Of This String:\n";
		for (short i = 0; i < str.size(); i++)
		{
			if (str[i] != ' ' && isFirstLetter) {
				cout << str[i] << endl;

			}
			isFirstLetter = str[i] == ' ' ? true : false;
		}
	}

	static string firstLetterToUpperCase(string str) {
		bool isFirstLetter = true;//flag

		for (short i = 0; i < str.size(); i++)
		{
			if (str[i] != ' ' && isFirstLetter) {
				str[i] = toupper(str[i]);

			}
			isFirstLetter = str[i] == ' ' ? true : false;
		}
		return str;
	}
	
	void firstLetterToUpperCase() {
		_Value= firstLetterToUpperCase(_Value);
	}

	static string firstLetterToLowerCase(string str) {
		bool isFirstLetter = true;//flag

		for (short i = 0; i < str.size(); i++)
		{
			if (str[i] != ' ' && isFirstLetter) {
				str[i] = tolower(str[i]);

			}
			isFirstLetter = str[i] == ' ' ? true : false;
		}
		return str;
	}
	
	void firstLetterToLowerCase( ) {

		_Value= firstLetterToLowerCase(_Value);
	}

	static string lowerAllString(string str) {


		for (short i = 0; i < str.size(); i++)
		{
			str[i] = tolower(str[i]);
		}
		return str;
	}
	
	void lowerAllString() {

		_Value = lowerAllString(_Value);
	}

	static string upperAllString(string str) {

		for (short i = 0; i < str.size(); i++)
		{
			str[i] = toupper(str[i]);
		}
		return str;
	}
	
	void upperAllString() {

		_Value = upperAllString(_Value);
	}

	static char invertCharcter(char c) {
		return isupper(c) ? tolower(c) : toupper(c);
	}
	
	static string invertAllStringLetters(string str) {

		for (short i = 0; i < str.size(); i++)
		{
			str[i] = invertCharcter(str[i]);
		}
		return str;
	}
	
	void invertAllStringLetters() {

		
		_Value = invertAllStringLetters(_Value);
	}

	enum enLetter { Capital = 1, Small, All };
	static short countLetters(string str, enLetter letter = All) {

		if (letter == All)
			return str.length();

		short counter = 0;
		for (int i = 0; i < str.size(); i++)
		{
			if (letter == Capital && isupper(str[i]))
				counter++;

			if (letter == Small && islower(str[i]))
				counter++;

		}
		return counter;//Genaric Function
	}

	static short countCapitalLetters(string str) {
		short counter = 0;
		for (int i = 0; i < str.size(); i++)
		{
			if (isupper(str[i]))
				counter++;

		}
		return counter;
	}	
	
	short countCapitalLetters() {
		return countCapitalLetters(_Value);
	}

	static short countSmallLetters(string str) {

		short counter = 0;
		for (int i = 0; i < str.size(); i++)
		{

			if (islower(str[i]))
				counter++;

		}
		return counter;
	}
	
	short countSmallLetters() {

		return countSmallLetters(_Value);
	}

	static short countSpecificLetter(string str, char letter, bool matchCase = true) {

		short counter = 0;
		for (int i = 0; i < str.size(); i++)
		{
			if (matchCase) {
				if (str[i] == letter)
				{
					counter++;
				}
			}
			else {
				if (tolower(str[i]) == tolower(letter)) {
					counter++;
				}
			}

		}
		return counter;
	}
	
	short countSpecificLetter(char letter, bool matchCase = true) {

		return countSpecificLetter(_Value, letter, matchCase);
	}

	static bool isVowel(char c) {
		//Vowel Letters {a,e,i,o,u}
		c = tolower(c);
		return ((c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u'));

	}

	static short countVowels(string str) {
		short counter = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (isVowel(str[i]))
				counter++;
		}
		return counter;
	}
	
	short countVowels() {
		return countVowels(_Value);
	}

	//static void printVowels(string str) {
	//	cout << "Vowels In String Are: ";
	//	for (int i = 0; i < str.length(); i++)
	//	{
	//		if (isVowel(str[i]))
	//			cout << str[i] << "   ";
	//	}

	//}
	//
	//void printVowels() {
	//	cout << "Vomels In String Are: ";
	//	for (int i = 0; i < _Value.length(); i++)
	//	{
	//		if (isVowel(_Value[i]))
	//			cout << _Value[i] << "   ";
	//	}
	//}

	//static void printEachWord(string str) {
	//	string delim = " ";
	//	short spacePos = 0;
	//	string word = "";
	//	while ((spacePos = str.find(delim)) != std::string::npos)
	//	{
	//		word = str.substr(0, spacePos);
	//		if (word != "")
	//			cout << word << endl;
	//		str.erase(0, spacePos + delim.length());
	//	}
	//	if (str != "")
	//		cout << str;
	//}
	
	//void printEachWord() {
	//	string delim = " ";
	//	short spacePos = 0;
	//	string word = "";
	//	while ((spacePos = _Value.find(delim)) != std::string::npos)
	//	{
	//		word = _Value.substr(0, spacePos);
	//		if (word != "")
	//		   cout << word << endl;
	//		_Value.erase(0, spacePos + delim.length());
	//	}
	//	
	//	if (_Value != "")
	//		cout << _Value;
	//}

	static short countWords(string str) {
		string delim = " ";
		short spacePos = 0;
		string word;
		short counter = 0;
		while ((spacePos = str.find(delim)) != std::string::npos) {

			word = str.substr(0, spacePos);
			if (word != "")
				counter++;
			str.erase(0, spacePos + delim.length());
		}
		if (word != "")
			counter++;
		return counter;
	}
	
	short countWords() {
		return countWords(_Value);
	}

	static vector <string> split(string str, string delim) {
		vector <string> vStr;
		short spacePos = 0;
		string word;

		while ((spacePos = str.find(delim)) != std::string::npos) {

			word = str.substr(0, spacePos);
			if (word != "")
			{
				vStr.push_back(word);
			}
			str.erase(0, spacePos + delim.length());
		}
		if (str != "")
		{
			vStr.push_back(str);
		}
		return vStr;

	}
	
	vector <string> split(string delim) {

		return split(_Value, delim);
	}

	static string trimLeft(string str) {

		for (short i = 0; i < str.length(); i++) {

			if (str[i] != ' ')
				return str.substr(i, str.length() - i);

		}
		return "";
	}
	
	void trimLeft() {

		_Value = trimLeft(_Value);
	}

	static string trimRight(string str) {
		short counter = 0;
		for (short i = str.length() - 1; i >= 0; i--) {
			if (str[i] != ' ')
				return str.substr(0, i + 1);
		}
		return "";
	}
	
	void trimRight() {
		_Value = trimRight(_Value);
	}

	static string Trim(string str) {


		return trimLeft(trimRight(str));
	}
	
	void Trim() {

		_Value = Trim(_Value);
	}

	static string joinString(vector<string>vStr, string delim) {
		string str = "";

		for (string& w : vStr)
			str += w + delim;

		return str.substr(0, str.length() - delim.length());
	}
	
	static string joinString(string arr[], short arrLength, string delim) {
		string str = "";
		for (short i = 0; i < arrLength; i++) {
			str += arr[i] + delim;
		}
		return str.substr(0, str.length() - delim.length());
	}

	static string reverseString(string str)
	{
		vector<string>vStr = split(str, " ");
		string reversedStr = "";
		vector<string>::iterator itr = vStr.end();
		while (itr != vStr.begin()) {
			itr--;
			reversedStr += *itr + " ";
		}


		return reversedStr.substr(0, reversedStr.length() - 1);
	}
	 void reverseString()

	{
		 _Value = reverseString(_Value);
	}



	 static string replaceWord(string str, string target, string replacement, bool matchCase = true) {

		 vector<string>vStr = split(str, " ");

		 for (string& w : vStr) {

			 if (matchCase) {
				 if (w == target)
					 w = replacement;
			 }
			 else {
				 if (lowerAllString(w) == lowerAllString(target))
					 w = replacement;
			 }

		 }

		 return joinString(vStr, " ");
	 }
	 void replaceWord(string target, string replacement, bool matchCase = true) {
	 
		 _Value= replaceWord(_Value, target, replacement, matchCase);
	 }

	 static string replaceUsingBultIn(string str, string target, string replacment) {
		 short targetPos = 0;
		 while ((targetPos = str.find(target)) != std::string::npos) {
			 str = str.replace(targetPos, target.length(), replacment);
		 }
		 return str;
	 }
	 string replaceUsingBultIn(string target, string replacment) {
		 _Value = replaceUsingBultIn(_Value, target, replacment);
	 }

	static string removePunct(string str) {
		 string str2 = "";
		 for (short i = 0; i < str.length(); i++) {
			 if (!ispunct(str[i]))
				 str2 += str[i];
		 }
		 return str2;
	 }
	 void removePunct() {
		 
		 _Value = removePunct(_Value);
	 }

};

