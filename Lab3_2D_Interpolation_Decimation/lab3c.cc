/*===
lab3-skeleton.cc

Abstract: Skeleton for Lab 3 parts (a), (b), and (c)
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "imagefft.h"
using namespace std;

int main (int argc, char* argv[])
{
	cout<< "Success1" <<endl;
	// check parameters' correctness [for parts (a) and (b) -- this needs to be changed for (c)]
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	// read the top row and left column that will be used [remove this for part (c)]
	//int topLeftRow = atoi(argv[3]);
	//int topLeftColumn = atoi(argv[4]);
	/*
	cout<< argv[6] <<endl;
	int deci;
	if (argv[6]== char(2)){
		cout<< "Success000" <<endl;
		deci = 2;
		cout<< "Success00" <<endl;
	}

	else if (argv[6] ==char(8)){
		deci = 8;
	}
	*/
	// load the input image
	int deci = 2;
	int flag = 1;
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);

	ComplexFFTImage smallImage;
	smallImage.Resize (512/deci, 512/deci);

	ComplexFFTImage outputImage;
	outputImage.Resize (512, 512);

	ComplexFFTImage differenceImage;
	differenceImage.Resize (512, 512);
/*
	int flag;
	if(argv[5] ==char(1)){
		flag = 1;
	}
	else if (argv[5]== char(2)){
		flag = 2;
	}

	*/
	double m,M;

	if(flag ==0){
	// initialize the output interpolated image


	Complex pix;
	for (int i = 0; i< 512/deci; i++){
		for (int j =0; j<512/deci; j++){
			pix = inputImage.Pixel(deci*i, deci*j);
			smallImage.Pixel(i,j)= pix;
		}
	}

	cout<< "Success2" <<endl;
	//restore:
	for ( int i = 0; i< 512/deci; i++){
		for(int j = 0; j< 512/deci; j++){
			pix = smallImage.Pixel(i,j);
			outputImage.Pixel(deci*i, deci*j)= pix;
		}
	}
	//First interpolate linearly along each row between the copied pixels
	int A_idx, B_idx;
	Complex A, B;
	for (int i = 0; i< 512/deci; i++){ //row; also excluding the boundary 4 rows
		for (int j= 0; j<512/deci; j++){  //column; also excluding the boundary 4 columns
			A = outputImage.Pixel(deci*i,deci*j);
			B = outputImage.Pixel(deci*i,deci*j+deci);
			for (int k = 1; k<deci; k ++){
				outputImage.Pixel(deci*i,deci*j+k) = ( ( double(1)- double(k)/double(deci) )*A) + ((double(k)/double(deci))*B);

			}
		}
	}

	int A_row;
	int idx;
	//Second interpolate linearly along each column
	for( int i = 0; i< 512-deci; i++){ //excluding the boundaries 4 rows
		for (int j = 0 ; j<512-deci; j++){ //excluding the boundaries 4 columns
			idx = i%deci;
			if(idx != 0){
				A_row = i-idx;
				//cout << A_row <<endl;
				A = outputImage.Pixel(A_row, j);
				B = outputImage.Pixel(A_row+deci, j);
				outputImage.Pixel(i, j ) = (( double(1) - double(idx)/double(deci) )*A) + (double(idx)/(double)(deci)*B);

				}
			}
		}

		//generate difference image
		double mse;
		for ( int i =0; i<512; i++){
			for (int j = 0; j<512; j++){
				differenceImage.Pixel(i,j) = inputImage.Pixel(i,j) - outputImage.Pixel(i,j);
				mse = mse + differenceImage.Pixel(i,j).real()*differenceImage.Pixel(i,j).real();
			}
		}
		mse = mse /double(512*512);
		cout <<"Mean square error:" << mse << endl;

		//scale image
		for(int w=0; w<differenceImage.Width(); w++){
			for(int h=0; h<differenceImage.Height();h++){
				if(differenceImage.Pixel(w,h).real()<m){
					m=differenceImage.Pixel(w,h).real();
				}
				if(differenceImage.Pixel(w,h).real()>M){
					M=differenceImage.Pixel(w,h).real();
				}
			}
		}


	// scale image pixel so that each pixel value is within (0,255) range
	for(int i=0; i<differenceImage.Height(); i++){
		for(int j=0; j<differenceImage.Width(); j++){
			if(differenceImage.Pixel(i,j).real() < 0)
				//D_out[i] = 128*(D[i]-m)/(-m);
				differenceImage.Pixel(i,j)= double(128)* ( differenceImage.Pixel(i,j) - m)/ (-m);
			else {
			//D_out[i] = 127*D[i]/M + 128;
			  differenceImage.Pixel(i,j) = double(127) * (differenceImage.Pixel(i,j))/M +double(128);
		}

	}

}


}


