__kernel void adder(__global const float* a, __global const float* b, __global float* result)
{
	int idx = get_global_id(0);
	float i = 0;

	/////////////////
	for (int ab = 0; ab < 100; ab++) {///////////////1�ڻῨ����10�ڻ���ʱ�Ժ���
		i =  ab;
	}
	/////////////////

	result[idx] = a[idx] + b[idx];//////////////////

	//printf("STEP_GLOBAL_FINAL f:[%f] \n", i);


}
