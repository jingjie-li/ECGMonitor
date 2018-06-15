#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "iostream"
using namespace std;


int input_array[100000],output_array[100000];

// (C) Sergey Aleynik.   aleyniks@yahoo.com
   
     // BW_Coeff is changing from 0.0 to 1.0 (excluded) and the more the narrow:
     // |  BW_Coeff   |  Real BandWidth (approxim.)  |
     // |   0.975     | 0.00907 * Sampling_Frequency |
     // |   0.95      | 0.01814 * Sampling_Frequency |
     // |   0.9       | 0.03628 * Sampling_Frequency |

void  Notch_Filter_Test(int *Data_In,int *Data_Out, long nData_Length,double Sampling_Frequency,double CutOff_Frequency,double BW_Coeff){
	// If wrong parameters:
	cout<<Data_In;
	if((Data_In == NULL)||(nData_Length <= 0))   return;
	if((Sampling_Frequency < 0.0)||(CutOff_Frequency < 0.0)) return;
	if(CutOff_Frequency > (Sampling_Frequency/2))            return;
	if((BW_Coeff <= 0.0)||(BW_Coeff >= 1.0))                 return; 
	
	cout<<"doing";
	static const double  pi = 3.1415926535; 
	
	// Filter coefficients:
	double z1x = cos(2*pi*CutOff_Frequency/Sampling_Frequency); 
	double b0 = (1-BW_Coeff)*(1-BW_Coeff)/(2*(fabs(z1x)+1)) + BW_Coeff; 
	double b2 = b0;
	double b1 = -2*z1x*b0; 
	double a1 = -2*z1x*BW_Coeff; 
	double a2 = BW_Coeff*BW_Coeff; 
	
	// Filter internal vars:
	double y=0,  y1=0, y2=0; 
	double x0=0, x1=0, x2=0; 
	
	long i;
	for(i=0; i<nData_Length; i++)
	{
		y  = b0 * x0 + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2; 
		y2 = y1; 
		y1 = y;
		x2 = x1;
		x1 = x0;
		x0 = Data_In[i];
		
//		if(      y >  32767) y =  32767;
//		else if (y < -32768) y = -32768;
		
		Data_Out[i] = (int)y;
	}
}

//
//void design_bandpass_filter(long double *fir_filter,int n, float f1, float f2)
//{
//	int m=(n-1)/2,i;
//	double M_PI = 3.1415926;
//	for(i=0;i<n;i++)
//	{
//		if(i==m)
//			fir_filter[i]=(0.54-(0.46*(cos(2*M_PI*i/(n-1)))))*2*(f2-f1);
//		else
//			fir_filter[i]=((0.54-(0.46*(cos(2*M_PI*i/(n-1)))))*((sin(f2*2*M_PI*(i-m))-sin(f1*2*M_PI*(i-m)))/(M_PI*(i-m))));
//	}
//}
//
//
//void filter(long double *fir_filter, int* input, int* output, int n, int len)
//{
//	int i,j,m=(n-1)/2;
//	for(i=0;i<len;i++)
//		for(j=0;j<n;j++)
//		{
//			if(i>=j)
//				output[i]+=fir_filter[j]*input[i-j];
//		}
//}


int main(){
	FILE *fp,*fp2;
	fp=fopen("ecgdata_raw.txt","r");
	fp2=fopen("out.txt","w");
	int i=0;
	do
   	{
      	fscanf(fp,"%d",&input_array[i] );
		i++;
   	}
   	while(!feof(fp));
   	cout<<input_array[10]; 
   	long int len = i-1;
//   	
//   	int taps=101;
//	long double fir_filter[taps];
//	
//	long double sampling_freq = 500;
//	long double cutoff_freq1 = 1;
//	long double cutoff_freq2 = 250;
//	design_bandpass_filter(fir_filter,taps,cutoff_freq1/(sampling_freq),cutoff_freq2/(sampling_freq));
//	filter(fir_filter,input_array,output_array,taps,len);

	Notch_Filter_Test(input_array,output_array,len,217.4,50,0.6);
	
	
	int j;
	for(j=0;j<len;j++)
		fprintf(fp2,"%d\n",output_array[j]);
	fclose(fp);
	fclose(fp2);
	return 0;
} 
