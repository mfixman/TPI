#include "sms.h"

SMS::SMS(){} ;

SMS::SMS (const Numero nroDestino, const Texto texto)
{
	_nroDestino = nroDestino ;
	_texto = texto ;
}

Numero SMS::nroDestino() const
{
	return _nroDestino ;
}

Texto SMS::texto() const
{
	return _texto ;
}

bool SMS::operator ==(const SMS &s) const
{
	return nroDestino() == s.nroDestino() && texto() == s.texto() ;
}

void SMS::mostrar( std::ostream &os ) const
{
	os << nroDestino() << ": " << texto() << std::endl ;
}

void SMS::guardar( std::ostream &os ) const
{
	os << ENCABEZADO_ARCHIVO << ' ' << nroDestino() << " |" << texto() << std::endl ;
}

void SMS::cargar( std::istream &is )
{
	char p ;
	is >> p >> p >> _nroDestino >> p >> _texto ;
	_texto = _texto.substr(1, _texto.size() - 2) ;
}


