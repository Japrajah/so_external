
#include "bw_math.hh"
#include <Windows.h>
#include <cfloat>



/**
 *	Constructor
 *	Defaults to the unset/inside out state
 */

inline BoundingBox::BoundingBox() 
{
	min_ = { FLT_MAX, FLT_MAX, FLT_MAX };
	max_ = {-FLT_MAX, -FLT_MAX, -FLT_MAX};
}

/**
 *	Constructor taking min and max
 */
inline BoundingBox::BoundingBox( const Vector3&  min, const Vector3&  max ) 
{
	    min_ = min;
		max_ = max;
}

/**
 *	This method tests if two bounding boxen are equal
 */
inline bool BoundingBox::operator==( const BoundingBox & bb ) const
{
	return (min_ == bb.min_) && (max_ == bb.max_); 
}

/**
 *	This method tests if two bounding boxen are not equal
 */
inline bool BoundingBox::operator!=( const BoundingBox & bb ) const
{
	return (min_ != bb.min_) || (max_ != bb.max_); 
}

/**
 *	This method gets the min bounds
 */
inline const Vector3 & BoundingBox::minBounds() const
{
//	MF_ASSERT_DEBUG( !this->insideOut() );

	return min_;
}

/**
 *	This method gets the max bounds
 */
inline const Vector3 & BoundingBox::maxBounds() const
{
	//MF_ASSERT_DEBUG( !this->insideOut() );

	return max_;
}

/**
 *	This method sets the bounds
 */
inline void BoundingBox::setBounds( const Vector3 & min, const Vector3 & max )
{
	min_ = min;
	max_ = max;
}


inline 	bool BoundingBox::insideOut() const
{
	return min_.x > max_.x || min_.y > max_.y || min_.z > max_.z;
}

/**
 *  This gets the width (x-direction) of the bounding box.
 */
inline float BoundingBox::width() const
{
	if (insideOut())
		return 0.0f;
	else
		return max_.x - min_.x;
}

/**
 *  This gets the height (y-direction) of the bounding box.
 */
inline float BoundingBox::height() const
{
	if (insideOut())
		return 0.0f;
	else
		return max_.y - min_.y;
}

/**
 *  This gets the depth (z-direction) of the bounding box.
 */
inline float BoundingBox::depth() const
{
	if (insideOut())
		return 0.0f;
	else
		return max_.z - min_.z;
}

inline void BoundingBox::addYBounds( float y )
{
	if( min_.y > y )
		min_.y = y;
	if( max_.y < y )
		max_.y = y;
}

/**
 *	This method expands the bounding box to contain the given point
 */
inline void BoundingBox::addBounds( const Vector3 & v )
{
	if( this->insideOut() )
	{
		min_ = v;
		max_ = v;
		return;
	}

	if (min_.x > v.x)
		min_.x = v.x;

	if (min_.y > v.y)
		min_.y = v.y;

	if (min_.z > v.z)
		min_.z = v.z;

	if (max_.x < v.x)
		max_.x = v.x;

	if (max_.y < v.y)
		max_.y = v.y;

	if (max_.z < v.z)
		max_.z = v.z;
}

/**
 * This method expands the bounding box by the given amounts in each direction.
 * Empty bounding boxes are left alone.  Offseting inwards too much can make, 
 * for example, min_.x > max_.x which in turns makes the box inside out as 
 * you'd expect.
 */
inline void BoundingBox::expandSymmetrically( float dx, float dy, float dz )
{
	if (!insideOut())
	{
		min_.x -= dx; min_.y -= dy; min_.z -= dz;
		max_.x += dx; max_.y += dy; max_.z += dz;
	}
}

/**
 * This method expands the bounding box by the given amounts in each direction.
 * Empty bounding boxes are left alone.  Offseting inwards too much can make, 
 * for example, min_.x > max_.x which in turns makes the box inside out as 
 * you'd expect.
 */
inline void BoundingBox::expandSymmetrically( const Vector3 & v )
{
	expandSymmetrically(v.x, v.y, v.z);
}

/**
 *	This method expands the bounding box to contain the given bounding box
 */
inline void BoundingBox::addBounds( const BoundingBox & bb )
{
	if( bb.insideOut() )
		return;

	if( this->insideOut() )
	{
		min_ = bb.min_;
		max_ = bb.max_;
		return;
	}

	if (min_.x > bb.min_.x)
		min_.x = bb.min_.x;

	if (min_.y > bb.min_.y)
		min_.y = bb.min_.y;

	if (min_.z > bb.min_.z)
		min_.z = bb.min_.z;

	if (max_.x < bb.max_.x)
		max_.x = bb.max_.x;

	if (max_.y < bb.max_.y)
		max_.y = bb.max_.y;

	if (max_.z < bb.max_.z)
		max_.z = bb.max_.z;
}


/**
 *	This inline function is used by BoundingBox::intersects
 */
inline bool intervalsIntersect( float min1, float max1, float min2, float max2 )
{
	return min2 <= max1 && min1 <= max2;
}

/**
 *	This method tests if two bounding boxen intersect
 */
inline bool BoundingBox::intersects( const BoundingBox & box ) const
{
	const Vector3 & min1 = this->min_;
	const Vector3 & max1 = this->max_;

	const Vector3 & min2 = box.min_;
	const Vector3 & max2 = box.max_;

	return(
		intervalsIntersect(min1.x, max1.x, min2.x, max2.x) &&
		intervalsIntersect(min1.y, max1.y, min2.y, max2.y) &&
		intervalsIntersect(min1.z, max1.z, min2.z, max2.z));
}


/**
 *	This method tests if the bounding box contains the given point
 */
inline bool BoundingBox::intersects( const Vector3 & v ) const
{
	return ( v.x >= min_.x ) && ( v.y >= min_.y ) && ( v.z >= min_.z ) &&
		   ( v.x <  max_.x ) && ( v.y <  max_.y ) && ( v.z <  max_.z );
}

/**
 *	This method tests if the bounding box enlarged by the given bias
 *	(in each dimension) contains the given point
 */
inline bool BoundingBox::intersects( const Vector3 &v, float bias ) const
{
	return ( v.x >= ( min_.x - bias ) ) && ( v.y >= ( min_.y - bias ) ) && ( v.z >= ( min_.z - bias ) ) &&
		   ( v.x <  ( max_.x + bias ) ) && ( v.y <  ( max_.y + bias ) ) && ( v.z <  ( max_.z + bias ) );
}


/**
 * The centre point of the bounding box
 */
inline Vector3 BoundingBox::centre() const
{
	//MF_ASSERT_DEBUG( !this->insideOut() );

	return (min_ + max_) / 2.f;
}




//boundbox.ipp
