/*===
lab10-part2-solution.cc

Abstract: Skeleton for part two of lab ten (run length coding)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
using namespace std;

// calculate the log base 2 of a number
double log2 (double x);

// snake raster scan function -- updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y);

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
	int totalPixels = image.Width () * image.Height ();

	// create the normalized (sum of elements is one) histogram for the run lengths
	vector<double> runLengthHistogram (totalPixels + 1, 0);

	double current_pixel = image.Pixel(0,0);
	int current_len = 0;
	int total_run = 1;
	// traverse the image in raster-snake order
	for (int x = 0, y = 0; SnakePixel (image, x, y); )
	{
		if(image.Pixel(x,y) == current_pixel){
			current_len += 1;
		}
		else{
			runLengthHistogram[current_len] += 1;
			current_len = 1;
			total_run += 1;
		}
		current_pixel = image.Pixel(x,y);
		//THE ORDER OF X, Y PIXEL

		/*===

		Insert Lab 10 Part 2 Code Here
			-you will probably need to insert some code before this
			 to calculate run length histogram (initialize current
			 run length, current run's pixel value, etc).
			-don't forget to include last run in the calculation
			 and normalize your histogram (so its elements sum to
			 one).

		===*/
	}


	// calculate and print the entropy of the histogram
	double entropy = 0;
	for (int i = 0; i < runLengthHistogram.size (); i++)
	{
		runLengthHistogram[i] = runLengthHistogram[i]/total_run;
		entropy += runLengthHistogram[i] * log2(runLengthHistogram[i]);
		/*===

		Insert Lab 10 Part 2 Code Here

		===*/
	}
	entropy = -entropy;
	double total_bits = entropy * total_run;
	double avg_bits = total_bits/(image.Width() * image.Height());
	cout << "total number of runs is "<<total_run <<"."<<endl;
	cout << "total bits is "<<total_bits << "." << endl;
	cout << "average bits per pixel is "<<avg_bits << "." << endl;
	cout << "Run-Length Entropy is " << entropy << "." << endl;
	// print other requested data

	// print the histogram the specified file (only as many entries as are nonzero)
	ofstream out (argv[2]);
	if (out.fail () )
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	int maxNonZeroIndex = 0;
	for (int i = 0; i < runLengthHistogram.size (); i++)
	{
		if (runLengthHistogram[i] != 0) {
			maxNonZeroIndex = i;
		}
	}
	for (int i = 0, pixels = 0; i <= maxNonZeroIndex; i++)
	{
		out << runLengthHistogram[i] << endl;
	}
	out.close ();

	return 0;
}

// calculate the log base 2 of a number
double log2 (double x)
{
	if (x == 0) return 0;
	return log (x) / (log (2.0) );
}

// snake raster scan function -- updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y)
{
	if (y % 2 == 0)
	{
		x++;
		if (x == image.Width () )
		{
			x--;
			y++;
		}
	}
	else
	{
		x--;
		if (x == -1)
		{
			x++;
			y++;
		}
	}
	return (y < image.Height () );
}
