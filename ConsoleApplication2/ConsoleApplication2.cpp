// OpenCL_Starter.cpp : 
//


#include "stdafx.h"
#include "CL\cl.h"
#include <vector>
#include <fstream>
#include <string> 
//#pragma warning( disable : 4996 )//����Intel��OpenCL�汾Ϊ1.2���޷�ʹ��Create Command Queque
#define DATA_SIZE  100

using namespace std;


void CL_Errores(cl_int errNum) {
	switch (errNum) {
		/*

CL_SUCCESS������ɹ�ִ�У�û�г��ִ���

CL_DEVICE_NOT_FOUND��δ����������ƥ���OpenCL�豸

CL_DEVICE_NOT_AVAILABLE��OpenCL�豸Ŀǰ������

CL_COMPILER_NOT_AVAILABLE��������Դ���봴��������û�п��õ�OpenCL C������

CL_MEM_OBJECT_ALLOCATION_FAILURE���޷�Ϊ�ڴ�����ͼ���������ڴ�

CL_OUT_OF_RESOURCES��û���㹻����Դִ������

CL_OUT_OF_HOST_MEMORY����������û���㹻���ڴ�ִ������

CL_PROFILING_INFO_NOT_AVAILABLE���޷��õ��¼�������������Ϣ����������в�֧����������

CL_MEM_COPY_OVERLAP��������������ͬһ���ڴ������ص�

CL_IMAGE_FORMAT_MISMATCH��ͼ��δ������ͬ��ͼ���ʽ

CL_IMAGE_FORMAT_NOT_SUPPORTED����֧��ָ����ͼ���ʽ

CL_BUILD_PROGRAM_FAILURE���޷�Ϊ���򹹽���ִ�д���

CL_MAP_FAILURE���ڴ������޷�ӳ�䵽�������ڴ�

CL_INVALID_VALUE�������һ����������ָ���˷Ƿ�ֵ

CL_INVALID_DEVICE_TYPE��������豸���Ͳ��ǺϷ�ֵ

CL_INVALID_PLATFORM�������ƽ̨���ǺϷ�ֵ

CL_INVALID_DEVICE��������豸���ǺϷ�ֵ

CL_INVALID_CONTEXT������������Ĳ��ǺϷ�ֵ

CL_INVALID_QUEUE_PROPERTIES���豸��֧�������������

CL_INVALID_COMMAND_QUEUE�������������в��ǺϷ�ֵ

CL_INVALID_HOST_PTR��������ָ�벻�Ϸ�

CL_INVALID_MEM_OBJECT��������ڴ�����ǺϷ�ֵ

CL_INVALID_IMAGE_FORMAT_DESCRIPTOR�������ͼ���ʽ���������ǺϷ�ֵ

CL_INVALID_IMAGE_SIZE���豸��֧�����ͼ���С

CL_INVALID_SAMPLER������Ĳ������߲��ǺϷ�ֵ

CL_INVALID_BINARY�������˷Ƿ��Ķ����Ƴ���

CL_INVALID_BUILD_OPTIONS��һ����������ѡ��Ϸ�

CL_INVALID_PROGRAM������ĳ����ǺϷ�ֵ

CL_INVALID_PROGRAM_EXECUTABLE������δ�ܳɹ��ع���������й����豸�ϵ�һ����ִ�г���

CL_INVALID_KERNEL_NAME�������в�����ָ�����ں�

CL_INVALID_KERNEL_DEFINITION������Դ�����ж�����ں˲��Ϸ�

CL_INVALID_KERNEL��������ں˲��ǺϷ�ֵ

CL_INVALID_ARG_INDEX����������ָʾ�Ĳ��������ں˲��Ϸ�

CL_INVALID_ARG_VALUE ������һ���Ǿֲ��������ں˲���ֵΪNULL�����߶���һ���ֲ��������ں˲���ֵΪ��NULL

CL_INVALID_ARG_SIZE��������С���ں˲�����һ��

CL_INVALID_KERNEL_ARGS��һ�������ں˲���δ��ֵ

CL_INVALID_WORK_DIMENSION������ά��ֵ���ǽ���1��3��һ��ֵ

CL_INVALID_WORK_GROUP_SIZE���ֲ���ȫ�ֹ������С���Ϸ�

CL_INVALID_WORK_ITEM_SIZE��һ�������������С�������豸֧�ֵ�����С

CL_INVALID_GLOBAL_OFFSET��ȫ��ƫ������������֧�ֵĽ���

CL_INVALID_EVENT_WAIT_LIST���ṩ�ĵȴ��б��С���Ϸ��������а������¼�

CL_INVALID_EVENT��������¼�����һ���Ϸ�ֵ

CL_INVALID_OPERATION��ִ������³���һ�����Ϸ��Ĳ���

CL_INVALID_GL_OBJECT��OpenGL���õĶ����������

CL_INVALID_BUFFER_SIZE��ָ���Ļ�������СԽ��

CL_INVALID_MIP_LEVEL��ΪOpenGL����ָ����mipmap�������OpenGL���󲻺Ϸ�

CL_INVALID_GLOBAL_WORK_SIZE�������ȫ�ֹ�����С���Ϸ�������Ϊ0���߳������豸֧�ֵĴ�С*/
	}

}

