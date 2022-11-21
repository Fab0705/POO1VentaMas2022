#pragma once
#include <vector>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include"ventaController.h"
#include"../model/detalleCompra.h"
#include"../model/detalleVenta.h"
#include"detalleVentaController.h"
#include"../../CLIENTES/controller/clienteController.h"
#include"../../PRODUCTOS/controller/productoController.h"
#include<fstream>
#include <ctime>
using namespace std;
void generarVenta(string);
void buscarProdCom(int,int);
void eliminarProCom();
void listarProCom();
int buscarxNomCompra();
string generarFecha();
string generarSerie(string);

class DetalleCompraController
{
private:
 	vector<DetalleCompra> vectorDetalleCompra;/*Crear el arreglo de objetos*/	
public:
	void add(DetalleCompra obj)
	{
		vectorDetalleCompra.push_back(obj);
	}
	
	DetalleCompra get(int pos)
	{
		return vectorDetalleCompra[pos];
	}
	
	int size()
	{
		return vectorDetalleCompra.size();
	}
	
	int getPostArray(DetalleCompra obj)
	{
		for(int i=0;i<vectorDetalleCompra.size();i++)
		{
			if(obj.getCodProCom() == vectorDetalleCompra[i].getCodProCom())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(DetalleCompra obj)
	{
		vectorDetalleCompra.erase(vectorDetalleCompra.begin() + getPostArray(obj));
	}
	
	DetalleCompra getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int central;
		DetalleCompra objError;
		objError.setNomProCom("Error");
		if (inferior > superior) // no encontrado
			return objError;
		else
		{
			central = (inferior + superior) / 2;
			if (vectorDetalleCompra[central].getCodProCom() == codigo)
				return vectorDetalleCompra[central];
			else if (vectorDetalleCompra[central].getCodProCom() < codigo)
				return getBuscarPorCodigo(codigo, central + 1, superior);
			else
				return getBuscarPorCodigo(codigo, inferior, central - 1);
		}
	}
};

DetalleCompraController* detCompraController = new DetalleCompraController();
DetalleVentaController* detVentaController = new DetalleVentaController();
DetalleCompra objDetCompra;

float importe;
float total = 0;

void generarVenta(string vendedor)
{
	int	codPro,
		codCli,
		cantPro,
		codEli,
		cont = 0;
	string	fecha,
			codVenta,
			nomPro,
			flag,
			flagE,
			flagC,
			flagB,
			flagBuscarOtraVez;
	cout<<"\t\t\t\t**********G E N E R A R   C O M P R A***********\n";
	cout<<"\t\t-----------------------------CLIENTE------------------------------\n";
	cout<<"Desea agregar un nuevo cliente?(S/s): "<<endl;
	cin>>flag;
	if(flag == "S" || flag == "s")
	{
		addItems();
	}
	flag = "a";
	codCli = buscarxNomCompra();
	fecha = generarFecha();
	cout<<"\t-----------------------------PRODUCTOS------------------------------\n";
	do
	{
		if(cont != 0)
		{
			ingreso:
			{
				cout<<"Ingrese el nombre del producto a buscar: "<<endl;
				cin>>nomPro;
			}
			cont++;
		}
		else
		{
			cout<<"Ingrese el nombre del producto a buscar: "<<endl;
			cin>>nomPro;
			
		}
		if(proController->buscarPorNombre(nomPro) == true)
		{
			//cout<<"--------------------------DETALLE COMPRA----------------------------\n";
			do
			{
				do
				{
					cout<<"Ingrese el codigo del producto a comprar: "<<endl;
					cin>>codPro;
					cin.ignore();
					cout<<"Ingrese la cantidad de productos a comprar: "<<endl;
					cin>>cantPro;
					buscarProdCom(codPro, cantPro);
					cout<<"Desea seguir comprando este producto?(S/s): ";
					cin>>flagC;
				} while(flagC == "S" || flagC == "s");
				cout<<"\t--------------------------DETALLE COMPRA----------------------------\n";
				listarProCom();
				cout<<"Desea eliminar alguna compra?(S/s): ";
				cin>>flagE;
				if(flagE == "S" || flagE == "s")
				{
					eliminarProCom();
					listarProCom();
				}
				cout<<"Desea buscar otro producto?(S/s): ";
				cin>>flagB;
				if(flagB == "S" || flagB == "s")
				{
					system("cls");
					goto ingreso;
				}
				cout<<"Desea terminar la compra?(S/s): ";
				cin>>flag;
				system("cls");
				if(flag == "S" ||  flag == "s")
				{
					goto listargrabar;
				}
			} while(flag != "S" || flag != "s");
		}
		else
		{
			cout<<"\t\t\t\tNo tenemos ese producto :C\n";
			cout<<"Deseas buscar otra vez?(S/s): ";
			cin>>flagBuscarOtraVez;
			system("cls");
		}
	} while(flagBuscarOtraVez == "S" || flagBuscarOtraVez == "s" || flag != "S" || flag != "s");
	listargrabar:
	{
		cout<<"\n\n\n\t\t---------------------------------VENTA EXITOSA!!!!-----------------------------------";
		cout<<"\n\n\n\t\t-------------------------GRACIAS POR CONFIAR EN VENTAMAS-----------------------------";
		listarProCom();
		//----------------------GRABAR EN ARCHIVO VENTA-------------------------//
		codVenta = generarSerie(to_string(ventaController->getCorrelativo()));
		Venta objVenta(stoi(codVenta),codCli,fecha,total,vendedor);
		/*Agregar el objeto al arreglo*/
		ventaController->add(objVenta);
		//grabar en archivo
		ventaController->grabarEnArchivoVenta(objVenta);
		//------------------GRABAR EN ARCHIVO DETALLE DE VENTA-------------------//
		if(detCompraController->size() > 1)
		{
			for(int i = 0; i<detCompraController->size(); i++)
			{
				//crear objeto
				DetalleVenta objDetVenta(stoi(codVenta),detCompraController->get(i).getCodProCom(), detCompraController->get(i).getCantProdCom(), detCompraController->get(i).getPrecProdCom(), detCompraController->get(i).getImCom());
				//agregarlo al arreglo de objetos
				detVentaController->add(objDetVenta);
				//grabar en archivo
				detVentaController->grabarEnArchivoDetalleVenta(objDetVenta);
			}
		}
	}
	system("pause");
	system("cls");
}


void buscarProdCom(int codPro, int cantPro)
{
	int	inferior,
		superior;
	inferior = 0;
	superior = proController->size()-1;
	Producto proObj = proController->getBuscarPorCodigo(codPro, inferior, superior);
	if(proObj.getNomPro() !="Error")
	{
		string nombre;
		float precio;
		nombre = proObj.getNomPro();
		precio = proObj.getPrePro();
		importe = cantPro*proObj.getPrePro();
		total = total + importe;
		//Crear objeto de tipo DetalleCompra
		DetalleCompra objDetCompra(codPro, nombre, cantPro, precio, importe);
		//Agregar el objeto al arreglo//
		detCompraController->add(objDetCompra);
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
	system("pause");
}

void eliminarProCom()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = detCompraController->size()-1;
	cout<<"\t\t\t\tIngrese el codigo a eliminar: ";
	cin>>cod;
	DetalleCompra objEliminar = detCompraController->getBuscarPorCodigo(cod, inferior, superior);
	if(objEliminar.getNomProdCom() !="Error")
	{
		detCompraController->remove(objEliminar);
		cout<<"\t\t\t\tRegistro eliminado satisfactoriamente!!";
	}
	else
	{
		cout<<"\t\t\t\tNo se encontro el registro!\n";
	}
}

void listarProCom()
{
	cout<<"\n\n\n";
	cout<<"\t|----CODIGO----|  |----NOMBRE----|   |----CANTIDAD----|  |----PRECIO---|  |----IMPORTE---|\n\n";
	for(int i = 0; i<detCompraController->size(); i++)
	{
		cout<<"\t\t\t"<<detCompraController->get(i).getCodProCom()<<"\t"<<detCompraController->get(i).getNomProdCom()<<
			"\t"<<detCompraController->get(i).getCantProdCom()<<"\t"<<detCompraController->get(i).getPrecProdCom()<<"\t"<<
			detCompraController->get(i).getImCom()<<endl;
	}
}

int buscarxNomCompra()
{
	string nom;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese el nombre a buscar: ";
	cin.ignore();
	getline(cin,nom);
	Cliente cliObj = cliController->getBuscarPorNombre(nom);
	if(cliObj.getNomCli() !="Error")
	{
		cout<<"\t\t\t\t\t\tRegistro encontrado!\n\n";
		cout<<"\t\t\t\t\t\tCodigo: "<<cliObj.getCodigo()<<"\n";
		//cout<<"\t\t\t\t\t\tNombre :"<<cliObj.getNomCli()<<"\n";
		cout<<"\t\t\t\t\t\tDni: "<<cliObj.getDni()<<"\n";
		cout<<"\t\t\t\t\t\tEdad: "<<cliObj.getEdad()<<"\n\n";
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
	system("pause");
	system("cls");
	return cliObj.getCodigo();
}

string generarFecha()
{
	time_t now = time(0);
	tm* time = localtime(&now);

	int anio = 1900 + time->tm_year;
	int mes = time->tm_mon + 1;
	int dia = time->tm_mday;

	return to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
}

string generarSerie(string str)
{	
	string s;
	size_t n = 8;
	int precision = n - std::min(n, str.size());
	s = string(precision, '0').append(str);
	
	return s;
}
