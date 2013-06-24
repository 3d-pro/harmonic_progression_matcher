
#include "vector_template.h"

/*
max function on a list
*/

template <class T> vector<double> max<T>::max_list(T *const dataVector, const int N)
{
	T maxValue=-numeric_limits<T>::infinity();
	int maxIndex=-1;
	for (int i=0;i<N;i++)
	{
		if (maxValue<dataVector[i])
		{
			maxValue=dataVector[i];
			maxIndex=i;
		}
	}

	vector<double> returnMax(2,0.0);
	returnMax[0]=(double)(maxValue);
	returnMax[1]=(double)(maxIndex);

	return returnMax;
}


/*
min function on a list
*/

template <class T> vector<double> min<T>::min_list(T *const dataVector, const int N)
{
	T minValue=numeric_limits<T>::infinity();
	int minIndex=-1;
	for (int i=0;i<N;i++)
	{
		if (minValue>dataVector[i])
		{
			minValue=dataVector[i];
			minIndex=i;
		}
	}

	vector<double> returnMin(2,0.0);
	returnMin[0]=(double)(minValue);
	returnMin[1]=(double)(minIndex);

	return returnMin;
}






/*
//Exponential of the complex number patch
complex exp(complex x)
{
	double re, im, factor;
	factor=exp(x.re());
	re=factor*cos(x.im());
	im=factor*sin(x.im());
	return complex(re,im);
}
*/