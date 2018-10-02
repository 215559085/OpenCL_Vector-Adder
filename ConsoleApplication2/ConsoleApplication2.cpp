// OpenCL_Starter.cpp : 
//


#include "stdafx.h"
#include "CL\cl.h"
#include <vector>
#include <fstream>
#include <string> 
//#pragma warning( disable : 4996 )//因在Intel中OpenCL版本为1.2，无法使用Create Command Queque
#define DATA_SIZE  100

using namespace std;


void CL_Errores(cl_int errNum) {
	switch (errNum) {
		/*

CL_SUCCESS　命令成功执行，没有出现错误

CL_DEVICE_NOT_FOUND　未发现与条件匹配的OpenCL设备

CL_DEVICE_NOT_AVAILABLE　OpenCL设备目前不可用

CL_COMPILER_NOT_AVAILABLE　程序由源代码创建，不过没有可用的OpenCL C编译器

CL_MEM_OBJECT_ALLOCATION_FAILURE　无法为内存对象或图像对象分配内存

CL_OUT_OF_RESOURCES　没有足够的资源执行命令

CL_OUT_OF_HOST_MEMORY　宿主机上没有足够的内存执行命令

CL_PROFILING_INFO_NOT_AVAILABLE　无法得到事件的性能评测信息或者命令队列不支持性能评测

CL_MEM_COPY_OVERLAP　两个缓冲区在同一个内存区域重叠

CL_IMAGE_FORMAT_MISMATCH　图像未采用相同的图像格式

CL_IMAGE_FORMAT_NOT_SUPPORTED　不支持指定的图像格式

CL_BUILD_PROGRAM_FAILURE　无法为程序构建可执行代码

CL_MAP_FAILURE　内存区域无法映射到宿主机内存

CL_INVALID_VALUE　命令的一个或多个参数指定了非法值

CL_INVALID_DEVICE_TYPE　传入的设备类型不是合法值

CL_INVALID_PLATFORM　传入的平台不是合法值

CL_INVALID_DEVICE　传入的设备不是合法值

CL_INVALID_CONTEXT　传入的上下文不是合法值

CL_INVALID_QUEUE_PROPERTIES　设备不支持命令队列属性

CL_INVALID_COMMAND_QUEUE　传入的命令队列不是合法值

CL_INVALID_HOST_PTR　宿主机指针不合法

CL_INVALID_MEM_OBJECT　传入的内存对象不是合法值

CL_INVALID_IMAGE_FORMAT_DESCRIPTOR　传入的图像格式描述符不是合法值

CL_INVALID_IMAGE_SIZE　设备不支持这个图像大小

CL_INVALID_SAMPLER　传入的采样工具不是合法值

CL_INVALID_BINARY　传入了非法的二进制程序

CL_INVALID_BUILD_OPTIONS　一个或多个构建选项不合法

CL_INVALID_PROGRAM　传入的程序不是合法值

CL_INVALID_PROGRAM_EXECUTABLE　程序未能成功地构建命令队列关联设备上的一个可执行程序

CL_INVALID_KERNEL_NAME　程序中不存在指定的内核

CL_INVALID_KERNEL_DEFINITION　程序源代码中定义的内核不合法

CL_INVALID_KERNEL　传入的内核不是合法值

CL_INVALID_ARG_INDEX　参数索引指示的参数对于内核不合法

CL_INVALID_ARG_VALUE 　对于一个非局部参数，内核参数值为NULL；或者对于一个局部参数，内核参数值为非NULL

CL_INVALID_ARG_SIZE　参数大小与内核参数不一致

CL_INVALID_KERNEL_ARGS　一个或多个内核参数未赋值

CL_INVALID_WORK_DIMENSION　工作维度值不是介于1～3的一个值

CL_INVALID_WORK_GROUP_SIZE　局部或全局工作组大小不合法

CL_INVALID_WORK_ITEM_SIZE　一个或多个工作项大小超出了设备支持的最大大小

CL_INVALID_GLOBAL_OFFSET　全局偏移量超出了所支持的界限

CL_INVALID_EVENT_WAIT_LIST　提供的等待列表大小不合法或者其中包含非事件

CL_INVALID_EVENT　传入的事件不是一个合法值

CL_INVALID_OPERATION　执行命令导致出现一个不合法的操作

CL_INVALID_GL_OBJECT　OpenGL引用的对象存在问题

CL_INVALID_BUFFER_SIZE　指定的缓冲区大小越界

CL_INVALID_MIP_LEVEL　为OpenGL纹理指定的mipmap级别对于OpenGL对象不合法

CL_INVALID_GLOBAL_WORK_SIZE　传入的全局工作大小不合法，可能为0或者超出了设备支持的大小*/
	}

}

