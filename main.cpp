/*
// Standard includes

#include <stdio.h>

#include <string.h>



// ZED include

#include <sl/Camera.hpp>



// OpenCV include (for display)

#include <opencv2/opencv.hpp>



// Using std and sl namespaces

using namespace std;

using namespace sl;



// Sample functions

void updateCameraSettings(char key, sl::Camera &zed);

void switchCameraSettings();

void printHelp();



// Sample variables

CAMERA_SETTINGS camera_settings_ = CAMERA_SETTINGS_BRIGHTNESS;

string str_camera_settings = "BRIGHTNESS";

int step_camera_setting = 1;





int main(int argc, char **argv) {



	// Create a ZED Camera object

	Camera zed;



	// Open the camera

	ERROR_CODE err = zed.open();

	if (err != SUCCESS) {

		cout << toString(err) << endl;

		zed.close();

		return 1; // Quit if an error occurred

	}



	// Print help in console

	printHelp();



	// Print camera information

	printf("ZED Model                 : %s\n", toString(zed.getCameraInformation().camera_model).c_str());

	printf("ZED Serial Number         : %d\n", zed.getCameraInformation().serial_number);

	printf("ZED Firmware              : %d\n", zed.getCameraInformation().firmware_version);

	printf("ZED Camera Resolution     : %dx%d\n", (int)zed.getResolution().width, (int)zed.getResolution().height);

	printf("ZED Camera FPS            : %d\n", (int)zed.getCameraFPS());



	// Create a Mat to store images

	Mat zed_image;



	// Capture new images until 'q' is pressed

	char key = ' ';

	while (key != 'q') {



		// Check that grab() is successful

		if (zed.grab() == SUCCESS) {

			// Retrieve left image

			zed.retrieveImage(zed_image, VIEW_RIGHT);



			// Display image with OpenCV
			//zed_image = rgb2gray
			cv::imshow("VIEW", cv::Mat((int)zed_image.getHeight(), (int)zed_image.getWidth(), CV_8UC4, zed_image.getPtr<sl::uchar1>(sl::MEM_CPU)));

			key = cv::waitKey(5);



			// Change camera settings with keyboard

			updateCameraSettings(key, zed);

		}
		else

			key = cv::waitKey(5);

	}



	// Exit

	zed.close();

	return EXIT_SUCCESS;

}





//This function updates camera settings



void updateCameraSettings(char key, sl::Camera &zed) {

	int current_value;



	// Keyboard shortcuts

	switch (key) {



		// Switch to the next camera parameter

	case 's':

		switchCameraSettings();

		break;



		// Increase camera settings value ('+' key)

	case '+':

		current_value = zed.getCameraSettings(camera_settings_);

		zed.setCameraSettings(camera_settings_, current_value + step_camera_setting);

		std::cout << str_camera_settings << ": " << current_value + step_camera_setting << std::endl;

		break;



		// Decrease camera settings value ('-' key)

	case '-':

		current_value = zed.getCameraSettings(camera_settings_);

		if (current_value >= 1) {

			zed.setCameraSettings(camera_settings_, current_value - step_camera_setting);

			std::cout << str_camera_settings << ": " << current_value - step_camera_setting << std::endl;

		}

		break;



		// Reset to default parameters

	case 'r':

		std::cout << "Reset all settings to default" << std::endl;

		zed.setCameraSettings(sl::CAMERA_SETTINGS_BRIGHTNESS, -1, true);

		zed.setCameraSettings(sl::CAMERA_SETTINGS_CONTRAST, -1, true);

		zed.setCameraSettings(sl::CAMERA_SETTINGS_HUE, -1, true);

		zed.setCameraSettings(sl::CAMERA_SETTINGS_SATURATION, -1, true);

		zed.setCameraSettings(sl::CAMERA_SETTINGS_GAIN, -1, true);

		zed.setCameraSettings(sl::CAMERA_SETTINGS_EXPOSURE, -1, true);

		zed.setCameraSettings(sl::CAMERA_SETTINGS_WHITEBALANCE, -1, true);

		break;

	}

}





//This function toggles between camera settings



void switchCameraSettings() {

	step_camera_setting = 1;

	switch (camera_settings_) {

	case CAMERA_SETTINGS_BRIGHTNESS:

		camera_settings_ = CAMERA_SETTINGS_CONTRAST;

		str_camera_settings = "Contrast";

		std::cout << "Camera Settings: CONTRAST" << std::endl;

		break;



	case CAMERA_SETTINGS_CONTRAST:

		camera_settings_ = CAMERA_SETTINGS_HUE;

		str_camera_settings = "Hue";

		std::cout << "Camera Settings: HUE" << std::endl;

		break;



	case CAMERA_SETTINGS_HUE:

		camera_settings_ = CAMERA_SETTINGS_SATURATION;

		str_camera_settings = "Saturation";

		std::cout << "Camera Settings: SATURATION" << std::endl;

		break;



	case CAMERA_SETTINGS_SATURATION:

		camera_settings_ = CAMERA_SETTINGS_GAIN;

		str_camera_settings = "Gain";

		std::cout << "Camera Settings: GAIN" << std::endl;

		break;



	case CAMERA_SETTINGS_GAIN:

		camera_settings_ = CAMERA_SETTINGS_EXPOSURE;

		str_camera_settings = "Exposure";

		std::cout << "Camera Settings: EXPOSURE" << std::endl;

		break;



	case CAMERA_SETTINGS_EXPOSURE:

		camera_settings_ = CAMERA_SETTINGS_WHITEBALANCE;

		str_camera_settings = "White Balance";

		step_camera_setting = 100;

		std::cout << "Camera Settings: WHITE BALANCE" << std::endl;

		break;



	case CAMERA_SETTINGS_WHITEBALANCE:

		camera_settings_ = CAMERA_SETTINGS_BRIGHTNESS;

		str_camera_settings = "Brightness";

		std::cout << "Camera Settings: BRIGHTNESS" << std::endl;

		break;

	}

}





//This function displays help



void printHelp() {

	cout << endl;

	cout << endl;

	cout << "Camera controls hotkeys: " << endl;

	cout << "  Increase camera settings value:            '+'" << endl;

	cout << "  Decrease camera settings value:            '-'" << endl;

	cout << "  Toggle camera settings:                    's'" << endl;

	cout << "  Reset all parameters:                      'r'" << endl;

	cout << endl;

	cout << "Exit : 'q'" << endl;

	cout << endl;

	cout << endl;

	cout << endl;

}

**/

