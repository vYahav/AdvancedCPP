
#ifndef PART1_UTILITIES_H
#define PART1_UTILITIES_H






                        // -= List =-
//Declaration
template<typename...>
struct List;

//Empty
template<>
struct List<>{
    constexpr static int size = 0;
};

//Non-empty
template<typename T,typename... TT>
struct List<T,TT...>{
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = 1 + sizeof...(TT);
};

                        // -= Prepend =-
//Declaration
template<typename,typename...>
struct PrependList;

//Empty
template<typename T>
struct PrependList<T,List<>>{
    typedef List<T> list;
};
//Non-Empty
template<typename T1,typename T2,typename... TT>
struct PrependList<T1,List<T2,TT...>>{
    typedef List<T1,T2,TT...> list;
};

                        // -= Int =-
//Declaration
template<int>
struct Int;

//Implementation
template<int N>
struct Int{
    constexpr static int value = N;
};

                        // -= Get =-
//Declaration
template<int,typename>
struct ListGet;

//Stop condition
template<typename T,typename... TT>
struct ListGet<0,List<T,TT...>>{
    typedef T value;
};

//Get the value of index N using recursion
template<int N,typename T,typename... TT>
struct ListGet<N,List<T,TT...>>{
    typedef typename ListGet<N-1, List<TT...>>::value value;
};


                        // -= Set =-
//Declaration
template<int,typename,typename>
struct ListSet;

//Set the value of index N using recursion
template<int N,typename S,typename T,typename... TT>
struct ListSet<N,S,List<T,TT...>>{
    typedef typename PrependList<T,typename ListSet<N-1,S,List<TT...>>::list>::list list;
};
//Stop condition- Reached the wanted index
template<typename S,typename T,typename... TT>
struct ListSet<0,S,List<T,TT...>>{
    typedef typename PrependList<S,List<TT...>>::list list;
};

//Stop condition- No more list to concat
template<typename S>
struct ListSet<0,S,List<>>{
    typedef typename PrependList<S,List<>>::list list;
};

#endif //PART1_UTILITIES_H