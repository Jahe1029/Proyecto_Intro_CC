#include <cmath>
#include <iostream>
#include <string>
#include <vector>

//librería para matemática de vectores
#include "inc/vector_math.h"

double G = 6.6743e-11;

class cuerpo {

public:
	std::vector<double> pos;
	std::vector<double> v;
	std::vector<double> a;
	double m;
	std::string filename;

	//member initialization list
	cuerpo(std::string name, double posx, double posy, double posz,
			double vx, double vy, double vz, double mass) :
		pos{posx, posy, posz},
		v{vx, vy, vz},
		a{0, 0,0},
		m(mass)
	{}

	cuerpo(){
		//alocación de memoria al ser llamada por el constructor de sistema para evitar el uso de .pusback() o crear un std::vector innecesario
		pos.reserve(3);
		v.reserve(3);
		a.reserve(3);
		filename.reserve(4);
		// m = 0.0;
	}

	std::vector<double> gravitational_force(const cuerpo &C){
		//r2 - r1
		std::vector<double> resta = pos - C.pos;

		// |r2 - r1|³
		double sq_distance = std::pow(sum(resta * resta), 2);

		// -G*m_2*(r2 - r1)
		std::vector<double> force = (-1*G*C.m)*resta;

		return  force;
	}





	//print to stdout
	void print(){
		std::cout << "\n" << filename << "\nmass: " << m << "\npos\tv\ta\n";
		for(int i = 0; i < 3; i++){
			std::cout << pos[i] << "\t" << v[i] << "\t" << a[i] << "\n";
		}

	}
	
	// cuerpo() = default;
	// cuerpo(cuerpo &&) = default;
	// cuerpo(const cuerpo &) = default;
	// cuerpo &operator=(cuerpo &&) = default;
	// cuerpo &operator=(const cuerpo &) = default;
	// ~cuerpo();
	//
private:
	
};


class sistema {
public:
	//std::vector para el uso de .reserve() y allocar memoria al crear una instancia de sistema
	std::vector<cuerpo> sis;


	int N;
	//constructor de vector con N cuerpos reservados en memoria
	//TODO assign N
	sistema(int GG){sis.reserve(GG); N = GG;}

	void add_body(std::string name, double x, double y, double z, double vx, double vy, double vz, double mass){
		// cuerpo c = 
		sis.push_back(cuerpo(name, x, y, z, vx, vy, vz, mass));
	}

	std::vector<double> total_acceleration(double h, int index){

		std::vector<double> a = {0.0, 0.0, 0.0};
			std::cout <<  "N: "<< N << "\tindex: " << index << "\n\nparcial acc\n";
			print(a);

			for(int i = 0; i < N; i++){
				if(i == index){i++;}
				else{

					double x; double y; double z;
					double vx; double vy; double vz;
					// double ax += sis[i].sis[2];
					a = a + sis[index].gravitational_force(sis[i]);
					std::cout << "\n\nparcial acc\n";

					print(a);
				}
			}


			std::cout << "Mass: " << sis[index].m << "\n";
		return a/sis[index].m;
	}

	void print_s(){
		for (cuerpo x : sis){
			x.print();
		}
	}
	// sistema(sistema &&) = default;
	// sistema(const sistema &) = default;
	// sistema &operator=(sistema &&) = default;
	// sistema &operator=(const sistema &) = default;
	// ~sistema();

private:
	
};



// cuerpo::cuerpo() {
// }
//
// cuerpo::~cuerpo() {
// }

int main (int argc, char *argv[]) {

	// std::cout << "hello";
	sistema test(3);
	test.add_body("venus", -1, 1, 0, 2, 2, 2, 33.0);
	test.add_body("marte", 4, 1, 0, 6, 6, 6, 4343.0);
	test.add_body("tierra", 3, 1, 0, 6, 6, 6, 43.0);

	auto v = test.total_acceleration(1.0, 2);
	std::cout << "\n\ntotal\n";
	print(v);
	// test.print();
	return 0;
}
