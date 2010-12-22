/*
 * of3DVideo.h
 *
 *  Created on: 16/12/2010
 *      Author: arturo
 */

#ifndef OF3DVIDEO_H_
#define OF3DVIDEO_H_

class of3DVideo: public ofBaseVideo{
public:
	virtual unsigned char 	* getDepthPixels()=0;		// grey scale values
	virtual float* getDistancePixels()=0;
};

#endif /* OF3DVIDEO_H_ */
