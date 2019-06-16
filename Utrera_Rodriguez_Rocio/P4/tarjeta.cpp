#include "tarjeta.hpp"
#include "cadena.hpp"
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <functional>

using namespace std;
bool luhn (const Cadena&);

struct EsDigito{
	bool operator()(char c) const{ return isdigit(c); }
};

//CONSTRUCTORES
Numero::Numero(const Cadena& num):numero_(num){
	
	Cadena::iterator fin = remove_if(numero_.begin(), numero_.end(), [](char c){ return isspace(c); });
	if(fin != numero_.end()){
		*fin='\0';
		Cadena sd(numero_.c_str());
		numero_ = sd;
	}
	if(find_if(numero_.begin(), numero_.end(), not1(function<bool(char)>(EsDigito()))) != numero_.end()){
		throw Incorrecto(DIGITOS);
	}

	size_t j = numero_.length();
	if(j < 13 || j > 19) throw Incorrecto(LONGITUD);
	if(!luhn(numero_)) throw Incorrecto(NO_VALIDO);

}

Tarjeta::Tarjeta(const Numero& numero,Usuario& titular, const Fecha& caducidad):
	numero_(numero), titular_(&titular),caducidad_(caducidad){
	
	if(caducidad < Fecha() ){ throw Tarjeta::Caducada(caducidad_); }

	int caracter1 = numero[0];
	int caracter2;
	switch(caracter1 - '0'){
		case 3: caracter2 = numero[1];
					caracter2 -= '0';
					if(caracter2 == 4 || caracter2 == 7)
						tipo_ = Tipo::AmericanExpress;
					else
						tipo_ = Tipo::JCB; 
					break;

		case 4: tipo_ = Tipo::VISA; break;
		case 5: tipo_ = Tipo::Mastercard; break;
		case 6: tipo_ = Tipo::Maestro; break;
		default: tipo_ = Tipo::Otro; break;
	}
	activa_ = true;

	titular_facial_ = titular_->nombre()+" "+titular_->apellidos();
	for(int i = 0; i < titular_facial_.length(); i++) {
		titular_facial_[i] = toupper(titular_facial_[i]);
	}
	titular.es_titular_de(*this);
}

//DESTRUCTOR
Tarjeta::~Tarjeta(){
	
	if(titular_){
		Usuario* aux = const_cast<Usuario *> (titular_);
		aux->no_es_titular_de(*this);
	}
	
}

void Tarjeta::anular_titular(){ titular_ = nullptr; }

ostream& operator <<(ostream& os,const Tarjeta& tarjeta){
	
	os << tarjeta.tipo() <<"\n";
	os << tarjeta.numero() <<"\n";
	os << tarjeta.titular_facial() <<"\n";
	os << "Caduca: " << setfill('0') << setw(2) << tarjeta.caducidad().mes() << "/" << tarjeta.caducidad().anno()%100  <<"\n";
	return os;
	
}

ostream& operator<<(ostream& os,const Tarjeta::Tipo& tipo){
	
	switch (tipo){
		case static_cast<const Tarjeta::Tipo>(0):	os << "Tipo indeterminado ";	break;	//case Tarjeta::VISA:
		case static_cast<const Tarjeta::Tipo>(1):	os << "VISA "; 					break;	//case Tarjeta::Mastercard:
		case static_cast<const Tarjeta::Tipo>(2):	os << "Mastercard "; 			break;	//case Tarjeta::Maestro:
		case static_cast<const Tarjeta::Tipo>(3):	os << "Maestro "; 				break; 	//case Tarjeta::JCB:
		case static_cast<const Tarjeta::Tipo>(4):	os << "JCB ";					break;	//case Tarjeta::AmericanExpress:
		case static_cast<const Tarjeta::Tipo>(5):	os << "AmericanExpress ";		break;	//case Tarjeta::AmericanExpress:
	}
	return os;
	
}
