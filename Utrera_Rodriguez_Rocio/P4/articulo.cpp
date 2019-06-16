#include "articulo.hpp"

using namespace std;

//CONSTRUCTOR
Articulo::Articulo(const Autores& autores, const Cadena& referencia,const Cadena& titulo, const Fecha& f_publi, const double precio):
	referencia_(referencia), titulo_(titulo), f_publi_(f_publi), precio_(precio){
	
	if(autores.empty()){ throw Autores_vacios();}
	
	autores_=autores;
	
}

ostream& operator <<(ostream& os,const Articulo& articulo){
	
	os 	<< 	"[" << articulo.referencia() << "] \"" << articulo.titulo() << "\", de " ;
	
	Articulo::Autores::const_iterator  iter_autor = articulo.autores().cbegin();
	os << (*iter_autor)->apellidos();
	iter_autor++;
	while(iter_autor != articulo.autores().cend()){
		os << ", " << (*iter_autor)->apellidos();
		iter_autor++;
	}
	
	os << ". " << articulo.f_publi().anno() << ". " ;
	os << fixed << setprecision(2);
	
	os << articulo.precio() <<" €\n";
	os << "\t";
	
	articulo.impresion_especifica(os);
	return os;

}