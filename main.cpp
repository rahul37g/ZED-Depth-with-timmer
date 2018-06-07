#include <iostream>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <sl/Camera.hpp>

using namespace sl;

int main(int argc, char **argv) {
	
	// Create a ZED camera object
	Camera zed;

	// Set configuration parameters
	InitParameters init_params;
	
	// Set camera resolution to 1080HD with 30 @fps
	init_params.camera_resolution = RESOLUTION_HD1080;
	
	// Use PERFORMANCE depth mode
	init_params.depth_mode = DEPTH_MODE_PERFORMANCE; 
	
	// Use Meter units (for depth measurements)
	init_params.coordinate_units = UNIT_METER; 

	
	// Open the camera
	ERROR_CODE err = zed.open(init_params);
	if (err != SUCCESS)
		exit(-1);

	// Set runtime parameters after opening the camera
	RuntimeParameters runtime_parameters;
	// Use STANDARD sensing mode
	runtime_parameters.sensing_mode = SENSING_MODE_STANDARD; 

	// Capture 100 images and depth, then stop
	int i = 0;
	sl::Mat image, depth, point_cloud;

	while (i < 100) {
		// A new image is available if grab() returns SUCCESS
		if (zed.grab(runtime_parameters) == SUCCESS) {
			
			// Retrieve left image
			zed.retrieveImage(image, VIEW_LEFT);
			
			// Start Time count
			auto start = std::chrono::system_clock::now();
			
			// Retrieve depth map. Depth is aligned on the left image
			zed.retrieveMeasure(depth, MEASURE_DEPTH);
			
			// Retrieve colored point cloud. Point cloud is aligned on the left image.
			zed.retrieveMeasure(point_cloud, MEASURE_XYZRGBA);
			
			// Get and print distance value in m at the center of the image
			// We measure the distance camera - object using Euclidean distance
			int x = image.getWidth() / 2;
			int y = image.getHeight() / 2;
			sl::float4 point_cloud_value;
			point_cloud.getValue(x, y, &point_cloud_value);
			float distance = sqrt(point_cloud_value.x * point_cloud_value.x + point_cloud_value.y * point_cloud_value.y + point_cloud_value.z * point_cloud_value.z);
			
			// Stop Time count
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = (end-start)*1000;
			std::time_t end_time = std::chrono::system_clock::to_time_t(end);
			
			// Diplay the result of Distance and Time.
			printf("Distance to Camera at (%d, %d): %f meter\n", x, y, distance);
			printf("finished computation at %s \n", std::ctime(&end_time));
			printf("elapsed time: %f ms \n", elapsed_seconds.count());

			// Increment the loop
			i++;
		}
	}
	// Close the camera
	zed.close();
	
	return 0;
}
