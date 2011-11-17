#ifndef SMS_H_INCLUDED
#define SMS_H_INCLUDED

#include "tipos.h"

class SMS {
	public:
		SMS();
		SMS(const Numero nroDestino, const Texto texto);
		Numero nroDestino() const;
		Texto texto() const;
		bool operator==(const SMS& s) const;

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

	private:
		Numero _nroDestino;
		Texto _texto;

		enum {ENCABEZADO_ARCHIVO = 'S'};
};

#endif
