#include <iostream>
#include <vector>
#include <cassert>
#include "Stream.h"
#include <list>
template <typename T>
struct Cell {
    T value;

    explicit Cell(const T value) : value(value) {}

    bool operator==(const Cell<T>& other) const {
        return other.value == value;
    }


};

template <typename T>
bool compareValues(std::vector<T*> vPointer, std::vector<T> v) {
    for(int i = 0 ; i < vPointer.size() ; i++){
        if(*vPointer[i] != v[i]){
            return false;
        }
    }
    return true;
}

template <typename Container1 , typename Container2>
bool Compare(Container1& c1, Container2 c2) {
    auto  it1 = c1.begin();
    auto  it2 = c2.begin();
    for (; it1 != c1.end(); it1++,it2++){
        if(**it1!= **it2){
            return false;
        }
    }
    return true;
}


void TestOf(  vector<string*> empty_vec ,map<int,int*> empty_map ,
            map<int,int*> map1 ,map<int,string*> map_strings ,  vector<string*> vec_strings){

    list<string*> lst = Stream<string>::of(empty_vec).collect<std::list<string*>>();
    assert(lst.empty());
    Stream<int>::of(empty_map);
    Stream<int>::of(map1);
    Stream<string>::of( map_strings);
    Stream<string>::of( vec_strings);
    lst = Stream<string>::of(vec_strings).collect<std::list<string*>>();
    assert(lst.size() == 3);
   Compare(vec_strings,lst);
}


void TestFilter(vector<string*>& empty_vec , map<int,int*>& empty_map  ,  map<int,string*>& map_strings,
                vector<string*>& vec_strings, vector<string*> vec_strings_b_c ,vector<string*> vec_strings_c
                ,vector<string*> vec_strings_a_a_a){
    assert(Stream<string>::of(empty_vec).filter([](const string* str) { return *str != "d"; } )
                            .collect<std::list<string*>>().empty() )  ;
   Stream<int>::of(empty_map).filter([](const int* val) { return *val != 2; } );
    assert(Compare (vec_strings,
                   Stream<string>::of(vec_strings).filter([](const string* str) { return *str != "d"; } )
                    .collect<std::list<string*>>()  ) )  ;
    list<string*> lst ( Stream<string>::of(vec_strings).filter([](const string* str) { return *str != "a"; } )
            .collect<std::list<string*>>() ) ;
    assert(Compare (vec_strings_b_c, lst)  );
    list<string*> lst_c ( Stream<string>::of(lst).filter([](const string* str) { return *str != "b"; } )
                                .collect<std::list<string*>>() ) ;
    assert(Compare (vec_strings_c, lst_c)  );
    assert(Stream<string>::of(lst_c).filter([](const string* str) { return *str != "c"; } )
                   .collect<std::list<string*>>().empty() )  ;
    assert(Stream<string>::of(vec_strings_a_a_a).filter([](const string* str) { return *str != "a"; } )
                   .collect<std::list<string*>>().empty() )  ;
    //check lazy,should work because the lazy eval.
    int* a = nullptr;
    Stream<string>::of(vec_strings_a_a_a).filter([&a](const string* str) { *a = 3; return *str != "a"; } )  ;
    assert(Compare(vec_strings_c, Stream<string>::of(vec_strings).filter([](const string* str) { return *str != "a"; } )
            .filter([](const string* str) { return *str != "b"; } ).collect<std::list<string*>>() ) ) ;
}

void TestMap(vector<string*>& empty_vec , map<int,int*>& empty_map  ,  map<int,string*>& map_strings, vector<string*>& vec_strings, vector<string*>& vec_strings_b_c
        ,vector<string*> vec_strings_a_a_a,vector<int*> vec_int_0_1_2, int* x){


    Stream<string>::of(empty_vec).map<int>([x](const string* a) {  return x; });
    Stream<int>::of(empty_map).map<int>([x](const int* a) { return x; });
    int array[3]={0,1,2};
    int i = -1;
   list<int*> lst = Stream<string>::of(vec_strings).map<int>([&i,&array](const string* a) {i++;return (int*)(array+i); })
           .collect< std::list<int*> >();
    assert (Compare(vec_int_0_1_2 ,lst  ));

    //check lazy before map
    int* a = nullptr;
    Stream<string>::of(vec_strings_a_a_a).filter([&a](const string* str) { *a = 3; return *str != "a"; } )
            .map<int>([&a](const string* b) {return a; });
    //check lazy  aftter map
    Stream<string>::of(vec_strings_a_a_a).filter([](const string* str) { ; return *str != "a"; } )
            .map<int>([&a](const string* b) {*a=3;return (a); });
    int array2[3]={0,1,2};
     int j = 0;
    lst = Stream<string>::of(vec_strings).filter([](const string* str) { return *str != "a"; } )
            .map<int>([&j,&array2](const string* a) {j++;return (int*)(array2+j); }) // 1 2
            .filter([](const int* a) { return *a != 1; } ).collect< std::list<int*> >();
   *x =2;
    vector<int*> vec({x});
    assert(Compare(vec,lst));
}

