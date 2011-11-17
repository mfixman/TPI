#include "interfaz.h"
#include "tipos.h"
#include "trivia.h"

using namespace std;


template<class T> void mostrarLista(Lista<T> lista){
  for(int i=0;i<lista.longitud();i++){
    mostrar(lista.iesimo(i));
    if(i<lista.longitud() -1)
        cout << ',';
  }
}

void Salir()
{
    cout << "Adios" << endl;
}

void Pausar()
{
    string opt = "n";
#ifdef WIN32
    system("Pause");
#else
    while (opt != "s" && opt!="")
    {
        cout << "Desea continuar?[s/n]";
        getline(cin,opt);
    }
#endif

}

void limpiarPantalla()
{
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
}
void mostrar(const SMS &sms){
    sms.mostrar(cout);
}

void mostrar(const Pregunta &preg){
    preg.mostrar(cout);
}

void mostrar(const Trivia &t){
    t.mostrar(cout);
}

void mostrar(const Gateway &g){
    g.mostrar(cout);
}

void mostrar(const pair<Gateway,pair<int,int> > &par){
  par.first.mostrar(cout);
  cout<<" Participantes: " << par.second.first << " Ganadores: " << par.second.second<<endl;
  cout << endl;
}

void mostrar(const pair<SMS,SMS> &par){
  cout<<"Enviado: ";
  par.first.mostrar(cout);
  cout<<"Recibido: ";
  par.second.mostrar(cout);
  cout<< endl;
}

int LeerOpcion(int maxOpcion)
{
    cout << "  Ingrese una opcion [" << 1 << "-" << maxOpcion << "]: ";
    int opt;
    bool ok = false;
    while (!ok)
    {
        cin >> opt;
        cin.ignore();
        ok = (opt <= maxOpcion && opt>0);

        if (!ok)
            cout << "  Opcion incorrecta. Ingrese un numero entre [" << 1 << "-" << maxOpcion << "]: ";
    }
    return opt;
}

void LeerArchivoParaLeer(ifstream &archivo)
{
    cout << "  Ingrese nombre de archivo existente: ";
    string opt;
    bool ok = false;
    while (!ok)
    {
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();

        if (!ok)
            cout << "  Valor incorrecto. Ingrese nombre de archivo existente: ";
    }
}

void LeerArchivoParaEscribir(ofstream &archivo)
{
    cout << "  Ingrese nombre de archivo: ";
    string opt;
    bool ok = false;
    while (!ok)
    {
        getline(cin, opt);
        archivo.open(opt.c_str());
        ok = archivo.good();
        if (!ok)
            cout << "  Valor incorrecto. Ingrese nombre de archivo: ";
    }
}

void MenuPrincipal()
{
    cout.setf(ios::boolalpha);

    bool exit = false;

    while (!exit)
    {
        cout << endl
            << "Bienvenidos" << endl
            << "1. Trivia" << endl
            << "2. Gateway" << endl
            << "3. Telco" << endl
            << "4. Salir" << endl;

        int opt = LeerOpcion(4);
        switch (opt)
        {
            case 1:
            {
                limpiarPantalla();
                MenuTrivia();
            }
                break;
            case 2:
            {
                limpiarPantalla();
                MenuGateway();
            }
                break;
            case 3:
            {
                limpiarPantalla();
                MenuTelco();
            }
                break;
            case 4:
                limpiarPantalla();
                Salir();
                cout << endl << endl;
                exit = true;
                break;
        }
    }
}

Usuario participante;
Keyword keyword;
Texto respuesta;
bool seCreoTrivia=false;
Trivia nuevaTrivia;

