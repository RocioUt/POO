#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <cctype>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"
#include <cstring>

using namespace std;

class Usuario;

class Numero{
	public:
		enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
		
		//CONSTRCUTOR
		Numero(const Cadena& cad);
		
		//SUBCLASE
		class Incorrecto{
			public:
				Incorrecto(const Razon razon): razon_(razon) {}
				const Razon razon() const{ return razon_; }
			private:
				Razon razon_;
		};
		
		//CONVERSOR
		inline operator const char*() const{ return numero_.c_str(); }
		
	private:
		Cadena numero_;
};

inline bool operator <(const Numero& n1, const Numero& n2){ return strcmp(n1,n2) < 0; }


class Tarjeta{
	public:
		enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
		
		//CONSTRCUTOR
		Tarjeta(const Numero& numero, Usuario& titular, const Fecha& caducidad);
		
		Tarjeta(const Tarjeta& tarjeta) = delete;
		Tarjeta& operator = (const Tarjeta& tarjeta) = delete;
		
		//SUBCLASES
		class Caducada{
			public:
				Caducada(const Fecha& cuando):cuando_(cuando){}
				const Fecha& cuando() const{ return cuando_; }
			private:
				const Fecha cuando_;
		};
	
		class Num_duplicado{
			public:
				Num_duplicado(const Numero& numero): numero_(numero){}
				const Numero& que() const {return numero_;}
			private:
				Numero numero_;
		};	
		
		class Desactivada {};		

		//OBSERVADORES Y MODIFICADORES
		const Usuario* titular() const noexcept{ return titular_; }
		Tipo tipo() const noexcept{ return tipo_; }
		Fecha caducidad() const noexcept{ return caducidad_; }
		Cadena titular_facial() const noexcept{ return titular_facial_; }
		Numero numero() const noexcept{ return numero_; }
		bool activa() const noexcept { return activa_; } 
		bool activa(bool activada = true) { activa_ = activada; return activa_; }
		void anular_titular();
		
		//DESTRUCTOR
		~Tarjeta();
		
	private:
		Tipo tipo_;
		Cadena titular_facial_;
		Numero numero_;
		Fecha caducidad_;
		const Usuario* titular_;
		bool activa_;
		
};

inline bool operator <(const Tarjeta& t1, const Tarjeta& t2){ return t1.numero() < t2.numero(); }

ostream& operator <<(ostream& os, const Tarjeta& t);
ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo);

#endif

