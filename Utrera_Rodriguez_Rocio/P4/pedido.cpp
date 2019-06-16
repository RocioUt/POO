#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iomanip>

using namespace std;
unsigned Pedido::N_pedidos=0;

//CONSTRUCTOR
Pedido::Pedido(Usuario_Pedido& usuario_pedidos, Pedido_Articulo& pedido_articulo, Usuario& user, const Tarjeta& tarjeta, const Fecha& fecha):
	num_(N_pedidos+1), tarjeta_(&tarjeta), fecha_(fecha), total_(0.0){
	
	if(user.n_articulos()==0)throw Vacio(user);
	if(&user != tarjeta.titular()) throw Impostor(user);
	if(tarjeta.caducidad()<fecha) throw Tarjeta::Caducada(tarjeta.caducidad());
	if(tarjeta.activa()==false) throw Tarjeta::Desactivada();
	
	Usuario::Articulos carro = user.compra();
	bool pedido_final_vacio = true;
	for(auto c : carro ){
		Articulo *pa = c.first;
		unsigned cantidad = c.second;
		double precio = pa->precio();
		
		if(ArticuloAlmacenable *paa = dynamic_cast<ArticuloAlmacenable*>(pa) ){
			if(paa->stock() < c.second){
				const_cast<Usuario::Articulos&>(user.compra()) .clear();
				throw SinStock(*c.first);
			}			
			paa->stock() -= cantidad;
			pedido_articulo.pedir(*this,*pa,precio,cantidad);
			total_ += cantidad*precio;
			user.compra(*pa,0);
			pedido_final_vacio=false;
		}else if(LibroDigital* pdl = dynamic_cast<LibroDigital*>(pa)){
			if(pdl->f_expir() > fecha){
				pedido_articulo.pedir(*this, *pa, precio, cantidad);
				total_ += cantidad*precio;
				user.compra(*pa, 0);
				pedido_final_vacio=false;
			}
		}
	}
	if(pedido_final_vacio) throw Vacio(user);
	usuario_pedidos.asocia(user,*this);
	++N_pedidos;
	
} 
			
ostream& operator <<(ostream& os,const Pedido& pedido){
	
	os << "Núm. pedido: "<< pedido.numero()<<"\n";
	os << "Fecha: "<< pedido.fecha()<<"\n";
	os << "Pagado con: "<<pedido.tarjeta()->tipo()<<"n.º: "<< pedido.tarjeta()->numero()<<"\n";
	os << "Importe: "<<pedido.total()<<" €\n";
	return os;

}