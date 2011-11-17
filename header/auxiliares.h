#ifndef AUX_H
#define AUX_H

#include <stdlib.h>

#include <string>
#include <iostream>
#include "tipos.h"
#include "lista.h"


string intToString(const int n);

Lista<string> palabras(const string& s);
string primerPalabra(const string& s);
string sacarPrimerPalabra(const string& s);

template <typename A, typename B> parte ( Lista < pair <A, B> >, A ) ;

#endif /*AUX_H*/
