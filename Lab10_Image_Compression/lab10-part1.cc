/*===
lab10-part1-solution.cc

Abstract: Skeleton for part one of lab ten (entropy calculation)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
using namespace std;

// calculate the log base 2 of a number, using the conventation that log2(0)=0
double log2 (double x)
{
	if (x == 0) return 0;
	return log (x) / (log (2.0) );
}

// main routine
int main (int argc, char* argv[])
{
	// verify arguments' correctness
	if (argc != 3)
	{
		cerr << "Useage: " << argv[0]
		     << " input.png histogram.txt" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);

	// create the normalized (sum of elements is one) histogram for image
	vector<double> histogram (256, 0.0);
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			histogram[image.Pixel (x, y)] += 1.0;
		}
	}


	// calculate and print the entropy of the histogram
	double entropy = 0;
	for (int i = 0; i < histogram.size (); i++){
			histogram[i] = histogram[i]/(image.Width()*image.Height());
			entropy += histogram[i] * log2(histogram[i]);
	}

	double total_bits;
	total_bits = (entropy) * image.Width() * image.Height();
	/*===

	Insert Lab 10 Part 1 Code Here
		-don't forget to normalize the histogram (so its elements sum
		 to one)

	===*/
	cout << "Entropy = " << entropy << endl;
	cout << "Total bits = "<< total_bits <<endl;

	// print the histogram the specified file
	ofstream out (argv[2]);
	if (out.fail () )
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	for (int i = 0; i < histogram.size (); i++)
	{
		out << histogram[i] << endl;
	}
	out.close ();

	return 0;
}
