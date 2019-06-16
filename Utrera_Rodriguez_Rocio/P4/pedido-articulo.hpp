#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iomanip>
#include "pedido.hpp"

using namespace std;

class LineaPedido{
	public:
		//CONSTRUCTOR
		explicit LineaPedido(double pv, unsigned cant = 1u):precio_venta_(pv),cantidad_(cant){}
		
		//OBSERBADORES
		double precio_venta() const{ return precio_venta_; }
		unsigned cantidad() const{ return cantidad_; }
		
	private:
		double precio_venta_;
		unsigned cantidad_;
};

struct OrdenaPedidos : public binary_function<Pedido*, Pedido*, bool> {
  bool operator()(const Pedido* p1, const Pedido* p2) const { return p1->numero() < p2->numero(); }
};

struct OrdenaArticulos : public binary_function<Articulo*, Articulo*, bool> {
  bool operator()(const Articulo* a1, const Articulo* a2) const { return a1->referencia() < a2->referencia(); }
};

ostream& operator <<(ostream& os, const LineaPedido& l);

class Pedido_Articulo{
	public:
		typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
		typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
		void pedir(Pedido& pedido, Articulo& articulo,double precio,unsigned cantidad=1u){
			directo[&pedido].insert(make_pair(&articulo, LineaPedido(precio, cantidad)));
			inverso[&articulo].insert(make_pair(&pedido, LineaPedido(precio, cantidad)));
		}
		void pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad = 1u){
			pedir(pedido, articulo, precio, cantidad);
		}
		const ItemsPedido& detalle(Pedido& pedido){return directo[&pedido];}
		const Pedidos& ventas(Articulo& articulo){return inverso[&articulo];}
		ostream& mostrarDetallePedidos(ostream& os);
		ostream& mostrarVentasArticulos(ostream& os);
	private:
		map<Articulo*, Pedidos, OrdenaArticulos> inverso;
		map<Pedido*, ItemsPedido, OrdenaPedidos> directo;
};

ostream& operator<<(ostream& os, const Pedido_Articulo::ItemsPedido& pedido);
ostream& operator<<(ostream& os, const Pedido_Articulo::Pedidos& pedido);

#endif
