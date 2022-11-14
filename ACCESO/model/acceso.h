#pragma once
#include <iostream>
#include<vector>
using namespace std;

class Acceso
{
private:
	string usuario;
	string contrasena;
public:
	Acceso(){}
	Acceso(string usu, string contra)
	{
		usuario = usu;
		contrasena = contra;
	}
	string getUsu()
	{
		return this->usuario;
	}
	string getContrasena()
	{
		return this->contrasena;
	}
	
};
