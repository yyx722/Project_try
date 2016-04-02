#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
void print_code(int bram_num, int fm_layer, string filename);
int get_counter_range (int fm_size);

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
	time_t currentTime;
	struct tm *localTime;
	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time
	int Day = localTime->tm_mday;
	int Month = localTime->tm_mon + 1;
	int Year = localTime->tm_year + 1900;
	int Hour = localTime->tm_hour;
	int Min = localTime->tm_min;
	int Sec = localTime->tm_sec;
	string date = to_string(Month) + "/" + to_string(Day) + "/" + to_string(Year);



	ofstream ofs(filename, ifstream::out);
	
  for (int i = 0; i < inst_num; i++)
  {
    ofs << "  Convolution_3x3_on_224x224_strd1 conv_" << fm_layer+1 << "_" << i << "(" << endl; 
    ofs << "    .clk              (clk)," << endl;
    ofs << "    .reset            (reset)," << endl;
    ofs << "    .enable           (conv_en)," << endl;
    ofs << "    .img_in           (fm_" << fm_layer << "_" << i << "_din)," << endl;
    ofs << "    .img_to_ip        (fm_" << fm_layer << "_" << i << "_flatten)," << endl;
    if (i == 0)
    {
      ofs << "    .img_to_ip_valid  (img_to_ip_valid)," << endl;
      ofs << "    .newline_out      (newline_out)," << endl;
      ofs << "    .newimg_out       (newimg_out)," << endl;
      ofs << "    .img_finish_out   (finish_out)" << endl;
    }
    else
    {
      ofs << "    .img_to_ip_valid  ()," << endl;
      ofs << "    .newline_out      ()," << endl;
      ofs << "    .newimg_out       ()," << endl;
      ofs << "    .img_finish_out   ()" << endl;      
    }
    ofs << " );" << endl << endl;
  }

  ofs.close();

}

// calculate number of bits needed for counter to cover feature map size
int get_counter_range (int fm_size)
{
  int num_bits = 1;
  while (pow(2, num_bits) < fm_size)
  {
    num_bits ++;
  }
  return num_bits; 
}