void TesTDistinct(vector<string*>& empty_vec , map<int,int*>& empty_map  ,  map<int,string*>& map_strings,
                  vector<string*>& vec_strings, vector<string*>& vec_strings_b_c ,vector<string*>& vec_strings_c
        ,vector<string*> vec_strings_a_a_a,vector<int*>& vec_int_0_1_2 , vector<string*> vec_strings_a ){

    Stream<string>::of(empty_vec).distinct( [] (const string* s1 , const string* s2) {return true;} );
    Stream<int>::of(empty_map).distinct( [] (const int* s1 , const int* s2) {return true;} );
    assert(  Compare(vec_strings_a,
            Stream<string>::of(vec_strings_a_a_a).distinct( [] (const string* s1 , const string* s2) {return( *s1 == *s2);} ).collect< std::list<string*> >() ));

    assert(   Stream<string>::of(vec_strings_a_a_a).distinct( [] (const string* s1 , const string* s2) {return( *s1 == "b");} ).count() == 3  );
    int *a = nullptr;
    Stream<string>::of(vec_strings_a_a_a).distinct( [a] (const string* s1 , const string* s2) {*a = 3; return true;} );

}

void TestSorted(vector<string*>& empty_vec , map<int,int*>& empty_map  ,  map<int,string*>& map_strings,
                vector<string*>& vec_strings,vector<string*>& vec_strings_a_a_a,vector<int*>& vec_int_0_1_2, int* x , vector<string*>& vec_strings_a ,vector<string*>& vec_strings_c_b_a ){

    Stream<string>::of(empty_vec).sorted( [] (const string* s1 , const string* s2) {return true;} );
    Stream<int>::of(empty_map).sorted( [] (const int* s1 , const int* s2) {return true;} );
    assert(Compare(vec_strings,
                   Stream<string>::of(vec_strings_c_b_a).sorted( [] (const string* s1 , const string* s2)
                                                                   {return( *s1 < *s2);} ).collect< std::list<string*> >() ));

}

void TestForEach(vector<string*>& empty_vec , map<int,int*>& empty_map  ,  map<int,string*>& map_strings,
                 vector<string*>& vec_strings ,vector<string*> vec_strings_c
        ,vector<string*> vec_strings_a_a_a,vector<int*> vec_int_0_1_2, int* x , vector<string*> vec_strings_a ,vector<string*> vec_strings_c_b_a ){

    Stream<string>::of(empty_vec).forEach( [] (const string* s1 ) {;} );
    Stream<int>::of(empty_map).forEach( [] (const int* s1 ) {;} );
    vector<int*> vec;
   Stream<int>::of(vec_int_0_1_2).forEach( [&vec] (int* s) {vec.push_back(s);});
   assert( Compare(vec_int_0_1_2,vec) );
}

void TestReduce(){
    double array[4] = { 1, 2, 3,4};
    vector<double*> vector;
    for(int i = 0 ; i < 4; i++) {
        vector.push_back(array + i);
    }
    double initial = 2;
    //if it doesnt work, check the order of reduce.

   assert( (*Stream<double>::of(vector).reduce(&initial, [](const double * a, const double* b) { auto * c = new double; *c = *a / *b; return c; }) ) == (double)(4/3.0) );

}

