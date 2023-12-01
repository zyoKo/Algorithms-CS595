#include "e-dijkstra-solver.h"
#include <iostream>
#include <iomanip>

#include <string>
#include <map> 

void test0() { std::cout << e_dijkstra_solver( "./src/in0" ) << std::endl; }
void test1() { std::cout << e_dijkstra_solver( "./src/in1" ) << std::endl; }
void test2() { std::cout << e_dijkstra_solver( "./src/in2" ) << std::endl; }
void test3() { std::cout << e_dijkstra_solver( "./src/in3" ) << std::endl; }
void test4() { std::cout << e_dijkstra_solver( "./src/in4" ) << std::endl; }
void test5() { std::cout << e_dijkstra_solver( "./src/in5" ) << std::endl; }
void test6() { std::cout << e_dijkstra_solver( "./src/in6" ) << std::endl; }
void test7() { std::cout << e_dijkstra_solver( "./src/in7" ) << std::endl; }

void (*pTests[])( ) = { 
    test0,test1,test2,test3,test4,
    test5,test6,test7
}; 

int main()
{
    test0();

	return 0;
}

//#include <cstdio> // sscanf
//int main(int argc, char ** argv) {
//    if ( argc == 2 ) {
//        int test = 0;
//        std::sscanf(argv[1],"%i",&test);
//        pTests[test]();
//    }
//    return 0;
//}
