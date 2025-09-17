// // Define vector unit width here
// #define VECTOR_WIDTH 4

// #ifndef CS149INTRIN_H_
// #define CS149INTRIN_H_

// #include <cstdlib>
// #include <cmath>
// #include "logger.h"

// //*******************
// //* Type Definition *
// //*******************

// extern Logger CS149Logger;

// template <typename T>
// struct __cs149_vec {
//   T value[VECTOR_WIDTH];
// };

// // Declare a mask with __cs149_mask
// struct __cs149_mask : __cs149_vec<bool> {};

// // Declare a floating point vector register with __cs149_vec_float
// #define __cs149_vec_float __cs149_vec<float>

// // Declare an integer vector register with __cs149_vec_int
// #define __cs149_vec_int   __cs149_vec<int>

// //***********************
// //* Function Definition *
// //***********************

// // Return a mask initialized to 1 in the first N lanes and 0 in the others
// __cs149_mask _cs149_init_ones(int first = VECTOR_WIDTH);

// // Return the inverse of maska
// __cs149_mask _cs149_mask_not(__cs149_mask &maska);

// // Return (maska | maskb)
// __cs149_mask _cs149_mask_or(__cs149_mask &maska, __cs149_mask &maskb);

// // Return (maska & maskb)
// __cs149_mask _cs149_mask_and(__cs149_mask &maska, __cs149_mask &maskb);

// // Count the number of 1s in maska
// int _cs149_cntbits(__cs149_mask &maska);

// // Set register to value if vector lane is active
// //  otherwise keep the old value
// void _cs149_vset_float(__cs149_vec_float &vecResult, float value, __cs149_mask &mask);
// void _cs149_vset_int(__cs149_vec_int &vecResult, int value, __cs149_mask &mask);
// // For user's convenience, returns a vector register with all lanes initialized to value
// __cs149_vec_float _cs149_vset_float(float value);
// __cs149_vec_int _cs149_vset_int(int value);

// // Copy values from vector register src to vector register dest if vector lane active
// // otherwise keep the old value
// void _cs149_vmove_float(__cs149_vec_float &dest, __cs149_vec_float &src, __cs149_mask &mask);
// void _cs149_vmove_int(__cs149_vec_int &dest, __cs149_vec_int &src, __cs149_mask &mask);

// // Load values from array src to vector register dest if vector lane active
// //  otherwise keep the old value
// void _cs149_vload_float(__cs149_vec_float &dest, float* src, __cs149_mask &mask);
// void _cs149_vload_int(__cs149_vec_int &dest, int* src, __cs149_mask &mask);

// // Store values from vector register src to array dest if vector lane active
// //  otherwise keep the old value
// void _cs149_vstore_float(float* dest, __cs149_vec_float &src, __cs149_mask &mask);
// void _cs149_vstore_int(int* dest, __cs149_vec_int &src, __cs149_mask &mask);

// // Return calculation of (veca + vecb) if vector lane active
// //  otherwise keep the old value
// void _cs149_vadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
// void _cs149_vadd_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// // Return calculation of (veca - vecb) if vector lane active
// //  otherwise keep the old value
// void _cs149_vsub_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
// void _cs149_vsub_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// // Return calculation of (veca * vecb) if vector lane active
// //  otherwise keep the old value
// void _cs149_vmult_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
// void _cs149_vmult_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// // Return calculation of (veca / vecb) if vector lane active
// //  otherwise keep the old value
// void _cs149_vdiv_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
// void _cs149_vdiv_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);


// // Return calculation of absolute value abs(veca) if vector lane active
// //  otherwise keep the old value
// void _cs149_vabs_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_mask &mask);
// void _cs149_vabs_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_mask &mask);

// // Return a mask of (veca > vecb) if vector lane active
// //  otherwise keep the old value
// void _cs149_vgt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
// void _cs149_vgt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// // Return a mask of (veca < vecb) if vector lane active
// //  otherwise keep the old value
// void _cs149_vlt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
// void _cs149_vlt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// // Return a mask of (veca == vecb) if vector lane active
// //  otherwise keep the old value
// void _cs149_veq_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
// void _cs149_veq_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// // Adds up adjacent pairs of elements, so
// //  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
// void _cs149_hadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// // Performs an even-odd interleaving where all even-indexed elements move to front half
// //  of the array and odd-indexed to the back half, so
// //  [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
// void _cs149_interleave_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// // Add a customized log to help debugging
// void addUserLog(const char * logStr);

// #endif
// 在此处定义向量单元宽度
#define VECTOR_WIDTH 4

#ifndef CS149INTRIN_H_
#define CS149INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* 类型定义         *
//*******************

// 声明日志器CS149Logger
extern Logger CS149Logger;

