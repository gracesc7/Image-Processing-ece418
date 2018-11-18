/*===
lab7-part3-skeleton.cc

Abstract: Skeleton for part three of lab seven (histogram equalization)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// verify arguments' correctness
	if (argc != 3)
	{
		cerr << "Useage: " << argv[0]
		     << " input.png output.png" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);

	// set up the histogram
	vector<int> histogram (256, 0);
	cout<<"hisss"<< histogram[23,0]<<endl;

	int range;
	range = 256/256;
	int bin_idx;
	// calculate the image's histogram
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			bin_idx = int(image.Pixel(x,y)/(double)range);
			histogram[bin_idx] += 1;
			/*===

			Insert Lab 7 Part 3 Code Here - fill in the histogram

			===*/
		}
	}

	// calculate the cumulative distribution function from the histogram
	vector<int> cDistFunction (256, 0);

	for(int i =  0; i < 256; i++){
		if(i==0){
			cDistFunction[0] = histogram[0];
		}
		else{
		cDistFunction[i] = cDistFunction[i-1]+histogram[i];
	}
	}

	/*===

	Insert Lab 7 Part 3 Code Here - Compute the cumulative distribution
	function

	===*/

	// apply the cumulative distribution function
	/*===

	Insert Lab 7 Part 3 Code Here - Apply the cumulative distribution
	function to equalize the image's histogram.  You can then use part two
	to compute the equalized image's histogram.

	===*/

	//histogram equalization:
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			int val = image.Pixel(x,y);
			//cout<<"cc"<<cDistFunction[val]<<endl;
			//cout<<"dd" <<int((cDistFunction[val] - 1)/double((image.Width()*image.Height())) * 255)<<endl;
			image.Pixel(x,y) = int((cDistFunction[val] - 1)/double(image.Width()*image.Height()) * 255);
			//cout<<image.Pixel(x,y)<<endl;
		}
	}

	// save the image
	image.SavePng (argv[2]);


	//compute the histogram for the image after histogram equalization

	vector<int> histogram2 (256, 0);
	histogram2.resize(256);

	int range2;
	range2 = 256/256;
	int bin_idx2;
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			bin_idx2 = int(image.Pixel(x,y)/(double)range2);
			histogram2[bin_idx2] += 1;
			/*===

			Insert Lab 7 Part 2 Code Here -- fill in the histogram

			===*/
		}
	}
	ofstream out ("histogram_256bins_part3.txt");
	if (out.fail () )
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	for (int i = 0; i < histogram2.size (); i++)
	{
		out << histogram2[i] << endl;
		cout<<histogram2[i]<<endl;
	}
	out.close ();


	return 0;
}
