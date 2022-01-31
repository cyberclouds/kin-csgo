#pragma once

#include "vec3.h"

namespace game {
    class matrix3x4_t {

    public:
        matrix3x4_t( ) {}

        matrix3x4_t(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23 ) {
            m_flMatVal[ 0 ][ 0 ] = m00;
            m_flMatVal[ 0 ][ 1 ] = m01;
            m_flMatVal[ 0 ][ 2 ] = m02;
            m_flMatVal[ 0 ][ 3 ] = m03;
            m_flMatVal[ 1 ][ 0 ] = m10;
            m_flMatVal[ 1 ][ 1 ] = m11;
            m_flMatVal[ 1 ][ 2 ] = m12;
            m_flMatVal[ 1 ][ 3 ] = m13;
            m_flMatVal[ 2 ][ 0 ] = m20;
            m_flMatVal[ 2 ][ 1 ] = m21;
            m_flMatVal[ 2 ][ 2 ] = m22;
            m_flMatVal[ 2 ][ 3 ] = m23;
        }

        //-----------------------------------------------------------------------------
        // Creates a matrix where the X axis = forward
        // the Y axis = left, and the Z axis = up
        //-----------------------------------------------------------------------------
        void Init( const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis, const vec3_t& vecOrigin ) {
            m_flMatVal[ 0 ][ 0 ] = xAxis.x;
            m_flMatVal[ 0 ][ 1 ] = yAxis.x;
            m_flMatVal[ 0 ][ 2 ] = zAxis.x;
            m_flMatVal[ 0 ][ 3 ] = vecOrigin.x;
            m_flMatVal[ 1 ][ 0 ] = xAxis.y;
            m_flMatVal[ 1 ][ 1 ] = yAxis.y;
            m_flMatVal[ 1 ][ 2 ] = zAxis.y;
            m_flMatVal[ 1 ][ 3 ] = vecOrigin.y;
            m_flMatVal[ 2 ][ 0 ] = xAxis.z;
            m_flMatVal[ 2 ][ 1 ] = yAxis.z;
            m_flMatVal[ 2 ][ 2 ] = zAxis.z;
            m_flMatVal[ 2 ][ 3 ] = vecOrigin.z;
        }

        //-----------------------------------------------------------------------------
        // Creates a matrix where the X axis = forward
        // the Y axis = left, and the Z axis = up
        //-----------------------------------------------------------------------------
        matrix3x4_t( const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis, const vec3_t& vecOrigin ) {
            Init( xAxis, yAxis, zAxis, vecOrigin );
        }

        void SetOrigin( const vec3_t& p ) {
            m_flMatVal[ 0 ][ 3 ] = p.x;
            m_flMatVal[ 1 ][ 3 ] = p.y;
            m_flMatVal[ 2 ][ 3 ] = p.z;
        }

        void Invalidate( void ) {
            for ( int i = 0; i < 3; i++ ) {
                for ( int j = 0; j < 4; j++ ) {
                    m_flMatVal[ i ][ j ] = std::numeric_limits< float >::infinity( );
                }
            }
        }

        vec3_t GetXAxis( ) const {
            return at( 0 );
        }

        vec3_t GetYAxis( ) const {
            return at( 1 );
        }

        vec3_t GetZAxis( ) const {
            return at( 2 );
        }

        vec3_t GetOrigin( ) const {
            return at( 3 );
        }

        vec3_t at( int i ) const {
            return vec3_t{ m_flMatVal[ 0 ][ i ], m_flMatVal[ 1 ][ i ], m_flMatVal[ 2 ][ i ] };
        }

        float* operator[]( int i ) {
            return m_flMatVal[ i ];
        }

        const float* operator[]( int i ) const {
            return m_flMatVal[ i ];
        }

        float* Base( ) {
            return &m_flMatVal[ 0 ][ 0 ];
        }

        const float* Base( ) const {
            return &m_flMatVal[ 0 ][ 0 ];
        }

        float m_flMatVal[ 3 ][ 4 ];
    };

    class v_matrix {

    public:
        v_matrix( );
        v_matrix(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33
        );

