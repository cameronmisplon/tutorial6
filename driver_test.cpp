#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

class nd_vector_t {
private:
	vector<double> data;
public:
	//Define the big six:
	nd_vector_t(const initializer_list<double> &lst) : data(lst.size()) { //1A, allows 'nd_vector a = { 1.0, 2.0, 3.0 };' syntax
		copy(lst.begin(), lst.end(), data.begin() );
	}
	nd_vector_t(const size_t dim = 0) : data(dim) {} //1B basic constructor
	virtual ~nd_vector_t() = default; //2
	nd_vector_t(const nd_vector_t & rhs) = default; //3
	nd_vector_t & operator=(const nd_vector_t & rhs) = default; //4
	nd_vector_t(nd_vector_t && rhs) : data(move(rhs.data)) {} //5
	nd_vector_t & nd_vector_t::operator=(nd_vector_t && rhs) {  //6
		if (this != &rhs) {
			this->data = move(rhs.data);
			return *this;
		}
	}
	nd_vector_t nd_vector_t::operator++ (int){
		nd_vector_t temp = *this;
		for (vector<double>:iterator i = data.begin(); i!= data.end(); ++i){
			*i = *i + 1.0;
		}
		return temp;
	}	
	nd_vector_t & nd_vector_t operator++ (void){
		for (vector<double>:iterator i = data.begin(); i!= data.end(); ++i){
			*i = *i + 1.0;
		}
		return *this;
	}
	nd_vector_t & nd_vector_t::operator+= (const double amount){
		for (vector<double>:iterator i = data.begin(); i!= data.end(); ++i){
			*i = *i + amount;
		}
		return *this;
	}
	nd_vector_t & nd_vector_t::operator+= (const nd_vector_t & rhs) {
		for (int i=0; i<(this->data).size(); ++i){
			(this->data)[i] = rhs.data[i]
		}
		return *this;
	}
	nd_vector_t & nd_vector_t::operator*= (const double multiple) {
		for (vector<double>:iterator i = data.begin(); i!= data.end(); ++i){
			*i = *i * multiple;
		}
		return *this;
	}
	nd_vector_t nd_vector_t::operator• (void) {
		nd_vector_t temp = *this;
		for (vector<double>:iterator i = temp.begin(); i!= temp.end(); ++i){
			*i = *i * -1;
		}
		return temp;
	}
	nd_vector_t nd_vector_t::operator+ (const double amount) const{
		nd_vector_t temp = *this;
		temp = temp+=amount;
		return temp;
	}
	nd_vector_t nd_vector_t::operator+ (const nd_vector_t rhs) const{
		nd_vector_t temp = *this;
		temp = temp+=rhs;
		return temp;
	}
	nd_vector_t nd_vector_t::operator* (const double multiple) const{
		nd_vector_t temp = *this;
		temp = temp*= multiple;
		return temp;
	}
	double & nd_vector_t::operator[] (int index) const{
		if (index >= (this->data).size() ){
			cout << "Index out of bounds" << endl;
			return (this->data)[0];
		}
		return (this->data)[index];
	}
	double & nd_vector_t::operator! (void) const{
		double magnitude = 0.0;
		for (vector<double>:iterator i = data.begin(); i!= data.end(); ++i){
			magnitude += ((*i) * (*i));
		}
		return sqrt(magnitude);
	}
	friend nd_vector_t & operator*(const double multiple, nd_vector_t rhs);
	friend ostream& operator<<(ostream& theStream, const nd_vector_t rhs);
	friend istream& operator>>(istream& theStream, const nd_vector_t rhs);
	
	vector<double> get_buffer() const {
		return data;
	}

	//TODO 1: implement each of the operators, see unit tests below (except for the last 3) here as member functions

	//TODO 2:implement scalar * nd_vector, << and >> here (as 'friend' operators)
};




/************************************************************************************************
	TODO:UNCOMMENT THE FOLLOWING UNIT TESTS BIT BY BIT AS YOU IMPLEMENT THE OPERATORS
*************************************************************************************************/

//tests whether two doubles are close to equal
bool is_close(const double a, const double b, const double epsilon=0.0000000000001) {
	return abs(a - b) < epsilon;
}
nd_vector_t operator*(const double multiple, nd_vector_t & rhs){
	nd_vector_t temp = rhs;
	for (vector<double>:iterator i = temp.begin(); i!= temp.end(); ++i){
		*i = *i * multiple;
	}
	return temp;
}
ostream& operator<<(ostream& theStream, const nd_vector_t & rhs){
	for (int i=0; i<rhs.data.size();++i){
		theStream << rhs.data[i] << " ";
	}
	return theStream;
}
istream& operator>>(istream& theStream, nd_vector_t & rhs){
	for (int i=0; i<rhs.data.size();++i){
		double temp;
		theStream >> temp;
		rhs.data[i] = temp;
	}
	return theStream;
}

