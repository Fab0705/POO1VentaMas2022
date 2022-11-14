#pragma once
#include <iostream>
using namespace std;

class Categoria
{
private:
	int codCat;
	string nomCat;
public:
	Categoria(int codCat, string nomCat)
	{
		this->codCat = codCat;
		this->nomCat = nomCat;
	}
	Categoria()
	{
		
	}
	void setCodCat(int codCat)
	{
		this->codCat = codCat;
	}
	void setNomCat(string nomCat)
	{
		this->nomCat = nomCat;
	}
	int getCodCat()
	{
		return this->codCat;
	}
	string getNomCat()
	{
		return this->nomCat;
	}
};
