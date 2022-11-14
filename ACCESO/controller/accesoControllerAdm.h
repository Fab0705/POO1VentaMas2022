#pragma once
#include<iostream>
#include<vector>
#include<conio.h>
#include<fstream>
#include<string>
#include"../model/acceso.h"

class AccesoControllerAdm
{
private:
	vector<Acceso> vectorAccesoAdm;
public:
	AccesoControllerAdm()
	{
		cargarDatosDelArchivoAlVectorAdm();
	}
	//agregar objetos de tipo acceso
	void addAdm(Acceso objeto)
	{
		vectorAccesoAdm.push_back(objeto);
	}
	//grabar los datos en el archivo 
	void grabarEnArchivoAdm(Acceso acceso)
	{
		try
		{
			fstream archivoAccesoAdm;
			archivoAccesoAdm.open("accesoAdm.csv", ios::app);
			if(archivoAccesoAdm.is_open())
			{
				archivoAccesoAdm<<acceso.getUsu()<<";"
					<<acceso.getContrasena()<<";"<<endl;
				archivoAccesoAdm.close();
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
	//cargar datos del archivo
	void cargarDatosDelArchivoAlVectorAdm()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string 	temporal[2];
			fstream	archivoAccesoAdm;
			archivoAccesoAdm.open("accesoAdm.csv",ios::in);
			if(archivoAccesoAdm.is_open())
			{
				while(!archivoAccesoAdm.eof() && getline(archivoAccesoAdm,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Acceso objAccesoAdm(temporal[0],temporal[1]);
					
					addAdm(objAccesoAdm);
				}
			}
			//archivoAcceso.close();
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
	
	bool loginUsuario(Acceso obj)
	{
		for (Acceso x : vectorAccesoAdm)
		{
			if (obj.getUsu() == x.getUsu() && obj.getContrasena() == x.getContrasena())
			{
				return true;
			}
		}
		return false;
	}
};
