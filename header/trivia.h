#ifndef TRIVIA_H_INCLUDED
#define TRIVIA_H_INCLUDED

#include "tipos.h"
#include "lista.h"
#include "auxiliares.h"
#include "sms.h"
#include "pregunta.h"

class Trivia {
	public:
		Trivia();
		Trivia(const Lista<Keyword>& ks, const Lista<Pregunta>& ps);
		Trivia(const Trivia& t);
		bool operator==(const Trivia& t) const;

		Lista<Keyword> keywords() const;
		Lista<Pregunta> preguntas() const;
		Lista<Usuario> participantes() const;
		Lista<Usuario> ganadores() const;

		Pregunta proxPregunta(Usuario u) const;
		Puntaje puntajeAcumulado(Usuario u) const;

		SMS registrarJugador(Usuario u, Keyword k);
		void desregistrarJugador(Usuario u);
		SMS procesarRespuesta(Usuario u, Texto r);


		Lista<Usuario> usuariosEficientes() const;
		int posicion(Usuario u) const;

		Lista<string> palabrasRecurrentes(int n) const;

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

	private:
		Lista<Keyword> _keywords;
		Lista<Pregunta> _preguntas;
		Lista<Usuario> _participantes;
		Lista<Usuario> _ganadores;
		Lista< pair<Usuario, int> > _preguntasPorUsuario;
		Lista< pair<Usuario, int> > _puntajeUsuario ;

		//Mio
		Lista <int> donde ;

		enum {ENCABEZADO_ARCHIVO = 'V'};
};
#endif
