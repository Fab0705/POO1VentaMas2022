using namespace std;

string encriptar(string texto)
{
	char encriptado;
	for(int i=0; i<texto.size(); i++)
	{
		encriptado = (texto[i] - 20);
		texto[i] = encriptado;
	}
	return texto;
}

string desencriptar(string texto)
{
	char desencriptado;
	for(int i=0; i<texto.size(); i++)
	{
		desencriptado = (texto[i] + 20);
		texto[i] = desencriptado;
	}
	return texto;
}
