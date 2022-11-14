#pragma once
#include <vector>
#include<iostream>
#include<fstream>
#include"../model/detalleVenta.h"

using namespace std;

class DetalleVentaController
{
private:
	vector<DetalleVenta> vectorDetalleVenta;
public:
	DetalleVentaController()
	{
		cargarDatosDelArchivoAlVectorDetalleVenta();
	}
	
	void add(DetalleVenta obj)
	{
		vectorDetalleVenta.push_back(obj);
	}
	
	DetalleVenta get(int pos)
	{
		return vectorDetalleVenta[pos];
	}
	
	int size()
	{
		return vectorDetalleVenta.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorDetalleVenta[size() - 1].getCodDetVen() + 1;
		}
	}
	
	void grabarEnArchivoDetalleVenta(DetalleVenta obj)
	{
		try
		{
			fstream archivoDetalleVenta;
			archivoDetalleVenta.open("detalleVenta.csv",ios::app);
			if(archivoDetalleVenta.is_open())
			{
				archivoDetalleVenta<<obj.getCodDetVen()<<";"<<obj.getCodProDetVen()<<";"<<obj.getCantDetVen()<<";"<<obj.getPrecDetVen()<<";"<<obj.getImDetVen()<<";"<<endl;
				archivoDetalleVenta.close();					
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
		}
	}
	
	void grabarModificarEliminarArchivoDetalleVenta()
	{
		try
		{
			fstream archivoDetalleVenta;
			archivoDetalleVenta.open("detalleVenta.csv",ios::out);
			if(archivoDetalleVenta.is_open())
			{
				for(DetalleVenta x:vectorDetalleVenta)
				{
					archivoDetalleVenta<<x.getCodDetVen()<<";"<<x.getCodProDetVen()<<";"<<x.getCantDetVen()<<";"<<x.getPrecDetVen()<<";"<<x.getImDetVen()<<";"<<endl;
				}
				archivoDetalleVenta.close();					
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
		}		
	}
	
	void cargarDatosDelArchivoAlVectorDetalleVenta()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string 	temporal[5];
			fstream	archivoDetalleVenta;
			archivoDetalleVenta.open("venta.csv",ios::in);
			if(archivoDetalleVenta.is_open())
			{
				while(!archivoDetalleVenta.eof() && getline(archivoDetalleVenta,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					DetalleVenta objDetVenta(stoi(temporal[0]),stoi(temporal[1]),
								   stoi(temporal[2]),stof(temporal[3]),stof(temporal[4]));
					
					add(objDetVenta);
				}
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
		}
	}
	
};
