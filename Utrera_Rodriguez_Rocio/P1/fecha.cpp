#include "fecha.hpp"

using namespace std;

Fecha::Fecha(int dia, int mes, int anno): dia_(dia), mes_(mes), anno_(anno){

	time_t tiempo_cal = time(nullptr);
    tm* tiempo_descompuesto = localtime(&tiempo_cal);

    if(dia == 0)
      dia_ = tiempo_descompuesto->tm_mday;

    if(mes == 0)
      mes_ = tiempo_descompuesto->tm_mon + 1;

    if(anno == 0)
      anno_ = tiempo_descompuesto->tm_year + 1900;

    Correcta();

}

Fecha::Fecha(const char* cad){

  if(sscanf(cad, "%d/%d/%d", &dia_, &mes_, &anno_) == 3)
      *this = Fecha(dia_, mes_, anno_);

  else
    throw Fecha::Invalida("ERROR DE CONVERSION\n");

}

Fecha& Fecha::operator += (int i){

	dia_ += i;
	
	//Para normalizar la fecha
	time_t tiempo_cal = time(nullptr);
    tm* t = localtime(&tiempo_cal);
	t->tm_mday = dia_,
	t->tm_mon = mes_ - 1;
	t->tm_year = anno_ - 1900;
	
	mktime(t);
	
		dia_ = t->tm_mday;
		mes_ = t->tm_mon + 1;
		anno_ = t->tm_year + 1900;
	
	Correcta();
	
	return *this;

}

Fecha& Fecha::operator -=(int i){

  *this += -i;

  return *this;

}

Fecha& Fecha::operator++(){

  *this += 1;

  return (*this);

}

Fecha Fecha::operator++(int){

  Fecha auxiliar = (*this);
  *this += 1;

  return auxiliar;

}

Fecha& Fecha::operator--(){

  *this += -1;

  return (*this);

}

Fecha Fecha::operator--(int){

  Fecha auxiliar = (*this);
  *this += -1;

  return auxiliar;

}

Fecha Fecha::operator +(int i) const{

  Fecha auxiliar = *this;
  auxiliar += i;

  return auxiliar;

}

Fecha Fecha::operator -(int i) const{

  Fecha auxiliar = (*this);
  auxiliar += -i;

  return auxiliar;

}

/*Fecha::operator const char*() const{     //P0

  static char fechaCad[36];

  tm t = {0, 0, 0, dia_, mes_ - 1, anno_ - 1900, 0, 0, 0};
  static const char* semana[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
  static const char* mes[] = {"", "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio","agosto", "septiembre", "octubre", "noviembre", "diciembre"};

  mktime(&t); 
  int diasem = t.tm_wday;

  sprintf(fechaCad, "%s %d de %s de %d", semana[diasem], dia_, mes[mes_], anno_);

  return fechaCad;

}*/

const char* Fecha::cadena() const { //Modificar de Pablo*****************************
	
	static char fechaCad[36];

	tm t = {0, 0, 0, dia_, mes_ - 1, anno_ - 1900, 0, 0, 0};
	
	static const char* semana[7] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
	static const char* mes[13] = {"", "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

	mktime(&t);
	int diasem = t.tm_wday;

	sprintf(fechaCad, "%s %d de %s de %d", semana[diasem], dia_, mes[mes_], anno_);

	return fechaCad;
	
}

istream& operator >> (istream& is, Fecha& f){
	
	char* cadena = new char[11];
	is.getline(cadena, 11);
	
	try{
		f = Fecha(cadena);
	}catch(Fecha::Invalida& e){
		is.setstate(ios::failbit);
		cerr << e.por_que() << endl;
		throw;
	}
	
	return is;
	
}

ostream& operator << (ostream& os, const Fecha& f){
	
	os << f.cadena();
	return os;

}

void Fecha::Correcta() const{

	int dias[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	
	if(anno_ % 4 == 0 &&(anno_ % 400 == 0 || anno_ % 100 != 0))
		dias[2]++;
	
	if(anno_ < AnnoMinimo || anno_ > AnnoMaximo)
		throw Invalida("ERROR, anno fuera de rango");
	
	if(mes_ < 1 || mes_ > 12)
		throw Invalida("ERROR, mes invalido");
	
	if(dia_ < 1 || dia_ > dias[mes_])
		throw Invalida("ERROR, dia invalido");

}


bool operator == (const Fecha& a, const Fecha& b){

  return ((a.dia() == b.dia()) && (a.mes() == b.mes()) && (a.anno() == b.anno()));

}

bool operator != (const Fecha& a, const Fecha& b){ return !(a==b); }

bool operator < (const Fecha& a, const Fecha& b){

	if(a.anno() < b.anno())
		return true;

	else 
		if(a.anno() == b.anno() && a.mes() < b.mes())
			return true;

		else 
			if(a.anno() == b.anno() && a.mes() == b.mes() && a.dia() < b.dia())
				return true;
			
			else
				return false;

}

bool operator > (const Fecha& a, const Fecha& b){ return (b < a); }

bool operator <= (const Fecha& a, const Fecha& b){ return (a < b || a == b); }

bool operator >= (const Fecha& a, const Fecha& b){ return (a > b || a == b); }