void MenuTrivia()
{

    int maxOption = 3;
    cout << "Menu Trivia" << endl
          << "1. Volver al Menu Principal" << endl
          << "2. Crear" << endl
          << "3. Cargar de archivo" << endl;
    if (seCreoTrivia)
    {
        maxOption = 17;
        cout << "4. Guardar a archivo" << endl
            << "5. Mostrar" << endl
            << "6. Keywords"<< endl
            << "7. Preguntas"<< endl
            << "8. Participantes"<< endl
            << "9. Ganadores"<< endl
            << "10. Proxima pregunta"<< endl
            << "11. Puntaje acumulado"<< endl
            << "12. Registrar jugador"<< endl
            << "13. Procesar respuesta"<< endl
            << "14. Usuarios eficientes"<< endl
            << "15. Posicion"<< endl
            << "16. Palabras recurrentes"<< endl
            << "17. Volver al menu anterior" << endl;
    }

    int opt = LeerOpcion(maxOption)-1;
    switch (opt)
    {
        case 0:
        {
            limpiarPantalla();
            break;
        }
        break;
        case 1:
        {
            limpiarPantalla();
            nuevaTrivia = MenuCrearTrivia();
            seCreoTrivia = true;

            limpiarPantalla();
            MenuTrivia();
        }
        break;
        case 2:
        {
            limpiarPantalla();
            ifstream archivoEntrada;
            LeerArchivoParaLeer(archivoEntrada);
            nuevaTrivia.cargar(archivoEntrada);
            archivoEntrada.close();
            seCreoTrivia = true;
            limpiarPantalla();
            MenuTrivia();
        }
        break;
        case 3:
        {
            limpiarPantalla();

            if (!seCreoTrivia)
            {
              cout << "ERROR: No se creo ninguna trivia aun"<<endl;
              MenuTrivia();
              break;
            }

            ofstream archivoSalida;

            LeerArchivoParaEscribir(archivoSalida);
            nuevaTrivia.guardar(archivoSalida);
            archivoSalida.close();

            limpiarPantalla();
            MenuTrivia();
        }
        break;
        case 4:
        {
            limpiarPantalla();
            if (!seCreoTrivia)
            {
              cout << "ERROR: No se creo ninguna trivia aun"<<endl;
              MenuTrivia();
              break;
            }

            cout << "La ultima trivia creada es: "<< endl<< endl;
            nuevaTrivia.mostrar(cout);
            cout << endl<< endl;
            Pausar();

            limpiarPantalla();
            MenuTrivia();
        }
        break;
        case 5:
        {
            limpiarPantalla();

            nuevaTrivia.keywords().mostrar(cout);

            cout << endl;
            Pausar();

            limpiarPantalla();
            MenuTrivia();

        }
        break;
        case 6:
        {
            limpiarPantalla();

            mostrarLista(nuevaTrivia.preguntas());

            cout << endl;

            Pausar();

            limpiarPantalla();
            MenuTrivia();

        }
        break;
        case 7:
        {
            limpiarPantalla();

            nuevaTrivia.participantes().mostrar(cout);
            cout << endl;

            Pausar();

            limpiarPantalla();
            MenuTrivia();

        }
        break;
        case 8:
        {
            limpiarPantalla();

            nuevaTrivia.ganadores().mostrar(cout);
            cout<<endl;

            Pausar();

            limpiarPantalla();
            MenuTrivia();
        }
        break;
        case 9:
        {
            limpiarPantalla();

            if (nuevaTrivia.participantes().longitud()==0){
                cout << "ERROR: No hay participantes aun"<<endl;
                MenuTrivia();
                break;
            }

            participante=-1;

            while(participante==-1){
              cout << "Ingrese numero de usuario: "<<endl;
              cin>>participante;
              cin.ignore();
              if (!nuevaTrivia.participantes().pertenece(participante)){
                participante=-1;
              }
              if (participante==-1) cout<< "Ese usuario no esta jugando "<<endl;
            }


            nuevaTrivia.proxPregunta(participante).mostrar(cout);
            cout<<endl;

            Pausar();

            limpiarPantalla();
            MenuTrivia();
        }
        break;
        case 10:
        {
            limpiarPantalla();

            if (nuevaTrivia.participantes().longitud()==0){
                cout << "ERROR: No hay participantes aun"<<endl;
                MenuTrivia();
                break;
            }
            participante=-1;
            while(participante==-1){
              cout << "Ingrese numero de particpante:"<<endl;
              cin>>participante;
              cin.ignore();
              if (!nuevaTrivia.participantes().pertenece(participante)){
                participante=-1;
              }
              if (participante==-1) cout<< "Ese usuario no esta jugando "<<endl;
            }


            cout <<"Tiene " << (nuevaTrivia.puntajeAcumulado(participante))<<" puntos"<< endl;

            Pausar();

            limpiarPantalla();
            MenuTrivia();
        }
        break;
        case 11:
        {
          cout<<"Ingrese numero de usuario:"<<endl;
          cin>>participante;
          cin.ignore();
          cout<<"Ingrese keyword:"<<endl;
          getline(cin,keyword);

          nuevaTrivia.registrarJugador(participante,keyword).mostrar(cout);
          cout<<endl;


          Pausar();

          limpiarPantalla();
          MenuTrivia();
        }
        break;
        case 12:
        {
          if (nuevaTrivia.participantes().longitud()==0){
            limpiarPantalla();
            cout<<"ERROR: No hay participantes para procesar respuesta"<<endl<<endl;
            MenuTrivia();
            break;
          }

          do{
            cout<<"Ingrese numero de particpante:"<<endl;
            cin>>participante;
            cin.ignore();
          }while(!nuevaTrivia.participantes().pertenece(participante));

          cout<<"Ingrese respuesta:"<<endl;
          getline(cin,respuesta);
          nuevaTrivia.procesarRespuesta(participante,respuesta).mostrar(cout);
          cout<<endl;

          Pausar();

          limpiarPantalla();
          MenuTrivia();
        }
        break;
        case 13:
        {
          limpiarPantalla();
          nuevaTrivia.usuariosEficientes().mostrar(cout);
          cout<<endl;
          Pausar();
          limpiarPantalla();
          MenuTrivia();
        }
        case 14:
        {
            limpiarPantalla();
            if (nuevaTrivia.participantes().longitud()==0){
                cout << "ERROR: No hay participantes aun"<<endl;
                MenuTrivia();
                break;
            }
            participante=-1;
            while(participante==-1){
              cout << "Ingrese numero de usuario:"<<endl;
              cin>>participante;
              cin.ignore();
              if (!nuevaTrivia.participantes().pertenece(participante)){
                participante=-1;
              }
              if (participante==-1) cout<< "Ese usuario no esta jugando "<<endl;
            }


            cout<<"Esta en la posicion: "<<nuevaTrivia.posicion(participante)<<endl;
            Pausar();
            limpiarPantalla();
            MenuTrivia();

        }
        break;
        case 15:
        {
          limpiarPantalla();

          cout<<"Ingrese largo de palabra:"<<endl;
          int n;
          cin>>n;
          cin.ignore();
          (nuevaTrivia.palabrasRecurrentes(n)).mostrar(cout);
          Pausar();
          limpiarPantalla();
          MenuTrivia();
        }
        break;
        case 16:
            limpiarPantalla();
            break;
    }
}

