#pragma once
struct Vector3
{
	float x, y, z;

	
	bool operator==( const Vector3& bb ) const
	{
		return (this->x == bb.x && this->y == bb.y && this->z == bb.z);
	}
	Vector3 operator+(const Vector3& bb) const
	{
		return {this->x + bb.x, this->y + bb.y, this->z + bb.z} ;
	}
	Vector3 operator-(const Vector3& bb) const
	{
		return { this->x - bb.x, this->y - bb.y, this->z - bb.z };
	}
	Vector3 operator/(const Vector3& bb) const
	{
		return { this->x / bb.x, this->y / bb.y, this->z / bb.z };
	}
	Vector3 operator/(const float& bb) const
	{
		return { this->x / bb, this->y / bb, this->z / bb };
	}

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	Vector3(float _x,float _y,float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
		Vector3(float _val)
	{
		x = _val;
		y = _val;
		z = _val;
	}
};
struct Vector2
{
	float x, y;
		Vector2()
	{
		x = 0;
		y = 0;
	}
Vector2(float _x,float _y)
	{
		x = _x;
		y = _y;

	}	Vector2(float _val)
	{
		x = _val;
		y = _val;

	}
};

struct Matrix4x4
{

	float m[4][4];
};
struct Matrix3x4
{
	float m[3][4];
};