#include <iostream>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <sl/Camera.hpp>

using namespace sl;

int main(int argc, char **argv) {
	
	//auto start = std::chrono::system_clock::now();
	
	// Create a ZED camera object
	Camera zed;

	// Set configuration parameters
	InitParameters init_params;
	init_params.camera_resolution = RESOLUTION_HD1080;
	init_params.depth_mode = DEPTH_MODE_PERFORMANCE; // Use PERFORMANCE depth mode
	init_params.coordinate_units = UNIT_METER; // Use meter units (for depth measurements)


	
// Open the camera
	ERROR_CODE err = zed.open(init_params);
	if (err != SUCCESS)
		exit(-1);

	// Set runtime parameters after opening the camera
	RuntimeParameters runtime_parameters;
	runtime_parameters.sensing_mode = SENSING_MODE_STANDARD; // Use STANDARD sensing mode

	// Capture 50 images and depth, then stop
	int i = 0;
	sl::Mat image, depth, point_cloud;

	while (i < 50) {
		// A new image is available if grab() returns SUCCESS
		if (zed.grab(runtime_parameters) == SUCCESS) {
			// Retrieve left image
			zed.retrieveImage(image, VIEW_LEFT);
			auto start = std::chrono::system_clock::now();
			// Retrieve depth map. Depth is aligned on the left image
			zed.retrieveMeasure(depth, MEASURE_DEPTH);
			// Retrieve colored point cloud. Point cloud is aligned on the left image.
			zed.retrieveMeasure(point_cloud, MEASURE_XYZRGBA);
			// Get and print distance value in mm at the center of the image
			// We measure the distance camera - object using Euclidean distance
			int x = image.getWidth() / 2;
			int y = image.getHeight() / 2;
			sl::float4 point_cloud_value;
			point_cloud.getValue(x, y, &point_cloud_value);
			float distance = sqrt(point_cloud_value.x * point_cloud_value.x + point_cloud_value.y * point_cloud_value.y + point_cloud_value.z * point_cloud_value.z);
			
			// Timer count
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

