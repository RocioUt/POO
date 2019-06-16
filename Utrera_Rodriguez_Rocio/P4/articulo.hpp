#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <set>
#include <iomanip>	//para la funcion setprecision()

using namespace	std;

class Autor{
	public:
		//CONSTRUCTOR
		Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) noexcept:
			nombre_(nombre),apellidos_(apellidos),direccion_(direccion){}
		
		//OBSERVADORES
		const Cadena& nombre() const noexcept{ return nombre_;}
		const Cadena& apellidos() const noexcept{ return apellidos_;}
		const Cadena& direccion() const noexcept{ return direccion_;}
		
	private:
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
};

class Articulo{
	public:
		typedef set<Autor*> Autores;
		class Autores_vacios{};
		
		//CONSTRUCTOR
		Articulo(const Autores& autores, const Cadena& referencia,const Cadena& titulo, const Fecha& f_publi, const double precio);
		
		//OBSERVADORES Y MODIFICADORES
		const Autores& autores() const{ return autores_;}
		Cadena referencia() const{ return referencia_;}
		Cadena titulo() const{ return titulo_ ;	}
		Fecha f_publi() const{ return f_publi_;	}
		double& precio(){ return precio_; }
		const double precio() const { return precio_;}
		virtual void impresion_especifica(ostream& os) const = 0;
		
		//DESTRUCTOR
		virtual ~Articulo(){}
		
	protected:
		double precio_;
		Autores autores_;
		Cadena referencia_;
		Fecha f_publi_;
		Cadena titulo_;
};

class ArticuloAlmacenable: public Articulo {
	public:
		//CONSTRUCTOR
		ArticuloAlmacenable(const Autores& autores, const Cadena& referencia,const Cadena& titulo, const Fecha& f_publi, const double precio,const unsigned stock):
			Articulo(autores,referencia,titulo,f_publi,precio),stock_(stock){}
			
		//OBSERVADORES Y MODIFICADORES
		unsigned& stock(){ return stock_; }
		const unsigned stock() const	{ return stock_; }
		
	protected: 
		unsigned stock_;
};

class Libro: public ArticuloAlmacenable {
	public:
		//CONSTRUCTOR
		Libro(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, const double precio,
			const unsigned n_pag,unsigned stock=0): ArticuloAlmacenable(autores, referencia, titulo, f_publi, precio, stock), n_pag_(n_pag){}
			
		//OBSERVADORES
		const unsigned n_pag() const {return n_pag_;}
		void impresion_especifica(ostream& os) const{ os << n_pag_ << " págs., " << stock_ << " unidades."; }
		
	protected:
		const unsigned n_pag_;
};

class Cederron: public ArticuloAlmacenable {
	public:
		//CONSTRUCTOR
		Cederron(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, const double precio,
			const unsigned tam, unsigned stock = 0): ArticuloAlmacenable(autores, referencia, titulo, f_publi, precio, stock), tam_(tam){}
			
		//OBSERVADORES
		void impresion_especifica(ostream& os) const{ os << tam_ << " MB, " << stock_ << " unidades."; }
		const unsigned tam() const{ return tam_; }
		
	protected:
		const unsigned tam_;
};


class LibroDigital: public Articulo{
	public:
		//CONSTRUCTOR
		LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, const double precio,
			const Fecha& f_expir): Articulo(autores, referencia, titulo, f_publi, precio), f_expir_(f_expir){}
			
		//OBSERVADORES
		const Fecha& f_expir() const{ return f_expir_; }
		void impresion_especifica(ostream& os) const{ os << "A la venta hasta el " << f_expir_ <<"."; }
		
	protected:
		Fecha f_expir_;
};

ostream& operator <<(ostream& os, const Articulo& articulo);

#endif