////////控制台打印OpenCL设备信息，缓存大小，支持的拓展功能，设备名称，生产商，平台版本
cl_uint CL_printf_PlatformInformation(){

	cl_platform_id *platforms;
	int CL_Version = 1.2;
	cl_uint num_platforms;
	cl_int i, err, platform_index = -1, errNum;
	char* ext_data;
	size_t ext_size;
	const char icd_ext[] = "cl_khr_icd";
	char *name, *vendor, *version, *profile;
	/////////////////////设备信息获取
	//get platform numbers
	//err = clGetPlatformIDs(0, 0, &num_platforms);
	err = clGetPlatformIDs(5, NULL, &num_platforms);
	if (err < 0)
	{
		perror("Couldn't find any platforms.");
		exit(1);
	}
	printf("本机上支持OpenCL的环境数量: %d\n", num_platforms);

	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id)*num_platforms);
	clGetPlatformIDs(num_platforms, platforms, NULL);

	for (i = 0; i < num_platforms; i++) {
		////缓存大小
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 0, NULL, &ext_size);
		if (err < 0) {
			printf("无法读取缓存大小数据");
			exit(1);
		}
		printf("缓存大小为 %d \n", ext_size);

		ext_data = (char*)malloc(ext_size);
		////支持的拓展功能
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, ext_size, ext_data, NULL);
		printf("支持的拓展功能：\n %s \n", ext_data);
		////名称
		name = (char*)malloc(ext_size);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, ext_size, name, NULL);
		printf("显卡名称为：%s \n", name);
		free(name);
		////生产商
		vendor = (char*)malloc(ext_size);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, ext_size, vendor, NULL);
		printf("显卡生产商: %s \n", vendor);
		free(vendor);
		////平台版本
		version = (char*)malloc(ext_size);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, ext_size, version, NULL);
		printf("平台版本: %s \n", version);
		free(version);
		////独立显卡or集成显卡？？
		profile = (char*)malloc(ext_size);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, ext_size, profile, NULL);
		printf("独立or集成: %s \n", profile);
		free(profile);
		//...等
	}
	return num_platforms;
}

/////取得CL_deviceID,用于构建program。
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


//////取得设备总数
cl_int CL_getPlatformNums() {
	cl_int err;
	cl_uint num_platforms;

	err = clGetPlatformIDs(5, NULL, &num_platforms);
	if (err < 0)
	{
		perror("Couldn't find any platforms.");
		return err;
	}
	printf("本机上支持OpenCL的环境数量: %d\n", num_platforms);
	return (cl_int)num_platforms;
}

void CL_creatContext() {


}


/////利用第PlatformID个设备创建一个OpenCL上下文
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

/////创建一个OpenCL消息队列
cl_command_queue CL_createCqueue(cl_context context) {
	size_t deviceBufferSize = -1;
	cl_int errNum;

	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &deviceBufferSize);
	cl_device_id *deviceID = new cl_device_id[deviceBufferSize / sizeof(cl_device_id)];
	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, deviceBufferSize, deviceID, NULL);

	cl_command_queue cqueue = clCreateCommandQueue(context, deviceID[0], 0, NULL);

	return cqueue;

}

/////创建一个CL program用于clBuildProgram，目前集成于kernel方法内
//cl_program CL_createProgram() {
//
//}

/////创建一个kernel
cl_kernel CL_createKernel(cl_context context, cl_uint cluint, cl_device_id* devices, const char* sourceFileName, const char* kernelName) {
	ifstream in(sourceFileName, std::ios_base::binary);
	if (!in.good()) {
		return 0;
	}
	
	// 取得.cl文件
	in.seekg(0, std::ios_base::end);
	size_t length = in.tellg();
	in.seekg(0, std::ios_base::beg);

	// 读取.cl源码
	std::vector<char> data(length + 1);
	in.read(&data[0], length);
	data[length] = 0;

	// 创建程序并编译
	const char* source = &data[0];

	cl_program program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);

	clBuildProgram(program, cluint, devices, NULL, NULL, NULL);

	cl_kernel kernel1 = clCreateKernel(program, kernelName, NULL);
	return kernel1;

}


//////////////////////打扫
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
	int platformID = 0;//指定第N+1个设备

	CL_printf_PlatformInformation();
	int platFormNum = CL_getPlatformNums();

	if (platformID+1 > platFormNum) {
		printf("指定设备不存在");
			exit(1);
	}

	context = CL_createContextFromPlatfromIDs(platformID);
	cl_device_id *devices = getCl_device_id(platformID);
	//cqueue = clCreateCommandQueue(context, *devices, 0, 0);
	cqueue = CL_createCqueue(context);

	cl_kernel adder;
	adder = CL_createKernel(context, platformID+1, devices, "kernel_1.cl", "adder");//CL_createKernel(context,第N个设备，devices...


////////////创建一堆数据，用于导入kernel
	float c = 1;
	float a[DATA_SIZE];
	float b[DATA_SIZE];
	//float res[DATA_SIZE];
	for (int i = 0; i < DATA_SIZE; i++) {
		a[i] = i;
		b[i] = i;
	}
	////////////////创建OpenCL设备缓存区块
		cl_mem cl_a = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * DATA_SIZE, a, NULL);
		cl_mem cl_b = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * DATA_SIZE, b, NULL);
		cl_mem cl_res = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_float) * DATA_SIZE, NULL, NULL);
		//////////////////传递数据
		clSetKernelArg(adder, 0, sizeof(cl_mem), &cl_a);
		clSetKernelArg(adder, 1, sizeof(cl_mem), &cl_b);
		clSetKernelArg(adder, 2, sizeof(cl_mem), &cl_res);
		//////////////////两项运算参数，目前可知的是globalWorkSize既传入数据大小，localWorkSize既运算维度(相关数学问题)
		size_t globalWorkSize[1] = { DATA_SIZE };
		size_t localWorkSize[1] = { 1 };
		err = clEnqueueNDRangeKernel(cqueue, adder, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
		if (err < 0) {
			printf("Culculate Error : clEnqueueNDRangeKernel \n");
		}
		//////////////////取出结果

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
		for (int ab = 0; ab < 1000; ab++) {/////注意，1亿，非自动int64，会错误
			ib =  ab + ab;
		}
		printf("result : %f \n", ib);
		//printf("result : %f \n", res[0]);
/////////////打扫战场  program未打扫
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