SMS leerSMS(){
  Numero num;
  Texto tex;
  cout<<"Ingrese numero de sms: "<<endl;
  cin>> num;
  cin.ignore();
  cout<<"Ingrese texto de sms: "<<endl;
  getline(cin,tex);
  return SMS(num,tex);

}

bool seCreoGateway=false;
Gateway nuevaGateway;
SMS sms;

void MenuGateway(){
  int maxOption = 3;
  cout << "Menu Gateway" << endl
          << "1. Volver al Menu Principal" << endl
          << "2. Crear" << endl
          << "3. Cargar de archivo" << endl;
  if (seCreoGateway)
  {
      maxOption = 12;
      cout << "4. Guardar a archivo" << endl
          << "5. Mostrar" << endl
          << "6. Numero"<< endl
          << "7. Trivias"<< endl
          << "8. Comandos"<< endl
          << "9. Procesar Comando"<< endl
          << "10. Procesar Mensaje"<< endl
          << "11. Se anotan en todas"<< endl
          << "12. Volver al menu anterior" << endl;
  }

  int opt = LeerOpcion(maxOption)-1;
  switch (opt)
  {
    case 0:
      {
          limpiarPantalla();
          break;
      }
        break;
      case 1:
      {
          limpiarPantalla();
          nuevaGateway = MenuCrearGateway();
          seCreoGateway = true;

          limpiarPantalla();
          MenuGateway();
      }
        break;
      case 2:
      {
          limpiarPantalla();
          ifstream archivoEntrada;
          LeerArchivoParaLeer(archivoEntrada);
          nuevaGateway.cargar(archivoEntrada);
          archivoEntrada.close();
          seCreoGateway = true;
          limpiarPantalla();
          MenuGateway();
      }
        break;
      case 3:
      {
          limpiarPantalla();

          if (!seCreoGateway)
          {
              cout << "ERROR: No se creo ningun gateway aun"<<endl;
          MenuGateway();
              break;
          }

          ofstream archivoSalida;

          LeerArchivoParaEscribir(archivoSalida);
          nuevaGateway.guardar(archivoSalida);
          archivoSalida.close();

          limpiarPantalla();
          MenuGateway();
      }
        break;
      case 4:
      {
          limpiarPantalla();
          if (!seCreoGateway)
          {
              cout << "ERROR: No se creo ningun gateway aun";
              break;
          }

          cout << "La ultima gateway creada es: "<< endl<< endl;
          nuevaGateway.mostrar(cout);
          cout << endl<< endl;
          Pausar();

          limpiarPantalla();
          MenuGateway();
      }
        break;
      case 5:
      {
          limpiarPantalla();

          cout << nuevaGateway.numero() <<endl;
          cout<<endl;

          Pausar();

          limpiarPantalla();
          MenuGateway();

      }
        break;
      case 6:
      {
          limpiarPantalla();

          mostrarLista(nuevaGateway.trivias());
          cout<<endl;

          Pausar();

          limpiarPantalla();
          MenuGateway();

      }
        break;
      case 7:
      {
          limpiarPantalla();

          nuevaGateway.comandos().mostrar(cout);
          cout<<endl;

          Pausar();

          limpiarPantalla();
          MenuGateway();

      }
        break;
      case 8:
      {
          cout<<"Ingrese numero de usuario: "<<endl;
          cin>>participante;
          cin.ignore();
          sms=leerSMS();

          sms=nuevaGateway.procesarComando(participante,sms);

          sms.mostrar(cout);
          cout<<endl;

          Pausar();

          limpiarPantalla();
          MenuGateway();

      }
        break;
      case 9:
      {
          cout<<"Ingrese numero de usuario: "<<endl;
          cin>>participante;
          cin.ignore();
          sms=leerSMS();

          sms=nuevaGateway.procesarMensaje(participante,sms);

          sms.mostrar(cout);
          cout<<endl;

          Pausar();

          limpiarPantalla();
          MenuGateway();

      }
        break;
      case 10:
      {
        limpiarPantalla();

        nuevaGateway.seAnotanEnTodas().mostrar(cout);

          cout<<endl;
        Pausar();

        limpiarPantalla();
        MenuGateway();
      }
        break;
      case 11:
          limpiarPantalla();
          MenuPrincipal();
          break;


  }
}

