#pragma once

#include <limits>
#include <cassert>
#include <algorithm>

class ZBuffer
{
public:
    struct Plane
    {
        float A, B, C, D;
    };
    Plane plane;
    
	ZBuffer( int width,int height )
		:
		width( width ),
		height( height ),
		pBuffer( new float[width*height] )
	{}
	~ZBuffer()
	{
		delete[] pBuffer;
		pBuffer = nullptr;
	}
	ZBuffer( const ZBuffer& ) = delete;
	ZBuffer& operator=( const ZBuffer& ) = delete;
	void Clear()
	{
		const int nDepths = width * height;
		for( int i = 0; i < nDepths; i++ )
		{
			// pBuffer[i] = std::numeric_limits<float>::infinity();
			pBuffer[i] = std::numeric_limits<float>::infinity();
		}
	}
	float& At( int x,int y )
	{
		assert( x >= 0 );
		assert( x < width );
		assert( y >= 0 );
		assert( y < height );
		return pBuffer[y * width + x];
	}
	const float& At( int x,int y ) const
	{
		return const_cast<ZBuffer*>(this)->At( x,y );
	}
	bool TestAndSet( int x,int y,float depth )
	{
		float& depthInBuffer = At( x,y );
		if( depth < depthInBuffer )
		{
			depthInBuffer = depth;
			return true;
		}
		return false;
	}
	int GetWidth() const
	{
		return width;
	}
	int GetHeight() const
	{
		return height;
	}
	auto GetMinMax() const
	{
		return std::minmax_element( pBuffer,pBuffer + width * height );
	}

    void makePlaneEquation(glMath::vec3f p1, glMath::vec3f p2, glMath::vec3f p3)
    {
        glMath::vec3f f1 = p2 - p1;
        glMath::vec3f f2 = p3 - p1;
        f1 = glMath::cross<float>(f1, f2);
        float val = f1.dotProduct(p1);
        // if(p1.x==1 and p1.y==2 and p1.z==-2){
        //     std::cout<<"------------DEBUG plane eqn------------"<<std::endl;
        //     std::cout<<f1.x<<" "<<f1.y<<" "<<f1.z<<" "<<-val<<std::endl;
        //     std::cout<<"------------DEBUG plane eqn end------------"<<std::endl;
        //     return;
        // }
        plane.A = f1.x;
        plane.B = f1.y;
        plane.C = f1.z;
        plane.D = -val;
    }
    float returnZ(int x, int y)
    {
        float val = -plane.D - plane.A * x - plane.B * y;
        val = val * (1 / plane.C);
        return -val;
    }

private:
	int width;
	int height;
	float* pBuffer = nullptr;
};