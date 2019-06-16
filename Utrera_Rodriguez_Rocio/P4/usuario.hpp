#ifndef USUARIO_HPP_
#define USUARIO_HPP_


#include "articulo.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"

#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Tarjeta;
class Numero;

class Clave{
	public:
		//CONSTRUCTOR
		Clave(const char* texto_claro);
		
		//OBSERVADOR
		const Cadena& clave()const{ return clave_; }
		
		bool verifica(const char* cad)const;
		
		enum Razon{CORTA,ERROR_CRYPT};
		//SUBCLASE
		class Incorrecta{
			public:
				Incorrecta(Razon razon):razon_(razon){}
				 Razon razon() const { return razon_; }
			private:
				const Razon razon_;
		};
		
	private:
		Cadena clave_;
};

class Usuario{
	public:
		typedef map<Numero, Tarjeta*> Tarjetas;
		typedef unordered_map<Articulo*, unsigned int> Articulos;
		
		//CONSTRUCTOR
		Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& password);
		
		Usuario(const Usuario& usuario) = delete;
		Usuario& operator = (const Usuario& usuario) = delete;
		
		//SUBCLASE
		class Id_duplicado{
			public:
				Id_duplicado(const Cadena id): idd_(id) {}
				 const Cadena idd()const{ return idd_; }
			private:
				const Cadena idd_;
		};

	    
		//OBSERVADORES
		const Tarjetas& tarjetas() const{ return tarjetas_; }
		Cadena id() const{	return id_; }
		Cadena apellidos() const{ return apellidos_; }
		Cadena direccion() const{ return direccion_; }
		Cadena nombre() const{ return nombre_; }
		const Articulos& compra() const{ return articulos_; }
		size_t n_articulos() const{ return articulos_.size(); }
		
		void es_titular_de(Tarjeta& tarjeta);
		void no_es_titular_de(Tarjeta& tarjeta);
		
		//DESTRUCTOR
		~Usuario();
		
		void compra(Articulo& articulo, unsigned cantidad = 1);		
		
		friend ostream& operator <<(ostream& os, const Usuario& usuario);
		
	private:
		static unordered_set<Cadena> identificadores;
		Cadena id_;
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
		Tarjetas tarjetas_;
		Articulos articulos_;
		Clave clave_;
};

ostream& mostrar_carro(ostream& os, const Usuario& usuario);

#endif
