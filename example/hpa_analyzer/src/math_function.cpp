#include "math_function.h"
using std::cerr;


/*
1. median function definition
*/
double math_fun::median_score(vector<double> scores)
{
	/*
  double median;
  size_t size = scores.size();

  sort(scores.begin(), scores.end());

  if (size  % 2 == 0)
  {
      median = (scores[size / 2 - 1] + scores[size / 2]) / 2;
  }
  else 
  {
      median = scores[size / 2];
  }
  */


	//linear time vector version (C++ O(n) implementation)
	double median;
	size_t size = scores.size();
	vector<double>::iterator first = scores.begin();
	vector<double>::iterator last = scores.end();

	if (size % 2 ==0)
	{
		//A. Get upper median
		vector<double>::iterator middle = first + (last - first) / 2;
		std::nth_element(first,middle,last); // can specify comparator as optional 4th argument
		median=*middle;
		//B. Get lower median
		middle=first+(last-first)/2-1;
		std::nth_element(first,middle,last);
		median+=*middle;
		//C. Average
		median=median/2;
	}
	else
	{
		//A. Get upper median
		vector<double>::iterator middle = first + (last - first) / 2;
		std::nth_element(first,middle,last);
		median=*middle;
	}

	 return median;
}



/*
2. Return 1 where there are local maxima in x
Remark: Don't include the first point, maybe last one
P.S. Inherited from (2005-04-19 dpwe@ee.columbia.edu) and modified (slightly) by the author, used it carefully.
*/
bool math_fun::localmax(double *x, bool* output, const size_t N)
{

	//Loop and return the local maximum
	output[0]=false;
	output[N-1]=false;

	for (size_t i=1;i<N-1;i++)
	{
		if (x[i]>x[i-1] && x[i]>=x[i+1])
			output[i]=true;
		else
			output[i]=false;
	}
	return true;
}


/*
3.Reverse a list (will modified the original list)
*/
void math_fun::reverse(double *const x, const size_t N)
{
	//Check parameters 
	if (!x || N<1)
	{
		cerr<<"Error in function reverse (math_function.cpp): the input size is 0.\n";
	}


	//Get the half length
	size_t halff;
	if (N %2)
		halff=N/2;
	else
		halff=(N-1)/2;

	double tempValue;
	for (size_t i=0;i<halff;i++)
	{
		tempValue=x[i];
		x[i]=x[N-i-1];
		x[N-i-1]=tempValue;
	}
}

/*
4. Filter function (MATLAB version)
%   Y = FILTER(B,A,X) filters the data in vector X with the
%   filter described by vectors A and B to create the filtered
%   data Y.  The filter is a "Direct Form II Transposed"
%   implementation of the standard difference equation:
%
%   a(1)*y(n) = b(1)*x(n) + b(2)*x(n-1) + ... + b(nb+1)*x(n-nb)
%                         - a(2)*y(n-1) - ... - a(na+1)*y(n-na)
%
%   If a(1) is not equal to 1, FILTER normalizes the filter
%   coefficients by a(1). 
*/
void math_fun::filter(double const *b, const size_t Nb, double const *a, const size_t Na, double const *x, const size_t N, double *const y)
{
	//Check the parameters
	if (!b || !a || Nb<1 || Na<1)
		cerr<<"Error in function filter (math_function.cpp): parameter errors!\n";
	if (!x || !y || N<1)
		cerr<<"Error in function filter (math_function.cpp): input/output errors!\n";


	//Initialization
	y[0]=b[0]*x[0];
	bool switch_flag_a=true;
	bool switch_flag_b=true;
	
	if (Nb>2)
		switch_flag_b=false;
	if (Na>2)
		switch_flag_a=false;

	for (size_t i=1;i<N;i++)
	{
		y[i]=0.0;

		//Update B
		if (switch_flag_b)
		{
			for (size_t j=0;j<Nb;j++)
				y[i]+=b[j]*x[i-j];
		}
		else
		{
			if (i>=Nb-1)
				switch_flag_b=true;
			for (size_t j=0;j<i+1;j++)
				y[i]+=b[j]*x[i-j];	
		}

		//Update A
		if (switch_flag_a)
		{
			for (size_t j=1;j<Na;j++)
			{
				y[i]-=a[j]*y[i-j];
			}
		}
		else
		{
			if (i>=Na-1)
				switch_flag_a=true;
			for (size_t j=1;j<i+1;j++)
				y[i]-=a[j]*y[i-j];
		}
	}

	if (a[0]!=1.0)
	{
		//Normalized by a[0]
		for (size_t i=0;i<N;i++)
			y[i]=y[i]/a[0];
	}

}



