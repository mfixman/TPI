#include "tipos.h"
#include "auxiliares.h"

//template <typename A, typename B> B parte ( Lista < pair < A, B > > q, A b )
template <typename A, typename B> parte ( Lista < pair <A, B> > q, A b )
{
	int i = 0 ;
	pair <A, B> r ;

	while ( i < q.longitud() )
	{
		if ( q.iesimo(i).first == b ) r = q.iesimo(i) ;
	}

	return r ;
}