else if( flag = 1){

	// Compute FFT for each row
	inputImage.FourierTransform();

	//copy left top corner to 2D small array
	for(int i =0; i< 512/(deci*2) ; i++){
		for (int j = 0; j< 512/(deci*2); j ++){
			smallImage.Pixel(i,j) = inputImage.Pixel(i,j);
		}
	}
	int temprow, tempcol;
	//copy left bottom corner to 2D small array
	for(int i = (512-512/(deci*2)); i< 512 ; i++){
		for (int j = 0; j< 512/(deci*2); j ++){
		  temprow = i - (512-512/(deci*2));
			tempcol = j ;
			smallImage.Pixel(512/(deci*2) + temprow, tempcol) = inputImage.Pixel(i,j);
		}
	}
	//copy right top corner to 2D small array
	for(int i =0; i< 512/(deci*2) ; i++){
		for (int j = (512-512/(deci*2)); j< 512; j ++){
			tempcol = j - (512-512/(deci*2));
			temprow  = i;
			smallImage.Pixel(temprow, 512/(deci*2) + tempcol) = inputImage.Pixel(i,j);
		}
	}

	//copy right bottom corner to 2D small array
	for(int i =(512-512/(deci*2)); i< 512; i++){
		for (int j = (512-512/(deci*2)); j< 512; j ++){
			tempcol = j - (512-512/(deci*2));
			temprow  = i - (512-512/(deci*2));
			smallImage.Pixel(512/(deci*2)+temprow, 512/(deci*2) + tempcol) = inputImage.Pixel(i,j);
		}
	}


	//Take inverse FFT:
	smallImage.InverseFourierTransform();



	for (int i =0; i< 512/deci; i++){
		for(int j = 0; j<512/deci; j++){
			smallImage.Pixel(i,j) = smallImage.Pixel(i,j) / double(deci*deci);
		}
	}


	//Restore:

	//restore:
	Complex pix2;
	for ( int i = 0; i< 512/deci; i++){
		for(int j = 0; j< 512/deci; j++){
			pix2 = smallImage.Pixel(i,j);
			outputImage.Pixel(deci*i, deci*j)= pix2;
		}
	}
	//First interpolate linearly along each row between the copied pixels
	int A_idx, B_idx;
	Complex A, B;
	for (int i = 0; i< 512/deci; i++){ //row; also excluding the boundary 4 rows
		for (int j= 0; j<512/deci; j++){  //column; also excluding the boundary 4 columns
			A = outputImage.Pixel(deci*i,deci*j);
			B = outputImage.Pixel(deci*i,deci*j+deci);
			for (int k = 1; k<deci; k ++){
				outputImage.Pixel(deci*i,deci*j+k) = ( ( double(1)- double(k)/double(deci) )*A) + ((double(k)/double(deci))*B);

			}
		}
	}

	int A_row;
	int idx;
	//Second interpolate linearly along each column
	for( int i = 0; i< 512-deci; i++){ //excluding the boundaries 4 rows
		for (int j = 0 ; j<512-deci; j++){ //excluding the boundaries 4 columns
			idx = i%deci;
			if(idx != 0){
				A_row = i-idx;
				//cout << A_row <<endl;
				A = outputImage.Pixel(A_row, j);
				B = outputImage.Pixel(A_row+deci, j);
				outputImage.Pixel(i, j ) = (( double(1) - double(idx)/double(deci) )*A) + (double(idx)/(double)(deci)*B);

				}
			}
		}

		//generate difference image
		double mse;
		for ( int i =0; i<512; i++){
			for (int j = 0; j<512; j++){
				differenceImage.Pixel(i,j) = inputImage.Pixel(i,j) - outputImage.Pixel(i,j);
				if(differenceImage.Pixel(i,j).real() < 0 ){
					differenceImage.Pixel(i,j)= double(0);
				}
				else if(differenceImage.Pixel(i,j).real() > 255 ){
					differenceImage.Pixel(i,j)= double(255);
				}
				mse = mse + differenceImage.Pixel(i,j).real()*differenceImage.Pixel(i,j).real();
				}
			}
			mse = mse / (512*512);
			cout<<"Mean Square Error:" << mse<<endl;

			cout<< "Success5" <<endl;

}


	/*===

	Insert Lab 3 code here

	Note that in this lab if you want to take the FFT of a ComplexsmallImage called image,
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()

	===*/

	// save the image

	//save image order: input.png
	//small_output  restored. png  difference.png  decimation factor
	smallImage.SavePng (argv[2]);    //decimated image
	outputImage.SavePng (argv[3]);  //restored image
	differenceImage.SavePng (argv[4]); //difference image

	return 0;
}
