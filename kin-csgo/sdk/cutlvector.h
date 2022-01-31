#pragma once

template< class T, class I = int >
class c_utl_memory {
public:
    T& operator[]( I i ) {
        return m_memory[ i ];
    }

    T* base( ) {
        return m_memory;
    }

    int num_allocated( ) const {
        return m_allocation_count;
    }

    bool is_externally_allocated( ) const {
        return m_grow_size < 0;
    }

protected:
    T* m_memory;
    int m_allocation_count;
    int m_grow_size;
};

template< class T >
T* construct( T* memory ) {
    return ::new( memory ) T;
}

template< class T >
void destruct( T* memory ) {
    memory->~T( );
}

template< class T, class A = c_utl_memory< T > >
class c_utl_vector {
    using c_allocator = A;
public:
    T& operator[]( int i ) {
        return m_memory[ i ];
    }

    T& element( int i ) {
        return m_memory[ i ];
    }

    T* base( ) {
        return m_memory.base( );
    }

    int count( ) const {
        return m_size;
    }

    void remove_all( ) {
        for ( int i = m_size; --i >= 0; )
            destruct( &element( i ) );

        m_size = 0;
    }

    int add_to_tail( ) {
        return insert_before( m_size );
    }

    void set_size( int size ) {
        m_size = size;
    }

    int insert_before( int elem ) {
        grow_vector( );
        shift_elements_right( elem );
        construct( &element( elem ) );

        return elem;
    }

protected:
    void grow_vector( int num = 1 ) {
        if ( m_size + num > m_memory.num_allocated( ) )
            m_memory.grow( m_size + num - m_memory.num_allocated( ) );

        m_size += num;
        reset_dbg_info( );
    }

    void shift_elements_right( int elem, int num = 1 ) {
        int num_to_move = m_size - elem - num;
        if ( ( num_to_move > 0 ) && ( num > 0 ) )
            memmove( &element( elem + num ), &element( elem ), num_to_move * sizeof( T ) );
    }

    c_allocator m_memory;
    int m_size;

    T* m_elements;

    void reset_dbg_info( ) {
        m_elements = base( );
    }
};
