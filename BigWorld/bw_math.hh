#pragma once
#include "Vectors.hh"

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox( const Vector3 & min, const Vector3 & max );

	bool operator==( const BoundingBox& bb ) const;
	bool operator!=( const BoundingBox& bb ) const;
	bool insideOut() const;
	const Vector3 & minBounds() const;
	const Vector3 & maxBounds() const;
	void setBounds( const Vector3 & min, const Vector3 & max );

    float width() const;
    float height() const;
    float depth() const;

	void addYBounds( float y );
	void addBounds( const Vector3 & v );
	void addBounds( const BoundingBox & bb );
    void expandSymmetrically( float dx, float dy, float dz );
    void expandSymmetrically( const Vector3 & v );
	void calculateOutcode( const Matrix4x4 & m ) const;    

	/*Outcode outcode() const;
	Outcode combinedOutcode() const;
	void outcode( Outcode oc );
	void combinedOutcode( Outcode oc );*/

	void transformBy( const Matrix4x4 & transform );

	bool intersects( const BoundingBox & box ) const;
	bool intersects( const Vector3 & v ) const;
	bool intersects( const Vector3 & v, float bias ) const;
	bool intersectsRay( const Vector3 & origin, const Vector3 & dir ) const;
	bool intersectsLine( const Vector3 & origin, const Vector3 & dest ) const;

	bool clip( Vector3 & start, Vector3 & extent, float bloat = 0.f ) const;

	float distance( const Vector3& point ) const;

	inline Vector3 centre() const;

	//INLINE bool insideOut() const;

private:
	Vector3 min_;
	Vector3 max_;
};