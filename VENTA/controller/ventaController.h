#pragma once
#include <vector>
#include<iostream>
#include<fstream>
#include"../model/venta.h"
#include"../../CLIENTES/controller/clienteController.h"
#include"../../VIEW/interfazdemas.h"

void menuDeVentas();
void listarVentas();
void buscarVenta();
void eliminarVenta();
string dameNomCli(int);

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
	
	int getPostArray(Venta obj)
	{
		for(int i=0;i<vectorVenta.size();i++)
		{
			if(obj.getCodVenta() == vectorVenta[i].getCodVenta())	
			{
				return i;
			}
		}		
		return -1;
	}
	
	void remove(Venta obj)
	{
		vectorVenta.erase(vectorVenta.begin() + getPostArray(obj));
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
				archivoVenta<<obj.getCodVenta()<<";"<<obj.getCodCliVen()<<";"<<obj.getFechaVen()<<";"<<obj.getCodVenta()<<";"<<obj.getTotalVen()<<";"<<obj.getVendedor()<<";"<<endl;
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
					archivoVenta<<x.getCodVenta()<<";"<<x.getCodCliVen()<<";"<<x.getFechaVen()<<";"/*<<x.getSerieVen()<<";"*/<<x.getTotalVen()<<";"<<x.getVendedor()<<";"<<endl;
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

void menuDeVentas()
{
	int opt;
	do
	{
		interfazDemasG();
		gotoxyD(0,2);
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\t\t\t\t\t\t*************MENU DE VENTAS************\n\n";
		cout<<"\t\t\t\t\t\t**********LISTAR VENTAS**************[1]\n\n";
		cout<<"\t\t\t\t\t\t************BUSCAR VENTAS************[2]\n\n";
		cout<<"\t\t\t\t\t\t***********ELIMINAR VENTAS***********[3]\n\n";
		cout<<"\t\t\t\t\t\t****************SALIR****************[4]\n\n";
		cout<<"\t\t\t\t\t\t***********INGRESE UNA OPCION***********:";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");listarVentas();break;
		case 2:system("cls");buscarVenta();break;
		case 3:system("cls");eliminarVenta();break;
		case 4:cout<<"\t\t\t\t\t\tGracias por usar nuestro programa\n";break;
		default:system("cls");cout<<"\t\t\t\t\t\tINGRESA UNA OPCION CORRECTA[1-4]\n";
		}
	}
	while(opt!=4);
}


void listarVentas()
{
	cout<<"\n\n\n\n\n\n";
	cout<<"\t|----COD.VENTA----|  |----CLIENTE----|  |----FECHA----|   |----SERIE----|   |----TOTAL---|     |----VENDEDOR---| \n";
	for(int i = 0;i<ventaController->size();i++)
	{
		cout<<"\t\t"<<ventaController->get(i).getCodVenta()<<"     \t\t"<<dameNomCli(ventaController->get(i).getCodCliVen())<<"\t"
			<<ventaController->get(i).getFechaVen()<<"\t\t"
/*			<<ventaController->get(i).getSerieVen()<<"\t\t"*/
			<<ventaController->get(i).getTotalVen()<<"\t\t";
/*			<<ventaController->get(i).getVendedor()<<endl;
*/	}
	
	system("pause");
	system("cls");	
}

void buscarVenta()
{
	interfazDemasG();
	gotoxyD(0,5);
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = ventaController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese codigo a buscar: ";
	cin>>cod;
	Venta venObj = ventaController->getBuscarPorCodigo(cod, inferior, superior);
	if(venObj.getFechaVen() !="Error")
	{
		cout<<"\t\t\t\t\t\tRegistro encontrado!\n\n";
		cout<<"\t\t\t\t\t\tCodigo de venta: "<<venObj.getCodVenta()<<"\n";
		cout<<"\t\t\t\t\t\tCliente :"<<dameNomCli(venObj.getCodCliVen())<<"\n";
		cout<<"\t\t\t\t\t\tFecha: "<<venObj.getFechaVen()<<"\n";
/*		cout<<"\t\t\t\t\t\tSerie: "<<venObj.getSerieVen()<<"\n";*/
		cout<<"\t\t\t\t\t\tTotal: "<<venObj.getTotalVen()<<"\n";
		cout<<"\t\t\t\t\t\tVendedor: "<<venObj.getVendedor()<<"\n";
		
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
	system("pause");
	system("cls");
}


void eliminarVenta()
{
	interfazDemasG();
	gotoxyD(0,5);
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = ventaController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese codigo a eliminar: ";
	cin>>cod;
	Venta venEliminar = ventaController->getBuscarPorCodigo(cod, inferior, superior);
	if(venEliminar.getFechaVen() != "Error")
	{
		ventaController->remove(venEliminar);
		cout<<"\t\t\t\t\t\tRegistro eliminado satisfactoriamente!!!";
		/*Grabar en archivo*/
		ventaController->grabarModificarEliminarArchivoVenta();
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
}

string dameNomCli(int cod)
{
	for(int i = 0; i<cliController->size(); i++)
	{
		if(cod == cliController->get(i).getCodigo())
		{
			return cliController->get(i).getNomCli();
		}
	}
	return "no encontrado";
}
