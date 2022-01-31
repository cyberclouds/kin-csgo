#include "matrix3x4.h"

//-----------------------------------------------------------------------------
// v_matrix inlines.
//-----------------------------------------------------------------------------
inline game::v_matrix::v_matrix( ) {}

inline game::v_matrix::v_matrix(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33 ) {
    Init(
        m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33
    );
}

inline game::v_matrix::v_matrix( const matrix3x4_t& matrix3x4 ) {
    Init( matrix3x4 );
}

//-----------------------------------------------------------------------------
// Creates a matrix where the X axis = forward
// the Y axis = left, and the Z axis = up
//-----------------------------------------------------------------------------
inline game::v_matrix::v_matrix( const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis ) {
    Init(
        xAxis.x, yAxis.x, zAxis.x, 0.0f,
        xAxis.y, yAxis.y, zAxis.y, 0.0f,
        xAxis.z, yAxis.z, zAxis.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

inline void game::v_matrix::Init(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
) {
    m[ 0 ][ 0 ] = m00;
    m[ 0 ][ 1 ] = m01;
    m[ 0 ][ 2 ] = m02;
    m[ 0 ][ 3 ] = m03;

    m[ 1 ][ 0 ] = m10;
    m[ 1 ][ 1 ] = m11;
    m[ 1 ][ 2 ] = m12;
    m[ 1 ][ 3 ] = m13;

    m[ 2 ][ 0 ] = m20;
    m[ 2 ][ 1 ] = m21;
    m[ 2 ][ 2 ] = m22;
    m[ 2 ][ 3 ] = m23;

    m[ 3 ][ 0 ] = m30;
    m[ 3 ][ 1 ] = m31;
    m[ 3 ][ 2 ] = m32;
    m[ 3 ][ 3 ] = m33;
}

//-----------------------------------------------------------------------------
// Initialize from a 3x4
//-----------------------------------------------------------------------------
inline void game::v_matrix::Init( const matrix3x4_t& matrix3x4 ) {
    memcpy( m, matrix3x4.Base( ), sizeof( matrix3x4_t ) );

    m[ 3 ][ 0 ] = 0.0f;
    m[ 3 ][ 1 ] = 0.0f;
    m[ 3 ][ 2 ] = 0.0f;
    m[ 3 ][ 3 ] = 1.0f;
}

//-----------------------------------------------------------------------------
// vec3_t3DMultiplyPosition treats src2 as if it's a point (adds the translation)
//-----------------------------------------------------------------------------
// NJS: src2 is passed in as a full vector rather than a reference to prevent the need
// for 2 branches and a potential copy in the body.  (ie, handling the case when the src2
// reference is the same as the dst reference ).
inline void vec3_t3DMultiplyPosition( const game::v_matrix& src1, const game::vec3_t& src2, game::vec3_t& dst ) {
    dst[ 0 ] = src1[ 0 ][ 0 ] * src2.x + src1[ 0 ][ 1 ] * src2.y + src1[ 0 ][ 2 ] * src2.z + src1[ 0 ][ 3 ];
    dst[ 1 ] = src1[ 1 ][ 0 ] * src2.x + src1[ 1 ][ 1 ] * src2.y + src1[ 1 ][ 2 ] * src2.z + src1[ 1 ][ 3 ];
    dst[ 2 ] = src1[ 2 ][ 0 ] * src2.x + src1[ 2 ][ 1 ] * src2.y + src1[ 2 ][ 2 ] * src2.z + src1[ 2 ][ 3 ];
}

//-----------------------------------------------------------------------------
// Methods related to the basis vectors of the matrix
//-----------------------------------------------------------------------------

inline game::vec3_t game::v_matrix::GetForward( ) const {
    return vec3_t( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ] );
}

inline game::vec3_t game::v_matrix::GetLeft( ) const {
    return vec3_t( m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ] );
}

inline game::vec3_t game::v_matrix::GetUp( ) const {
    return vec3_t( m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ] );
}

inline void game::v_matrix::SetForward( const vec3_t& vForward ) {
    m[ 0 ][ 0 ] = vForward.x;
    m[ 1 ][ 0 ] = vForward.y;
    m[ 2 ][ 0 ] = vForward.z;
}

inline void game::v_matrix::SetLeft( const vec3_t& vLeft ) {
    m[ 0 ][ 1 ] = vLeft.x;
    m[ 1 ][ 1 ] = vLeft.y;
    m[ 2 ][ 1 ] = vLeft.z;
}

inline void game::v_matrix::SetUp( const vec3_t& vUp ) {
    m[ 0 ][ 2 ] = vUp.x;
    m[ 1 ][ 2 ] = vUp.y;
    m[ 2 ][ 2 ] = vUp.z;
}

inline void game::v_matrix::GetBasisvec3_ts( vec3_t& vForward, vec3_t& vLeft, vec3_t& vUp ) const {
    vForward.init( m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ] );
    vLeft.init( m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ] );
    vUp.init( m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ] );
}

inline void game::v_matrix::SetBasisvec3_ts( const vec3_t& vForward, const vec3_t& vLeft, const vec3_t& vUp ) {
    SetForward( vForward );
    SetLeft( vLeft );
    SetUp( vUp );
}

