#include <iostream>
using namespace std;

class Cliente
{
private:
	int 	codigo;
	string 	nomCli;
	string 	dni;
	int 	edad;
public:	
	Cliente()
	{
		
	}
	Cliente(int cod,string nomCli,string dni,int edad)
	{
		this->codigo = cod;
		this->nomCli = nomCli;
		this->dni 	 = dni;
		this->edad	 = edad;		
	}
	void setCodigo(int cod)
	{
		this->codigo = cod;
	}
	
	void setNomCli(string nom)
	{
		this->nomCli = nom;
	}
	
	void setDni(string dni)
	{
		this->dni = dni;
	}
	
	void setEdad(int edad)
	{
		this->edad = edad;
	}
	
	int getCodigo()
	{
		return this->codigo;
	}
	string getNomCli()
	{
		return this->nomCli;
	}
	string getDni()
	{
		return this->dni;
	}
	int getEdad()
	{
		return this->edad;
	}
};
