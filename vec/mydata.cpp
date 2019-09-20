#include "mydata.h"
#include <random>
// #include <omp.h>

/* Important note: operators < and > are used for sorting:
 * If first differing byte smaller value of operator < is true
 * Operator <= isn't < or == 
 * It means that all bytes have values <= 
 */

bool SimpleElem::operator<(const SimpleElem& v)const {
    for(size_t i=0;i<size;++i){
        if(data[0][i]<v.data[0][i]) return true;
        if(data[0][i]>v.data[0][i]) return false;
        }
    return false;
}

bool SimpleElem::operator>(const SimpleElem& v)const {
    for(size_t i=0;i<size;++i){
        if(data[0][i]>v.data[0][i]) return true;
        if(data[0][i]<v.data[0][i]) return false;
        }
    return false;
}
bool SimpleElem::operator>(const u8x32& v)const {
    for(size_t i=0;i<size;++i){
        if(data[0][i]>v[i]) return true;
        if(data[0][i]<v[i]) return false;
        }
    return false;
}

/*
bool Elem::operator>(const Elem& v)const {
    ulli64x4 l1=(ulli64x4)data[0];
    ulli64x4 l2=(ulli64x4)v.data[0];
    for(size_t i=0;i<4;++i){
        if(l1[i]>l2[i]) return true;
        if(l1[i]<l2[i]) return false;
        }
    return false;
}
*/

/*

*/

#ifdef __AVX2__
bool SimpleElem::operator<=(const SimpleElem& v)const {
    __m256i cvec=(__m256i)(data[0]<=v.data[0]);
    int cbool=_mm256_movemask_epi8(cvec);
    return cbool==-1;
}

bool SimpleElem::operator<=(const u8x32& v)const {
    __m256i cvec=(__m256i)(data[0]<=v);
    int cbool=_mm256_movemask_epi8(cvec);
    return cbool==-1;
}

bool SimpleElem::operator==(const SimpleElem& v)const {
    __m256i cvec=(__m256i)(data[0]==v.data[0]);
    int cbool=_mm256_movemask_epi8(cvec);
    return cbool==-1;
}

bool SimpleElem::operator!=(const SimpleElem& v)const {
    __m256i cvec=(__m256i)(data[0]==v.data[0]);
    int cbool=_mm256_movemask_epi8(cvec);
    return cbool!=-1;
}

#else
bool SimpleElem::operator<=(const SimpleElem& v)const {
    for(size_t i=0;i<size;++i)
        if(data[0][i]>v.data[0][i]) return false;
    return true;
}

bool SimpleElem::operator<=(const u8x32& v)const {
    for(size_t i=0;i<size;++i)
        if(data[0][i]>v[i]) return false;
    return true;
}

bool SimpleElem::operator==(const SimpleElem& v)const {
    for(size_t i=0;i<size;++i)
        if(data[0][i]!=v.data[0][i]) return false;
    return true;
}

bool SimpleElem::operator!=(const SimpleElem& v)const {
    for(size_t i=0;i<size;++i)
        if(data[0][i]!=v.data[0][i]) return true;
    return false;
}
#endif

SimpleVecList& SimpleVecList::simplify(){
//    sort(std::greater<Elem>());
//    unique();
    if(size()>=1){
        SimpleVecList::iterator i=begin();
        ++i;
        while(i!=end()){
            for(SimpleVecList::iterator j=begin();j!=i;++j){
                if((*i)<=(*j)){
                    erase(i++);
                    goto inext;
                }
            }
            ++i;
            inext: ;
        }
    }
    return *this;
}



VecList& VecList::simplify(){
//    sort(std::greater<Elem>());
//    unique();
    if(size()>=1){
        VecList::iterator i=begin();
        ++i;
        while(i!=end()){
            for(VecList::iterator j=begin();j!=i;++j){
                if((*i)<=(*j)){
                    erase(i++);
                    goto inext;
                }
            }
            ++i;
            inext: ;
        }
    }
    return *this;
}

std::istream& read_elem(std::istream& in, Elem& val){
    std::string line;
    // Find header
    do {
        if(!std::getline(in, line)) return in;
    }
    while(line.find("[ELB ")!=0);
    std::string header(line);
    if(!std::getline(in, line)) return in;
    // copy line to a vector
    std::vector<Eltype> temp_vec;
    std::istringstream buf(line.substr(4,line.length()-5));
    unsigned short n;
    while(buf>>n){
        temp_vec.push_back(n);
    }
    // Fill str
    std::vector<std::string> str;
    do {
        if(!std::getline(in, line)) return in;
        str.push_back(line);
    }
    while(line.length()>=1);
       
    // copy the vector to the valarray
    u8x32 elbuf;
    val = Elem(&(temp_vec[0]), temp_vec.size(),&elbuf,header,str);
//   std::cout<<temp_vec.size()<<' ';
//    std::cout<<val<<'\n';
    return in;
};

std::ostream& operator<<(std::ostream& os, const Elem& v){
    os<<v.suppl.get_header()<<'\n';
    os<<"[SV ";
    for(size_t i=0;i<v.size;++i)
        os<<short(v.data[0][i])<<' ';
    os<<"]\n";
    
    for(size_t i=0;i<v.suppl.get_str().size();++i)
        os<<v.suppl.get_str()[i]<<'\n';
        
    return os;
}

std::ostream& operator<<(std::ostream& os, const SimpleElem& v){
    os<<"[SV ";
    for(size_t i=0;i<v.size;++i)
        os<<short(v.data[0][i])<<' ';
    os<<"]\n";
        
    return os;
}

