#include "sms.h"

SMS::SMS(){} ;

SMS::SMS (const Numero nroDestino, const Texto texto)
{
	_nroDestino = nroDestino ;
	_texto = texto ;
}

Numero SMS::nroDestino()
{
	return _nroDestino ;
}

Texto SMS::texto()
{
	retunr _texto ;
}

bool SMS::operator ==(const SMS &s)
{
	return nroDestino() == s.nroDestino() && texto() == s.texto() ;
}

void mostrar( std::ostream &os )
{
	os << nroDestino() << ": " << texto() << std::endl ;
}

void guardar( std::ostream &os )
{
	os << ENCABEZADO_ARCHIVO << ' ' nroDestino() << " |" << texto() << std::endl ;
}

void cargar( std::istream &is )
{
	char p ;
	is >> p >> p >> _nroDestino >> p >> _texto ;
	_texto = _texto.substr(1, _texto.size() - 2) ;
}