/*
5.1 In house median function (partition)
based on: Partition-based general selection algorithm
see http://en.wikipedia.org/wiki/Selection_algorithm#Linear_general_selection_algorithm_-_.22Median_of_Medians_algorithm.22
*/
size_t math_fun::partition(double *const list, const size_t left, const size_t right, const size_t pivotIndex)
{
	double pivotValue=list[pivotIndex];
	double tempValue;
	
	//1. Move pivot to end
	list[pivotIndex]=list[right];
	list[right]=pivotValue;

	//2. storeIndex
	size_t storeIndex = left;
	for (size_t i=left;i<right;i++)
	{
		if (list[i]<=pivotValue)
		{
			//Swap list[i] to storeIndex such that before storeIndex all values > pivotValue
			tempValue=list[i];
			list[i]=list[storeIndex];
			list[storeIndex]=tempValue;
			storeIndex++;
		}
	}
	
	//3. Finally Move the pivot value to its final place
	tempValue=list[right];
	list[right]=list[storeIndex];
	list[storeIndex]=tempValue;

	//Return the store index (this means, the pivot value is in this index)
	return storeIndex;
}


/*
5.2 In house median function (selection, in place)
based on: Partition-based general selection algorithm
see http://en.wikipedia.org/wiki/Selection_algorithm#Linear_general_selection_algorithm_-_.22Median_of_Medians_algorithm.22

INPUTS:
list - the list of the data
left - the left bound of the data (start from 0)
right - the right bound of the data (list[right] is the last value)
k - the index (e.g. the median) of the list
maxRound - the maximum iteration (for stopping the in place function)
*/
double math_fun::selection(double *const list, size_t left, size_t right, size_t k, const size_t maxRound)
{

	//If obvious
	if (left==right)
		return list[left];

	//1. Parameters
	size_t pivotIndex=left+k; //search starts from k
	size_t pivotNewIndex=k;
	size_t pivotDist=k;

	//2. Main loop
	for (size_t r=0;r<maxRound;r++)
	{
		pivotIndex=(left+right)/2; //pivotIndex is always middle of the list
		pivotNewIndex=partition(list,left,right,pivotIndex);
		pivotDist=pivotNewIndex-left+1;
		if (pivotDist==k)
			return list[pivotNewIndex];
		else if(k<pivotDist) //If the pivot value is < k-th point, then search the left side
			right=pivotNewIndex-1;
		else
		{
			k-=pivotDist;    //k is now the index in the right block
			left=pivotNewIndex+1;
		}

	}

	return negInf; //Return null
}


/*
5.3 In house median function (median)
based on: Partition-based general selection algorithm
see http://en.wikipedia.org/wiki/Selection_algorithm#Linear_general_selection_algorithm_-_.22Median_of_Medians_algorithm.22

INPUTS:
list - the list of the data
left - the left bound of the data (start from 0)
right - the right bound of the data (list[right] is the last value)
maxRound - the maximum iteration (for stopping the in place function)

REMARK: if N is even then return (list[median]+list[median-1])/2;
*/
double math_fun::median(double *const list, size_t left, size_t right, const size_t maxRound)
{
	size_t N=right-left+1;
	double median_value=0.0;

	if (N%2 ==0)
	{
		size_t median_index=N/2;
		//The upper median value
		median_value=selection(list,left,right,median_index,maxRound);
		median_index++;
		median_value+=selection(list,left,right,median_index,maxRound);
		median_value/=2.0;

	}
	else
	{
		size_t median_index = (N+1)/2;
		median_value=selection(list,left,right,median_index,maxRound);
	}

	return median_value;
}


/*
6. Function:
decimal to fraction
See: http://homepage.smc.edu/kennedy_john/DEC2FRAC.PDF
*/
vector<double> math_fun::dec2frac(const double org_x, const double tol)
{
	size_t Nmax=100; //The maximum iteration is 100
	double *fracInt = new double[Nmax];
	size_t count=0;
	double x=org_x;

	//1. Forward inverse integer
	for (size_t i=0;i<Nmax;i++)
	{
		x=1.0/x;
		fracInt[i]=floor(x);
		x=x-fracInt[i];

		if (x<tol)
		{
			count=i;
			break;
		}
		else if ((1.0-x)<tol)
		{
			count=i;
			fracInt[i]++;
			break;
		}
	}

	//2. Reconstruct the number
	vector<double> output(2,0.0);
	if (count==0)
	{
		output[0]=1;
		output[1]=floor(1/org_x);
	}
	else if (count==1)
	{
		output[0]=fracInt[1];
		output[1]=floor(output[0]/org_x);
	}
	else
	{
		double N1=1.0;
		double N2=fracInt[1];
		double N;
		for (size_t i=2;i<=count;i++)
		{
			N=fracInt[i]*N2+N1;
			N1=N2;
			N2=N;
		}
		output[0]=N;
		output[1]=floor(N/org_x);
	}

	//3. Output
	delete[] fracInt;
	return output;

}







