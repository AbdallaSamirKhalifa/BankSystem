#pragma once
#include<iostream>
#include<string>
using namespace std;
//Absttract/Interface Class
class InterfaceCommunication
{
public:
	//Pure Virtual Methods
	virtual void SendSMS(string Title, string Body) = 0;
	virtual void SendFax(string Title, string Body) = 0;
	virtual void SendEmail(string Title, string Body) = 0;
};

