#include "tsp.h"
#include <iostream>
#include <vector>
#include <limits>  // numeric_limits
#include <numeric> // accumulate
#include <fstream> // ifstream

void read( char const* filename, MAP& map, int& TotalCity )
{
    map.clear();
    std::ifstream in( filename, std::ifstream::in );
    if( !in.is_open() ) {
        std::cout << "problem reading " << filename << std::endl;
        return;
    }
    in >> TotalCity;
    for( int i = 0; i < TotalCity; ++i ) {
        std::vector<int> row;
        for( int j = 0; j < TotalCity; ++j ) {
            row.push_back( std::numeric_limits<int>::max() );
        }
        map.push_back( row );
    }
    for( int i = 0; i < TotalCity; ++i ) {
        for( int j = i + 1; j < TotalCity; ++j ) {
            if( !in.good() ) {
                std::cout << "problem reading " << filename << std::endl;
                return;
            }
            in >> map[i][j];
            map[j][i] = map[i][j];
        }
    }
}

bool check_legal( std::vector<int> const& sol, int const& num_cities ) 
{
    std::vector<int> visits( num_cities, 0 );

    for ( int const& i : sol ) {
        ++visits[i];
    }

    return sol.front() == 0 
        && sol.back() == 0
        && visits[0] == 2
        && std::accumulate( visits.begin()+1, visits.end(), 1, std::multiplies<int>() ) == 1;
}

void run( char const * filename ) {
    std::vector<int> sol = SolveTSP( filename );

    MAP map;
    int num_cities;
    // load & check
    read( filename, map, num_cities );

    int prev = 0;
    int total = 0;

    for( int i=1; i<num_cities+1; ++i ) {
        total += map[prev][sol[i]];
        prev=sol[i];
    }
    if ( check_legal( sol, num_cities ) ) {
        std::cout << total << '\n';
    } else {
        std::cout << "Path is illegal\n";
    }
}

void test0()  { run( "./src/map0"  ); }
void test1()  { run( "./src/map1"  ); }
void test2()  { run( "./src/map2"  ); }
void test3()  { run( "./src/map3"  ); }
void test4()  { run( "./src/map4"  ); }
void test5()  { run( "./src/map5"  ); }
void test6()  { run( "./src/map6"  ); }
void test7()  { run( "./src/map7"  ); }
void test8()  { run( "./src/map8"  ); }
void test9()  { run( "./src/map9"  ); }
void test10() { run( "./src/map10" ); }
void test11() { run( "./src/map11" ); }

void (*pTests[])() = { 
    test0,test1,test2,test3,test4,test5,
    test6,test7,test8,test9,test10,test11
}; 

#include <cstdio> // sscanf
int main(int argc, char ** argv)
{
    test0();
    //test1(); std::cout << "\n";
    //test2(); std::cout << "\n";
    //test3(); std::cout << "\n";
    //test4(); std::cout << "\n";
    //test5(); std::cout << "\n";
    //test6(); std::cout << "\n";
    //test7(); std::cout << "\n";
    //test8(); std::cout << "\n";
    //test9(); std::cout << "\n";
    //test10(); std::cout << "\n";
    //test11(); std::cout << "\n";
	/*if ( argc == 2 ) {
        int test = 0;
        std::sscanf(argv[1],"%i",&test);
        pTests[test]();
    }*/
    return 0;
}