//-----------------------------------------------------------------------------
// Methods related to the translation component of the matrix
//-----------------------------------------------------------------------------

inline game::vec3_t game::v_matrix::GetTranslation( ) const {
    return vec3_t( m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ] );
}

inline game::vec3_t& game::v_matrix::GetTranslation( vec3_t& vTrans ) const {
    vTrans.x = m[ 0 ][ 3 ];
    vTrans.y = m[ 1 ][ 3 ];
    vTrans.z = m[ 2 ][ 3 ];
    return vTrans;
}

inline void game::v_matrix::SetTranslation( const vec3_t& vTrans ) {
    m[ 0 ][ 3 ] = vTrans.x;
    m[ 1 ][ 3 ] = vTrans.y;
    m[ 2 ][ 3 ] = vTrans.z;
}

//-----------------------------------------------------------------------------
// appply translation to this matrix in the input space
//-----------------------------------------------------------------------------
inline void game::v_matrix::PreTranslate( const vec3_t& vTrans ) {
    vec3_t tmp;
    vec3_t3DMultiplyPosition( *this, vTrans, tmp );
    m[ 0 ][ 3 ] = tmp.x;
    m[ 1 ][ 3 ] = tmp.y;
    m[ 2 ][ 3 ] = tmp.z;
}

//-----------------------------------------------------------------------------
// appply translation to this matrix in the output space
//-----------------------------------------------------------------------------
inline void game::v_matrix::PostTranslate( const vec3_t& vTrans ) {
    m[ 0 ][ 3 ] += vTrans.x;
    m[ 1 ][ 3 ] += vTrans.y;
    m[ 2 ][ 3 ] += vTrans.z;
}

inline const game::matrix3x4_t& game::v_matrix::As3x4( ) const {
    return *( ( const matrix3x4_t* )this );
}

inline game::matrix3x4_t& game::v_matrix::As3x4( ) {
    return *( ( matrix3x4_t* )this );
}

inline void game::v_matrix::CopyFrom3x4( const matrix3x4_t& m3x4 ) {
    memcpy( m, m3x4.Base( ), sizeof( matrix3x4_t ) );
    m[ 3 ][ 0 ] = m[ 3 ][ 1 ] = m[ 3 ][ 2 ] = 0;
    m[ 3 ][ 3 ] = 1;
}

inline void game::v_matrix::Set3x4( matrix3x4_t& matrix3x4 ) const {
    memcpy( matrix3x4.Base( ), m, sizeof( matrix3x4_t ) );
}

//-----------------------------------------------------------------------------
// Matrix Math operations
//-----------------------------------------------------------------------------
inline const game::v_matrix& game::v_matrix::operator+=( const v_matrix& other ) {
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            m[ i ][ j ] += other.m[ i ][ j ];
        }
    }

    return *this;
}

inline game::v_matrix game::v_matrix::operator+( const v_matrix& other ) const {
    v_matrix ret;
    for ( int i = 0; i < 16; i++ ) {
        ( ( float* )ret.m )[ i ] = ( ( float* )m )[ i ] + ( ( float* )other.m )[ i ];
    }
    return ret;
}

inline game::v_matrix game::v_matrix::operator-( const v_matrix& other ) const {
    v_matrix ret;

    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            ret.m[ i ][ j ] = m[ i ][ j ] - other.m[ i ][ j ];
        }
    }

    return ret;
}

inline game::v_matrix game::v_matrix::operator-( ) const {
    v_matrix ret;
    for ( int i = 0; i < 16; i++ ) {
        ( ( float* )ret.m )[ i ] = -( ( float* )m )[ i ];
    }
    return ret;
}

//-----------------------------------------------------------------------------
// vec3_t transformation
//-----------------------------------------------------------------------------

inline game::vec3_t game::v_matrix::operator*( const vec3_t& vVec ) const {
    vec3_t vRet;
    vRet.x = m[ 0 ][ 0 ] * vVec.x + m[ 0 ][ 1 ] * vVec.y + m[ 0 ][ 2 ] * vVec.z + m[ 0 ][ 3 ];
    vRet.y = m[ 1 ][ 0 ] * vVec.x + m[ 1 ][ 1 ] * vVec.y + m[ 1 ][ 2 ] * vVec.z + m[ 1 ][ 3 ];
    vRet.z = m[ 2 ][ 0 ] * vVec.x + m[ 2 ][ 1 ] * vVec.y + m[ 2 ][ 2 ] * vVec.z + m[ 2 ][ 3 ];

    return vRet;
}

inline game::vec3_t game::v_matrix::VMul4x3( const vec3_t& vVec ) const {
    vec3_t vResult;
    vec3_t3DMultiplyPosition( *this, vVec, vResult );
    return vResult;
}

