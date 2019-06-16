#include "pedido-articulo.hpp"

using namespace std;

ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& p){
	
	os << "PVP \tCantidad \tArtículo \n";
	os << "==================================================================\n";
	double t=0;
	for(auto it : p){
		os << it.second<<"\t";
		os << "[" << it.first->referencia() << "] \"" << it.first->titulo() << "\"" << "\n";
		t = t + it.second.precio_venta() * it.second.cantidad();
	}  
	os << "==================================================================\n";
	os << "Total \t" << t << " € \n";
	return os;
	
}

ostream& operator <<(ostream& os, const LineaPedido& l){
	
	os << fixed << setprecision(2) << l.precio_venta() << " €" << "\t" << l.cantidad();
	return os;
	
}

ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& p){
	
	os << "[Pedidos: " << p.size() << "]\n";
	os << "==================================================================\n";
	os << "PVP \tCantidad \tFecha de venta\n";
	os << "==================================================================\n";
	
	double t=0;
	unsigned n=0;
	for(auto it : p){
		os << it.second << "\t" << it.first->fecha() << "\n";
		t = t + it.second.precio_venta() * it.second.cantidad();
		n = n + it.second.cantidad();
	}
	
	os << "==================================================================\n";
	os << fixed << setprecision(2);
	os << t << " €\t" << n << "\n";
	return os;
	
}

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os){
	
	for(auto it : inverso){
		os << "Ventas de [" << it.first->referencia() << "] \"" << it.first->titulo() << "\"" << "\n";
		os << it.second << "\n";
	}

	return os;
	
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os){
	
	double t=0.0;
	for(auto it:directo){
		os << "Pedido num." << it.first->numero() << "\n";
		os << "Cliente: " << it.first->tarjeta()->titular()->nombre() << "\n";
		os << "Fecha: " << it.first->fecha() << "\n";
		os << it.second << "\n";
		for(auto iterator : it.second){
			t += iterator.second.precio_venta() * iterator.second.cantidad();
		}
	}
	os << "TOTAL VENTAS \t" << fixed << setprecision(2) << t << " €\n";
	return os;
	
}


