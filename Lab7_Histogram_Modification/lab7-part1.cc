/*===
lab7-part1-skeleton.cc

Abstract: Skeleton code for part one of lab seven (gamma correction)
===*/

#include <stdlib.h>
#include <iostream>
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

	// perform gamma point operation
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			cout<<image.Pixel(x,y)<< "   "<< double(image.Pixel(x,y)/double(255))<< endl;

			image.Pixel(x,y) = 255*(pow(double(image.Pixel(x,y)/double(255)),2.5));
		  //cout<<pow(image.Pixel(x,y),2.5) <<endl;

			/*===

			Insert Lab 7 Part 1 Code Here

			===*/

		}
	}

	// save the image to PNG format
	image.SavePng (argv[2]);

	return 0;
}
