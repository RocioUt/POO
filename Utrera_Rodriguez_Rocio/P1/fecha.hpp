#ifndef FECHA_HPP_
#define FECHA_HPP_

#include <iostream>
#include <ctime>
#include <cstring>
#include <iostream>

using namespace std;

class Fecha{
	public:
	//Constructores
		explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
		//Fecha(const Fecha& fecha);   No hace falta 
		Fecha(const char* cadena); //Constructor conversion a través de cadena; 11/12/1973 
		
		class Invalida{
			public:
				Invalida(const char* motivo) : why_ (motivo) {};
				const char* por_que() const { return why_; };
			private:
				const char* why_;
		};
	
	//Observadores
		int dia() const { return dia_; }
		int mes() const { return mes_; }
		int anno() const { return anno_; }
		
	//Operadores
		Fecha& operator +=(int i);
		Fecha& operator -=(int i);
		Fecha& operator ++(); //Preincremento
		Fecha operator ++(int); //Postincremento
		Fecha& operator --(); //Predecremento
		Fecha operator --(int); //Postdecremento
		Fecha operator +(int i) const;
		Fecha operator -(int i) const;
		//Fecha& operator =(const Fecha& fecha); Tampoco hace falta
		
		//operator const char*() const; //P0
		const char* cadena () const; //P1
  
		static const int AnnoMinimo = 1902;
		static const int AnnoMaximo = 2037;
		
	private:
		int dia_, mes_, anno_;
		void Correcta() const;
	
};

//Operadores de comparacion
	bool operator ==(const Fecha& a, const Fecha& b);
	bool operator !=(const Fecha& a, const Fecha& b);
	bool operator <(const Fecha& a, const Fecha& b);
	bool operator >(const Fecha& a, const Fecha& b);
	bool operator <=(const Fecha& a, const Fecha& b);
	bool operator >=(const Fecha& a, const Fecha& b);
	
	
	istream& operator >> (istream& os, Fecha& f);
	ostream& operator << (ostream& os, const Fecha& f);
	
#endif //FECHA_HPP_