        // Creates a matrix where the X axis = forward
        // the Y axis = left, and the Z axis = up
        v_matrix( const vec3_t& forward, const vec3_t& left, const vec3_t& up );

        // Construct from a 3x4 matrix
        v_matrix( const matrix3x4_t& matrix3x4 );

        // Set the values in the matrix.
        void Init(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33
        );

        // Initialize from a 3x4
        void Init( const matrix3x4_t& matrix3x4 );

        // array access
        float* operator[]( int i ) {
            return m[ i ];
        }

        const float* operator[]( int i ) const {
            return m[ i ];
        }

        // Get a pointer to m[0][0]
        float* Base( ) {
            return &m[ 0 ][ 0 ];
        }

        const float* Base( ) const {
            return &m[ 0 ][ 0 ];
        }

        void SetLeft( const vec3_t& vLeft );
        void SetUp( const vec3_t& vUp );
        void SetForward( const vec3_t& vForward );

        void GetBasisvec3_ts( vec3_t& vForward, vec3_t& vLeft, vec3_t& vUp ) const;
        void SetBasisvec3_ts( const vec3_t& vForward, const vec3_t& vLeft, const vec3_t& vUp );

        // Get/Set the translation.
        vec3_t& GetTranslation( vec3_t& vTrans ) const;
        void SetTranslation( const vec3_t& vTrans );

        void PreTranslate( const vec3_t& vTrans );
        void PostTranslate( const vec3_t& vTrans );

        matrix3x4_t& As3x4( );
        const matrix3x4_t& As3x4( ) const;
        void CopyFrom3x4( const matrix3x4_t& m3x4 );
        void Set3x4( matrix3x4_t& matrix3x4 ) const;

        bool operator==( const v_matrix& src ) const;

        bool operator!=( const v_matrix& src ) const {
            return !( *this == src );
        }

        // Access the basis vec3_ts.
        vec3_t GetLeft( ) const;
        vec3_t GetUp( ) const;
        vec3_t GetForward( ) const;
        vec3_t GetTranslation( ) const;

        // Matrix->vec3_t operations.
    public:
        // Multiply by a 3D vec3_t (same as operator*).
        void V3Mul( const vec3_t& vIn, vec3_t& vOut ) const;

        // Multiply by a 4D vec3_t.
        //void  V4Mul( const vec3_t4D &vIn, vec3_t4D &vOut ) const;

        // Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
        vec3_t ApplyRotation( const vec3_t& vVec ) const;

        // Multiply by a vec3_t (divides by w, assumes input w is 1).
        vec3_t operator*( const vec3_t& vVec ) const;

        // Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
        vec3_t VMul3x3( const vec3_t& vVec ) const;

        // Apply the inverse (transposed) rotation (only works on pure rotation matrix)
        vec3_t VMul3x3Transpose( const vec3_t& vVec ) const;

        // Multiply by the upper 3 rows.
        vec3_t VMul4x3( const vec3_t& vVec ) const;

        // Apply the inverse (transposed) transformation (only works on pure rotation/translation)
        vec3_t VMul4x3Transpose( const vec3_t& vVec ) const;

        // Matrix->plane operations.
        //public:
        // Transform the plane. The matrix can only contain translation and rotation.
        //void  TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

        // Just calls TransformPlane and returns the result.
        //VPlane  operator*(const VPlane &thePlane) const;

        // Matrix->matrix operations.
    public:
        v_matrix& operator=( const v_matrix& mOther );

        // Add two matrices.
        const v_matrix& operator+=( const v_matrix& other );

        // Add/Subtract two matrices.
        v_matrix operator+( const v_matrix& other ) const;
        v_matrix operator-( const v_matrix& other ) const;

        // Negation.
        v_matrix operator-( ) const;

        // Return inverse matrix. Be careful because the results are undefined 
        // if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
        v_matrix operator~( ) const;

        // Matrix operations.
    public:
        // Set to identity.
        void Identity( );
        bool IsIdentity( ) const;
    public:
        // The matrix.
        float m[ 4 ][ 4 ];
    };
}
