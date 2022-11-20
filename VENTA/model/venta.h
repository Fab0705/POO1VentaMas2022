#pragma once
#include <iostream>

using namespace std;

class Venta
{
private:
	int codigoVenta;
	int codigoCliente;
	string fecha;
	float total;
	string vendedor;
public:
	Venta(){}
	Venta(int codigoVenta, int codigoCliente, string fecha, float total, string vendedor)
	{
		this->codigoVenta = codigoVenta;
		this->codigoCliente = codigoCliente;
		this->fecha = fecha;
		this->total = total;
		this->vendedor = vendedor;
	}
	
	void setFecha(string fecha)
	{
		this->fecha = fecha;
	}
	
	int getCodVenta()
	{
		return this->codigoVenta;
	}
	
	int getCodCliVen()
	{
		return this->codigoCliente;
	}
	
	string getFechaVen()
	{
		return this->fecha;
	}
	
	float getTotalVen()
	{
		return this->total;
	}
	
	string getVendedor()
	{
		return this->vendedor;
	}
};
