#pragma once
#include <iostream>
using namespace std;

class Producto
{
private:
	int 	codPro;
	int 	stkPro;
	float	prePro;
	string 	nomPro;
	int		codCat;
public:
	Producto()
	{
		
	}
	Producto(int codPro, int stkPro, float prePro, string nomPro, int codCat)
	{
		this->codPro = codPro;
		this->stkPro = stkPro;
		this->prePro = prePro;
		this->nomPro = nomPro;
		this->codCat = codCat;
	}
	
	void setCodPro(int codPro)
	{
		this->codPro = codPro;
	}
	
	void setStkPro(int stkPro)
	{
		this->stkPro = stkPro;
	}
	
	void setPrePro(float prePro)
	{
		this->prePro = prePro;
	}
	
	void setNomPro(string nomPro)
	{
		this->nomPro = nomPro;
	}
	
	void setCodCat(int codCat)
	{
		this->codCat = codCat;
	}
	
	int getCodPro()
	{
		return this->codPro;
	}
	int getStkPro()
	{
		return this->stkPro;
	}
	float getPrePro()
	{
		return this->prePro;
	}
	
	string getNomPro()
	{
		return this->nomPro;
	}
	int getCodCat()
	{
		return this->codCat;
	}
	
};
