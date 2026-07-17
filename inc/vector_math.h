#pragma once
#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::vector<T> operator+(const std::vector<T> &v1, const std::vector<T> &v2){
	std::vector<T> r(3);
	for (int i = 0; i < v1.size(); i++) {
		r[i] = v1[i] + v2[i];
	}
	return r;
}


// template<typename T>
// std::vector<T> power(const std::vector<T> &v, ){
// 	std::vector<T> r(3);
// 	for (int i = 0; i < v.size(); i++) {
// 		r[i] = v[i];
// 	}
// 	return r;
// }

template<typename T>
std::vector<T> operator-(const std::vector<T> &v1, const std::vector<T> &v2){
	std::vector<T> r(3);
	for (int i = 0; i < v1.size(); i++) {
		r[i] = v1[i] - v2[i];
	}
	return r;
}

template<typename T>
std::vector<T> operator*(const T N, const std::vector<T> &v){
	std::vector<T> r(3);
	for (int i = 0; i < v.size(); i++) {
		r[i] = N * v[i];
	}
	return r;
}

template<typename T>
std::vector<T> operator*(const std::vector<T> &v, const T N){
	std::vector<T> r(3);
	for (int i = 0; i < v.size(); i++) {
		r[i] = N * v[i];
	}
	return r;
}


template<typename T>
std::vector<T> operator/(const T N, const std::vector<T> &v){
	std::vector<T> r(3);
	for (int i = 0; i < v.size(); i++) {
		r[i] = N / v[i];
	}
	return r;
}

template<typename T>
std::vector<T> operator/(const std::vector<T> &v, const T N){
	std::vector<T> r(3);
	for (int i = 0; i < v.size(); i++) {
		r[i] = v[i]/N;
	}
	return r;
}

template<typename T>
std::vector<T> operator*(const std::vector<T> &v1, const std::vector<T> &v2){
	std::vector<T> r(3);
	for (int i = 0; i < v1.size(); i++) {
		r[i] = v1[i] * v2[i];
	}
	return r;
}

template<typename T>
std::vector<T> operator/(const std::vector<T> &v1, const std::vector<T> &v2){
	std::vector<T> r(3);
	for (int i = 0; i < v1.size(); i++) {
		r[i] = v1[i] / v2[i];
	}
	return r;
}


template<typename T>
double sum(const std::vector<T> &v1){
	//returns the sum of all elements in a vector
	double r = 0;
	for (int i = 0; i < v1.size(); i++) {
		r += v1[i];
	}
	return r;
}
template<typename T>
void print(const std::vector<T> &v){
	for (int i = 0; i < v.size(); i++) {
		std::cout << "\t" << v[i];
	}
	std::cout << std::endl;
}