inline game::vec3_t game::v_matrix::VMul4x3Transpose( const vec3_t& vVec ) const {
    vec3_t tmp = vVec;
    tmp.x -= m[ 0 ][ 3 ];
    tmp.y -= m[ 1 ][ 3 ];
    tmp.z -= m[ 2 ][ 3 ];

    return vec3_t(
        m[ 0 ][ 0 ] * tmp.x + m[ 1 ][ 0 ] * tmp.y + m[ 2 ][ 0 ] * tmp.z,
        m[ 0 ][ 1 ] * tmp.x + m[ 1 ][ 1 ] * tmp.y + m[ 2 ][ 1 ] * tmp.z,
        m[ 0 ][ 2 ] * tmp.x + m[ 1 ][ 2 ] * tmp.y + m[ 2 ][ 2 ] * tmp.z
    );
}

inline game::vec3_t game::v_matrix::VMul3x3( const vec3_t& vVec ) const {
    return vec3_t(
        m[ 0 ][ 0 ] * vVec.x + m[ 0 ][ 1 ] * vVec.y + m[ 0 ][ 2 ] * vVec.z,
        m[ 1 ][ 0 ] * vVec.x + m[ 1 ][ 1 ] * vVec.y + m[ 1 ][ 2 ] * vVec.z,
        m[ 2 ][ 0 ] * vVec.x + m[ 2 ][ 1 ] * vVec.y + m[ 2 ][ 2 ] * vVec.z
    );
}

inline game::vec3_t game::v_matrix::VMul3x3Transpose( const vec3_t& vVec ) const {
    return vec3_t(
        m[ 0 ][ 0 ] * vVec.x + m[ 1 ][ 0 ] * vVec.y + m[ 2 ][ 0 ] * vVec.z,
        m[ 0 ][ 1 ] * vVec.x + m[ 1 ][ 1 ] * vVec.y + m[ 2 ][ 1 ] * vVec.z,
        m[ 0 ][ 2 ] * vVec.x + m[ 1 ][ 2 ] * vVec.y + m[ 2 ][ 2 ] * vVec.z
    );
}

inline void game::v_matrix::V3Mul( const vec3_t& vIn, vec3_t& vOut ) const {
    float rw;

    rw = 1.0f / ( m[ 3 ][ 0 ] * vIn.x + m[ 3 ][ 1 ] * vIn.y + m[ 3 ][ 2 ] * vIn.z + m[ 3 ][ 3 ] );
    vOut.x = ( m[ 0 ][ 0 ] * vIn.x + m[ 0 ][ 1 ] * vIn.y + m[ 0 ][ 2 ] * vIn.z + m[ 0 ][ 3 ] ) * rw;
    vOut.y = ( m[ 1 ][ 0 ] * vIn.x + m[ 1 ][ 1 ] * vIn.y + m[ 1 ][ 2 ] * vIn.z + m[ 1 ][ 3 ] ) * rw;
    vOut.z = ( m[ 2 ][ 0 ] * vIn.x + m[ 2 ][ 1 ] * vIn.y + m[ 2 ][ 2 ] * vIn.z + m[ 2 ][ 3 ] ) * rw;
}

//-----------------------------------------------------------------------------
// Other random stuff
//-----------------------------------------------------------------------------
inline void game::v_matrix::Identity( ) {
    m[ 0 ][ 0 ] = 1.0f;
    m[ 0 ][ 1 ] = 0.0f;
    m[ 0 ][ 2 ] = 0.0f;
    m[ 0 ][ 3 ] = 0.0f;
    m[ 1 ][ 0 ] = 0.0f;
    m[ 1 ][ 1 ] = 1.0f;
    m[ 1 ][ 2 ] = 0.0f;
    m[ 1 ][ 3 ] = 0.0f;
    m[ 2 ][ 0 ] = 0.0f;
    m[ 2 ][ 1 ] = 0.0f;
    m[ 2 ][ 2 ] = 1.0f;
    m[ 2 ][ 3 ] = 0.0f;
    m[ 3 ][ 0 ] = 0.0f;
    m[ 3 ][ 1 ] = 0.0f;
    m[ 3 ][ 2 ] = 0.0f;
    m[ 3 ][ 3 ] = 1.0f;
}

inline bool game::v_matrix::IsIdentity( ) const {
    return
            m[ 0 ][ 0 ] == 1.0f && m[ 0 ][ 1 ] == 0.0f && m[ 0 ][ 2 ] == 0.0f && m[ 0 ][ 3 ] == 0.0f &&
            m[ 1 ][ 0 ] == 0.0f && m[ 1 ][ 1 ] == 1.0f && m[ 1 ][ 2 ] == 0.0f && m[ 1 ][ 3 ] == 0.0f &&
            m[ 2 ][ 0 ] == 0.0f && m[ 2 ][ 1 ] == 0.0f && m[ 2 ][ 2 ] == 1.0f && m[ 2 ][ 3 ] == 0.0f &&
            m[ 3 ][ 0 ] == 0.0f && m[ 3 ][ 1 ] == 0.0f && m[ 3 ][ 2 ] == 0.0f && m[ 3 ][ 3 ] == 1.0f;
}

inline game::vec3_t game::v_matrix::ApplyRotation( const vec3_t& vVec ) const {
    return VMul3x3( vVec );
}
