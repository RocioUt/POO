#include "usuario.hpp"
#include <random>
#include <utility> 
#include <cstdlib>
#include <iomanip>

extern "C"{
	#include <unistd.h>
}

using namespace std;

unordered_set<Cadena> Usuario::identificadores;

//CONSTRUCTORES
Clave::Clave(const char* pass){
	
	if(strlen(pass) < 5){ throw Incorrecta(CORTA); }
	
	static const char* const cv = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./";
	static size_t longtud = sizeof(cv) - 1;
	static random_device r;
	static uniform_int_distribution<size_t> dist(0, longtud-1);
	
	char sal[]={ cv[ dist(r) ] , cv[ dist(r) ] };
	
	if (char* constraseña = crypt(pass,sal)){ 
		clave_ = Cadena(constraseña); 
	}else{ 
		throw Incorrecta(ERROR_CRYPT); 
	}
	
}

Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& clave):
	id_(id), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), clave_(clave){
	
	if(!identificadores.insert(id_).second) throw Id_duplicado(id_);

}

bool Clave::verifica(const char* pass) const{
	
	if(char* tc = crypt(pass, clave_.c_str())){ return tc==clave_; }
	
	throw Incorrecta(ERROR_CRYPT); 

}


/*Asociación con Tarjeta .*/
void Usuario::es_titular_de(Tarjeta& tarjeta){
	
	if(this == tarjeta.titular()){
		tarjetas_.insert(make_pair(tarjeta.numero(), &tarjeta));
	}

}

void Usuario::no_es_titular_de(Tarjeta& tarjeta){ tarjetas_.erase(tarjeta.numero()); }

//DESTRUCTOR
Usuario::~Usuario(){
	
	identificadores.erase(id_);
	
	while(!tarjetas_.empty()){
		tarjetas_.begin()->second->anular_titular();
		tarjetas_.erase(tarjetas_.begin());
	}
	
}

/*Asociación  con Articulo */
void Usuario::compra(Articulo& articulo,unsigned cantidad){
	
	if(!cantidad){
		articulos_.erase(&articulo);
	}else{
		articulos_[&articulo]=cantidad;
	}

}


ostream& operator <<(ostream& os, const Usuario& usuario){
	
	os << usuario.id() << " [" << usuario.clave_.clave() << "] " << usuario.nombre() << " " << usuario.apellidos() << "\n";
	os << usuario.direccion()<< "\n";
	os << "Tarjetas:\n";
	
	for(Usuario::Tarjetas::const_iterator it=usuario.tarjetas().begin(); it != usuario.tarjetas().end(); it++){
		os << *it->second;
	}
	
	return os;
}

ostream& mostrar_carro(ostream& os, const Usuario& usuario){
	
	os << "Carrito de compra de " << usuario.id() << " [Artículos: " << usuario.n_articulos() << "]\n";
	os << " Cant. Artículo \n";
	os << "=========================================================== \n";
  
	for(Usuario::Articulos::const_iterator it=usuario.compra().begin(); it!=usuario.compra().end(); ++it){
		os 	<< it->second << " [" << it->first->referencia() << "] " << "\"" << it->first->titulo() << "\"" << ", " << it->first->f_publi().anno()  << ". "
				<< fixed << setprecision(2) << it->first->precio() << " €" << "\n";
	}
	
	return os;

}
