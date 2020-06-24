
#ifndef PART1_MATRIXOPERATIONS_H
#define PART1_MATRIXOPERATIONS_H


#include "Transpose.h"

//Helper functions:

        //AddHelper
//Declaration
template<int,int,int,typename,typename>
struct AddHelper;

template<int I,int J,int WIDTH,typename LeftMatrix,typename RightMatrix>
struct AddHelper{//      LeftMatrix[I,J] + RightMatrix[I,J]


    //ListSet params: index , Int< a[i,j]+a[i,j] > , i row of LeftMatrix
    typedef typename ListSet<J ,Int<  ListGet< J, typename ListGet< I,LeftMatrix >::value >::value::value
                                      + ListGet<J, typename ListGet<I,RightMatrix>::value>::value::value  >
                                     ,typename ListGet< I,LeftMatrix >::value >::list goodRow;
    typedef typename ListSet<I,goodRow,LeftMatrix>::list mat;
    typedef typename AddHelper<I,J-1,WIDTH,mat,RightMatrix>::result result;
};


template<int I,int WIDTH,typename LeftMatrix,typename RightMatrix>
struct AddHelper<I,0,WIDTH,LeftMatrix,RightMatrix>{//      LeftMatrix[I,0] + RightMatrix[I,0]

    typedef typename ListSet<0,Int<ListGet<0, typename ListGet<I,LeftMatrix>::value>::value::value + ListGet<0, typename ListGet<I,RightMatrix>::value>::value::value>,typename ListGet<I,LeftMatrix>::value>::list goodRow;
    typedef typename ListSet<I,goodRow,LeftMatrix>::list tempMatrix;
    typedef typename AddHelper<I-1,WIDTH,WIDTH,tempMatrix,RightMatrix>::result result;
};

//Stop condition- Reached 0,0
template<int WIDTH,typename LeftMatrix,typename RightMatrix>
struct AddHelper<0,0,WIDTH,LeftMatrix,RightMatrix>{
    typedef typename ListSet<0,Int<ListGet<0, typename ListGet<0,LeftMatrix>::value>::value::value + ListGet<0, typename ListGet<0,RightMatrix>::value>::value::value>,typename ListGet<0,LeftMatrix>::value>::list goodRow;
    typedef typename ListSet<0,goodRow,LeftMatrix>::list result;
};




//Functions:

                                //Add

//Declaration
template<typename,typename>
struct Add;
//Implementation
template<typename LeftMatrix,typename RightMatrix>
struct Add{
    constexpr static int matrix1height= LeftMatrix::size;
    constexpr static int matrix2height= RightMatrix::size;
    static_assert(matrix1height == matrix2height,"No match- height");
    constexpr static int matrix1width= LeftMatrix::head::size;
    constexpr static int matrix2width= RightMatrix::head::size;
    static_assert(matrix1width == matrix2width,"No match- width");

    typedef typename AddHelper<matrix1height-1,matrix1width-1,matrix1width-1,LeftMatrix,RightMatrix>::result result;
};

//param1: vector 1*n =A , parm2: vector 1*n = B^T ,for example List< Int<1>, Int<2>, Int<0> is vector1
//Result : A*B 1*1 MATRIX an integer
template<typename,typename  >
struct VectorDotVector;

template<  >
struct VectorDotVector<List<> , List<> >{
    constexpr static int scalar = 0;
};

template<typename  T1, typename ...TT1,typename  T2, typename ...TT2>
struct VectorDotVector< List<T1,TT1...>, List<T2,TT2...> >{
    constexpr static int  scalar =   ( (T1::value)* (T2::value) + VectorDotVector < List<TT1...> , List<TT2...> > ::scalar ) ;
};

//Result: 1*m vector A * B   , a List<Int<c_1> , Int <c_2> , .... ,Int <c_m> >
//Param1: vector 1*n = A (not a list of list, but one list ) , param2: B^T  (B - n*m Transpose) -lists of lists!!!

template<typename,typename  >
struct RowDotMat ;



template<typename  T1, typename ...TT1>
struct RowDotMat< List<T1,TT1...>, List<> >{
   typedef List<> vector;
};


template<typename  T1, typename ...TT1,typename  T2, typename ...TT2>
struct RowDotMat< List<T1,TT1...>, List<T2,TT2...> >{
    typedef typename  PrependList < Int< VectorDotVector < List<T1,TT1...> , T2 >::scalar >,
            typename RowDotMat< List<T1,TT1...> ,  List<TT2...> >::vector > ::list vector;
};


template<typename,typename  >
struct MultiplyHelper;


template<typename  T2, typename ...TT2>
struct MultiplyHelper< List<>, List<T2,TT2...> >{
    typedef  List<> matrix;
};

template<typename  T1, typename ...TT1,typename  T2, typename ...TT2>
struct MultiplyHelper< List<T1,TT1...>, List<T2,TT2...> >{
    typedef  typename MultiplyHelper< List<TT1...>,List<T2,TT2...> >::matrix tail_mat;
    typedef  typename RowDotMat< T1, List<T2,TT2...> >::vector  vec;

    typedef typename PrependList < vec,tail_mat >::list matrix;

};


template<typename,typename>
struct Multiply;


template<typename LeftMatrix,typename RightMatrix>
struct Multiply {
    constexpr static int matrix1col= LeftMatrix::head::size;
    constexpr static int matrix2row= RightMatrix::size;
    static_assert(matrix1col == matrix2row,"No match- height");
    typedef typename MultiplyHelper <LeftMatrix, typename Transpose<RightMatrix>::matrix >::matrix result;
};




#endif //PART1_MATRIXOPERATIONS_H