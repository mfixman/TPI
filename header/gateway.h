#ifndef GATEWAY_H_INCLUDED
#define GATEWAY_H_INCLUDED

#include "tipos.h"
#include "lista.h"
#include "trivia.h"
#include "auxiliares.h"

class Gateway {
	public:
        Gateway();
		Gateway(const Numero n, const Lista<Trivia>& t, const Lista<Keyword>& c);

		Numero numero() const;
		Lista<Trivia> trivias() const;
		Lista<Keyword> comandos() const;
		SMS procesarComando(const Usuario u,const SMS& r);
		SMS procesarMensaje(const Usuario u,const SMS& r);
		Lista<Usuario> seAnotanEnTodas() const;
		bool operator==(const Gateway& g) const;

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

	private:

		Numero _numero;
		Lista<Trivia> _trivias;
		Lista<Keyword> _comandos;

		enum {ENCABEZADO_ARCHIVO = 'G'};


};

#endif

