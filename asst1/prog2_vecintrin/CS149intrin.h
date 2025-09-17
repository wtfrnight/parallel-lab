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
// �ڴ˴�����������Ԫ���
#define VECTOR_WIDTH 4

#ifndef CS149INTRIN_H_
#define CS149INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* ���Ͷ���         *
//*******************

// ������־��CS149Logger
extern Logger CS149Logger;

// �����ṹ��ģ�壺�洢VECTOR_WIDTH��T���͵�ֵ
template <typename T>
struct __cs149_vec {
  T value[VECTOR_WIDTH];
};

// ʹ��__cs149_mask�����������ͣ��̳��Դ洢bool���͵�__cs149_vec��
struct __cs149_mask : __cs149_vec<bool> {};

// ʹ��__cs149_vec_float���������������Ĵ���
#define __cs149_vec_float __cs149_vec<float>

// ʹ��__cs149_vec_int�������������Ĵ���
#define __cs149_vec_int   __cs149_vec<int>

//***********************
//* ��������             *
//***********************

// ����һ�����룺ǰN��ͨ����ʼ��Ϊ1������ͨ����ʼ��Ϊ0������firstĬ��ֵΪVECTOR_WIDTH��
__cs149_mask _cs149_init_ones(int first = VECTOR_WIDTH);

// ��������maska�ķ����루1��0��0��1��
__cs149_mask _cs149_mask_not(__cs149_mask &maska);

// ��������maska��maskb�İ�λ����
__cs149_mask _cs149_mask_or(__cs149_mask &maska, __cs149_mask &maskb);

// ��������maska��maskb�İ�λ����
__cs149_mask _cs149_mask_and(__cs149_mask &maska, __cs149_mask &maskb);

// ͳ������maska��ֵΪ1��ͨ������
int _cs149_cntbits(__cs149_mask &maska);

// ������ͨ�����ڼ���״̬���򽫼Ĵ���vecResult�ĸ�ͨ��ֵ��Ϊvalue��������ԭ��ֵ
void _cs149_vset_float(__cs149_vec_float &vecResult, float value, __cs149_mask &mask);
void _cs149_vset_int(__cs149_vec_int &vecResult, int value, __cs149_mask &mask);

// Ϊ�����û�ʹ�ã�����һ������ͨ������ʼ��Ϊvalue�������Ĵ���
__cs149_vec_float _cs149_vset_float(float value);
__cs149_vec_int _cs149_vset_int(int value);

// ������ͨ�����ڼ���״̬����Դ�����Ĵ���src�ĸ�ͨ��ֵ���Ƶ�Ŀ��Ĵ���dest��������destԭ��ֵ
void _cs149_vmove_float(__cs149_vec_float &dest, __cs149_vec_float &src, __cs149_mask &mask);
void _cs149_vmove_int(__cs149_vec_int &dest, __cs149_vec_int &src, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬��������src�Ķ�Ӧֵ���ص��Ĵ���dest�ĸ�ͨ����������destԭ��ֵ
void _cs149_vload_float(__cs149_vec_float &dest, float* src, __cs149_mask &mask);
void _cs149_vload_int(__cs149_vec_int &dest, int* src, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬���򽫼Ĵ���src��ͨ����ֵ�洢������dest�Ķ�Ӧλ�ã�������destԭ��ֵ
void _cs149_vstore_float(float* dest, __cs149_vec_float &src, __cs149_mask &mask);
void _cs149_vstore_int(int* dest, __cs149_vec_int &src, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬�������veca��vecb��Ӧͨ��ֵ�ĺͣ�����vecResult��������vecResultԭ��ֵ
void _cs149_vadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vadd_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬�������veca��vecb��Ӧͨ��ֵ�Ĳ����vecResult��������vecResultԭ��ֵ
void _cs149_vsub_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vsub_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬�������veca��vecb��Ӧͨ��ֵ�Ļ�������vecResult��������vecResultԭ��ֵ
void _cs149_vmult_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vmult_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬�������veca��vecb��Ӧͨ��ֵ���̣�����vecResult��������vecResultԭ��ֵ
void _cs149_vdiv_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vdiv_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);


// ������ͨ�����ڼ���״̬�������veca��Ӧͨ��ֵ�ľ���ֵ������vecResult��������vecResultԭ��ֵ
void _cs149_vabs_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_mask &mask);
void _cs149_vabs_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬���Ƚ�veca��vecb��Ӧͨ��ֵ��veca>vecb������ͨ����1��������0������������ԭ��ֵ
void _cs149_vgt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vgt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬���Ƚ�veca��vecb��Ӧͨ��ֵ��veca<vecb������ͨ����1��������0������������ԭ��ֵ
void _cs149_vlt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vlt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// ������ͨ�����ڼ���״̬���Ƚ�veca��vecb��Ӧͨ��ֵ��veca==vecb������ͨ����1��������0������������ԭ��ֵ
void _cs149_veq_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_veq_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// ������Ԫ�ؽ������ڳɶ���ͣ�ʾ��������[0 1 2 3] �� ���[0+1 0+1 2+3 2+3]
void _cs149_hadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// ִ��������ż���������ż����������0��ʼ��Ԫ���Ƶ�ǰ�벿�֣���������Ԫ���Ƶ���벿��
// ʾ��������[0 1 2 3 4 5 6 7] �� ���[0 2 4 6 1 3 5 7]
void _cs149_interleave_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// ����Զ�����־�����ڸ�������
void addUserLog(const char * logStr);

#endif
