#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED

#include "tipos.h"

class Pregunta {
	public:
		Pregunta();
		Pregunta(const Texto texto, const Texto rtaCorrecta, const Puntaje puntaje);
		Texto rtaCorrecta() const;
		Texto texto() const;
		Puntaje puntaje() const;
		bool operator==(const Pregunta& p) const;

        void mostrar(std::ostream& os) const;
		void guardar(std::ostream& os) const;
		void cargar (std::istream& is);

	private:
		Texto _rtaCorrecta;
		Texto _texto;
		Puntaje _puntaje;

		enum {ENCABEZADO_ARCHIVO = 'P'};
};

#endif