bool seCreoTelco=false;
TelCO nuevoTelco;
void MenuTelco(){
    int maxOption = 3;
    cout << "Menu Telco" << endl
            << "1. Volver al Menu Principal" << endl
            << "2. Crear" << endl
            << "3. Cargar de archivo" << endl;
    if (seCreoTelco)
    {
        maxOption = 12;
        cout << "4. Guardar a archivo" << endl
            << "5. Mostrar" << endl
            << "6. Usuarios"<< endl
            << "7. Mensajes"<< endl
            << "8. Gateways"<< endl
            << "9. Procesar Mensaje"<< endl
            << "10. Volver al menu anterior" << endl;
    }

    int opt = LeerOpcion(maxOption)-1;
    switch (opt)
    {
        case 0:
        {
            limpiarPantalla();
            break;
        }
        break;
        case 1:
        {
            limpiarPantalla();
            nuevoTelco = MenuCrearTelco();
            seCreoTelco = true;

            limpiarPantalla();
            MenuTelco();
        }
        break;
        case 2:
        {
            limpiarPantalla();
            ifstream archivoEntrada;
            LeerArchivoParaLeer(archivoEntrada);
            nuevoTelco.cargar(archivoEntrada);
            archivoEntrada.close();
            seCreoTelco = true;
            limpiarPantalla();
            MenuTelco();
        }
        break;
        case 3:
        {
            limpiarPantalla();

            if (!seCreoTelco)
            {
                cout << "ERROR: No se creo ningun TelCO aun";
                break;
            }

            ofstream archivoSalida;

            LeerArchivoParaEscribir(archivoSalida);
            nuevoTelco.guardar(archivoSalida);
            archivoSalida.close();

            limpiarPantalla();
            MenuTelco();
        }
        break;
        case 4:
        {
            limpiarPantalla();
            if (!seCreoTelco)
            {
                cout << "ERROR: No se creo ningun TelCO aun";
                break;
            }

            cout << "La ultima trivia creada es: "<< endl<< endl;
            nuevoTelco.mostrar(cout);
            cout << endl<< endl;
            Pausar();

            limpiarPantalla();
            MenuTelco();
        }
        break;
        case 5:
        {
            limpiarPantalla();

            nuevoTelco.usuarios().mostrar(cout);

            cout << endl;
            Pausar();

            limpiarPantalla();
            MenuTelco();

        }
        break;
        case 6:
        {
            limpiarPantalla();

            mostrarLista(nuevoTelco.mensajes());

            cout << endl;

            Pausar();

            limpiarPantalla();
            MenuTelco();

        }
        break;
        case 7:
        {
            limpiarPantalla();

            mostrarLista(nuevoTelco.gateways());
            cout << endl;

            Pausar();

            limpiarPantalla();
            MenuTelco();

        }
        break;
        case 8:
        {
            limpiarPantalla();
            cout<<"Ingrese numero de usuario: "<< endl;
            cin>>participante;
            cin.ignore();
            sms=leerSMS();

            nuevoTelco.procesarMensaje(participante,sms);

            Pausar();

            limpiarPantalla();
            MenuTelco();
        }
        break;
        case 9:
            limpiarPantalla();
            MenuPrincipal();
            break;
    }
}

