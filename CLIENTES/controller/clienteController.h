#pragma once
#include <iostream>
#include <vector>
#include"../model/cliente.h"
#include<fstream>
using namespace std;
void menuClientes();
void menuClientesPersonal();
void addItems();
void listOfItems();
void buscar();
void buscarxNom();
void modificar();
void eliminar();
int generarCod_0(int);

class ClienteController
{
private:
	vector<Cliente> vectorCliente;/*Crear el arreglo de objetos*/	
public:
	ClienteController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arregl
	void add(Cliente obj)
	{
		vectorCliente.push_back(obj);
	}
	
	Cliente get(int pos)
	{
		return vectorCliente[pos];
	}
	
	int size()
	{
		return vectorCliente.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorCliente[size() - 1].getCodigo() + 1;
		}
	}
	
	Cliente getBuscarPorCodigo(int codigo, int inferior, int superior)
	{
		int central;
		Cliente objError;
		objError.setNomCli("Error");
		if (inferior > superior) // no encontrado
			return objError;
		else
		{
			central = (inferior + superior) / 2;
			if (vectorCliente[central].getCodigo() == codigo)
				return vectorCliente[central];
			else if (vectorCliente[central].getCodigo() < codigo)
				return getBuscarPorCodigo(codigo, central + 1, superior);
			else
				return getBuscarPorCodigo(codigo, inferior, central - 1);
		}
	}
	
	Cliente getBuscarPorNombre(string nombre)
	{
		Cliente objError;
		objError.setNomCli("Error");
		for(Cliente x:vectorCliente)
		{
			if(nombre == x.getNomCli())	
			{
				return x;
			}
		}
		
		return objError;
	}
	
	
	bool modificar(Cliente obj,string nom,string dni,int edad)
	{
		for(int i=0;i<vectorCliente.size();i++)
		{
			if(obj.getCodigo() == vectorCliente[i].getCodigo())	
			{
				vectorCliente[i].setNomCli(nom);
				vectorCliente[i].setDni(dni);
				vectorCliente[i].setEdad(edad);
				return true;
			}
		}
		return false;
	}
	
	int getPostArray(Cliente obj)
	{
		for(int i=0;i<vectorCliente.size();i++)
		{
			if(obj.getCodigo() == vectorCliente[i].getCodigo())	
			{
				return i;
			}
		}		
		return -1;
	}
	
	void remove(Cliente obj)
	{
		vectorCliente.erase(vectorCliente.begin() + getPostArray(obj));
	}
	
	void grabarEnArchivo(Cliente obj)
	{
		try
		{
			fstream archivoCliente;
			archivoCliente.open("clientes.csv",ios::app);
			if(archivoCliente.is_open())
			{
				archivoCliente<<obj.getCodigo()<<";"<<obj.getNomCli()<<";"<<obj.getDni()<<";"<<obj.getEdad()<<";"<<endl;
				archivoCliente.close();					
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
		}
	}
	
	void grabarModificarEliminarArchivo()
	{
		try
		{
			fstream archivoCliente;
			archivoCliente.open("clientes.csv",ios::out);
			if(archivoCliente.is_open())
			{
				for(Cliente x:vectorCliente)
				{
					archivoCliente<<x.getCodigo()<<";"<<x.getNomCli()<<";"<<x.getDni()<<";"<<x.getEdad()<<";"<<endl;
				}
				archivoCliente.close();					
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
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
			fstream	archivoCliente;
			archivoCliente.open("clientes.csv",ios::in);
			if(archivoCliente.is_open())
			{
				while(!archivoCliente.eof() && getline(archivoCliente,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Cliente objCliente(stoi(temporal[0]),temporal[1],
									   temporal[2],stoi(temporal[3]));
					
					add(objCliente);
				}
			}
		}
		catch(exception e)
		{
			cout<<"\t\t\t\t\t\tOcurrio un error al grabar el archivo";
		}
	}
};

ClienteController* cliController = new ClienteController();

void menuClientes()
{
	int opt;
	do
	{
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\t\t\t\t\t\t*************MENU DE CLIENTES************\n\n";
		cout<<"\t\t\t\t\t\t********AGREGAR NUEVOS CLIENTES*******[1]\n\n";
		cout<<"\t\t\t\t\t\t***********LISTAR CLIENTES************[2]\n\n";
		cout<<"\t\t\t\t\t\t***********BUSCAR CLIENTES************[3]\n\n";
		cout<<"\t\t\t\t\t\t**********MODIFICAR CLIENTES**********[4]\n\n";
		cout<<"\t\t\t\t\t\t**********ELIMINAR CLIENTES***********[5]\n\n";
		cout<<"\t\t\t\t\t\t****************SALIR*****************[6]\n\n";
		cout<<"\t\t\t\t\t\t***********INGRESE UNA OPCION***********:";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");addItems();break;
		case 2:system("cls");listOfItems();break;
		case 3:system("cls");buscar();break;
		case 4:system("cls");modificar();break;
		case 5:system("cls");eliminar();break;
		case 6:cout<<"\t\t\t\t\t\tGracias por usar nuestro programa\n";break;
		default:system("cls");cout<<"\t\t\t\t\t\tINGRESE UNA OPCION CORRECTA[1-6]\n";
		}
	}
	while(opt!=6);
}

void addItems()
{
	string flag;
	int 	cod;
	int 	cod_0;
	string 	nCli;
	string	dni;
	int 	edad;
	do
	{
		cod = cliController->getCorrelativo();
		cod_0 = generarCod_0(cod);
		cout<<"\n\n\n\n\n\n\t\t\t\t\t\t******("<<cod<<")*******\n";
		cin.ignore();
		cout<<"\t\t\t\t\t\tNombres y Apellidos: ";
		getline(cin,nCli);
		cout<<"\t\t\t\t\t\tDNI: ";
		cin>>dni;
		cout<<"\t\t\t\t\t\tEdad: ";
		cin>>edad;
		cout<<"\t\t\t\t\t\tContinuar(S/s): ";
		cin>>flag;
		/*Crear el objeto de tipo alumno*/
		Cliente objCli(cod_0,nCli,dni,edad);
		/*Agregar el objeto al arreglo*/
		cliController->add(objCli);
		//grabar en archivo
		cliController->grabarEnArchivo(objCli);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}
void listOfItems()
{
	cout<<"\n\n\n\n\n\n";
	cout<<"\t\t|----CODIGO----|  |----NOMBRE----|   |----DNI----|   |----EDAD---|\n";
	for(int i = 0;i<cliController->size();i++)
	{
		cout<<"\t\t\t"<<cliController->get(i).getCodigo()<<"     \t"<<cliController->get(i).getNomCli()<<"\t"
			<<cliController->get(i).getDni()<<"\t\t"
			<<cliController->get(i).getEdad()<<endl;
	}
	
	system("pause");
	system("cls");	
}

void buscar()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = cliController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese codigo a buscar:";
	cin>>cod;
	Cliente cliObj = cliController->getBuscarPorCodigo(cod, inferior, superior);
	if(cliObj.getNomCli() !="Error")
	{
		cout<<"\t\t\t\t\t\tRegistro encontrado!\n\n";
		cout<<"\t\t\t\t\t\tCodigo: "<<cliObj.getCodigo()<<"\n";
		cout<<"\t\t\t\t\t\tNombre :"<<cliObj.getNomCli()<<"\n";
		cout<<"\t\t\t\t\t\tDni: "<<cliObj.getDni()<<"\n";
		cout<<"\t\t\t\t\t\tEdad: "<<cliObj.getEdad()<<"\n\n";
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
	system("pause");
	system("cls");
}

void modificar()
{
	int cod,
		inferior,
		superior,
		cont = 0;
	inferior = 0;
	superior = cliController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese el codigo a modificar:";
	cin>>cod;
	Cliente cliObj = cliController->getBuscarPorCodigo(cod, inferior, superior);
	if(cliObj.getNomCli() != "Error")
	{	
		/*Buscar objeto a modificar*/
		cout<<"\t\t\t\t\t\t*****Registro Encontrado*****!\n";
		cout<<"\t\t\t\t\t\tCodigo:"<<cliObj.getCodigo()<<"\n";
		cout<<"\t\t\t\t\t\tNombre:"<<cliObj.getNomCli()<<"\n";
		cout<<"\t\t\t\t\t\tDni:"<<cliObj.getDni()<<"\n";
		cout<<"\t\t\t\t\t\tEdad:"<<cliObj.getEdad()<<"\n";
		//cin.ignore();	
		/*Fin del objeto a modificar*/
		string nomM,dniM,flag;
		int	   edadM,opt;	
		bool estado;
		cout<<"\t\t\t\t\t\tDesea modificar todo el objeto?(S/s): ";
		cin>>flag;
		if(flag == "S" || flag == "s")
		{
			cout<<"\t\t\t\t\t\tModificando Campos\n";
			cout<<"\t\t\t\t\t\tModificando el Nombre...:";	
			getline(cin,nomM);
			cin.ignore();	
			cout<<"\t\t\t\t\t\tModificando el DNI...:";
			cin>>dniM;
			cout<<"\t\t\t\t\t\tModificando la edad...:";
			cin>>edadM;
			estado = cliController->modificar(cliObj,nomM,dniM,edadM);
		}
		else
		{
			do
			{
				cont++;
				cout<<"\t\t\t\t\t\t********MODIFICAR NOMBRE********[1]\n";
				cout<<"\t\t\t\t\t\t*********MODIFICAR DNI**********[2]\n";
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
							getline(cin,nomM);
							dniM = cliObj.getDni();
							edadM = cliObj.getEdad();
					estado = cliController->modificar(cliObj,nomM,dniM,edadM);
					break;
					}
					case 2: system("cls");
					{
						cout<<"\t\t\t\t\t\tModificando el DNI...: ";
						cin>>dniM;
						nomM = cliObj.getNomCli();
						edadM = cliObj.getEdad();
					estado = cliController->modificar(cliObj,nomM,dniM,edadM);
					break;
					}
					case 3:	system("cls");
					{
						cout<<"\t\t\t\t\t\tModificando la edad...: ";
						cin>>edadM;
						nomM = cliObj.getNomCli();
						dniM = cliObj.getDni();
						estado = cliController->modificar(cliObj,nomM,dniM,edadM);
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
			cliController->grabarModificarEliminarArchivo();
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

void eliminar()
{
	int cod,
		inferior,
		superior;
	inferior = 0;
	superior = cliController->size()-1;
	cout<<"\n\n\n\n\n\n\t\t\t\t\t\tIngrese codigo a eliminar:";
	cin>>cod;
	Cliente cliEliminar = cliController->getBuscarPorCodigo(cod, inferior, superior);
	if(cliEliminar.getNomCli() !="Error")
	{
		cliController->remove(cliEliminar);
		cout<<"\t\t\t\t\t\tRegistro eliminado satisfactoriamente!!!";
		/*Grabar en archivo*/
		cliController->grabarModificarEliminarArchivo();
	}
	else
	{
		cout<<"\t\t\t\t\t\tNo se encontro el registro!\n";
	}
}

void menuClientesPersonal()
{
	int opt;
	do
	{
		cout<<"\n\n\n\n\n\n\n\n";
		cout<<"\t\t\t\t\t\t*************MENU DE CLIENTES************\n\n";
		cout<<"\t\t\t\t\t\t***********LISTAR CLIENTES************[1]\n\n";
		cout<<"\t\t\t\t\t\t***********BUSCAR CLIENTES************[2]\n\n";
		cout<<"\t\t\t\t\t\t****************SALIR*****************[3]\n\n";
		cout<<"\t\t\t\t\t\t***********INGRESE UNA OPCION***********: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");listOfItems();break;
		case 2:system("cls");buscarxNom();break;
		case 3:cout<<"\t\t\t\t\t\tGracias por usar nuestro programa\n";break;
		default:system("cls");cout<<"\t\t\t\t\t\tINGRESE UNA OPCION CORRECTA[1-3]\n";
		}
	}
	while(opt!=3);
}

void buscarxNom()
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
}

int generarCod_0(int i)
{	
	cout.fill  ('0');    
	cout.width ( 8 );
	return i;
}
