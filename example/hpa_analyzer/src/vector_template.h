/* Ver 0.9
=======================================================================================================================
The vector/matrix operations library. Including the templates of:
1. Matrix class
2. min/max operation
3. median function (on a vector)
4. 
=======================================================================================================================
*/

//prevent multiple inclusions of head file
#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <vector>        //the vector operator
#include <limits>
#include <complex>
using std::vector;
using std::numeric_limits;


#ifndef posInf
	#define posInf numeric_limits<double>::infinity()
#endif


#ifndef negInf
	#define negInf -numeric_limits<double>::infinity()
#endif



template < class T>
class matrix {
public:
   matrix(int i, int j) {matrix_t= vector<vector<T> >(i,j);};
   T get(int i,int j) {return matrix_t[i][j];};
   void set(int i,int j, T val) {matrix_t[i][j]=val;};
   
   vector<T> getColumn (int j)
   {
	   int row_num=getSize_row();
	   vector<T> columnVec(row_num);
	   for (int i=0;i<row_num;i++)
	   {columnVec[i]=matrix_t[i][j];}
	   return columnVec;
   };
   vector<T> getRow(int i)
   {
	   int col_num=getSize_column();
	   vector<T> rowVec(col_num);
	   for (int j=0;j<col_num;j++)
	   {rowVec[j]=matrix_t[i][j];}
	   return rowVec;
   };
   
   int getSize_row()
   {return matrix_t.size();};
   
   int getSize_column()
   {
	   if (matrix_t.size()==0)
		return 0;
	else
		return matrix_t[0].size();
   };

private:
	vector<vector<T> > matrix_t;
};



/*************************************************************************************
-----------------------------------EVIL SEPARATION LINE--------------------------------
**************************************************************************************/

/*
TIP: How to define a template class in a .h file and implement it in a .cpp file.
To compile this class without any errors, you need to put the template specific declaration in a .cpp file, as shown in the max class
*/


template <class T>
class max{
public:
	//A. max function on two values
	static T max_two( const T a, const T b) {return (a<b)?b:a;};

	//B. max function on vector
	static vector<double> max_list(T *const dataVector, const int N);
};

//2. min function definition
template <class T>
class min{
public:
	//A. min function on two values
	static T min_two( const T a, const T b) {return (a<b)?a:b;};

	//B. min function on vector
	static vector<double> min_list(T *const dataVector, const int N);
};


#endif
