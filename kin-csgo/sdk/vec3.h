#pragma once
#pragma warning( push )
#pragma warning( disable : 4244 )
#include <limits>

#define CHECK_VALID(_v) 0

template< typename T >
T clip_number( const T& n, const T& lower, const T& upper ) {
    if ( n < lower )
        return lower;
    if ( n > upper )
        return upper;
    return n;
}

namespace game {
    class vec3_t {
    public:
        vec3_t( void ) {
            invalidate( );
        }

        vec3_t( float X, float Y, float Z ) {
            x = X;
            y = Y;
            z = Z;
        }

        vec3_t( const float* clr ) {
            x = clr[ 0 ];
            y = clr[ 1 ];
            z = clr[ 2 ];
        }

        void init( float ix = 0.0f, float iy = 0.0f, float iz = 0.0f ) {
            x = ix;
            y = iy;
            z = iz;
        }

        void invalidate( ) {
            x = y = z = std::numeric_limits< float >::infinity( );
        }

        float& operator[]( int i ) {
            return ( ( float* )this )[ i ];
        }

        float operator[]( int i ) const {
            return ( ( float* )this )[ i ];
        }

        void zero( ) {
            x = y = z = 0.0f;
        }

        bool operator==( const vec3_t& src ) const {
            return ( src.x == x ) && ( src.y == y ) && ( src.z == z );
        }

        bool operator!=( const vec3_t& src ) const {
            return ( src.x != x ) || ( src.y != y ) || ( src.z != z );
        }

        vec3_t& operator+=( const vec3_t& v ) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        vec3_t& operator+=( const float& v ) {
            x += v;
            y += v;
            z += v;
            return *this;
        }

        vec3_t& operator+( const float& v ) {
            x = x + v;
            y = y + v;
            z = z + v;
            return *this;
        }

        vec3_t& operator-( const float& v ) {
            x = x - v;
            y = y - v;
            z = z - v;
            return *this;
        }

        vec3_t& operator-=( const vec3_t& v ) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        vec3_t& operator*=( float fl ) {
            x *= fl;
            y *= fl;
            z *= fl;
            return *this;
        }

        vec3_t& operator*=( const vec3_t& v ) {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        vec3_t& operator/=( const vec3_t& v ) {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        vec3_t& operator+=( float fl ) {
            x += fl;
            y += fl;
            z += fl;
            return *this;
        }

        vec3_t& operator/=( float fl ) {
            x /= fl;
            y /= fl;
            z /= fl;
            return *this;
        }

        vec3_t& operator-=( float fl ) {
            x -= fl;
            y -= fl;
            z -= fl;
            return *this;
        }

        void normalize( ) {
            *this /= length( );
        }

        float distance( const vec3_t& vOther ) const {
            vec3_t delta;

            delta.x = x - vOther.x;
            delta.y = y - vOther.y;
            delta.z = z - vOther.z;

            return delta.length( );
        }

        vec3_t normalized( ) const {
            vec3_t vec = *this;
            vec.normalize( );
            return vec;
        }

        float dist_to_sqr( const vec3_t& vOther ) const {
            vec3_t delta;

            delta.x = x - vOther.x;
            delta.y = y - vOther.y;
            delta.z = z - vOther.z;

            return delta.length_sqr( );
        }

        float dot( const vec3_t& vOther ) const {
            return ( x * vOther.x + y * vOther.y + z * vOther.z );
        }

        vec3_t cross_product( const vec3_t& a, const vec3_t& b ) const {
            return vec3_t( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x );
        }

        vec3_t cross( const vec3_t& vOther ) const {
            return cross_product( *this, vOther );
        }

        float length( ) const {
            return sqrt( x * x + y * y + z * z );
        }

        float length_sqr( void ) const {
            return ( x * x + y * y + z * z );
        }

        float length_2d( ) const {
            return sqrt( x * x + y * y );
        }

        vec3_t& operator=( const vec3_t& vOther ) {
            x = vOther.x;
            y = vOther.y;
            z = vOther.z;
            return *this;
        }

        vec3_t operator-( void ) const {
            return vec3_t( -x, -y, -z );
        }

        vec3_t operator+( const vec3_t& v ) const {
            return vec3_t( x + v.x, y + v.y, z + v.z );
        }

        vec3_t operator-( const vec3_t& v ) const {
            return vec3_t( x - v.x, y - v.y, z - v.z );
        }

        vec3_t operator*( float fl ) const {
            return vec3_t( x * fl, y * fl, z * fl );
        }

        vec3_t operator*( const vec3_t& v ) const {
            return vec3_t( x * v.x, y * v.y, z * v.z );
        }

        vec3_t operator/( float fl ) const {
            return vec3_t( x / fl, y / fl, z / fl );
        }

        vec3_t operator/( const vec3_t& v ) const {
            return vec3_t( x / v.x, y / v.y, z / v.z );
        }

        float normalize_l( ) {
            vec3_t res = *this;
            float length = res.length( );
            if ( length != 0.0f )
                res /= length;
            else
                res.x = res.y = res.z = 0.0f;
            return length;
        }

        vec3_t clamp( ) {
            if ( this->x < -89.0f )
                this->x = -89.0f;

            if ( this->x > 89.0f )
                this->x = 89.0f;

            while ( this->y < -180.0f )
                this->y += 360.0f;

            while ( this->y > 180.0f )
                this->y -= 360.0f;

            this->z = 0.0f;

            return *this;
        }

        float x, y, z;

        void normalize_angles( ) {
            auto x_rev = this->x / 360.f;

            if ( this->x > 180.f || this->x < -180.f ) {
                x_rev = abs( x_rev );
                x_rev = round( x_rev );

                if ( this->x < 0.f )
                    this->x = ( this->x + 360.f * x_rev );

                else
                    this->x = ( this->x - 360.f * x_rev );
            }

            auto y_rev = this->y / 360.f;
            if ( this->y > 180.f || this->y < -180.f ) {
                y_rev = abs( y_rev );
                y_rev = round( y_rev );

                if ( this->y < 0.f )
                    this->y = ( this->y + 360.f * y_rev );

                else
                    this->y = ( this->y - 360.f * y_rev );
            }

            auto z_rev = this->z / 360.f;
            if ( this->z > 180.f || this->z < -180.f ) {
                z_rev = abs( z_rev );
                z_rev = round( z_rev );

                if ( this->z < 0.f )
                    this->z = ( this->z + 360.f * z_rev );

                else
                    this->z = ( this->z - 360.f * z_rev );
            }
        }
    };
}
#pragma warning( pop )