//TODO 3: after completing the operators, uncomment the define /*const*/->const and see if all code compiles
#define CONST const
TEST_CASE("Postfix Increment", "[PostfixIncrement]") {
	nd_vector_t a = { 1.0, 2.0, 3.0 }; //1A constructor.	
	const auto b = a++;
	SECTION("RETURN VALUE") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 1.0));
		REQUIRE(is_close(buf[1], 2.0));
		REQUIRE(is_close(buf[2], 3.0));
	}
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 2.0));
		REQUIRE(is_close(buf[1], 3.0));
		REQUIRE(is_close(buf[2], 4.0));
	}
}
TEST_CASE("Prefix Increment", "[PrefixIncrement]") {
	nd_vector_t a = { 1.0, 2.0, 3.0 };	
	const auto b = ++a;
	SECTION("SELF a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 2.0));
		REQUIRE(is_close(buf[1], 3.0));
		REQUIRE(is_close(buf[2], 4.0));
	}
    SECTION("RETURN VALUE b") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 2.0));
		REQUIRE(is_close(buf[1], 3.0));
		REQUIRE(is_close(buf[2], 4.0));
	}
}
TEST_CASE("SCALAR ADDITION ASSIGNMENT", "[ScalarAdditionAssignment]") {
	nd_vector_t a = { 1.0, 2.0, 3.0 };	
	const auto b = a += 5.5;
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 6.5));
		REQUIRE(is_close(buf[1], 7.5));
		REQUIRE(is_close(buf[2], 8.5));
	}
	SECTION("POST CONDITION VEC b") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 6.5));
		REQUIRE(is_close(buf[1], 7.5));
		REQUIRE(is_close(buf[2], 8.5));
	}
}
TEST_CASE("VECTOR ADDITION ASSIGNMENT", "[VectorAdditionAssignment]") {
	nd_vector_t a = { 1.0, 2.0, 3.0 };
	CONST nd_vector b = { 2.0, 3.5, 4.0 };	
	const auto c = a += b;
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 3.0));
		REQUIRE(is_close(buf[1], 5.5));
		REQUIRE(is_close(buf[2], 7.0));
	}
	SECTION("POST CONDITION VEC b") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 2.0));
		REQUIRE(is_close(buf[1], 3.5));
		REQUIRE(is_close(buf[2], 4.0));

	}
	SECTION("POST CONDITION VEC c") {
		const auto buf = c.get_buffer();
		REQUIRE(is_close(buf[0], 3.0));
		REQUIRE(is_close(buf[1], 5.5));
		REQUIRE(is_close(buf[2], 7.0));
	
	}
}
TEST_CASE("SCALAR MULTIPLY ASSIGNMENT", "[ScalarMultiplyAssign]") {
	nd_vector_t a = { 1.0, 2.0, 3.0 };	
	const auto b = a *= 3.25;
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 1.0 * 3.25));
		REQUIRE(is_close(buf[1], 2.0 * 3.25));
		REQUIRE(is_close(buf[2], 3.0 * 3.25));
	}
	SECTION("POST CONDITION VEC b") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 1.0 * 3.25));
		REQUIRE(is_close(buf[1], 2.0 * 3.25));
		REQUIRE(is_close(buf[2], 3.0 * 3.25));
	}

}
TEST_CASE("VECTOR NEGATE", "[VectorNegate]") {
	CONST nd_vector_t a = {1.0, 2.0, 3.0};
	const auto b = -a;
	SECTION("RETURN VALUE") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 1.0));
		REQUIRE(is_close(buf[1], 2.0));
		REQUIRE(is_close(buf[2], 3.0));
	}
	SECTION("POST CONDITION VEC a") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], -1.0));
		REQUIRE(is_close(buf[1], -2.0));
		REQUIRE(is_close(buf[2], -3.0));

	}
}
TEST_CASE("SCALAR ADDITION", "[ScalarAddition]") {
	CONST nd_vector_t a = { 1.0, 2.0, 3.0 };	
	const auto b = a + 5.5;
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 1.0));
		REQUIRE(is_close(buf[1], 2.0));
		REQUIRE(is_close(buf[2], 3.0));
	}
	SECTION("POST CONDITION VEC b") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 6.5));
		REQUIRE(is_close(buf[1], 7.5));
		REQUIRE(is_close(buf[2], 8.5));
	}

}
TEST_CASE("VECTOR ADDITION", "[VectorAddition]") {
	CONST nd_vector_t a = { 1.0, 2.0, 3.0 };
	CONST nd_vector_t b = { 2.0, 3.5, 4.0 };	
	const auto c = a + b;
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 1.0));
		REQUIRE(is_close(buf[1], 2.0));
		REQUIRE(is_close(buf[2], 3.0));
	}
	SECTION("POST CONDITION VEC b") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 2.0));
		REQUIRE(is_close(buf[1], 3.5));
		REQUIRE(is_close(buf[2], 4.0));

	}
	SECTION("POST CONDITION VEC c") {
		const auto buf = c.get_buffer();
		REQUIRE(is_close(buf[0], 3.0));
		REQUIRE(is_close(buf[1], 5.5));
		REQUIRE(is_close(buf[2], 7.0));

	}

}
TEST_CASE("SCALAR MULTIPLY", "[ScalarMultiply]") {
	CONST nd_vector_t a = { 1.0, 2.0, 3.0 };	
	const auto b = a * 3.25;
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 1.0));
		REQUIRE(is_close(buf[1], 2.0));
		REQUIRE(is_close(buf[2], 3.0));
	
	}
	SECTION("RETURN VAL") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 1.0 * 3.25));
		REQUIRE(is_close(buf[1], 2.0 * 3.25));
		REQUIRE(is_close(buf[2], 3.0 * 3.25));
	}
}
TEST_CASE("INDEXING OPERATOR", "[IndexingOperator]") {
	CONST nd_vector_t a = { 1.0, 2.0, 3.0 };
	REQUIRE(is_close(a[0], 1.0));
	REQUIRE(is_close(a[1], 2.0));
	REQUIRE(is_close(a[2], 3.0));
 
    nd_vector b = { 1.0, 2.0, 3.0 };
	REQUIRE(is_close(b[0]+= 1.0), 2.0));
	REQUIRE(is_close(b[0]), 2.0));
}
TEST_CASE("MAGNITUDE OPERATOR", "[MagnitudeOperator]") {
	CONST nd_vector_t a = { 1.6, 0.4, 2.7, 4.8, 3.4 };
	const double mag = !a;
	SECTION("POST CONDITION VEC a") {
		REQUIRE(is_close(a[0], 1.6));
		REQUIRE(is_close(a[1], 0.4));
		REQUIRE(is_close(a[2], 2.7));
		REQUIRE(is_close(a[3], 4.8));
		REQUIRE(is_close(a[4], 3.4));
	}
	SECTION("RETURN VALUE") {
		REQUIRE(is_close(mag, 6.67907179, 0.00001)); //test accurate up to p=5
	}
}
TEST_CASE("SCALAR MULTIPLICATION WITH SCALAR FIRST", "[ScalarMultVecOperator]") {
	CONST nd_vector_t a = {1.0, 2.0, 3.0};	
	const auto b = 3.25 * a;
	SECTION("POST CONDITION VEC a") {
		const auto buf = a.get_buffer();
		REQUIRE(is_close(buf[0], 1.0));
		REQUIRE(is_close(buf[1], 2.0));
		REQUIRE(is_close(buf[2], 3.0));
	}
	SECTION("RETURN VAL") {
		const auto buf = b.get_buffer();
		REQUIRE(is_close(buf[0], 1.0 * 3.25));
		REQUIRE(is_close(buf[1], 2.0 * 3.25));
		REQUIRE(is_close(buf[2], 3.0 * 3.25));
	}

}
TEST_CASE("STREAM OPERATOR <<", "[StreamOp<<]") {
	nd_vector_t a = { 1.4, 5.2, 4.8, 2.95 };
	nd_vector_t b = { 6.23,4.12 };
	ostringstream serialized;
	serialized << a << " " << b;
	REQUIRE(serialized.str() == "1.4 5.2 4.8 2.95 6.23 4.12");
}
TEST_CASE("STREAM OPERATOR >>", "[StreamOp>>]") {
	nd_vector_t a;
	istringstream data("1.4 5.2 4.8 2.95");
	data >> a;
	REQUIRE(is_close(a[0], 1.4));
	REQUIRE(is_close(a[1], 5.2));
	REQUIRE(is_close(a[2], 4.8));
	REQUIRE(is_close(a[3], 2.95));
}
