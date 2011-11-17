#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "tipos.h"
#include "sms.h"

#include <iostream>
#include <fstream>

#include "gateway.h"
#include "trivia.h"
#include "telco.h"


void MenuPrincipal();

void MenuTrivia();
void MenuGateway();
void MenuTelco();

Trivia MenuCrearTrivia();
Gateway MenuCrearGateway();
TelCO MenuCrearTelco();

Pregunta leerPregunta();
SMS leerSMS();

template<class T> void mostrarLista(Lista<T> lista);
void mostrar(const SMS &sms);
void mostrar(const Pregunta &preg);
void mostrar(const Trivia &t);
void mostrar(const Gateway &g);
void mostrar(const pair<Gateway,pair<int,int> > &par);
void mostrar(const pair<SMS,SMS> &par);

int LeerOpcion(int maxOpcion);
void LeerArchivoParaEscribir(ofstream &archivo);
void LeerArchivoParaLeer(ifstream &archivo);
void limpiarPantalla();
void Pausar();
void Salir();

#endif // INTERFAZ_H

