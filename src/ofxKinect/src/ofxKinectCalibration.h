/*
 * ofxKinectCalibration.h
 *
 *  Created on: 03/01/2011
 *      Author: arturo
 */

#ifndef OFXKINECTCALIBRATION_H_
#define OFXKINECTCALIBRATION_H_

#include "ofMain.h"
#include "ofxVectorMath.h"

class ofxKinectCalibration {
public:
	ofxKinectCalibration();
	virtual ~ofxKinectCalibration();

	void init(int _bytespp);
	void update(unsigned short * depth);
	void clear();

	/**
		set the near value of the pixels in the greyscale depth image to white?

		bEnabled = true : pixels close to the camera are brighter
		bEnabled = false: pixels closer to the camera are darker (default)
	**/
	void enableDepthNearValueWhite(bool bEnabled=true);
	bool isDepthNearValueWhite();


	ofxPoint2f getCalibratedColorCoordAt(int x, int y);
	ofxPoint2f getCalibratedColorCoordAt(const ofPoint & p);

	/// calculates the coordinate in the world for the pixel (perspective calculation). Center  of image is (0.0)
	ofxPoint3f getWorldCoordinateFor(int x, int y);
	ofxPoint3f getWorldCoordinateFor(int x, int y, double z);


	float getDistanceAt(int x, int y);
	float getDistanceAt(const ofPoint & p);


	unsigned char 	* getDepthPixels();		// grey scale values
	/// get the distance in centimeters to a given point
	float* getDistancePixels();
	// get the rgb pixels corrected to match the depth frame
	unsigned char * getCalibratedRGBPixels(unsigned char * rgb);

	const static int	width = 640;
	const static int	height = 480;
private:
	static void calculateLookups();
	static bool lookupsCalculated;
	static float distancePixelsLookup[2048];
	static unsigned char depthPixelsLookupNearWhite[2048];
	static unsigned char depthPixelsLookupFarWhite[2048];
	ofxVec3f T_rgb;
	ofxMatrix4x4 R_rgb;
	static double fx_d;
	static double fy_d;
	static double cx_d;
	static double cy_d;
	static double fx_rgb;
	static double fy_rgb;
	static double cx_rgb;
	static double cy_rgb;


	float * 				distancePixels;
	unsigned char *			depthPixels;
	unsigned char *			calibratedRGBPixels;

	bool bDepthNearValueWhite;

	int					bytespp;
};

#endif /* OFXKINECTCALIBRATION_H_ */
