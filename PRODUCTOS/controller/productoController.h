#pragma once
#include <string>
#include <vector>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include"../model/producto.h"
#include"../../CATEGORIAS/model/categoria.h"
#include"../../CATEGORIAS/controller/categoriaController.h"
#include<fstream>
using namespace std;
void menuProductos();
void menuProductosPersonal();
void agrCategorias();
void addItemsPro();
void listOfItemsPro();
void buscarPro();
void modificarPro();
void eliminarPro();
void listadoProductoCat();
int generarCod_0(int);
string removeCod_0(string);

COORD coord = {0,0};

void gotoxy(int x, int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

class ProductoController
{
private:
	vector<Producto> vectorProducto;/*Crear el arreglo de objetos*/	
public:
	ProductoController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arregl
	void add(Producto obj)
	{
		vectorProducto.push_back(obj);
	}
	
	Producto get(int pos)
	{
		return vectorProducto[pos];
	}
	
	int size()
	{
		return vectorProducto.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorProducto[size() - 1].getCodPro() + 1;
		}
	}
	
	Producto getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int central;
		Producto objError;
		objError.setNomPro("Error");
		if (inferior > superior) // no encontrado
			return objError;
		else
		{
			central = (inferior + superior) / 2;
			if (vectorProducto[central].getCodPro() == codigo)
				return vectorProducto[central];
			else if (vectorProducto[central].getCodPro() < codigo)
				return getBuscarPorCodigo(codigo, central + 1, superior);
			else
				return getBuscarPorCodigo(codigo, inferior, central - 1);
		}
	}
	
	bool buscarPorNombre(string nombre)
	{ 
		bool encontro = false;
		int cont = 0;  
		for(Producto x:vectorProducto)
		{
			size_t found = (x.getNomPro()).find(nombre);
			if (found != string::npos)
			{  if(cont<1)
				{
					cout<<"\n\n\n";
					cout<<"\t|----CODIGO----|  |----STOCK----|   |----PRECIO----|\t|----NOMBRE---|\n\n"; 
					cont++;
				}
				cout<<"\t\t"<<x.getCodPro()<<"\t\t"<<x.getStkPro()<<"\t\t"<<x.getPrePro()<<"\t\t"<<x.getNomPro()<<endl;
				encontro = true;
			}
		}
		if(encontro == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	bool modificar(Producto obj,int stk,float pre,string nom, int codC)
	{
		for(int i=0;i<vectorProducto.size();i++)
		{
			if(obj.getCodPro() == vectorProducto[i].getCodPro())	
			{
				vectorProducto[i].setStkPro(stk);
				vectorProducto[i].setPrePro(pre);
				vectorProducto[i].setNomPro(nom);
				vectorProducto[i].setCodCat(codC);
				return true;
			}
		}
		return false;
	}
	
	int getPostArray(Producto obj)
	{
		for(int i=0;i<vectorProducto.size();i++)
		{
			if(obj.getCodPro() == vectorProducto[i].getCodPro())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(Producto obj)
	{
		vectorProducto.erase(vectorProducto.begin() + getPostArray(obj));
	}
	
	
	void grabarEnArchivo(Producto obj)
	{
		try
		{
			fstream archivoProducto;
			archivoProducto.open("productos.csv",ios::app);
			if(archivoProducto.is_open())
			{
				archivoProducto<<obj.getCodPro()<<";"<<obj.getStkPro()<<";"<<obj.getPrePro()<<";"<<obj.getNomPro()<<";"<<obj.getCodCat()<<";"<<endl;
				archivoProducto.close();					
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
			fstream archivoProducto;
			archivoProducto.open("productos.csv",ios::out);
			if(archivoProducto.is_open())
			{
				for(Producto x:vectorProducto)
				{
					archivoProducto<<x.getCodPro()<<";"<<x.getStkPro()<<";"<<x.getPrePro()<<";"<<x.getNomPro()<<";"<<x.getCodCat()<<";"<<endl;
				}
				archivoProducto.close();					
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
			string 	temporal[5];
			fstream	archivoProducto;
			archivoProducto.open("productos.csv",ios::in);
			if(archivoProducto.is_open())
			{
				while(!archivoProducto.eof() && getline(archivoProducto,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Producto objProducto(stoi(temporal[0]),stoi(temporal[1]),
										 stof(temporal[2]), temporal[3], stoi(temporal[4]));
					
					add(objProducto);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};

ProductoController* proController = new ProductoController();

void menuProductos()
{
	int opt;
	do
	{
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\t\t\t\t\t\t*************MENU DE PRODUCTOS************\n\n";
		cout<<"\t\t\t\t\t\t********AGREGAR NUEVOS PRODUCTOS*******[1]\n\n";
		cout<<"\t\t\t\t\t\t***********LISTAR PRODUCTOS************[2]\n\n";
		cout<<"\t\t\t\t\t\t***LISTAR DE PRODUCTOS POR CATEGORIA***[3]\n\n";
		cout<<"\t\t\t\t\t\t***********BUSCAR PRODUCTOS************[4]\n\n";
		cout<<"\t\t\t\t\t\t**********MODIFICAR PRODUCTOS**********[5]\n\n";
		cout<<"\t\t\t\t\t\t**********ELIMINAR PRODUCTOS***********[6]\n\n";
		cout<<"\t\t\t\t\t\t*****************SALIR*****************[7]\n\n";
		cout<<"\t\t\t\t\t\t***********INGRESE UNA OPCION***********:";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");addItemsPro();break;
		case 2:system("cls");listOfItemsPro();break;
		case 3:system("cls");listadoProductoCat();break;
		case 4:system("cls");buscarPro();break;
		case 5:system("cls");modificarPro();break;
		case 6:system("cls");eliminarPro();break;
		case 7:cout<<"\t\t\t\t\t\tGracias por usar nuestro programa!!\n";break;
		default:system("cls");cout<<"I\t\t\t\t\t\tNGRESE UNA OPCION VALIDA[1-6]\n";
		}
	}while(opt!=7);
}


void addItemsPro()
{
	string flag;
	int 	cod;
	int 	cod_0;
	int 	codCat;
	int		codCat_0;
	string 	nPro;
	float	prePro;
	int 	stck;
	do
	{
		
		cod = proController->getCorrelativo();
		cod_0 = generarCod_0(cod);
		cout<<"\t\t\t\t\t\t******("<<cod<<")*******\n";
		cin.ignore();
		cout<<"\t\t\t\t\t\tNombre del producto:";
		getline(cin,nPro);
		cout<<"\t\t\t\t\t\tPrecio del producto:";
		cin>>prePro;
		cout<<"\t\t\t\t\t\tStock del producto:";
		cin>>stck;

		cout<<"\t\t\t\t\t\t---------CODIGOS DE LAS CATEGORIAS-----------"<<endl;
		for(int i = 0;i<catController->size();i++)
		{
			cout<<"\t\t\t\t\t\t"<<catController->get(i).getNomCat()<<"\t\t{"<<removeCod_0(to_string(catController->get(i).getCodCat()))<<"}\t"<<endl;
		}
		cout<<"\t\t\t\t\t\tIngrese el codigo: "<<endl;
		cin>>codCat;

		codCat_0 = generarCod_0(codCat);

		cout<<"\t\t\t\t\t\tContinuar(S/s): ";
		cin>>flag;
		/*Crear el objeto de tipo producto*/
		Producto objPro(cod_0,stck,prePro,nPro,codCat_0);
		/*Agregar el objeto al arreglo*/
		proController->add(objPro);
		//grabar en archivo
		proController->grabarEnArchivo(objPro);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}

void listOfItemsPro()
{
	cout<<"\n\n\n\n\n\n";
	cout<<"\t|----CODIGO----|  |----STOCK----|   |----PRECIO----|\t|----NOMBRE---|   |----CATEGORIA----|\n";
	for(int i = 0;i<proController->size();i++)
	{
			cout<<"\t\t"<<proController->get(i).getCodPro()<<"\t\t"<<proController->get(i).getStkPro()<<"\t\t"
			<<proController->get(i).getPrePro()<<"\t\t"
			<<proController->get(i).getNomPro()<<"\t    "
			<<dameNomCat(proController->get(i).getCodCat())<<endl;
	}
	
	system("pause");
	system("cls");	
}

void buscarPro()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = proController->size()-1;
	cout<<"\t\t\t\t\t\tIngrese codigo a buscar:";
	cin>>cod;
	Producto proObj = proController->getBuscarPorCodigo(cod, inferior, superior);
	if(proObj.getNomPro() !="Error")
	{
		cout<<"\t\t\t\t\t\tRegistro encontrado!!\n\n";
		cout<<"\t\t\t\t\t\tCodigo del producto: "<<proObj.getCodPro()<<"\n";
		cout<<"\t\t\t\t\t\tStock del producto: "<<proObj.getStkPro()<<"\n";
		cout<<"\t\t\t\t\t\tPrecio del producto: "<<proObj.getPrePro()<<"\n";
		cout<<"\t\t\t\t\t\tNombre del producto: "<<proObj.getNomPro()<<"\n";
		cout<<"\t\t\t\t\t\tCodigo de la categoria del producto: "<<proObj.getCodCat()<<"\n\n";
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
	system("pause");
	system("cls");
}

void modificarPro()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = proController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese el codigo a modificar:";
	cin>>cod;
	Producto proObj = proController->getBuscarPorCodigo(cod, inferior, superior);
	if(proObj.getNomPro() != "Error")
	{	
		/*Buscar objeto a modificar*/
		cout<<"\t\t\t\t\t\tRegistro encontrado\n";
		cout<<"\t\t\t\t\t\tCodigo del producto: "<<proObj.getCodPro()<<"\n";
		cout<<"\t\t\t\t\t\tStock del producto: "<<proObj.getStkPro()<<"\n";
		cout<<"\t\t\t\t\t\tPrecio del producto: "<<proObj.getPrePro()<<"\n";
		cout<<"\t\t\t\t\t\tNombre del producto: "<<proObj.getNomPro()<<"\n";
		cout<<"\t\t\t\t\t\tCategoria del producto: "<<proObj.getCodCat()<<"\n";
		cin.ignore();	
		/*Fin del objeto a modificar*/
		string nomP,flag;
		int	   stock, codCate, opt;
		float precio;
		bool estado;
		cout<<"\t\t\t\t\t\tDesea modificar todo el objeto?(S/s): ";
		cin>>flag;
		if(flag == "S" || flag == "s")
		{
			cout<<"\t\t\t\t\t\tModificando Campos\n";
			cout<<"\t\t\t\t\t\tModificando el Stock...: ";
			cin>>stock;
			cout<<"\t\t\t\t\t\tModificando el Precio...: ";
			cin>>precio;
			cout<<"\t\t\t\t\t\tModificando el Nombre...: ";
			cin.ignore();
			getline(cin, nomP);
			cout<<"\t\t\t\t\t\tModificando el Codigo de la Categoria...: ";
			cin>>codCate;
			estado = proController->modificar(proObj,stock,precio,nomP,codCate);
		}
		else
		{
			do
			{
				cout<<"\t\t\t\t\t\t************MODIFICAR STOCK*************[1]\n";
				cout<<"\t\t\t\t\t\t************MODIFICAR PRECIO************[2]\n";
				cout<<"\t\t\t\t\t\t************MODIFICAR NOMBRE************[3]\n";
				cout<<"\t\t\t\t\t\t****MODIFICAR CODIGO DE LA CATEGORIA****[4]\n";
				cout<<"\t\t\t\t\t\t******************SALIR*****************[5]\n\n";
				
				cout<<"\t\t\t\t\t\tINGRESE UNA OPCION: ";
				cin>>opt;
				switch(opt)
				{
					case 1:	system("cls");
					{
						cout<<"\t\t\t\t\t\tModificando el Stock...: ";
						cin>>stock;
						precio = proObj.getPrePro();
						nomP = proObj.getNomPro();
						codCate = proObj.getCodCat();
						estado = proController->modificar(proObj,stock,precio,nomP,codCate);
						break;
					}
					case 2: system("cls");
					{
						cout<<"\t\t\t\t\t\tModificando el Precio...: ";
						cin>>precio;
						stock = proObj.getStkPro();
						nomP = proObj.getNomPro();
						codCate = proObj.getCodCat();
						estado = proController->modificar(proObj,stock,precio,nomP,codCate);
						break;
					}
					case 3:	system("cls");
					{
						cout<<"\t\t\t\t\t\tModificando el nombre...: ";
						cin.ignore();
						getline(cin,nomP);
						stock = proObj.getStkPro();
						precio = proObj.getPrePro();
						codCate = proObj.getCodCat();
						estado = proController->modificar(proObj,stock,precio,nomP,codCate);
						break;
					}
					case 4: system("cls");
					{
						cout<<"\t\t\t\t\t\tModificando el codigo de la categoria...: ";
						cin>>codCate;
						stock = proObj.getStkPro();
						precio = proObj.getPrePro();
						nomP = proObj.getNomPro();
						estado = proController->modificar(proObj,stock,precio,nomP,codCate);
						break;
					}
					default:system("cls");"INGRESE UNA OPCION VALIDA[1-3]: ";
				}
			} while(opt != 5);
			
		}

		if(estado == true)
		{
			cout<<"Registro modificado satisfactoriamente!!!\n";
			//Grabar en archivo
			proController->grabarModificarEliminarArchivo();
		}
		else
		{
			cout<<"No se encontro el registro a modificar!\n";
			system("pause");
			menuProductos();
		}
	}
	else
	{
		cout<<"No se encontro el registro\n";		
	}
	system("pause");
	system("cls");	
}

void eliminarPro()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = proController->size()-1;
	cout<<"Ingrese codigo a eliminar:";
	cin>>cod;
	Producto objEliminar = proController->getBuscarPorCodigo(cod, inferior, superior);
	if(objEliminar.getNomPro() !="Error")
	{
		proController->remove(objEliminar);
		cout<<"Registro eliminado satisfactoriamente!!!";
		/*Grabar en archivo*/
		proController->grabarModificarEliminarArchivo();
	}
	else
	{
		cout<<"No se encontro el registro!\n";
	}
}

void listadoProductoCat()
{
	cout<<"\t\t\t\t   ***********************************\n";
	cout<<"\t\t\t\t   Listado de productos por categorias\n";
	for(int i = 0; i<catController->size(); i++)
	{
		int cont = 0;
		for(int j = 0; j<proController->size(); j++)
		{
			if(catController->get(i).getCodCat() == proController->get(j).getCodCat())
			{
				cont++;
			}
		}
		cout<<"\t\t\t\t   Hay "<<cont<<" producto(s) de categoria "<<catController->get(i).getNomCat()<<endl;
	}
	system("pause");
	system("cls");	
}

void menuProductosPersonal()
{
	int opt;
	do
	{
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\t\t\t\t\t\t*************MENU DE PRODUCTOS************\n\n";
		cout<<"\t\t\t\t\t\t***********LISTAR PRODUCTOS************[1]\n\n";
		cout<<"\t\t\t\t\t\t***LISTAR DE PRODUCTOS POR CATEGORIA***[2]\n\n";
		cout<<"\t\t\t\t\t\t***********BUSCAR PRODUCTOS************[3]\n\n";
		cout<<"\t\t\t\t\t\t*****************SALIR*****************[4]\n\n";
		cout<<"\t\t\t\t\t\t***********INGRESE UNA OPCION************: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");listOfItemsPro();break;
		case 2:system("cls");listadoProductoCat();break;
		case 3:system("cls");buscarPro();break;
		case 4:cout<<"\t\t\t\t\t\tGracias por usar nuestro programa\n";break;
		default:system("cls");cout<<"I\t\t\t\t\t\tNGRESE UNA OPCION VALIDA[1-4]\n";
		}
	}while(opt!=4);
}

int generarCod_0(int i)
{	
	cout.fill  ('0');    
	cout.width ( 8 );
	return i;
}

string removeCod_0(string str)
{
	// Count trailing zeros
	int i = 0;
	while (str[i] == '0')
		i++;
	
	// The erase function removes i characters
	// from given index (0 here)
	str.erase(0, i);
	
	return str;
}
