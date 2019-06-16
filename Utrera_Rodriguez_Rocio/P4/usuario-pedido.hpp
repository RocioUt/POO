#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <map>
#include <set>
#include "pedido.hpp"
#include "usuario.hpp"

using namespace std;

class Usuario_Pedido{
	public:
		typedef set <Pedido*> Pedidos ;
		typedef map <Usuario*, Pedidos> UsuarioPedidos ;
		typedef map <Pedido*, Usuario*> PedidoUsuario ;

		void asocia(Usuario& user,Pedido& pedido){
			directa[&user].insert(&pedido);
			inversa[&pedido] = &user;
		}
		
		void asocia(Pedido& pedido, Usuario& user){
			asocia(user, pedido);
		}
		
		const Pedidos&  pedidos(Usuario& user){ return directa[&user]; }
		const Usuario* cliente(Pedido& pedido){ return inversa[&pedido]; }

	private:
		UsuarioPedidos directa;
		PedidoUsuario  inversa;
};

#endif