#pragma once
#include <iostream>
#include<vector>
using namespace std;

class Vendedor
{
private:
	int codigo;
	string nomApeVendedor;
	string direccion;
	int edad;
public:
	Vendedor(){}
	Vendedor(int codigo, string nomApeVendedor, string direccion, int edad)
	{
		this->codigo = codigo;
		this->nomApeVendedor = nomApeVendedor;
		this->direccion = direccion;
		this->edad = edad;
	}
	void setCodVen(int codigo)
	{
		this->codigo = codigo;
	}
	void setNomApeVen(string nomApeVendedor)
	{
		this->nomApeVendedor = nomApeVendedor;
	}
	void setDirVen(string direccion)
	{
		this->direccion = direccion;
	}
	void setEdadVen(int edad)
	{
		this->edad = edad;
	}
	int getCodVen()
	{
		return this->codigo;
	}
	string getNomApeVen()
	{
		return this->nomApeVendedor;
	}
	string getDir()
	{
		return this->direccion;
	}
	int getEdad()
	{
		return this->edad;
	}
	
};
