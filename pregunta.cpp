#include "pregunta.h"

Pregunta::Pregunta() {} ;

Pregunta::Pregunta(const Texto texto, const Texto rtaCorrecta, const Puntaje puntaje)
{
	_texto = texto ;
	_rtaCorrecta = rtaCorrecta ;
	_puntaje = puntaje ;
}

Texto Pregunta::rtaCorrecta() const
{
	return _rtaCorrecta ;
}

Texto Pregunta::texto() const
{
	return _texto ;
}

Puntaje Pregunta::puntaje() const
{
	return _puntaje ;
}

bool Pregunta::operator == ( const Pregunta &p ) const
{
	return rtaCorrecta() == p.rtaCorrecta() && texto() == p.texto() && puntaje() == p.puntaje() ;
}


void Pregunta::mostrar( std::ostream &os ) const
{
	//os << nroDestino << ": " << texto << std::endl ;
	guardar ( os ) ;
}

void Pregunta::guardar( std::ostream &os ) const
{
	os << ENCABEZADO_ARCHIVO << " |" << texto() << "| |" << rtaCorrecta() << "| " << puntaje() ;
}

void Pregunta::cargar( std::istream &is )
{
	char p ;
	is >> p >> _texto >> _rtaCorrecta >> _puntaje ;

	_texto = _texto.substr(1, _texto.size() - 2) ;
	_rtaCorrecta = _rtaCorrecta.substr(1, _rtaCorrecta.size() - 2) ;
}


