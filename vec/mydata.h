#ifndef _MYDATA_H
#define _MYDATA_H 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <valarray>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <immintrin.h>
#include <algorithm>
#include <bitset>

// Vector length <= 32
typedef unsigned char Eltype;
const int Vsize=32;

#ifdef __AVX512__
const int Align=64;
#else
const int Align=32;
#endif
 
typedef Eltype u8x32 __attribute__ ((vector_size(Vsize)));


class SimpleElem // vectors only 
{
protected:
    u8x32 *data;
    int size;
public:
    SimpleElem(){};
    SimpleElem(const Eltype* t,size_t n,u8x32 *buf):size(n){
        set_ref(buf);
        for(size_t i=0;i<n;++i)data[0][i]=t[i];
        for(size_t i=n;i<Vsize;++i)data[0][i]=0;
    };
    bool operator<(const SimpleElem& v)const; // for sorting
    bool operator>(const SimpleElem& v)const; // for sorting
    bool operator>(const u8x32& v)const; 
    bool operator<=(const SimpleElem& v)const; // Main comparison function
    bool operator<=(const u8x32& v)const; // Main comparison function
    bool operator==(const SimpleElem& v)const; // for unique
    bool operator!=(const SimpleElem& v)const; // for unique
    u8x32 get_data()const{return *data;}
    int get_size()const{return size;}
    void set_ref(u8x32* ref){data=ref;}
    void set_size(int nsize){size=nsize;}
    friend std::ostream& operator<<(std::ostream& os, 
            const SimpleElem& v);
};

class Suppl // Supplement info for vectors
{
private:
    std::string header;
    std::vector<std::string> str;
public:
    Suppl(){};
    Suppl(std::string Head,std::vector<std::string>Str):
        header(Head),str(Str){};
    const std::string& get_header()const{return header;}
    const std::vector<std::string>& get_str()const{return str;}
};

class ElemPoint: public SimpleElem // Vectors + pointer to supplement
{
private:
    const Suppl* suppl;
public:
    ElemPoint():SimpleElem(){};
    void set_suppl(const Suppl* val){suppl=val;}
    friend std::ostream& operator<<(std::ostream& os, 
                                const ElemPoint& v);
};

class  Elem: public SimpleElem
{
private:
    Suppl suppl;
public:
    Elem():SimpleElem(),suppl(){};
    Elem(const Eltype* t,size_t n,u8x32 *buf,std::string Head,
        std::vector<std::string>Str):SimpleElem(t,n,buf),
        suppl(Head,Str){};
    const Suppl* get_suppl()const{return &suppl;};
    friend std::ostream& operator<<(std::ostream& os, const Elem& v);
};
std::istream& read_elem(std::istream& in, Elem& val);


class VecList: public std::list<Elem>
{
private:
    u8x32 *data;
    int allocsize;
    int cursize;
public:
    VecList():std::list<Elem>(),allocsize(10000000),cursize(0){
        data=(u8x32*)std::aligned_alloc(Align,
                    sizeof(Eltype)*Vsize*allocsize);}
    VecList& simplify();
    void push_back(const Elem& val);
    void clear(){cursize=0;std::list<Elem>::clear();}
    void repack();
    void merge_unique(VecList& v);
    iterator insert(const_iterator pos, const Elem& val);
    friend std::ostream& operator<<(std::ostream& os, 
                                    const VecList& vec);
    ~VecList(){std::free(data);}
};

std::istream& read_veclist(std::istream& in, VecList& lst);

class SimpleVecList: public std::list<ElemPoint>
{
private:
    u8x32 *data;
public:
    SimpleVecList(int nlist,VecList *vec);
    ~SimpleVecList(){std::free(data);}
    SimpleVecList& simplify();
    int get_size()const{return size();}
    int get_elemsize()const{return begin()->get_size();}
    void repack();
    bool check(const SimpleElem& val)const;
    friend std::ostream& operator<<(std::ostream& os, 
                                    const SimpleVecList& vec);
};

class RandomElem: public std::list<SimpleElem>
{
private:
    u8x32 *data;
public:
    RandomElem(int Nelem,int size, int Nmax);
    ~RandomElem(){std::free(data);}
    const u8x32* get_data(int i)const{return data+i;}
};

const int Hsize=1024*1024;
class DataTest {
private:
   int Lsize;
   std::bitset<Hsize> booldata[Vsize][8];
public:
    DataTest(const SimpleVecList& v);
    bool check(const SimpleElem& val)const;
};

#endif /* mydata.h */
