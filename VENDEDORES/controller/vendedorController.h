#pragma once
#include <iostream>
#include <vector>
#include"../model/vendedor.h"
#include<fstream>
using namespace std;
void menuVendedores();
void agrVendedores();
void listadoVen();
void buscarVen();
void modificarVen();
void eliminarVen();

class VendedorController
{
private:
	vector<Vendedor> vectorVendedor;/*Crear el arreglo de objetos*/	
public:
	VendedorController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arregl
	void add(Vendedor obj)
	{
		vectorVendedor.push_back(obj);
	}
	
	Vendedor get(int pos)
	{
		return vectorVendedor[pos];
	}
	
	int size()
	{
		return vectorVendedor.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorVendedor[size() - 1].getCodVen() + 1;
		}
	}
	
	Vendedor getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int central;
		Vendedor objError;
		objError.setNomApeVen("Error");
		if (inferior > superior) // no encontrado
			return objError;
		else
		{
			central = (inferior + superior) / 2;
			if (vectorVendedor[central].getCodVen() == codigo)
				return vectorVendedor[central];
			else if (vectorVendedor[central].getCodVen() < codigo)
				return getBuscarPorCodigo(codigo, central + 1, superior);
			else
				return getBuscarPorCodigo(codigo, inferior, central - 1);
		}
	}
	
	bool modificar(Vendedor obj,string nomApeVendedor, string direccion, int edad)
	{
		for(int i=0;i<vectorVendedor.size();i++)
		{
			if(obj.getCodVen() == vectorVendedor[i].getCodVen())	
			{
				vectorVendedor[i].setNomApeVen(nomApeVendedor);
				vectorVendedor[i].setDirVen(direccion);
				vectorVendedor[i].setEdadVen(edad);
				return true;
			}
		}
		return false;
	}
	
	int getPostArray(Vendedor obj)
	{
		for(int i=0;i<vectorVendedor.size();i++)
		{
			if(obj.getCodVen() == vectorVendedor[i].getCodVen())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(Vendedor obj)
	{
		vectorVendedor.erase(vectorVendedor.begin() + getPostArray(obj));
	}
	
	void grabarEnArchivo(Vendedor obj)
	{
		try
		{
			fstream archivoVendedores;
			archivoVendedores.open("vendedores.csv",ios::app);
			if(archivoVendedores.is_open())
			{
				archivoVendedores<<obj.getCodVen()<<";"<<obj.getNomApeVen()<<";"<<obj.getDir()<<";"<<obj.getEdad()<<";"<<endl;
				archivoVendedores.close();					
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
	
	void grabarModificarEliminarArchivo()
	{
		try
		{
			fstream archivoVendedores;
			archivoVendedores.open("vendedores.csv",ios::out);
			if(archivoVendedores.is_open())
			{
				for(Vendedor x:vectorVendedor)
				{
					archivoVendedores<<x.getCodVen()<<";"<<x.getNomApeVen()<<";"<<x.getDir()<<";"<<x.getEdad()<<endl;
				}
				archivoVendedores.close();					
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}		
	}
	
	void cargarDatosDelArchivoAlVector()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string 	temporal[4];
			fstream	archivoVendedores;
			archivoVendedores.open("vendedores.csv",ios::in);
			if(archivoVendedores.is_open())
			{
				while(!archivoVendedores.eof() && getline(archivoVendedores,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Vendedor objVendedor(stoi(temporal[0]),temporal[1],temporal[2],stoi(temporal[3]));
					
					add(objVendedor);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};

VendedorController* venController = new VendedorController();

void menuVendedores()
{
	int opt;
	do
	{
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\t\t\t\t\t\t*************MENU DE VENDEDORES************\n\n";
		cout<<"\t\t\t\t\t\t********AGREGAR NUEVOS VENDEDORES*******[1]\n\n";
		cout<<"\t\t\t\t\t\t***********LISTAR VENDEDORES************[2]\n\n";
		cout<<"\t\t\t\t\t\t***********BUSCAR VENDEDORES************[3]\n\n";
		cout<<"\t\t\t\t\t\t**********MODIFICAR VENDEDORES**********[4]\n\n";
		cout<<"\t\t\t\t\t\t**********ELIMINAR VENDEDORES***********[5]\n\n";
		cout<<"\t\t\t\t\t\t*****************SALIR******************[6]\n\n";
		cout<<"\t\t\t\t\t\t***********INGRESE UNA OPCION***********:";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");agrVendedores();break;
		case 2:system("cls");listadoVen();break;
		case 3:system("cls");buscarVen();break;
		case 4:system("cls");modificarVen();break;
		case 5:system("cls");eliminarVen();break;
		case 6:cout<<"\t\t\t\t\t\tGracias por usar nuestro programa\n";break;
		default:system("cls");cout<<"\t\t\t\t\t\tINGRESA UNA OPCION CORRECTA[1-6]\n";
		}
	}
	while(opt!=6);
}

void agrVendedores()
{
	string flag;
	int 	cod;
	string 	nApeVen;
	string	dir;
	int 	edad;
	do
	{
		cod = venController->getCorrelativo();
		cout<<"\n\n\n\n\n\n\t\t\t\t\t\t******("<<cod<<")*******\n";
		cin.ignore();
		cout<<"\t\t\t\t\t\tNombres y Apellidos: ";
		getline(cin,nApeVen);
		cout<<"\t\t\t\t\t\tDireccion: ";
		getline(cin,dir);
		cout<<"\t\t\t\t\t\tEdad: ";
		cin>>edad;
		cout<<"\t\t\t\t\t\tContinuar(S/s): ";
		cin>>flag;
		/*Crear el objeto de tipo alumno*/
		Vendedor objVen(cod,nApeVen,dir,edad);
		/*Agregar el objeto alarreglo*/
		venController->add(objVen);
		//grabar en archivo
		venController->grabarEnArchivo(objVen);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}

void listadoVen()
{
	cout<<"\n\n\n\n\n\n";
	cout<<"\t\t\t|----CODIGO----|  |----NOMBRE----|   |----DIRECCION----|\t|----EDAD---|\n";
	for(int i = 0;i<venController->size();i++)
	{
		cout<<"\t\t\t\t"<<venController->get(i).getCodVen()<<"\t      "<<venController->get(i).getNomApeVen()<<"\t      "
			<<venController->get(i).getDir()<<"\t      "
			<<venController->get(i).getEdad()<<endl;
	}
	system("pause");
	system("cls");	
}

void buscarVen()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = venController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese codigo a buscar:";
	cin>>cod;
	Vendedor venObj = venController->getBuscarPorCodigo(cod, inferior, superior);
	if(venObj.getNomApeVen() !="Error")
	{
		cout<<"\t\t\t\t\t\tRegistro encontrado!\n\n";
		cout<<"\t\t\t\t\t\tCodigo: "<<venObj.getCodVen()<<"\n";
		cout<<"\t\t\t\t\t\tNombre :"<<venObj.getNomApeVen()<<"\n";
		cout<<"\t\t\t\t\t\tDni: "<<venObj.getDir()<<"\n";
		cout<<"\t\t\t\t\t\tEdad: "<<venObj.getEdad()<<"\n\n";
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
	system("pause");
	system("cls");
}

void modificarVen()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = venController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngresar el codigo a modificar:";
	cin>>cod;
	Vendedor venObj = venController->getBuscarPorCodigo(cod, inferior, superior);
	if(venObj.getNomApeVen() != "Error")
	{	
		/*Buscar objeto a modificar*/
		cout<<"\t\t\t\t\t\t*****Registro Encontrado*****!\n";
		cout<<"\t\t\t\t\t\tCodigo:"<<venObj.getCodVen()<<"\n";
		cout<<"\t\t\t\t\t\tNombre:"<<venObj.getNomApeVen()<<"\n";
		cout<<"\t\t\t\t\t\tDni:"<<venObj.getDir()<<"\n";
		cout<<"\t\t\t\t\t\tEdad:"<<venObj.getEdad()<<"\n";
		//cin.ignore();	
		/*Fin del objeto a modificar*/
		string nomApeVen,dir,flag;
		int	   edad,opt;	
		bool estado;
		cout<<"\t\t\t\t\t\tDesea modificar todo el objeto?(S/s): ";
		cin>>flag;
		if(flag == "S" || flag == "s")
		{
			cout<<"\t\t\t\t\t\tModificando Campos\n";
			cout<<"\t\t\t\t\t\tModificando el Nombre...:";	
			getline(cin,nomApeVen);
			cout<<"\t\t\t\t\t\tModificando la direccion...:";
			getline(cin,dir);
			cin.ignore();
			cout<<"\t\t\t\t\t\tModificando la edad...:";
			cin>>edad;
			estado = venController->modificar(venObj,nomApeVen,dir,edad);
		}
		else
		{
			do
			{
				cout<<"\t\t\t\t\t\t********MODIFICAR NOMBRE********[1]\n";
				cout<<"\t\t\t\t\t\t*******MODIFICAR DIRECCION******[2]\n";
				cout<<"\t\t\t\t\t\t*********MODIFICAR EDAD*********[3]\n";
				cout<<"\t\t\t\t\t\t*************SALIR**************[4]\n\n";
				
				cout<<"\t\t\t\t\t\tINGRESE UNA OPCION: ";
				cin>>opt;
				switch(opt)
				{
				case 1:	system("cls");
				{
					cin.ignore();
					cout<<"\t\t\t\t\t\tModificando el Nombre...: ";
					getline(cin,nomApeVen);
					dir = venObj.getDir();
					edad = venObj.getEdad();
					estado = venController->modificar(venObj,nomApeVen,dir,edad);
					break;
				}
				case 2: system("cls");
				{
					cout<<"\t\t\t\t\t\tModificando la Direccion...: ";
					cin.ignore();
					getline(cin,dir);
					nomApeVen = venObj.getNomApeVen();
					edad = venObj.getEdad();
					estado = venController->modificar(venObj,nomApeVen,dir,edad);
					break;
				}
				case 3:	system("cls");
				{
					cout<<"\t\t\t\t\t\tModificando la edad...: ";
					cin>>edad;
					nomApeVen = venObj.getNomApeVen();
					dir = venObj.getDir();
					estado = venController->modificar(venObj,nomApeVen,dir,edad);
					break;
				}
				default:system("cls");"Ingrese una opcion valida[1-3]: ";
				}
			} while(opt != 4);
			
		}
		if(estado == true)
		{
			cout<<"\t\t\t\t\t\tRegistro modificado satisfactoriamente!!!\n";
			//Grabar en archivo
			venController->grabarModificarEliminarArchivo();
		}
		else
		{
			cout<<"\t\t\t\t\t\tNo encontro el registro a modificar!\n";
			system("pause");		
		}
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro\n";		
	}
	system("pause");
	system("cls");	
}

void eliminarVen()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = venController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese codigo a eliminar:";
	cin>>cod;
	Vendedor venEliminar = venController->getBuscarPorCodigo(cod, inferior, superior);
	if(venEliminar.getNomApeVen() !="Error")
	{
		venController->remove(venEliminar);
		cout<<"\t\t\t\t\t\tRegistro eliminado satisfactoriamente!!!";
		/*Grabar en archivo*/
		venController->grabarModificarEliminarArchivo();
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
}
