#include <string>
#include <iostream> 
#include <boost/lexical_cast.hpp>

#define numof(array) sizeof(array)/sizeof(array[0])
using namespace std;

double calc_y(double* x,double* w,int size){
	double y = 0;
	for(int i = 0;i < size;i++){
		if(w[i]){
			y += x[i] * w[i];
		}
	}
	return y;
}

void learning(double* w,double* x,int t,int size){
	double const lambda = 0.5;
	double const alpha = 0;
	int y = calc_y(x,w,size);
	
	if(y * t < lambda){
		for(int i = 0;i < size;i++){
			w[i] += t * x[i] - (alpha * w[i]);
		}
	}
}

int main(){
	//learning part
	double x_list[][4] = {  //[R,G,B,bais]
	  {100/255.0, 100/255.0, 100/255.0, 1},
      {127/255.0, 50/255.0, 100/255.0, 1},
	  {0, 200/255.0, 0, 1},
      {0, 0, 255/255.0, 1},
      {80/255.0, 40/255.0, 150/255.0, 1},
      {255/255.0, 255/255.0, 0, 1},
      {255/255.0, 0, 255/255.0, 1},
      {0, 255/255.0, 255/255.0, 1},
      {180/255.0, 190/255.0, 200/255.0, 1},
      {230/255.0, 240/255.0, 255/255.0, 1}   
      };
    int answer[] = {-1, -1, -1, -1, -1, 1, 1, 1, 1, 1};
    double weight[] = {0,0,0,1};//weight vector
    const int loop = 20;
    for(int i = 0;i < loop;i++){
    	for(int j = 0;j < numof(x_list);j++){
    		learning(weight,x_list[j],answer[j],numof(x_list[j]));
    	}
    }
    
    //estimate part
	//test
	cout << "output: weight" << endl;
	for(int i = 0;i < numof(weight);i++){
		cout << weight[i] << " ";
	}
	cout << endl << endl;
	
	string temp[3];
	double input[4];
	while(true){
		cin >> temp[0] >> temp[1] >> temp[2];
		
		input[0] = boost::lexical_cast<double>(temp[0])/255.0;
		input[1] = boost::lexical_cast<double>(temp[1])/255.0;
		input[2] = boost::lexical_cast<double>(temp[2])/255.0;
		input[3] = 1;//bais
		
		double t = calc_y(input,weight,numof(input));
		
		
		cout << "t = " << t << endl;
		if(t >= 0){
			cout << "White" << endl;
		}else{
			cout << "Black" << endl;
		}
	}
	return 0;
}