////////����̨��ӡOpenCL�豸��Ϣ�������С��֧�ֵ���չ���ܣ��豸���ƣ������̣�ƽ̨�汾
cl_uint CL_printf_PlatformInformation(){

	cl_platform_id *platforms;
	int CL_Version = 1.2;
	cl_uint num_platforms;
	cl_int i, err, platform_index = -1, errNum;
	char* ext_data;
	size_t ext_size;
	const char icd_ext[] = "cl_khr_icd";
	char *name, *vendor, *version, *profile;
	/////////////////////�豸��Ϣ��ȡ
	//get platform numbers
	//err = clGetPlatformIDs(0, 0, &num_platforms);
	err = clGetPlatformIDs(5, NULL, &num_platforms);
	if (err < 0)
	{
		perror("Couldn't find any platforms.");
		exit(1);
	}
	printf("������֧��OpenCL�Ļ�������: %d\n", num_platforms);

	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id)*num_platforms);
	clGetPlatformIDs(num_platforms, platforms, NULL);

	for (i = 0; i < num_platforms; i++) {
		////�����С
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 0, NULL, &ext_size);
		if (err < 0) {
			printf("�޷���ȡ�����С����");
			exit(1);
		}
		printf("�����СΪ %d \n", ext_size);

		ext_data = (char*)malloc(ext_size);
		////֧�ֵ���չ����
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, ext_size, ext_data, NULL);
		printf("֧�ֵ���չ���ܣ�\n %s \n", ext_data);
		////����
		name = (char*)malloc(ext_size);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, ext_size, name, NULL);
		printf("�Կ�����Ϊ��%s \n", name);
		free(name);
		////������
		vendor = (char*)malloc(ext_size);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, ext_size, vendor, NULL);
		printf("�Կ�������: %s \n", vendor);
		free(vendor);
		////ƽ̨�汾
		version = (char*)malloc(ext_size);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, ext_size, version, NULL);
		printf("ƽ̨�汾: %s \n", version);
		free(version);
		////�����Կ�or�����Կ�����
		profile = (char*)malloc(ext_size);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, ext_size, profile, NULL);
		printf("����or����: %s \n", profile);
		free(profile);
		//...��
	}
	return num_platforms;
}

/////ȡ��CL_deviceID,���ڹ���program��
cl_device_id *getCl_device_id(int PlatformID)

{
	cl_platform_id *platforms;
	cl_uint num_platforms;
	clGetPlatformIDs(5, NULL, &num_platforms);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id)*num_platforms);
	clGetPlatformIDs(num_platforms, platforms, NULL);
    cl_uint numDevices = 0;
    cl_device_id *devices ;
    cl_int    status = clGetDeviceIDs(platforms[PlatformID], CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
    if (numDevices > 0) //GPU available.
   {
        devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
        status = clGetDeviceIDs(platforms[PlatformID], CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
    }
  return devices;
 }


//////ȡ���豸����
cl_int CL_getPlatformNums() {
	cl_int err;
	cl_uint num_platforms;

	err = clGetPlatformIDs(5, NULL, &num_platforms);
	if (err < 0)
	{
		perror("Couldn't find any platforms.");
		return err;
	}
	printf("������֧��OpenCL�Ļ�������: %d\n", num_platforms);
	return (cl_int)num_platforms;
}

void CL_creatContext() {


}


/////���õ�PlatformID���豸����һ��OpenCL������
cl_context CL_createContextFromPlatfromIDs(int PlatformID) {
	cl_platform_id *platforms;
	cl_uint num_platforms;
	cl_int err;
	err = clGetPlatformIDs(5, NULL, &num_platforms);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id)*num_platforms);
	clGetPlatformIDs(num_platforms, platforms, NULL);
	cl_context_properties prop[] = {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)platforms[PlatformID],
		0,
	};
	cl_context context = clCreateContextFromType(prop, CL_DEVICE_TYPE_GPU, NULL, NULL, &err);
	if (err < 0) {
		printf("Culculate Error :  clCreateContextFromType \n");
	}

	return context;
}

/////����һ��OpenCL��Ϣ����
cl_command_queue CL_createCqueue(cl_context context) {
	size_t deviceBufferSize = -1;
	cl_int errNum;

	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &deviceBufferSize);
	cl_device_id *deviceID = new cl_device_id[deviceBufferSize / sizeof(cl_device_id)];
	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, deviceBufferSize, deviceID, NULL);

	cl_command_queue cqueue = clCreateCommandQueue(context, deviceID[0], 0, NULL);

	return cqueue;

}

