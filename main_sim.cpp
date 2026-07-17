#include <cmath>
#include <iostream>
#include <string>
#include <vector>

//librería para matemática de vectores
#include "inc/vector_math.h"

double G = 6.6743e-11;

class cuerpo {

public:
	//posición
	std::vector<double> pos;
	
	//vector de posición temporal, necesario para guardar el resultado de aplicar RK4 pero no modificar la posición antes de calcular la aceleración del resto de cuerpos del sistema
	std::vector<double> next_pos;
	
	//velocidad
	std::vector<double> v;
	
	//vector de velocidad temporal, necesario por las mismas razones que el de posición temporal
	std::vector<double> next_v;

	//aceleración
	std::vector<double> a;
	
	//masa
	double m;

	//nombre del planeta, este será el nombre del archivo en donde se guarden sus posiciones
	std::string filename;

	//member initialization list
	cuerpo(std::string name, double posx, double posy, double posz,
			double vx, double vy, double vz, double mass) :

		pos{posx, posy, posz},
		next_pos{posx, posy, posz},
		v{vx, vy, vz},
		next_v{vx, vy, vz},
		a{0, 0,0},
		m(mass)
	{}

	cuerpo(){
		//alocación de memoria al ser llamada por el constructor de sistema para evitar el uso de .pusback() o crear un std::vector innecesario
		next_pos.reserve(3);
		pos.reserve(3);
		v.reserve(3);
		next_v.reserve(3);
		a.reserve(3);
		filename.reserve(8);
		// m = 0.0;
	}

	std::vector<double> gravitational_force(const cuerpo &C){
		//r2 - r1
		std::vector<double> resta = next_pos - C.pos;

		// |r2 - r1|³
		double sq_distance = std::pow(sum(resta * resta), 2);

		// -G*m_2*(r2 - r1)
		std::vector<double> force = (-1.0*G*C.m)*resta;

		return  force;
	}


	void update_v_and_pos(){
		pos = next_pos;
		v = next_v;
	}


	//print to stdout
	void print(){
		std::cout << "\n" << filename << "\nmass: " << m << "\npos\tv\ta\ttp\ttv\n";
		for(int i = 0; i < 3; i++){
			std::cout << pos[i] << "\t" << v[i] << "\t" << a[i]  << "\t" << next_pos[i] << "\t" << next_v[i] << "\n";
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
	sistema(int size){sis.reserve(size); N = size;}

	void add_body(std::string name, double x, double y, double z, double vx, double vy, double vz, double mass){
		// cuerpo c = 
		sis.push_back(cuerpo(name, x, y, z, vx, vy, vz, mass));
	}

	std::vector<double> total_acceleration(int index){
		//función para calcular la aceleración total que experimenta un cuerpo específico del sistema por la fuerza gravitacional del resto de cuerpos del sistema

		std::vector<double> a = {0.0, 0.0, 0.0};
			// std::cout <<  "N: "<< N << "\tindex: " << index << "\n\nparcial acc\n";
			// print(a);

			for(int i = 0; i < N; i++){
				if(i == index){i++;}
				else{

					double x; double y; double z;
					double vx; double vy; double vz;
					// double ax += sis[i].sis[2];
					a = a + sis[index].gravitational_force(sis[i]);
					// std::cout << "\n\nparcial acc\n";

					// print(a);
				}
			}


			// std::cout << "Mass: " << sis[index].m << "\n";
		return a/sis[index].m;
	}
	void RK4(double h){
		for(int i = 0; i < sis.size(); i++){
			//k1
			// k1 = (v_i, a), la aceleración será calculada mientras que la velocidad será la inicial
			std::vector<double> k1_a = this->total_acceleration(i); 


			

			//k2
			//posición temporal que será guardada en el miembro next_pos del cuerpo
			std::vector<double> &temp_pos = sis[i].next_pos;
			//r = r + k1_v*(h/2))
			temp_pos = temp_pos + sis[i].v*(h/2.0);
			std::vector<double> k2_a = this->total_acceleration(i);
			std::vector<double> k2_v = sis[i].v + k1_a*(h/2.0);
			
			//k3
			temp_pos = sis[i].pos + k2_v*(h/2.0);
			std::vector<double> k3_a = this->total_acceleration(i);
			std::vector<double> k3_v = sis[i].v + k2_a*(h/2.0);

			//k3
			temp_pos = sis[i].pos + k3_v*h;
			std::vector<double> k4_a = this->total_acceleration(i);
			std::vector<double> k4_v = sis[i].v + k2_a*h;

			//velocidad temporal que será guardada en el miembro next_v del cuerpo
			std::vector<double> &temp_v = sis[i].next_v;
			// auto p = (h/6.0)*(k1_a + 2.0*k2_a + 2.0*k3_a + k4_a); std::cout << "\n\nP:\n"; print(p); std::cout << "\n\nfin_p\n\n";
			

			temp_v = temp_v + (h/6.0)*(k1_a + 2.0*k2_a + 2.0*k3_a + k4_a);
			temp_pos = temp_pos + (h/6.0)*(sis[i].v + 2.0*k2_v + 2.0*k3_v + k4_v);

			}
	}
	void update(){
		sis[0].update_v_and_pos();
	}
	void run_sim(int N_times, double h){
	// std::cout << "\n1\n";
		for(int i = 0; i < N_times; i++){
	// std::cout << "\n2";
			std::cout << "\ni: " << i;
	// std::cout << "\n3";
			this->RK4(h);
	// std::cout << "\n4";
			for(int j = 0; j < N; j++){
	// std::cout << "\n5";
	// std::cout << "\n6";
				sis[j].update_v_and_pos();
	// std::cout << "\n7";
			}
	// std::cout << "\n8";
			this->print_s();
	// std::cout << "\n9";
		}
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
	test.add_body("venus", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 33333.0);
	test.add_body("marte", 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 40.0);
	test.add_body("tierra", -4.0, -5.0, 0.0, 0.0, 0.0, 0.0, 500.0);
	test.print_s();
	// test.RK4(1.0);
	// test.print_s();
	// test.update();	
	// test.print_s();
	test.run_sim(50, 1.0);
	test.print_s();
	// auto v = test.total_acceleration(2);
	// std::cout << "\n\ntotal\n";
	// print(v);
	return 0;
}
