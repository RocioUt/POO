#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Cadena{
    public:
        explicit Cadena(size_t tam = 0, const char caracter  = ' ');
        Cadena(const Cadena& cadena);
		Cadena(Cadena&& cadena);
		Cadena (const char* cadena);        

        ~Cadena();
		
		Cadena& operator =(const char* cadena);
        Cadena& operator =(const Cadena& cadena);
		Cadena& operator=(Cadena&& cadena) noexcept;
        Cadena& operator +=(const Cadena& cadena);

		const char* c_str()const;
        size_t length() const;
		
        const char& operator [](size_t indice) const noexcept;
		char& operator [](size_t indice) noexcept;
        char& at(int n) ;
        char at(int n) const ;
    	Cadena substr(size_t indice,int tam) const;

        //Iteradores
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator>reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		iterator begin() const { return s_; };
		iterator end() const { return s_ + tam_; };
		const_iterator cbegin() const { return begin(); };
		const_iterator cend() const { return end(); };

		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }

		const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }


    private:
        char* s_; //cadena;
        size_t tam_;

};



//Operadores de comparacion
bool operator ==(const Cadena& cadena1, const Cadena& cadena2);
bool operator !=(const Cadena& cadena1, const Cadena& cadena2);
bool operator <=(const Cadena& cadena1, const Cadena& cadena2);
bool operator >=(const Cadena& cadena1, const Cadena& cadena2);
bool operator <(const Cadena& cadena1, const Cadena& cadena2);
bool operator >(const Cadena& cadena1, const Cadena& cadena2);

ostream& operator<<(ostream& os,const Cadena& cad);

istream& operator>>(istream& is,Cadena& cad);

Cadena operator +(const Cadena& c1, const Cadena& c2);

namespace std { 
    template <> 
    struct hash<Cadena> {
        size_t operator() (const Cadena& cad) const
        {
            hash<string> hs;
            const char * p = cad.c_str(); 
            string s(p);
            size_t res = hs(s);
            return res;
        }
    };
}

#endif
