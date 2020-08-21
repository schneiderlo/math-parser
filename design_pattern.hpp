#ifndef DESIGN_PATTERN_HPP
#define DESIGN_PATTERN_HPP

#include "library.hpp"

/**
 * @brief Prototype class
 *
 * Directly taken from developpez.com
 */
 
template <class T> class Prototype
{
public:
    virtual ~Prototype() {}        
    virtual T* clone() const = 0 ;
};



/** ********************************************************** **/

/**
 * @brief Factory class
 *
 * Factorised object must inherit from Prototype
 */

template <class Object, class Key = std::string> class Factory
{
public:
    static void Register( Key key, Object* obj );
    Object* create( const Key& key );
	
private:
    static std::map<Key,Object*> m_map;
};


// Static variable initialization
template <class Object, class Key> std::map<Key, Object*> Factory<Object,Key>::m_map = std::map<Key, Object*> ();

// object registration 
template <class Object, class Key> void Factory<Object, Key>::Register( Key key, Object* obj )
{
    if( m_map.find( key ) == m_map.end() )
    {
        m_map[key] = obj;
    }
}


// Creation of an instance of an object
template <class Object, class Key> Object* Factory<Object, Key>::create( const Key &key )
{
    Object* tmp=0;
    typename std::map<Key, Object*>::iterator it = m_map.find( key );

    if( it != m_map.end() )
    {
        tmp = ((*it).second)->clone();
    }

    return tmp;
}


/** ********************************************************** **/
#endif // SP_FACTORY_HPP
