#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;


int main() {
  int inst_num;
  int fm_layer;

  cout << "Please input number of convolution instances:";
  cin >> inst_num;
  cout << "Please input which layer of feature map it is:";
  cin >> fm_layer;
    
  string filename("conv_inst.v");
  cout << "Start generating " << filename << endl;
  
  print_code (inst_num, fm_layer, filename);
  
  cout << "Finish generating " << filename << endl;
	return 0;
}


void print_code(int inst_num, int fm_layer, string filename) {
	// get time
	
	ofstream ofs(filename, ifstream::out);
	ofs << " reg ["<<inst_num<<"*`DATA_WIDTH-1:0] fm_raw_data"<<endl;
  for (int i = 0; i < inst_num; i++)
    ofs << "wire [`DATA_WIDTH-1:0] fm_0_"<<i<<"_din = fm_raw_data["<<i+1<<"*`DATA_WIDTH-1:"<<i<<"*`DATA_WIDTH]"<<endl;

  ofs.close();

}
