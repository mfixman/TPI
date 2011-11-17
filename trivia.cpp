#include "trivia.h"
#include "auxiliares.h"

Trivia::Trivia() {} ;

Trivia::Trivia(const Lista <Keyword> &ks, const Lista <Pregunta> &ps) 
{
	_keywords = ks ;
	_preguntas = ps ;
}

Lista <Keyword> Trivia::keywords() const
{
	return _keywords ;
}

Lista <Pregunta> Trivia::preguntas() const
{
	return _preguntas ;
}

Lista <Usuario> Trivia::participantes() const
{
	return _participantes ;
}

Lista <Usuario> Trivia::ganadores() const
{
	return _ganadores ;
}

Pregunta Trivia::proxPregunta (Usuario u) const
{
	int i = 0 ;
	Pregunta r ;

	while ( i < _preguntasPorUsuario.longitud() )
	{
		if ( _preguntasPorUsuario.iesimo(i).first == u ) r = _preguntas.iesimo( _preguntasPorUsuario.iesimo(i).second ) ;
		i++ ;
	}

	return r ;
}

Puntaje Trivia::puntajeAcumulado(Usuario u) const
{
	int i = 0 ;
	Puntaje r ;

	while ( i < _puntajeUsuario.longitud() )
	{
		if ( _puntajeUsuario.iesimo(i).first == u ) r = _puntajeUsuario.iesimo(i).second ;
		i++ ;
	}

	return r ;
}

SMS Trivia::registrarJugador (Usuario u, Keyword k)
{
	_participantes.agregar(u) ;

	_preguntasPorUsuario.agregar( make_pair (u, 0) ) ;
	_puntajeUsuario.agregar ( make_pair (u, 0) ) ;

	SMS r(u, "Hola! Tenes 0 pts " + _preguntas.cabeza().texto() ) ;
}

void Trivia::desregistrarJugador (Usuario u)
{
	_participantes.sacar(u) ;
}

SMS Trivia::procesarRespuesta (Usuario u, Texto r)
{
	if ( !_ganadores.pertenece(u) && _preguntas.posicion(proxPregunta(u)) == _preguntas.longitud() - 1 )
	{
		_ganadores.agregar(u) ;
	}

	Pregunta pr = proxPregunta(u) ;

	pair <Usuario, int> b = parte( _preguntasPorUsuario, u ) ;

	_preguntasPorUsuario.sacar( b ) ; _preguntasPorUsuario.agregar ( make_pair ( b.first, b.second + 1 ) ) ;

	//parte ( _puntajeUsuario, u ) += pr.puntaje() * ( pr.rtaCorrecta() == r.substr(0, r.find(' ')) ) ;
}

