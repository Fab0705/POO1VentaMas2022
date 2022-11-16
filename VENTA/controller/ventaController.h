#pragma once
#include <vector>
#include<iostream>
#include<fstream>
#include"../model/venta.h"

using namespace std;

class VentaController
{
private:
	vector<Venta> vectorVenta;
public:
	VentaController()
	{
		cargarDatosDelArchivoAlVectorVenta();
	}
	
	void add(Venta obj)
	{
		vectorVenta.push_back(obj);
	}
	
	Venta get(int pos)
	{
		return vectorVenta[pos];
	}
	
	int size()
	{
		return vectorVenta.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorVenta[size() - 1].getCodVenta() + 1;
		}
	}
	
	Venta getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int central;
		Venta objError;
		objError.setFecha("Error");
		if (inferior > superior) // no encontrado
			return objError;
		else
		{
			central = (inferior + superior) / 2;
			if (vectorVenta[central].getCodVenta() == codigo)
				return vectorVenta[central];
			else if (vectorVenta[central].getCodVenta() < codigo)
				return getBuscarPorCodigo(codigo, central + 1, superior);
			else
				return getBuscarPorCodigo(codigo, inferior, central - 1);
		}
	}
	
	void grabarEnArchivoVenta(Venta obj)
	{
		try
		{
			fstream archivoVenta;
			archivoVenta.open("venta.csv",ios::app);
			if(archivoVenta.is_open())
			{
				archivoVenta<<obj.getCodVenta()<<";"<<obj.getCodCliVen()<<";"<<obj.getFechaVen()<<";"<<obj.getTotalVen()<<";"<<obj.getVendedor()<<";"<<endl;
				archivoVenta.close();					
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
		}
	}
	
	void grabarModificarEliminarArchivoVenta()
	{
		try
		{
			fstream archivoVenta;
			archivoVenta.open("venta.csv",ios::out);
			if(archivoVenta.is_open())
			{
				for(Venta x:vectorVenta)
				{
					archivoVenta<<x.getCodVenta()<<";"<<x.getCodCliVen()<<";"<<x.getFechaVen()<<";"<<x.getTotalVen()<<";"<<x.getVendedor()<<";"<<endl;
				}
				archivoVenta.close();					
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
		}		
	}
	
	void cargarDatosDelArchivoAlVectorVenta()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string 	temporal[5];
			fstream	archivoVenta;
			archivoVenta.open("venta.csv",ios::in);
			if(archivoVenta.is_open())
			{
				while(!archivoVenta.eof() && getline(archivoVenta,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Venta objVenta(stoi(temporal[0]),stoi(temporal[1]),
									   temporal[2],stof(temporal[3]),temporal[4]);
					
					add(objVenta);
				}
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
		}
	}
};

VentaController* ventaController = new VentaController();
