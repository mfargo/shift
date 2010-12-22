/*
 * PCRenderer.cpp
 *
 *  Created on: 14/12/2010
 *      Author: arturo
 */

#include "PCRenderer.h"
#include "ofMain.h"
#include "VertexArray.h"

PCRenderer::PCRenderer() {
	depthThreshold 	= 1000;
	minDistance 	= -10;
	scaleFactor 	= .0021;
	oneInX=1;
	oneInY=1;
	mesh = false;
}

PCRenderer::~PCRenderer() {
	// TODO Auto-generated destructor stub
}


void PCRenderer::setup(){

}

void PCRenderer::update(float * vertexes, int w,int h){
	va.clear();
	/// 125
	/// 346
	float depth1,depth2,depth3;
	int inc=0;
	if(mesh) inc=2;
	for(int y=0; y<h; y+=mesh?1:oneInY){
		for(int x=0;x<w;x+=mesh?inc:oneInX){
			depth1 = *vertexes++;
			if(mesh){
				depth2 = *vertexes++;
				depth3 = *(vertexes+(w-2));
				if(fabs(depth1-depth2)>10 || fabs(depth1-depth3)>10 || fabs(depth2-depth3)>10 || depth1==0 || depth1>depthThreshold || depth2==0 || depth2>depthThreshold || depth3==0 || depth3>depthThreshold){
					continue;
				}
			}


			float depthFactor = (depth1 + minDistance) * scaleFactor;



			if(!mesh){
				if(x+oneInX<w)
					vertexes+=oneInX-1;
				else
					vertexes+=w-x-1;

				if(depth1==0 || depth1>depthThreshold) continue;

				va.addVertex((x),(y),-depth1);
			}else{

				va.addVertex((x),(y),-depth1);

				float depthFactor = (-depth2 + minDistance) * scaleFactor;
				va.addVertex((x+1),(y),-depth2);
				va.addVertex((x),(y+1),-depth3);

				float depth4 = *(vertexes+(w-1));
				if(fabs(depth2-depth4)<10 && fabs(depth3-depth4)<10){
					va.addVertex((x+1),(y),-depth2);
					va.addVertex((x+1),(y+1),-depth4);
					va.addVertex((x),(y+1),-depth3);
				}

				float depth5 = *(vertexes+1);
				if(fabs(depth2-depth5)<10 && fabs(depth5-depth4)<10){
					va.addVertex((x+1),(y),-depth2);
					va.addVertex((x+2),(y),-depth5);
					va.addVertex((x+1),(y+1),-depth4);
				}

				float depth6 = *(vertexes+w);
				if(fabs(depth5-depth6)<10 && fabs(depth6-depth4)<10){
					va.addVertex((x+2),(y),-depth5);
					va.addVertex((x+2),(y+1),-depth6);
					va.addVertex((x+1),(y+1),-depth4);
				}
			}
		}
		if(!mesh)
			vertexes += (oneInY-1)*w;
	}
}

void PCRenderer::update(float * vertexes, unsigned char* rgb, int w,int h){
	float depth;
	int inc;
	if(mesh) inc=2;
	else inc=1;
	for(int y=0; y<h; y+=inc){
		for(int x=0;x<w;x+=inc){
			depth = *vertexes++;
			if(depth!=0 && depth<depthThreshold){
				float depthFactor = (-depth + minDistance) * scaleFactor;
				va.addVertex((x) * depthFactor,(y) * depthFactor,depth,rgb[0],rgb[1],rgb[2]);
			}
			if(mesh){
				depth = *vertexes++;
				if(depth!=0 && depth<depthThreshold){
					float depthFactor = (-depth + minDistance) * scaleFactor;
					va.addVertex((x+1) * depthFactor,(y) * depthFactor,depth,rgb[0],rgb[1],rgb[2]);
				}
				depth = *(vertexes+(w-1));
				if(depth!=0 && depth<depthThreshold){
					float depthFactor = (-depth + minDistance) * scaleFactor;
					va.addVertex((x) * depthFactor,(y+1) * depthFactor,depth,rgb[0],rgb[1],rgb[2]);
				}
			}
			rgb+=3;
		}
	}
}

void PCRenderer::draw(ofTexture * tex){
	GLenum drawType;
	if(mesh) drawType = GL_TRIANGLES;
	else drawType = GL_POINTS;
	va.draw(drawType,tex);
}

void PCRenderer::setDepthThreshold(float depthThres){
	depthThreshold = depthThres;
}

void PCRenderer::setMinDistance(float _minDistance){
	minDistance = _minDistance;
}

void PCRenderer::setScaleFactor(float _scaleFactor){
	scaleFactor = _scaleFactor;
}

