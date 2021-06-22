#include <iostream>
#include <time.h>
#include <fstream>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#define _USE_MATH_DEFINES

using namespace std;

int dice(){
    return rand() % 2 + 1;
}

int main()
{
std::ofstream ofs("bpsk.dat");    // 出力ファイルを開く
 if(!ofs){                // ファイルをストリームにリンクできない場合、偽(=0)が返される。
    cout << "出力ファイルを開けません\n";
    return 1;
  }

for(double a=0.0; a<12; a+=1.0){
int n =10000000;
double SNRDB = a;
double SNR = pow(10,SNRDB/10);
double No = 1/SNR;
double ave = 0.0;
double sca = No/2;
double rand1; 
double rand2; 
double R1;
double *TX_bit;
double *TX_BPSK;
double *noiser;
double *RX_BPSK;
double *RX_bit;
double error_sum = 0.0;
double BER = 0.0;
TX_bit = new double[n];
TX_BPSK = new double[n];
RX_BPSK = new double[n];
RX_bit = new double[n];
noiser = new double[n];

srand((unsigned int)time(NULL)); // 乱数の種を初期化（プログラムの先頭で1回のみ）
	for (int i = 0; i < n; ++i) { 
		TX_bit[i] = dice() - 1;
	}

for (int i = 0; i < n; ++i) { 
	
	if(TX_bit[i] == 0){
		TX_BPSK[i] = -1;
	}else{
		TX_BPSK[i] = 1;
	}
}
std::random_device seed_gen;
std::default_random_engine engine(seed_gen());

  // 平均0.0、標準偏差1.0で分布させる
  std::normal_distribution<> dist(0.0, 1.0);
for(int i = 0; i < n; i++) {
	R1 = dist(engine);
	noiser[i] = ((sqrt(sca) * R1) + ave);
}
for(int i = 0; i < n; i++){
	RX_BPSK[i] = TX_BPSK[i] + noiser[i];
		if(RX_BPSK[i] > 0){
			RX_bit[i] = 1;
		}else{
			RX_bit[i] = 0;
		}
		error_sum += abs(RX_bit[i]-TX_bit[i]);
}

BER = error_sum/n;
ofs<<BER<<"	"<<erfc(sqrt(pow(10,SNRDB/10)))/2<<endl;
delete[] TX_bit;
delete[] TX_BPSK;
delete[] noiser;
delete[] RX_BPSK;
delete[] RX_bit;

}
    return (0);
}

