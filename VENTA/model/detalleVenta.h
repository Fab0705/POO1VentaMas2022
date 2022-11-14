#pragma once
#include <iostream>

using namespace std;

class DetalleVenta
{
private:
	int codigoVenta;
	int codigoProducto;
	int cantidad;
	float precio;
	float importe;
public:
	DetalleVenta(){}
	DetalleVenta(int codigoVenta, int codigoProducto, int cantidad, float precio, float importe)
	{
		this->codigoVenta = codigoVenta;
		this->codigoProducto = codigoProducto;
		this->cantidad = cantidad;
		this->precio = precio;
		this->importe = importe;
	}
	int getCodDetVen()
	{
		return this->codigoVenta;
	}
	int getCodProDetVen()
	{
		return this->codigoProducto;
	}
	int getCantDetVen()
	{
		return this->cantidad;
	}
	float getPrecDetVen()
	{
		return this->precio;
	}
	float getImDetVen()
	{
		return this->importe;
	}
};
