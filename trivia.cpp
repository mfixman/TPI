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

int Trivia::nroPregunta (Usuario u) const
{
	int i = 0 ;
	int r ;

	while ( i < _preguntasPorUsuario.longitud() )
	{
		if ( _preguntasPorUsuario.iesimo(i).first == u ) r = _preguntasPorUsuario.iesimo(i).second ;
		i++ ;
	}

	return r ;
}

Pregunta Trivia::proxPregunta (Usuario u) const
{
	return _preguntas.iesimo( nroPregunta(u) ) ;
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

//Templates estan permitidos? Cambiar.
template <typename A, typename B> pair <A, B> Trivia::parte ( Lista < pair <A, B> > q, A b )
{
	int i = 0 ;
	pair <A, B> r ;

	while ( i < q.longitud() )
	{
		if ( q.iesimo(i).first == b ) r = q.iesimo(i) ;
		i++ ;
	}

	return r ;
}

SMS Trivia::procesarRespuesta (Usuario u, Texto r)
{
	SMS res ;

	if ( _ganadores.pertenece(u) )
	{
		res = SMS(u, "Gracias por seguir pagando, pero el juego termino") ;
	}
	else if ( !_ganadores.pertenece(u) && _preguntas.posicion(proxPregunta(u)) == _preguntas.longitud() - 1 )
	{
		_ganadores.agregar(u) ;

		stringstream s ;
		s << "Has respondido todas las preguntas. Tenes " << puntajeAcumulado(u) << " puntos." ;
		res = SMS(u, s.str()) ;
	}
	else
	{
		Pregunta pr = proxPregunta(u) ;

		pair <Usuario, int> b = parte( _preguntasPorUsuario, u ), n = parte( _puntajeUsuario, u ) ;
		int ptos = pr.puntaje() * ( pr.rtaCorrecta() == r.substr(0, r.find(' ')) ) ;

		_preguntasPorUsuario.sacar( b ) ; _preguntasPorUsuario.agregar ( make_pair ( u, b.second + 1 ) ) ;
		_puntajeUsuario.sacar( n ) ; _puntajeUsuario.agregar ( make_pair ( u, n.second + ptos ) ) ;

		stringstream s ;
		if ( pr.rtaCorrecta() == r.substr( 0, r.find(' ') ) ) s << "Bien! " ;
		else s << "Mal! " ;

		s << "Tenes " << puntajeAcumulado(u) << " puntos." ;
		s << pr.texto() ;
		res = SMS(u, s.str()) ;
	}

	return res ;
}

Lista < Usuario > Trivia::usuariosEficientes() const
{
	Lista < Usuario > r = _participantes ;

	int p = 0, i = 0 ;
	int l = r.longitud() ;

	while ( i < l )
	{
		p = max(p, puntajeAcumulado( r.iesimo(i) ) ) ;
		i++ ;
	}
	i = 0 ;
	while ( i < l )
	{
		if ( puntajeAcumulado( r.iesimo(i) ) < p ) r.sacar( r.iesimo(i) ) ;
		else i++ ;
	}

	i = 0 ; p = INT_MAX ;
	while ( i < l )
	{
		p = min(p, nroPregunta( r.iesimo(i) ) ) ;
		i++ ;
	}

	i = 0 ;
	while ( i < l )
	{
		if ( nroPregunta ( r.iesimo(i) ) > p ) r.sacar( r.iesimo(i) ) ;
		i++ ;
	}

	return r ;
}

int Trivia::posicion(Usuario u) const
{
	int r = 0 ;

	if ( _ganadores.pertenece(u) ) r = _ganadores.posicion(u) ;
	else
	{
		int i = 0 ;
		while ( i < _puntajeUsuario.longitud() )
		{
			if ( _puntajeUsuario.iesimo(i).second > puntajeAcumulado(u) ) r++ ;
			i++ ;
		}

		r += _ganadores.longitud() ;
	}

	return r ;
}

Lista < string > Trivia::unparse ( string n ) const
{
	Lista <string> r ;

	stringstream s(n) ; string p ;
	while ( s >> p ) r.agregar(p) ;

	return r ;
}

Lista <Texto> Trivia::palabrasRecurrentes(int n) const
{
	Lista <Texto> q ;

	int i = 0, p = 0 ;
	while ( i < _preguntas.longitud() )
	{
		q.concatenar( unparse( _preguntas.iesimo(i).texto() ) ) ;
		q.concatenar( unparse( _preguntas.iesimo(i).rtaCorrecta() ) ) ;
	}

	i = 0 ;
	while ( i < q.longitud() && q.iesimo(i).size() >= n ) p = max(p, q.cantidadDeApariciones( q.iesimo(i) )) ;

	i = 0 ;
	while ( i < q.longitud() ) if ( q.cantidadDeApariciones( q.iesimo(i) ) != p ) q.sacar( q.iesimo(i) ) ;

	i = 0 ;
	while ( i < q.longitud() ) if ( q.cantidadDeApariciones( q.iesimo(i) ) > 1 ) q.sacar( q.iesimo(i) ) ;

	return q ;
}

