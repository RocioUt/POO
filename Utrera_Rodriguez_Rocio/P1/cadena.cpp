#include "cadena.hpp"

using namespace std;

//CONSTRUCTORES
Cadena::Cadena(size_t tam, const char caracter) : s_ (new char[tam + 1]), tam_(tam){

	memset(s_, caracter, tam);
	s_[tam] = '\0';
	
}

Cadena::Cadena(const Cadena& cadena):s_(new char[cadena.tam_+1]),tam_(cadena.tam_){

    strcpy(s_,cadena.s_);

}

Cadena::Cadena(Cadena&& cad){
	
	tam_ = cad.tam_;
	s_ = new char[tam_ + 1];
	s_ = cad.s_;
	
	cad.tam_ = 0;
	cad.s_ = nullptr;
	
}

Cadena::Cadena(const char* cadena):s_(new char[strlen(cadena)+1]),tam_(strlen(cadena)){

    strcpy(s_,cadena);

}

//DESTRUCTOR
Cadena::~Cadena(){ delete[] s_; }

//OPERADORES
Cadena& Cadena::operator =(const char* cadena){
		
	tam_ = strlen(cadena);
	delete [] s_;
	s_ = new char[tam_ + 1];
	strcpy(s_, cadena);
	
	return *this;
	
}

Cadena& Cadena::operator=(const Cadena& cadena){
    
	if(this != &cadena){
    	delete[] s_;
    	tam_ = cadena.tam_;
	    s_ = new char[tam_+1];
    	strcpy(s_,cadena.c_str());
    }
	
    return *this;

}

Cadena& Cadena::operator =(Cadena&& cad) noexcept{
	
	if(this != &cad){
		delete[] s_;
		tam_ = cad.tam_;
		s_ = new char[tam_ + 1];
		s_ = cad.s_;
		
		cad.tam_ = 0;
		cad.s_ = nullptr;
		cad.s_ = new char[1];
		cad.s_[0] = '\0';
	}

  return *this;
}

Cadena& Cadena::operator +=(const Cadena& cadena){
	
	char* aux = new char[tam_ + cadena.tam_ + 1];
	stpcpy(aux,s_);
	strcat(aux,cadena.s_);
	delete[] s_;
	
	tam_ = tam_ + cadena.tam_;
	s_ = new char[tam_ + 1];
	strcpy(s_,aux);
	delete[] aux;
	
	return *this;
	
}

const char* Cadena::c_str() const{
    return s_;
}

size_t Cadena::length()const{
    return tam_;
}

//Acceso a cadena
const char& Cadena::operator [](size_t indice) const noexcept { return s_[indice]; }

char& Cadena::operator [](size_t indice) noexcept { return s_[indice]; }
	
char& Cadena::at(int n){
    if (n >= tam_)
		throw out_of_range("Llamada invalida a la funcion at");
  
	return (*this)[n];
	
}
	
char Cadena::at(int n) const{
    if (n >= tam_)
		throw out_of_range("Llamada invalida a la funcion at");
  
	return (*this)[n];
}
	
Cadena Cadena ::substr(size_t indice,int tam) const{
   if(indice >= tam_ || tam > tam_ - indice) 
		throw out_of_range("Indice superior al tamaño de la cadena");
	
	char* texto = new char[tam + 1];
	for(size_t i = indice; i < indice + tam; i++){
		texto[i - indice] =  s_[i];
	}
	
	texto[tam] = '\0';
	
	Cadena cad(texto);
	
	delete[] texto;
	
    return cad;
}

//Operadores de comparacion
bool operator ==(const Cadena& c1, const Cadena& c2){
	return strcmp(c1.c_str(), c2.c_str()) == 0;
}

bool operator !=(const Cadena& c1, const Cadena& c2){
	return !(c1 == c2);
}

bool operator <(const Cadena& c1, const Cadena& c2){
	return strcmp(c1.c_str(), c2.c_str()) < 0;
}

bool operator >(const Cadena& c1, const Cadena& c2){
	return (c2 < c1);
}

bool operator <=(const Cadena& c1, const Cadena& c2){
	return (c1 < c2 || c1 == c2);
}

bool operator >=(const Cadena& c1, const Cadena& c2){
	return (c1 > c2 || c1 == c2);
}

//Operadores de entrada y salida
istream& operator >> (istream& is, Cadena& cad){
	char* aux = new char[33]{'\0'};
	is >> setw(33) >> aux;
	cad = Cadena(aux);
	delete[] aux;
	return is;
}

ostream& operator << (ostream& os, const Cadena& cad){
	os << cad.c_str();
	return os;
}

Cadena operator +(const Cadena& c1, const Cadena& c2){
	
	Cadena auxiliar = c1;
	auxiliar += c2;

	return auxiliar;
	
}