Pregunta leerPreg(){
  Puntaje p;
  Texto preg,resp;
  cout << "Ingrese pregunta: "<<endl;
  getline(cin,preg);
  cout << "Ingrese respuesta: " <<endl;
  getline(cin,resp);
  cout << "Ingrese puntaje: "<<endl;
  cin>> p;
  cin.ignore();

  return Pregunta(preg,resp,p);
}

Trivia MenuCrearTrivia(){

  Lista<Keyword> keys;
  Keyword key;
  string otra;
  bool sigue;
  do{
    sigue=false;
    cout<<"Ingrese Keyword:"<<endl;
    getline(cin,key);
    if (keys.pertenece(key)){
      cout<< "Ya estaba esa keyword "<<endl;
    }else{
      keys.agregarAtras(key);
    }
    cout<<"Desea ingresar otra keyword? [s/n]   ";
    getline(cin,otra);
    sigue= (otra[0]=='S' || otra=="" || otra[0]=='s');
  }while(sigue);

  Lista<Pregunta> pregs;
  Pregunta preg;
  int i=1;
  do{
    cout << "Pregunta "<<i<<" :"<<endl;
    sigue=false;
    preg=leerPreg();
    pregs.agregarAtras(preg);
    cout<<"Desea ingresar otra pregunta? [s/n]   ";
    getline(cin,otra);
    sigue= (otra[0]=='S' || otra=="" || otra[0]=='s');
    i++;
  }while(sigue);

  cout << "La trivia fue creada " << endl;

  return Trivia(keys,pregs);
}

Gateway MenuCrearGateway(){
  int num;
  cout<< "Ingrese numero de gateway:"<<endl;
  cin>>num;
  cin.ignore();

  Lista<Trivia> trivs;
  Trivia tr;
  string otra;
  bool sigue;
  int i=1;
  do{
    cout << "Creando Triva "<< i++ << " :"<<endl;
    sigue=false;
    tr= MenuCrearTrivia() ;
    trivs.agregarAtras(tr);
    cout<<"Desea ingresar otra trvia? [s/n]   ";
    getline(cin,otra);
    sigue= (otra[0]=='S' || otra=="" || otra[0]=='s');
  }while(sigue);

  Lista<Keyword> keys;
  Keyword key;

  do{
    sigue=false;
    cout<<"Ingrese Comando:"<<endl;
    getline(cin,key);
    if (keys.pertenece(key)){
      cout<< "Ya estaba ese comando"<<endl;
    }else{
      keys.agregarAtras(key);
    }
    cout<<"Desea ingresar otro comando? [s/n]   ";
    getline(cin,otra);
    sigue= (otra[0]=='S' || otra=="" || otra[0]=='s');
  }while(sigue);

  return Gateway(num,trivs,keys);
}

TelCO MenuCrearTelco(){
  Lista<Usuario> us;
  Lista<Gateway> gates;
  Usuario usuario;
  string otra;
  bool sigue;
  do{
    sigue=false;
    cout<< "Ingrese usuario nuevo: "<<endl;
    cin>>usuario;
    cin.ignore();

    if(us.pertenece(usuario)){
      cout<<"Ese usuario ya fue ingresado." << endl;
    }else{
      us.agregarAtras(usuario);
    }

    cout<<"Desea ingresar otro usuario? [s/n]   ";
    getline(cin,otra);
    sigue= (otra[0]=='S' || otra=="" || otra[0]=='s');
  }while (sigue);

  Gateway gate;
  int i=1;
  do{
    cout << "Creando Gateway "<< i++ << " :"<<endl;
    sigue=false;
    gate= MenuCrearGateway() ;

    gates.agregarAtras(gate);
    cout<<"Desea ingresar otra gateway? [s/n]   ";
    getline(cin,otra);
    sigue= (otra[0]=='S' || otra=="" || otra[0]=='s');
  }while(sigue);


  return TelCO(us,gates);
}
