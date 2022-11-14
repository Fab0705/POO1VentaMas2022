#pragma once
#include <iostream>

using namespace std;

class DetalleCompra
{
private:
	int codigoProducto;
	string nombreProducto;
	int cantidad;
	float precioProducto;
	float importe;
public:
	DetalleCompra(){}
	DetalleCompra(int codigoProducto, string nombreProducto, int cantidad, float precioProducto, float importe)
	{
		this->codigoProducto = codigoProducto;
		this->nombreProducto = nombreProducto;
		this->cantidad = cantidad;
		this->precioProducto = precioProducto;
		this->importe = importe;
	}
	void setNomProCom(string nombreProducto)
	{
		this->nombreProducto = nombreProducto;
	}
	int getCodProCom()
	{
		return this->codigoProducto;
	}
	string getNomProdCom()
	{
		return this->nombreProducto;
	}
	int getCantProdCom()
	{
		return this->cantidad;
	}
	float getPrecProdCom()
	{
		return this->precioProducto;
	}
	float getImCom()
	{
		return this->importe;
	}
};
