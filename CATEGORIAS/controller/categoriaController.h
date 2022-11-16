#pragma once
#include <iostream>
#include <vector>
#include"../model/categoria.h"
#include<fstream>
using namespace std;
void menuCategorias();
void menuCategoriasPersonal();
void agrCategorias();
void listOfItemsCat();
void buscarCat();
void modificarCat();
void eliminarCat();
int generarCod_0(int)
string dameNomCat(int);

class CategoriaController
{
private:
	vector<Categoria> vectorCategoria;/*Crear el arreglo de objetos*/	
public:
	CategoriaController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arregl
	void add(Categoria obj)
	{
		vectorCategoria.push_back(obj);
	}
	
	Categoria get(int pos)
	{
		return vectorCategoria[pos];
	}
	
	int size()
	{
		return vectorCategoria.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorCategoria[size() - 1].getCodCat() + 1;
		}
	}
	
	Categoria getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int central;
		Categoria objError;
		objError.setNomCat("Error");
		if (inferior > superior) // no encontrado
			return objError;
		else
		{
			central = (inferior + superior) / 2;
			if (vectorCategoria[central].getCodCat() == codigo)
				return vectorCategoria[central];
			else if (vectorCategoria[central].getCodCat() < codigo)
				return getBuscarPorCodigo(codigo, central + 1, superior);
			else
				return getBuscarPorCodigo(codigo, inferior, central - 1);
		}
	}
	
	bool modificar(Categoria obj,string nom)
	{
		for(int i=0;i<vectorCategoria.size();i++)
		{
			if(obj.getCodCat() == vectorCategoria[i].getCodCat())	
			{
				vectorCategoria[i].setNomCat(nom);
				return true;
			}
		}
		return false;
	}
	
	int getPostArray(Categoria obj)
	{
		for(int i=0;i<vectorCategoria.size();i++)
		{
			if(obj.getCodCat() == vectorCategoria[i].getCodCat())	
			{
				return i;
			}
		}		
		return -1;
	}
	void remove(Categoria obj)
	{
		vectorCategoria.erase(vectorCategoria.begin() + getPostArray(obj));
	}
	
	void grabarEnArchivo(Categoria obj)
	{
		try
		{
			fstream archivoCategoria;
			archivoCategoria.open("categorias.csv",ios::app);
			if(archivoCategoria.is_open())
			{
				archivoCategoria<<obj.getCodCat()<<";"<<obj.getNomCat()<<";"<<endl;
				archivoCategoria.close();					
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
			fstream archivoCategoria;
			archivoCategoria.open("categorias.csv",ios::out);
			if(archivoCategoria.is_open())
			{
				for(Categoria x:vectorCategoria)
				{
					archivoCategoria<<x.getCodCat()<<";"<<x.getNomCat()<<";"<<endl;
				}
				archivoCategoria.close();					
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
			string 	temporal[2];
			fstream	archivoCategoria;
			archivoCategoria.open("categorias.csv",ios::in);
			if(archivoCategoria.is_open())
			{
				while(!archivoCategoria.eof() && getline(archivoCategoria,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Categoria objCategoria(stoi(temporal[0]),temporal[1]);
					
					add(objCategoria);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};
CategoriaController* catController = new CategoriaController();

void menuCategorias()
{
	int opt;
	do
	{
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\t\t\t\t\t\t*************MENU DE CATEGORIAS************\n\n";
		cout<<"\t\t\t\t\t\t**********AGREGAR CATEGORIAS***********[1]\n\n";
		cout<<"\t\t\t\t\t\t**********LISTAR CATEGORIAS************[2]\n\n";
		cout<<"\t\t\t\t\t\t**********BUSCAR CATEGORIAS************[3]\n\n";
		cout<<"\t\t\t\t\t\t*********MODIFICAR CATEGORIAS**********[4]\n\n";
		cout<<"\t\t\t\t\t\t*********ELIMINAR CATEGORIAS***********[5]\n\n";
		cout<<"\t\t\t\t\t\t*****************SALIR*****************[6]\n\n";
		cout<<"\t\t\t\t\t\t***********INGRESE UNA OPCION***********:";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");agrCategorias();break;
		case 2:system("cls");listOfItemsCat();break;
		case 3:system("cls");buscarCat();break;
		case 4:system("cls");modificarCat();break;
		case 5:system("cls");eliminarCat();break;
		case 6:cout<<"\t\t\t\t\t\tGracias por usar nuestro programa\n";break;
		default:system("cls");cout<<"INGRESA UNA OPCION CORRECTA[1-6]\n";
		}
	}while(opt!=6);
}

void agrCategorias()
{
	string categoria[10];
	string nomCat;
	string flag;
	int cod;
	int cod_0;
	bool correcto = true;
	do
	{
		cod = catController->getCorrelativo();
		cod_0 = generarCod_0(cod);
		cout<<"\t\t\t\t\t\t******("<<cod<<")*******\n";
		cin.ignore();
		cout<<"\t\t\t\t\t\tNombre de la categoria: ";
		getline(cin,nomCat);
		
		for(int i = 0;i<catController->size();i++)//obteniendo los datos del archivo para meterlos en un arreglo
		{
			categoria[i] = catController->get(i).getNomCat();
		}
		
		for(int i = 0;i<catController->size();i++)//iterando entre todos los elementos del arreglo para ver si a se ha introducido el nombre de la categoria anteriormente
		{
			if(nomCat == categoria[i])
			{
				cout<<"\t\t\t\t\t\tLa categoria ya existe en el registro de categorias\n";
				correcto = false;
				break;
			}
		}
		
		if(correcto == true)
		{
			Categoria cat(cod_0, nomCat);//creamos un objeto categoria 
			
			catController->add(cat);//agregamos el objeto a nuestro arreglo de objetos
			
			catController->grabarEnArchivo(cat);//grabamos la informacion del objeto en el archivo
		}
		
		cout<<"\t\t\t\t\t\tContinuar(S/s):";
		cin>>flag;
		system("cls");
	} while(flag == "S" || flag == "s");
}

void listOfItemsCat()
{
	cout<<"\n\n\n\n\n\n";
	cout<<"\t\t\t\t\t|----CODIGO----|\t\t|----NOMBRE----| \n";
	for(int i = 0;i<catController->size();i++)
	{
		cout<<"\t\t\t\t\t\t"<<catController->get(i).getCodCat()<<"\t\t\t"<<catController->get(i).getNomCat()<<endl;
	}
	
	system("pause");
	system("cls");	
}

void buscarCat()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = catController->size()-1;
	cout<<"\t\t\t\t\t\tIngrese codigo a buscar:";
	cin>>cod;
	Categoria catObj = catController->getBuscarPorCodigo(cod, inferior, superior);
	if(catObj.getNomCat() !="Error")
	{
		cout<<"\t\t\t\t\t\tRegistro encontrado!!\n\n";
		cout<<"\t\t\t\t\t\tCodigo de la categoria: "<<catObj.getCodCat()<<"\n";
		cout<<"\t\t\t\t\t\tNombre de la categoria: "<<catObj.getNomCat()<<"\n";
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
	system("pause");
	system("cls");
}

void modificarCat()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = catController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngresar el codigo a modificar:";
	cin>>cod;
	Categoria catObj = catController->getBuscarPorCodigo(cod, inferior, superior);
	if(catObj.getNomCat() != "Error")
	{	
		/*Buscar objeto a modificar*/
		cout<<"\t\t\t\t\t\tRegistro encontrado\n";
		cout<<"\t\t\t\t\t\tCodigo de la categoria: "<<catObj.getCodCat()<<"\n";
		cout<<"\t\t\t\t\t\tNombre de la categoria: "<<catObj.getNomCat()<<"\n";
		cin.ignore();	
		/*Fin del objeto a modificar*/
		string nomC;
		int	  codCate;
		bool estado;
		cout<<"\t\t\t\t\t\tModificando Campos\n";
		cout<<"\t\t\t\t\t\tModificando el nombre...: ";
		getline(cin, nomC);

		estado = catController->modificar(catObj,nomC);
		if(estado == true)
		{
			cout<<"\t\t\t\t\t\tRegistro modificado satisfactoriamente!!!\n";
			//Grabar en archivo
			catController->grabarModificarEliminarArchivo();
		}
		else
		{
			cout<<"\t\t\t\t\t\tNo encontro el registro a modificar!\n";
			system("pause");		
		}
	}
	else
	{
		cout<<"No se encontro el registro\n";		
	}
	system("pause");
	system("cls");	
}

void eliminarCat()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = catController->size()-1;
	cout<<"\t\t\t\t\t\tIngrese codigo a buscar:";
	cin>>cod;
	Categoria objEliminar = catController->getBuscarPorCodigo(cod, inferior, superior);
	if(objEliminar.getNomCat() !="Error")
	{
		catController->remove(objEliminar);
		cout<<"\t\t\t\t\t\tRegistro eliminado satisfactoriamente!!!";
		/*Grabar en archivo*/
		catController->grabarModificarEliminarArchivo();
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
}

string dameNomCat(int cod)
{
	for(int i = 0; i<catController->size(); i++)
	{
		if(cod == catController->get(i).getCodCat())
		{
			return catController->get(i).getNomCat();
		}
	}
	return "no encontrado";
}

void menuCategoriasPersonal()
{
	int opt;
	do
	{
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\t\t\t\t\t\t************MENU DE CATEGORIAS*************\n\n";
		cout<<"\t\t\t\t\t\t***********LISTAR CATEGORIAS************[1]\n\n";
		cout<<"\t\t\t\t\t\t***********BUSCAR CATEGORIAS************[2]\n\n";
		cout<<"\t\t\t\t\t\t*****************SALIR******************[3]\n\n";
		cout<<"\t\t\t\t\t\t************INGRESE UNA OPCION************: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");listOfItemsCat();break;
		case 2:system("cls");buscarCat();break;
		case 3:cout<<"\t\t\t\t\t\tGracias por usar nuestro programa\n";break;
		default:system("cls");cout<<"I\t\t\t\t\t\tNGRESA UNA OPCION CORRECTA[1-4]\n";
		}
	}while(opt!=3);
}

int generarCod_0(int i)
{	
	cout.fill  ('0');    
	cout.width ( 8 );
	return i;
}
