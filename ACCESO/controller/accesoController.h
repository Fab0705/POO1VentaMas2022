#pragma once
#include<iostream>
#include<vector>
#include<conio.h>
#include<fstream>
#include<string>
#include"encryption.h"
#include"accesoControllerAdm.h"
//#include"../model/acceso.h"
#include"../../CLIENTES/controller/clienteController.h"
#include"../../PRODUCTOS/controller/productoController.h"
#include"../../CATEGORIAS/controller/categoriaController.h"
#include"../../VENDEDORES/controller/vendedorController.h"
#include"../../VENTA/controller/detalleCompraController.h"

using namespace std;
void menuDeAcceso();
void registrarPersonal();
void accesoDePersonal();
void menuAdmin();
void menuPersonal(string);
string encriptar(string);
string desencriptar(string);

class AccesoController
{
	private:
		vector<Acceso> vectorAcceso;
	public:
		AccesoController()
		{
			cargarDatosDelArchivoAlVector();
		}
		//agregar objetos de tipo acceso
		void add(Acceso objeto)
		{
			vectorAcceso.push_back(objeto);
		}
		//obtener objeto de tipo acceso
		Acceso get(int posicion)
		{
			return vectorAcceso[posicion];
		}
		//obtener el tamano del arreglo
		int size()
		{
			return vectorAcceso.size();
		}	
		//grabar los datos en el archivo 
		void grabarEnArchivo(Acceso acceso)
		{
			try
			{
				fstream archivoAcceso;
				archivoAcceso.open("acceso.csv", ios::app);
				if(archivoAcceso.is_open())
				{
					archivoAcceso<<acceso.getUsu()<<";"
								<<acceso.getContrasena()<<";"<<endl;
					archivoAcceso.close();
				}
			}
			catch(exception e)
			{
				cout<<"Ocurrio un error al grabar el archivo";
			}
		}
		//cargar datos del archivo
		void cargarDatosDelArchivoAlVector()
		{
			try
			{
				int 	i;
				size_t 	posi;
				string 	linea;
				string 	temporal[2];
				fstream	archivoAcceso;
				archivoAcceso.open("acceso.csv",ios::in);
				if(archivoAcceso.is_open())
				{
					while(!archivoAcceso.eof() && getline(archivoAcceso,linea))
					{
						i = 0;
						while((posi = linea.find(";")) != string::npos)
						{
							temporal[i] = linea.substr(0,posi);
							linea.erase(0,posi+1);
							++i;
						}
						
						Acceso objAcceso(temporal[0],temporal[1]);
						
						add(objAcceso);
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
			for (Acceso x : vectorAcceso)
			{
				if (obj.getUsu() == x.getUsu() && obj.getContrasena() == x.getContrasena())
				{
					return true;
				}
			}
			return false;
		}
};
//creamos un objeto
AccesoController* accController = new AccesoController();
AccesoControllerAdm* accAdmController = new AccesoControllerAdm();
//menus 
			void menuDeAcceso()
				{
				int opt;
				do
				{
				cout<<"\n\n\n\n\n\n\n\n";
				cout<<"\t\t\t\t\t*******BIENVENIDO A VENTAMAS*******\n\n";
				cout<<"\t\t\t\t\t**********MENU DE ACCESO***********\n\n";
				cout<<"\t\t\t\t\t*******REGISTRAR PERSONAL*******[1]\n\n";
				cout<<"\t\t\t\t\t*******ACCESO DE PERSONAL*******[2]\n\n";
				cout<<"\t\t\t\t\t*************SALIR**************[3]\n\n";
				cout<<"\t\t\t\t\t******Ingrese una opci�n*********: ";
				cin>>opt;
				switch(opt)
				{
				case 1:system("cls");registrarPersonal();break;
				case 2:system("cls");accesoDePersonal();break;
				case 3:system("cls");cout<<"Gracias por usar nuestro programa\n";break;
				default:cout<<"Ingrese una opcion correcta[1-3]\n";
				
				}
			} while(opt != 3);
			system("cls");
			cout<<"\n\n\n\n\n\n\n";
			for(int i=0; i<5; i++)
			{
				cout<<"\t\t\t\t***************************************************************\n";
			}
			cout<<"\t\t\t\tG R A C I A S   P O R   U S A R  N U E S T R O  P R O G R A M A\n";
			for(int i=0; i<5; i++)
			{
				cout<<"\t\t\t\t***************************************************************\n";
			}	
		}
		
		void registrarPersonal()
		{
			string usu;
			string contra;
			string flag;
			cout<<"\n\n\n\n\n\n\n\n\n\n	";
			cout<<"\t\t\t\t\t\t*******REGISTRAR PERSONAL********\n";
			
			cout<<"\t\t\t\t\t\tUsuario: ";
			cin>>usu;
			cout<<"\t\t\t\t\t\tContrasenia: ";
			cin>>contra;
			//crear objeto
			Acceso obj(usu, contra);
			if(accAdmController->loginUsuario(obj) == true)
			{
				cout<<"\t\t\t\t\t\tREGISTRE UN PERSONAL: \n";
				cout<<"\t\t\t\t\t\tUsuario: ";
				cin>>usu;
				//usu = encriptar(usu);
				
				cout<<"\t\t\t\t\t\tContrasenia: ";
				cin>>contra;
				contra = encriptar(contra);
				//crear objeto tipo alumno
				Acceso acceso(usu,contra);	
				//meter en un arreglo el objeto tipo alumno
				accController->add(acceso);
				//grabar en un archibo csv la informacion
				accController->grabarEnArchivo(acceso);
			}
			//system("pause");
			system("cls");
		}
		
		void accesoDePersonal()
		{
			//bool estado;
			//string usuDesencript[50];
			//string contraDesencript[50];
			string usu;
			//string contra;
			string flag;
			//char caracter;
			bool ingresoPer = false;
			bool ingresoAdm = false;
			int cont = 1;
			
			do
			{
				string usuDesencript[50];
				string contraDesencript[50];
				string contra;
				char caracter;
				system("cls");
				for(int i = 0;i<accController->size();i++)
				{
					usuDesencript[i] = accController->get(i).getUsu();
					contraDesencript[i] = accController->get(i).getContrasena();
					cout<<"usuario: "<<usuDesencript[i]<<endl;
					cout<<"contraDesencript "<<desencriptar(contraDesencript[i])<<endl;
				}
				cout<<"\n\n\n\n\n\n\n\n\n\n";
				cout<<"\t\t\t\t\t\t*******ACCESO DE PERSONAL********\n";
				cout<<"\t\t\t\t\t\tUSUARIO: ";
				cin>>usu;
				cout<<"\t\t\t\t\t\tCONTRASENIA: ";
				//cin>>contra;
				caracter = getch();//al momento de ingresar la contrasena, getch no muestra el caracter que se ingreso, por eso mas abajo hay un cout con en *
				while(caracter != 13)//ejecuta mientras el caracter leido sea diferente a la tecla enter, en ASCII (13)
				{
					if(caracter != 8)//si el caracter leido es diferente al backspace en ASCII,
					{
						contra.push_back(caracter);//este pushback introduce el caracter a la contrasenia
						cout<<"*";
					}
					else//simula un borrado
					{
						if(contra.length() > 0)//si mi contrasena tiene al menos 1 caracter, se puede borrar
						{
							cout<<"\b \b";//\b mueve el cursor un espacio a la izquierda, se hace un espacio y luego se usa \b nuevamente para regresar al cursor hacia donde deberia estar, simmulando un eliminar caracter
							contra.pop_back();//elimina el ultimo caracter ingresado
						}
					}
					caracter = getch();//getch espera el ingreso de otro caracter, y afuera del if y else, porque siempre se tiene que hacer la lectura del caracter
				}
				//desencriptar el texto del archivo y comparar con el del usuario
				for(int i = 0;i<accController->size();i++)
				{
					if(usu == usuDesencript[i] && contra == desencriptar(contraDesencript[i]))
					{
						ingresoPer = true;
						goto ingresoPer;
					}
				}
				Acceso obj(encriptar(usu), encriptar(contra));
				if(accAdmController->loginUsuario(obj) == true)
				{
					ingresoAdm = true;
					goto ingresoAdm;
				}
				if(ingresoPer != true || ingresoAdm != true)
				{
					
					cout<<"\n\t\t\t\t\tEL USUARIO Y CONTRASENIA NO SON CORRECTOS .__."<<"\n\n";
					if(cont < 3)
					{
						cout<<"\t\t\t\t\tDESEA INTENTARLO DENUEVO?(S/s): ";
						cin>>flag;
					}
					if(flag == "S" || flag == "s")
					{
						cont++;
					}
					else
					{
						break;
					}
				}
			}while(cont < 4);
			
			//cout<<"El usuario es: "<<usu<<endl;
			//cout<<"La contrasenia es: "<<contra<<endl;
			//cout<<"\t\t\t\t\t\t\t\t";
			ingresoPer:
			{
				if(ingresoPer == true)
				{
					menuPersonal(usu);
				}
				else
				{
					cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tSE HAN EXCEDIDO LOS INTENTOS PARA HACER LOGIN\n\n\t\t\t\t\t\t";
				}
				
				system("cls");
			}
			ingresoAdm:
			{
				if(ingresoAdm == true)
				{
					menuAdmin();
				}
				else
				{
					cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tSE HAN EXCEDIDO LOS INTENTOS PARA HACER LOGIN\n\n\t\t\t\t\t\t";
				}
				system("cls");
			}
		}
		
		
		void menuAdmin()
		{
			int opt;
			do
			{
				system("cls");
				cout<<"\n\n\n\n\n\n\n\n";
				cout<<"\t\t\t\t\t******BIENVENIDO AL MENU DE ADMINISTRADOR*******\n\n";
				cout<<"\t\t\t\t\t*******************CLIENTES*******************[1]\n\n";
				cout<<"\t\t\t\t\t******************VENDEDORES******************[2]\n\n";
				cout<<"\t\t\t\t\t******************PRODUCTOS*******************[3]\n\n";
				cout<<"\t\t\t\t\t******************CATEGORIAS******************[4]\n\n";
				cout<<"\t\t\t\t\t********************SALIR*********************[5]\n\n";
				cout<<"\t\t\t\t\t***************INGRESE UNA OPCION***************: ";
				cin>>opt;
				switch(opt)
				{
				case 1:system("cls");menuClientes();break;
				case 2:system("cls");menuVendedores();break;
				case 3:system("cls");menuProductos();break;
				case 4:system("cls");menuCategorias();break;
				case 5:system("cls");cout<<"";break;
				default:cout<<"INGRESE UNA OPCION CORRECTA[1-4]\n";
				}
			} while(opt!=5);
		}
		
		void menuPersonal(string usu)
		{
			int opt;
			do
			{
				system("cls");
				cout<<"\n\n\n\n\n\n\n\n";
				cout<<"\t\t\t\t\t********BIENVENIDO AL MENU DEL PERSONAL "<<usu<<"**********\n\n";
				cout<<"\t\t\t\t\t****************GENERAR VENTA*****************[1]\n\n";
				cout<<"\t\t\t\t\t*******************CLIENTES*******************[2]\n\n";
				cout<<"\t\t\t\t\t******************PRODUCTOS*******************[3]\n\n";
				cout<<"\t\t\t\t\t******************CATEGORIAS******************[4]\n\n";
				cout<<"\t\t\t\t\t********************SALIR*********************[5]\n\n";
				cout<<"\t\t\t\t\t***************INGRESE UNA OPCION***************: ";
				cin>>opt;
				switch(opt)
				{
				case 1:system("cls");generarCompra();break;
				case 2:system("cls");menuClientesPersonal();break;
				case 3:system("cls");menuProductosPersonal();break;
				case 4:system("cls");menuCategoriasPersonal();break;
				case 5:system("cls");cout<<"";break;
				default:cout<<"INGRESE UNA OPCION CORRECTA[1-4]\n";
				}
			} while(opt!=5);
		}
		
