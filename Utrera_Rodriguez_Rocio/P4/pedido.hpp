#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "tarjeta.hpp"

using namespace std;

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
	public:
		//CONSTRUCTOR
		Pedido(Usuario_Pedido& usuario_pedidos, Pedido_Articulo& pedido_articulo, Usuario& user,const Tarjeta& tarjeta,const Fecha& fecha = Fecha());
		
		//OBSERVADORES
		int numero() const{ return num_; }
		const Tarjeta* tarjeta() const{ return tarjeta_; }
		Fecha fecha() const{ return fecha_; }
		double total() const{ return total_; }
		static int n_total_pedidos(){ return N_pedidos; }
		
		//SUBCLASES
		class Vacio{
			public:
				Usuario& usuario()const {return *user;}
				Vacio(Usuario& u):user(&u){};
			private:
				Usuario* user;	 
		};
		
		class Impostor{
			public:
				Usuario& usuario()const {return *user;}
				Impostor(Usuario& u):user(&u){};
			private:
				Usuario* user;	 
		};
		
		class SinStock{
			public:
				Articulo& articulo()const {return *articulo_;}
				SinStock(Articulo& a):articulo_(&a){};
			private:
				Articulo* articulo_;	 
		};
		
	private:
		static unsigned N_pedidos;
		int num_;
		double total_;
		const Tarjeta* tarjeta_;
		Fecha fecha_;
};

ostream& operator <<(ostream& os, const Pedido& pedido);

#endif