/////����һ��CL program����clBuildProgram��Ŀǰ������kernel������
//cl_program CL_createProgram() {
//
//}

/////����һ��kernel
cl_kernel CL_createKernel(cl_context context, cl_uint cluint, cl_device_id* devices, const char* sourceFileName, const char* kernelName) {
	ifstream in(sourceFileName, std::ios_base::binary);
	if (!in.good()) {
		return 0;
	}
	
	// ȡ��.cl�ļ�
	in.seekg(0, std::ios_base::end);
	size_t length = in.tellg();
	in.seekg(0, std::ios_base::beg);

	// ��ȡ.clԴ��
	std::vector<char> data(length + 1);
	in.read(&data[0], length);
	data[length] = 0;

	// �������򲢱���
	const char* source = &data[0];

	cl_program program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);

	clBuildProgram(program, cluint, devices, NULL, NULL, NULL);

	cl_kernel kernel1 = clCreateKernel(program, kernelName, NULL);
	return kernel1;

}


//////////////////////��ɨ
void Cleanup(cl_context context, cl_command_queue commandQueue,
	cl_program program, cl_kernel kernel)
{
	if (commandQueue != 0)
		clReleaseCommandQueue(commandQueue);

	if (kernel != 0)
		clReleaseKernel(kernel);

	if (program != 0)
		clReleaseProgram(program);

	if (context != 0)
		clReleaseContext(context);
}

int main()
{
	cl_platform_id *platforms;
	
	cl_uint num_platforms;
	cl_int  err, platform_index = -1,errNum;

	const char icd_ext[] = "cl_khr_icd";


    cl_context context;
    cl_command_queue cqueue;
	int platformID = 0;//ָ����N+1���豸

	CL_printf_PlatformInformation();
	int platFormNum = CL_getPlatformNums();

	if (platformID+1 > platFormNum) {
		printf("ָ���豸������");
			exit(1);
	}

	context = CL_createContextFromPlatfromIDs(platformID);
	cl_device_id *devices = getCl_device_id(platformID);
	//cqueue = clCreateCommandQueue(context, *devices, 0, 0);
	cqueue = CL_createCqueue(context);

	cl_kernel adder;
	adder = CL_createKernel(context, platformID+1, devices, "kernel_1.cl", "adder");//CL_createKernel(context,��N���豸��devices...


////////////����һ�����ݣ����ڵ���kernel
	float c = 1;
	float a[DATA_SIZE];
	float b[DATA_SIZE];
	//float res[DATA_SIZE];
	for (int i = 0; i < DATA_SIZE; i++) {
		a[i] = i;
		b[i] = i;
	}
	////////////////����OpenCL�豸��������
		cl_mem cl_a = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * DATA_SIZE, a, NULL);
		cl_mem cl_b = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * DATA_SIZE, b, NULL);
		cl_mem cl_res = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_float) * DATA_SIZE, NULL, NULL);
		//////////////////��������
		clSetKernelArg(adder, 0, sizeof(cl_mem), &cl_a);
		clSetKernelArg(adder, 1, sizeof(cl_mem), &cl_b);
		clSetKernelArg(adder, 2, sizeof(cl_mem), &cl_res);
		//////////////////�������������Ŀǰ��֪����globalWorkSize�ȴ������ݴ�С��localWorkSize������ά��(�����ѧ����)
		size_t globalWorkSize[1] = { DATA_SIZE };
		size_t localWorkSize[1] = { 1 };
		err = clEnqueueNDRangeKernel(cqueue, adder, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
		if (err < 0) {
			printf("Culculate Error : clEnqueueNDRangeKernel \n");
		}
		//////////////////ȡ�����

		float res2[DATA_SIZE];
		std::vector<float> res(DATA_SIZE);

		//err = clEnqueueReadBuffer(cqueue, cl_res, CL_TRUE, 0, sizeof(float) * DATA_SIZE, res, 0, NULL, NULL);
		err = clEnqueueReadBuffer(cqueue, cl_res, CL_TRUE, 1, sizeof(float) * DATA_SIZE, &res[0], 0, 0, 0);

		if (err < 0) {
			printf("Culculate Error : clEnqueueReadBuffer \n");
		}
		else {
			for (int i = 0; i < DATA_SIZE; i++) {
				printf("result : %i \n", res[i]);
			}
		}

		float ib = 0;
		for (int ab = 0; ab < 1000; ab++) {/////ע�⣬1�ڣ����Զ�int64�������
			ib =  ab + ab;
		}
		printf("result : %f \n", ib);
		//printf("result : %f \n", res[0]);
/////////////��ɨս��  programδ��ɨ
		Cleanup(context, cqueue, NULL, adder);
		clReleaseMemObject(cl_a);
		clReleaseMemObject(cl_b);
		clReleaseMemObject(cl_res);


	getchar();
	//get all platforms
	//vector<cl_platform_id> platforms(num);
	//err = clGetPlatformIDs(num, &platforms[0], &num);
    return 0;
}