// 向量结构体模板：存储VECTOR_WIDTH个T类型的值
template <typename T>
struct __cs149_vec {
  T value[VECTOR_WIDTH];
};

// 使用__cs149_mask声明掩码类型（继承自存储bool类型的__cs149_vec）
struct __cs149_mask : __cs149_vec<bool> {};

// 使用__cs149_vec_float声明浮点型向量寄存器
#define __cs149_vec_float __cs149_vec<float>

// 使用__cs149_vec_int声明整型向量寄存器
#define __cs149_vec_int   __cs149_vec<int>

//***********************
//* 函数定义             *
//***********************

// 返回一个掩码：前N个通道初始化为1，其余通道初始化为0（参数first默认值为VECTOR_WIDTH）
__cs149_mask _cs149_init_ones(int first = VECTOR_WIDTH);

// 返回掩码maska的反掩码（1变0，0变1）
__cs149_mask _cs149_mask_not(__cs149_mask &maska);

// 返回掩码maska与maskb的按位或结果
__cs149_mask _cs149_mask_or(__cs149_mask &maska, __cs149_mask &maskb);

// 返回掩码maska与maskb的按位与结果
__cs149_mask _cs149_mask_and(__cs149_mask &maska, __cs149_mask &maskb);

// 统计掩码maska中值为1的通道数量
int _cs149_cntbits(__cs149_mask &maska);

// 若向量通道处于激活状态，则将寄存器vecResult的该通道值设为value；否则保留原有值
void _cs149_vset_float(__cs149_vec_float &vecResult, float value, __cs149_mask &mask);
void _cs149_vset_int(__cs149_vec_int &vecResult, int value, __cs149_mask &mask);

// 为方便用户使用，返回一个所有通道均初始化为value的向量寄存器
__cs149_vec_float _cs149_vset_float(float value);
__cs149_vec_int _cs149_vset_int(int value);

// 若向量通道处于激活状态，则将源向量寄存器src的该通道值复制到目标寄存器dest；否则保留dest原有值
void _cs149_vmove_float(__cs149_vec_float &dest, __cs149_vec_float &src, __cs149_mask &mask);
void _cs149_vmove_int(__cs149_vec_int &dest, __cs149_vec_int &src, __cs149_mask &mask);

// 若向量通道处于激活状态，则将数组src的对应值加载到寄存器dest的该通道；否则保留dest原有值
void _cs149_vload_float(__cs149_vec_float &dest, float* src, __cs149_mask &mask);
void _cs149_vload_int(__cs149_vec_int &dest, int* src, __cs149_mask &mask);

// 若向量通道处于激活状态，则将寄存器src该通道的值存储到数组dest的对应位置；否则保留dest原有值
void _cs149_vstore_float(float* dest, __cs149_vec_float &src, __cs149_mask &mask);
void _cs149_vstore_int(int* dest, __cs149_vec_int &src, __cs149_mask &mask);

// 若向量通道处于激活状态，则计算veca与vecb对应通道值的和，存入vecResult；否则保留vecResult原有值
void _cs149_vadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vadd_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// 若向量通道处于激活状态，则计算veca与vecb对应通道值的差，存入vecResult；否则保留vecResult原有值
void _cs149_vsub_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vsub_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// 若向量通道处于激活状态，则计算veca与vecb对应通道值的积，存入vecResult；否则保留vecResult原有值
void _cs149_vmult_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vmult_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// 若向量通道处于激活状态，则计算veca与vecb对应通道值的商，存入vecResult；否则保留vecResult原有值
void _cs149_vdiv_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vdiv_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);


// 若向量通道处于激活状态，则计算veca对应通道值的绝对值，存入vecResult；否则保留vecResult原有值
void _cs149_vabs_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_mask &mask);
void _cs149_vabs_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_mask &mask);

// 若向量通道处于激活状态，比较veca与vecb对应通道值：veca>vecb则掩码通道设1，否则设0；否则保留掩码原有值
void _cs149_vgt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vgt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// 若向量通道处于激活状态，比较veca与vecb对应通道值：veca<vecb则掩码通道设1，否则设0；否则保留掩码原有值
void _cs149_vlt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vlt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// 若向量通道处于激活状态，比较veca与vecb对应通道值：veca==vecb则掩码通道设1，否则设0；否则保留掩码原有值
void _cs149_veq_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_veq_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// 对向量元素进行相邻成对求和，示例：输入[0 1 2 3] → 输出[0+1 0+1 2+3 2+3]
void _cs149_hadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// 执行向量奇偶交错操作：偶数索引（从0开始）元素移到前半部分，奇数索引元素移到后半部分
// 示例：输入[0 1 2 3 4 5 6 7] → 输出[0 2 4 6 1 3 5 7]
void _cs149_interleave_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// 添加自定义日志，用于辅助调试
void addUserLog(const char * logStr);

#endif
