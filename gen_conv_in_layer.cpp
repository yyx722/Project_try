#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
void print_code(int bram_num, int set_layer,int layer, string filename);
int get_counter_range(int fm_size);

int main() {
	int inst_num;
	int set_conv;
	int layer;

	cout << "Please input number of convolution instances:";
	cin >> inst_num;
	cout << "Please input which set of convolution it is:";
	cin >> set_conv;
	cout << "Please input which layer it is:";
	cin >> layer;

	string filename("C:\\Users\\yunxuan\\Documents\\deep learning\\conv_inst.v");
	cout << "Start generating " << filename << endl;

	print_code(inst_num, set_conv,layer, filename);

	cout << "Finish generating " << filename << endl;
	return 0;
}

void print_code(int inst_num, int set_conv, int layer, string filename) {
	// get time
	



	ofstream ofs(filename, ifstream::out);

	for (int i = 0; i < inst_num; i++)
	{
		ofs << "  Convolution_3x3_on_224x224_strd1 conv_" << set_conv << "_" <<layer<<"_"<< i << "(" << endl;
		ofs << "    .clk              (clk)," << endl;
		ofs << "    .reset            (reset)," << endl;
		ofs << "    .enable           (conv_en)," << endl;
		ofs << "    .img_in           (fm_" << set_conv-1 << "_" << i << "_din)," << endl;
		ofs << "    .img_to_ip        (fm_" << set_conv-1 << "_" << i << "_flatten)," << endl;
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
int get_counter_range(int fm_size)
{
	int num_bits = 1;
	while (pow(2, num_bits) < fm_size)
	{
		num_bits++;
	}
	return num_bits;
}
