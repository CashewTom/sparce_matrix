#include <iostream>
#include <vector>
#include <array>

template<class T>
static void print_vector(T &data){
	for(auto ref : data){
		std::cout << ref << " ";
	}
	std::cout << std::endl;
}

class CSR{
	public:
		int non_zero_size;
		int width;
		int height;
		std::vector<int> data;
		std::vector<int> column;
		std::vector<int> row;
		void print(){
			std::cout << "This is CSR matrix" << std::endl;
			std::cout << "NNZ: " << non_zero_size << std::endl;
			std::cout << "Matrix size: " << width << "x" << height << std::endl;
			std::cout << "DATA: ";
			print_vector(data);
			std::cout << "COL: ";
			print_vector(column);
			std::cout << "ROW: ";
			print_vector(row);
			std::cout << std::endl;
		}
		CSR mul(CSR b){
			CSR c;
			if(b.height != width){
				c.non_zero_size = 0;
				c.width = 0;
				c.height = 0;
				return c;
			}
			c.height = height;
			c.width = b.width;
			return c;
		}
		std::vector<int> spmv(std::vector<int> b){
			std::vector<int> c;
			for(int i = 0; i < height; i++){
				int accum = 0;
				int start_idx = row[i];
				int end_idx = i == height - 1 ? non_zero_size : row[i+1];
				for(int j = start_idx; j < end_idx; j++){
					int index = column[j];
					accum += b[index] * data[j];
				}
				c.push_back(accum);
			}
			return c;
		}
};



static const int non_zero_size = 5;
static const int matrix_size = 3;

/* 1 0 0
 * 0 3 1
 * 3 0 1
 */

std::array<int, non_zero_size> csr_data   = {1, 3, 1, 3, 1};
std::array<int, non_zero_size> csr_column = {0, 1, 2, 0, 2};
std::array<int, matrix_size>   csr_row    = {0, 1, 3};

int main(){
	CSR csr;
	csr.non_zero_size = 5;
	csr.height = 3;
	csr.width = 3;
	csr.data = std::vector<int>(csr_data.begin(), csr_data.end());
	csr.column = std::vector<int>(csr_column.begin(), csr_column.end());
	csr.row = std::vector<int>(csr_row.begin(), csr_row.end());
	csr.print();
	std::vector<int> vec = {1,2,3};
	auto result = csr.spmv(vec);
	print_vector(result);
	return 0;
}