std::ostream& operator<<(std::ostream& os, const ElemPoint& v){
    os<<v.suppl->get_header()<<'\n';
    os<<"[SV ";
    for(size_t i=0;i<v.size;++i)
        os<<short(v.data[0][i])<<' ';
    os<<"]\n";
    
    for(size_t i=0;i<v.suppl->get_str().size();++i)
        os<<v.suppl->get_str()[i]<<'\n';
        
    return os;
}

std::ostream& operator<<(std::ostream& os, const VecList& vec){
    for(VecList::const_iterator i=vec.begin();i!=vec.end();++i)
        os<<*i;
    return os;
}

std::ostream& operator<<(std::ostream& os, const SimpleVecList& vec){
    for(SimpleVecList::const_iterator i=vec.begin();i!=vec.end();++i)
        os<<*i;
    return os;
}



std::istream& read_veclist(std::istream& in, VecList& vec){
    u8x32 val;
    Elem elem;
    elem.set_ref(&val);
    
    while(read_elem(in, elem)){
        vec.push_back(elem);
    }
    return in;
}

void VecList::push_back(const Elem& val){
    u8x32 v=val.get_data();
    data[cursize]=v;
    std::list<Elem>::push_back(val);
    back().set_ref(data+cursize);
    if(++cursize>=allocsize) repack();
}

void VecList::repack(){
// reallocate new space for data and clean unused data
    u8x32 *newdata;
    allocsize=size()+1000000;
    newdata=(u8x32*)std::aligned_alloc(Align,
                    sizeof(Eltype)*Vsize*allocsize);
    int j=0;
    for(iterator i=begin();i!=end();++i,++j){
       newdata[j]=i->get_data();
       i->set_ref(newdata+j); 
    }
    std::free(data);
    data=newdata;
}

VecList::iterator VecList::insert(const_iterator pos, const Elem& val){
    u8x32 v=val.get_data();
    data[cursize]=v;
    iterator p=std::list<Elem>::insert(pos,val);
    p->set_ref(data+cursize);
    if(++cursize>=allocsize)repack();
    return p;
}

void VecList::merge_unique(VecList& v){
    iterator start=begin();
    for(iterator i=v.begin();i!=v.end();++i){
        iterator pos=std::lower_bound(start,end(),*i,
                            std::greater<Elem>());
        if(pos==end()){
            start=insert(pos,*i);
        }
        else {
            start=pos;
            if(*i!=*pos){
                insert(pos,*i);
            }
        }
    }
    // clean v list
    v.clear();
}

RandomElem::RandomElem(int Nelem,int size,int Nmax){
    u8x32 *buf;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,Nmax);
    
    data=(u8x32*)std::aligned_alloc(Align,
                    sizeof(Eltype)*Vsize*Nelem);
    insert(end(),Nelem,SimpleElem());
    auto pos=begin();
    for(int i=0;i<Nelem;++i,++pos){
        pos->set_size(size);
        pos->set_ref(data+i);
        for(int j=0;j<size;++j){
            data[i][j]=distribution(generator);
        }
    }
}

SimpleVecList::SimpleVecList(int nlist,VecList* vec){
    int Nelem=0;
    for(int i=0;i<nlist;++i){Nelem+=vec[i].size();}
    insert(end(),Nelem,ElemPoint());
    data=(u8x32*)std::aligned_alloc(Align,
                    sizeof(Eltype)*Vsize*Nelem);
                    
    iterator pos=begin();
    u8x32* curpos=data;
    for(int i=0;i<nlist;++i){
        for(VecList::const_iterator j=vec[i].begin();
                j!=vec[i].end();++j){
            *curpos=j->get_data();
            pos->set_size(j->get_size());
            pos->set_ref(curpos);
            pos->set_suppl(j->get_suppl());
            ++pos;
            ++curpos;
        }
    }
}

void SimpleVecList::repack(){
    sort(std::greater<ElemPoint>());
    unique();
    u8x32 *newdata;
    newdata=(u8x32*)std::aligned_alloc(Align,
                    sizeof(Eltype)*Vsize*size());
    int j=0;
    for(iterator i=begin();i!=end();++i,++j){
       newdata[j]=i->get_data();
       i->set_ref(newdata+j); 
    }
    std::free(data);
    data=newdata;
}

DataTest::DataTest(const SimpleVecList& v):
            Lsize(v.begin()->get_size()){
    
    for(int i=0;i<Lsize;++i){
        for(int j=1;j<9;++j){
            auto pos=v.begin();
            for(int k=0;k<v.size();++k,++pos){
                if(pos->get_data()[i]>=(Eltype)j){
                    booldata[i][j-1].set(k);
                }
            }
        }
    }
}

bool DataTest::check(const SimpleElem& val)const{
    auto bvec=std::move(std::bitset<Hsize>{}.set()); // All 1
    for(int i=0;i<Lsize;++i){
        int j=val.get_data()[i];
        if(j>0){
            bvec&=booldata[i][j-1];
        }
    }
    return !bvec.any();
}
/*
bool SimpleVecList::check(const SimpleElem& val)const{
    for(auto pos=begin();pos!=end();++pos){
        if(val<=*pos)return false;
        if(val>*pos){
//            std::cout<<val<<(const SimpleElem&)*pos<<std::endl;
            return true;
        }
    }
    return true;
}
*/
bool SimpleVecList::check(const SimpleElem& val)const{
    u8x32* v=data;
    for(int i=0;i<size();++i,++v){
        if(val<=*v)return false;
        if(val>*v){
//            std::cout<<val<<(const SimpleElem&)*pos<<std::endl;
            return true;
        }
    }
    return true;
}
