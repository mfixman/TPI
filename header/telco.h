#ifndef TELCO_H_INCLUDED
#define TELCO_H_INCLUDED

#include "lista.h"
#include "tipos.h"
#include "gateway.h"

class TelCO {
	public:
        TelCO();
		TelCO(Lista<Usuario>& u, Lista<Gateway>& g);
		bool operator==(const TelCO& t) const;

        Lista<Usuario> usuarios() const;
        Lista<pair<SMS,SMS> > mensajes() const;
        Lista<Gateway> gateways() const;
        void procesarMensaje(const Usuario u, const SMS& s);

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

	private:

		Lista<pair<SMS,SMS> > _mensajes;
		Lista<Usuario> _usuarios;
		Lista<Gateway> _gateways;

		enum {ENCABEZADO_ARCHIVO = 'T'};

};

#endif