void Mix(){
    double array[4] = { 1, 2, 3,4};
    double array2[4] = { 4,3, 1};
    vector<double*> vector2({array2,array2+1,array2+2});
    vector<double*> vector;

    for(int i = 0 ; i < 4; i++) {
        vector.push_back(array + i);
    }


    double initial = 2;
    assert ( Stream<double>::of(vector).filter([](const double* val) { return *val != 2; } ).distinct( [] (const double* s1 , const double * s2) {return true;} ).count() == 1 );
    assert ( Stream<double>::of(vector).filter([](const double* val) { return *val != 2; } ).distinct( [] (const double* s1 , const double * s2) {return *s1==*s2;} ).count() == 3 );
    assert ( Stream<double>::of(vector).filter([](const double* val) { return *val != 2; } ).distinct( [] (const double* s1 , const double * s2) {return *s1==*s2;} ).count() == 3 );
    assert (Compare(vector2  , Stream<double>::of(vector).filter([](const double* val) { return *val != 2; } ).sorted( [] (const double* s1 , const double * s2) {return *s1 >*s2;} ).collect< std::list<double*> >() ));

}
int main() {

    int array[10] = { 1, 2, 3, 2, 4, 6, 5, 7, 8, 9 };
    string strings[3] = { "a", "b", "c" };


    string strings_2[2] = {  "b", "c" };
    string strings_3[1] = {  "c" };
    string strings_4[3] = { "a", "a", "a" };
    string strings_5[1] = {"a"};
    string strings_6[3] = {"c","b","a"};
    vector<string*> vec_strings_c_b_a;
    vector<string*> vec_strings_a({strings_5});
    int array_0_1_2[3] = { 0,1,2};
    vector<int*> vec_int_0_1_2;
    vector<string*> vec_strings_a_a_a;
    vector<string*> vec_strings_c({strings_3+0});
    vector<string*> vec_strings_b_c( {( strings_2 + 0),strings_2+1 });
    map<int,string*> map_strings;
    vector<string*> vec_strings;

    for(int i = 0 ; i < 3; i++) {
        map_strings.insert({i, &strings[i]});
        vec_strings.push_back(strings + i);
        vec_strings_a_a_a.push_back(strings_4+i);
        vec_int_0_1_2.push_back(array_0_1_2+i);
        vec_strings_c_b_a.push_back(strings_6+i);
    }
    vector<int*> vec1;
    map<int,int*> empty_map;
    map<int,int*> map1;
    for(int i = 0 ; i < 10 ; i++) {
        map1.insert({i,&array[i]});
        vec1.push_back(array + i);
    }
    vector<string*> empty_vec;


  int x = 3;
    TestOf(empty_vec,empty_map,map1,map_strings,vec_strings);
   TestFilter(empty_vec,empty_map, map_strings ,vec_strings,vec_strings_b_c,vec_strings_c , vec_strings_a_a_a);
    TestMap(empty_vec,empty_map, map_strings ,vec_strings,vec_strings_b_c , vec_strings_a_a_a,vec_int_0_1_2 ,&x);
    TesTDistinct(empty_vec,empty_map, map_strings ,vec_strings,vec_strings_b_c,vec_strings_c , vec_strings_a_a_a,vec_int_0_1_2 , vec_strings_a);
    TestSorted(empty_vec,empty_map, map_strings ,vec_strings , vec_strings_a_a_a,vec_int_0_1_2 ,&x,vec_strings_a
               ,vec_strings_c_b_a);
    TestForEach(empty_vec,empty_map, map_strings ,vec_strings,vec_strings_c , vec_strings_a_a_a,vec_int_0_1_2 ,&x,vec_strings_a
            ,vec_strings_c_b_a);
    TestReduce();
    Mix();
    std::vector<int*> vector;
    for(int i = 0 ; i < 10 ; i++) vector.push_back(array + i);
    assert(Stream<int>::of(vector).filter([](const int* val) { return *val != 2; } ).count() == 8);
    assert(Stream<int>::of(vector).distinct().count() == 9);

    std::vector<int> other = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    assert(compareValues(Stream<int>::of(vector).distinct().sorted().collect<std::vector<int*>>(), other));

    assert(Stream<int>::of(vector).map<Cell<int>>([](const int* a) { return new Cell<int>(*a); }).distinct().count() == 9);

    int initial = 0;
    assert(*Stream<int>::of(vector).reduce(&initial, [](const int* a, const int* b) { auto * c = new int; *c = *a + *b; return c; }) == 47);
    cout<<"passed part2"<<endl;
    return 0;
}

