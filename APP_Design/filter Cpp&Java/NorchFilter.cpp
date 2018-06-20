#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "iostream"
using namespace std;

class NorchFilter{
	private: 
		int Data_In;
		int Data_Out = 0;
		double Sampling_Frequency;
		double CutOff_Frequency;
		double BW_Coeff;
		// Filter coefficients:
		double z1x;
		double b0;
		double b2;
		double b1;
		double a1;
		double a2;
		// Filter internal vars:
		double y = 0, y1 = 0, y2 = 0;
		double x0 = 0, x1 = 0, x2 = 0;
		double pi = 3.1415926535;
		double num = 0;    


    public:
		NorchFilter(double Sampling_Frequency,double CutOff_Frequency,double BW_Coeff) {
	        //If wrong parameters:
	        if((Sampling_Frequency < 0.0)||(CutOff_Frequency < 0.0)) return;
	        if(CutOff_Frequency > (Sampling_Frequency/2))            return;
	        if((BW_Coeff <= 0.0)||(BW_Coeff >= 1.0))                 return;
	        Sampling_Frequency = Sampling_Frequency;
	        CutOff_Frequency = CutOff_Frequency;
	        BW_Coeff = BW_Coeff;
	        // Filter coefficients:
	        z1x = cos(2 * pi * CutOff_Frequency / Sampling_Frequency);
	        b0 = (1 - BW_Coeff) * (1 - BW_Coeff) / (2 * (fabs(z1x) + 1)) + BW_Coeff;
	        b2 = b0;
	        b1 = -2 * z1x * b0;
	        a1 = -2 * z1x * BW_Coeff;
	        a2 = BW_Coeff * BW_Coeff;
	        cout<<Sampling_Frequency<<" "<<CutOff_Frequency<<" "<<BW_Coeff<<endl;
	        cout<<z1x<<" "<<b0<<" "<<b1<<" "<<b2<<" "<<a1<<" "<<a2;
	    }

	    int FilterThisOne(int Data_In){
	    	
	        // Filter internal vars:
	        y = y1;
	
	        y = b0 * x0 + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
	        y2 = y1;
	        y1 = y;
	        x2 = x1;
	        x1 = x0;
	        x0 = Data_In;
	        num += 1;
	        //		if(      y >  32767) y =  32767;
	        //		else if (y < -32768) y = -32768;
	
	        //int Data_Out = (int) y;
	        cout<<Data_In<<" "<<(int) y<<" "<<num<<endl;
	        return (int) y;
	    }
};

int input_array[100000],output_array[100000];
int main(){
	NorchFilter NorchFilter50 = NorchFilter(225,50,0.975);
	NorchFilter NorchFilter100 = NorchFilter(225,100,0.975);
	//return 0;
	FILE *fp,*fp2;
	fp=fopen("ecgdata_raw.txt","r");
	fp2=fopen("out.txt","w");
	int i=0;int temp;
	do
   	{
      	fscanf(fp,"%d",&input_array[i]);
      	cout<<input_array[i]<<":";
      	temp = ((input_array[i]-5900000)/80 -500)*5+500;
		temp = NorchFilter50.FilterThisOne(4*temp);
		output_array[i] = NorchFilter100.FilterThisOne(temp);
		i++;
   	}
   	while(!feof(fp));
   	cout<<input_array[10]; 
   	long int len = i-1;

	
	int j;
	for(j=0;j<len;j++)
		fprintf(fp2,"%d\n",output_array[j]);
	fclose(fp);
	fclose(fp2);
	return 0;
} 
