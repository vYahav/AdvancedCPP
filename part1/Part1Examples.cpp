#include <iostream>
#include "MatrixOperations.h"

int main() {

    typedef List<
            List< Int<1>, Int<2> >,
            List< Int<4>, Int<5> >,
            List< Int<7>, Int<8> >,
            List< Int<7>, Int<8> >
    > matrix_4on2;

    typedef List<
            List< Int<1>, Int<2>, Int<0> >,
            List< Int<0>, Int<1>, Int<0> >,
            List< Int<0>, Int<0>, Int<5> >
    > matrix3on3_1;

    typedef List<
            List< Int<7>, Int<6>, Int<0> >,
            List< Int<0>, Int<7>, Int<0> >,
            List< Int<8>, Int<0>, Int<3> >
    > matrix3on3_2;

    typedef List<
            List< Int<1>, Int<2>, Int<3> >,
            List< Int<4>, Int<5>, Int<6> >,
            List< Int<7>, Int<8>, Int<9> >
    > matrix3on3_3;

    typedef List<
            List< Int<1>, Int<2> >,
            List< Int<0>, Int<1> >
    > mat2on2_1;

    typedef List<
            List< Int<0>, Int<7> >,
            List< Int<8>, Int<0> >
    > mat2on2_2;

    typedef List< List< Int<1> > > matrix1on1_1;
    typedef List<List< Int<7> > > matrix1on1_2;

    typedef  List< List< Int<1>, Int<2>, Int<1> > >  vector1on3_1;
    typedef  List <List< Int<7>, Int<6>, Int<1> >  > vector1on3_2;

    typedef  List< Int<1> >  vector1on1_1;
    typedef  List< Int<-7> >  vector1on1_2;

    typedef List < List< Int<-7> ,  Int<6> ,Int<1>  ,Int<2> > > vector1on4;

    //List
    typedef List<Int<1>, Int<2>, Int<3>> list1;
	static_assert(list1::head::value == 1, "Failed"); // = Int<1>
	typedef typename list1::next list1Tail; // = List<Int<2>, Int<3>>
	static_assert(list1::size == 3, "Failed"); // = 3
	static_assert(list1Tail::size == 2, "Failed"); // = 2
    static_assert(list1Tail::head::value == 2, "Failed");
    typedef typename list1Tail::next list1Tail2; //  Int<3>>
    static_assert(list1Tail2::size == 1, "Failed");
    static_assert(list1Tail2::head::value == 3, "Failed");
    typedef typename list1Tail2::next list1Tail3; //  Int<3>>
    static_assert(list1Tail3::size == 0, "Failed");


    //Prepend
	typedef List<Int<1>, Int<2>> list2;
	typedef typename PrependList<Int<4>, list2>::list newList2; // = List< Int<4>, Int<1>, Int<2>, Int<3>>
	static_assert(newList2::head::value == 4, "Failed");
    typedef typename newList2::next list1Tail4;
    static_assert(list1Tail4::head::value == 1, "Failed");
    typedef typename list1Tail4::next list1Tail5;
    static_assert(list1Tail5::head::value == 2, "Failed");
    typedef typename PrependList<Int<4>, list1Tail5>::list newList3;
    static_assert(newList3::head::value == 4, "Failed");
    typedef typename newList3::next list1Tail5;
    static_assert(list1Tail5::head::value == 2, "Failed");

    typedef List<> empty;
    typedef typename PrependList<Int<4>, empty>::list newList4;
    static_assert(newList4::head::value == 4, "Failed");

    //ListGet
    typedef List<Int<1>, Int<2>, Int<3>> list3;
    static_assert(ListGet<0, list3>::value::value == 1, "Failed");
    static_assert(ListGet<1, list3>::value::value == 2, "Failed");
    static_assert(ListGet<2, list3>::value::value == 3, "Failed");

    typedef List<Int<1>> list5;
    static_assert(ListGet<0, list5>::value::value == 1, "Failed");

    //ListSet
    typedef List<Int<1>, Int<2>> list6;
    typedef typename ListSet<0, Int<3>, list6>::list listA;
    static_assert(ListGet<0, listA>::value::value == 3, "Failed");

    typedef typename ListSet<1, Int<3>, list6>::list listA3;
    static_assert(ListGet<1, listA3>::value::value == 3, "Failed");



    typedef List<> list7;


    //ADD


    typedef typename Add<matrix3on3_1, matrix3on3_2>::result matrix31; // = List<
                                                               //			List< Int<8>, Int<8>, Int<0> >,
                                                               //			List< Int<0>, Int<8>, Int<0> >,
                                                               //			List< Int<8>, Int<0>, Int<8> >

    //first row
    static_assert(matrix31::head::head::value == 8, "Failed");
    static_assert(ListGet<1,matrix31::head>::value::value == 8, "Failed");
    static_assert(ListGet<2,matrix31::head>::value::value == 0, "Failed");
    //second row
    typedef  typename  ListGet<1,matrix31>::value second_row;
    static_assert(ListGet<0,second_row >::value::value == 0, "Failed");
    static_assert(ListGet<1,second_row >::value::value == 8, "Failed");
    static_assert(ListGet<2,second_row >::value::value == 0, "Failed");
    //third row
    typedef  typename  ListGet<2,matrix31>::value third_row;
    static_assert(ListGet<0,third_row >::value::value == 8, "Failed");
    static_assert(ListGet<1,third_row >::value::value == 0, "Failed");
    static_assert(ListGet<2,third_row >::value::value == 8, "Failed");


    typedef typename Add<matrix_4on2, matrix_4on2>::result matrix32; // = List<


    //first row
    static_assert(matrix32::head::head::value == 2, "Failed");
    static_assert(ListGet<1,matrix32::head>::value::value == 4, "Failed");
    //second row
    typedef  typename  ListGet<1,matrix32>::value second_row2;
    static_assert(ListGet<0,second_row2 >::value::value == 8, "Failed");
    static_assert(ListGet<1,second_row2 >::value::value == 10, "Failed");
    //third row
    typedef  typename  ListGet<2,matrix32>::value third_row3;
    static_assert(ListGet<0,third_row3 >::value::value == 14, "Failed");
    static_assert(ListGet<1,third_row3 >::value::value == 16, "Failed");
//fourth row
    typedef  typename  ListGet<3,matrix32>::value furth_row4;
    static_assert(ListGet<0,furth_row4 >::value::value == 14, "Failed");
    static_assert(ListGet<1,furth_row4 >::value::value == 16, "Failed");

    //add scalar matrix
    typedef typename Add< matrix1on1_1,  matrix1on1_2  >::result matrix12;// List < List<Int<8> > >
    static_assert(matrix12::head::head::value == 8, "Failed");

//MUL
    //vector dot vector
   typedef  typename  Multiply  <vector1on3_1,typename Transpose<vector1on3_2>::matrix>::result res1;
    static_assert( res1::head::head::value == 20, "Failed");

    //scalar matrix
    typedef  typename  Multiply  <matrix1on1_1,matrix1on1_2>::result res2;
    static_assert( res2::head::head::value == 7, "Failed");


    //vector dot matrix


    typedef  typename  Multiply  <vector1on3_1,  matrix3on3_2>::result res3;
    typedef typename res3::head row;
    static_assert(ListGet<0,row >::value::value == 15, "Failed");
    static_assert(ListGet<1,row >::value::value == 20, "Failed");
    static_assert(ListGet<2,row >::value::value == 3, "Failed");


    typedef  typename  Multiply  <vector1on4,  matrix_4on2>::result res4;
    typedef typename res4::head row2;
    static_assert(ListGet<0,row2 >::value::value == 38, "Failed");
    static_assert(ListGet<1,row2 >::value::value == 40, "Failed");


  //mat dot mat


    typedef typename Multiply<mat2on2_1, mat2on2_2>::result res5;
    typedef  typename  ListGet<0,res5>::value first_row5;
    static_assert(ListGet<0,first_row5 >::value::value == 16, "Failed");
    static_assert(ListGet<1,first_row5 >::value::value == 7, "Failed");
    typedef  typename  ListGet<1,res5>::value second_row5;
    static_assert(ListGet<0,second_row5 >::value::value == 8, "Failed");
    static_assert(ListGet<1,second_row5 >::value::value == 0, "Failed");


    typedef typename Multiply<matrix3on3_3, matrix3on3_3>::result res6;
    typedef  typename  ListGet<0,res6>::value first_row6;
    static_assert(ListGet<0,first_row6 >::value::value == 30, "Failed");
    static_assert(ListGet<1,first_row6 >::value::value == 36, "Failed");
    static_assert(ListGet<2,first_row6 >::value::value == 42, "Failed");
    typedef  typename  ListGet<1,res6>::value second_row6;
    static_assert(ListGet<0,second_row6 >::value::value == 66, "Failed");
    static_assert(ListGet<1,second_row6 >::value::value == 81, "Failed");
    static_assert(ListGet<2,second_row6 >::value::value == 96, "Failed");
    typedef  typename  ListGet<2,res6>::value third_row6;
    static_assert(ListGet<0,third_row6 >::value::value == 102, "Failed");
    static_assert(ListGet<1,third_row6 >::value::value == 126, "Failed");
    static_assert(ListGet<2,third_row6 >::value::value == 150, "Failed");

    typedef typename Multiply<matrix3on3_3, res6>::result res7;
    typedef  typename  ListGet<0,res7>::value first_row7;
    static_assert(ListGet<0,first_row7 >::value::value == 468, "Failed");
    static_assert(ListGet<1,first_row7 >::value::value == 576, "Failed");
    static_assert(ListGet<2,first_row7 >::value::value == 684, "Failed");
    typedef  typename  ListGet<1,res7>::value second_row7;
    static_assert(ListGet<0,second_row7 >::value::value == 1062, "Failed");
    static_assert(ListGet<1,second_row7 >::value::value == 1305, "Failed");
    static_assert(ListGet<2,second_row7 >::value::value == 1548, "Failed");
    typedef  typename  ListGet<2,res7>::value third_row7;
    static_assert(ListGet<0,third_row7 >::value::value == 1656, "Failed");
    static_assert(ListGet<1,third_row7 >::value::value == 2034, "Failed");
    static_assert(ListGet<2,third_row7 >::value::value == 2412, "Failed");


    typedef typename Multiply<typename Transpose<matrix_4on2>::matrix, matrix_4on2>::result res9;
    typedef  typename  ListGet<0,res9>::value first_row9;
    static_assert(ListGet<0,first_row9 >::value::value == 115, "Failed");
    static_assert(ListGet<1,first_row9 >::value::value == 134, "Failed");
    typedef  typename  ListGet<1,res9>::value second_row9;
    static_assert(ListGet<0,second_row9 >::value::value == 134, "Failed");
    static_assert(ListGet<1,second_row9 >::value::value == 157, "Failed");
    std::cout << "Passed part1" << std::endl;//*/
}