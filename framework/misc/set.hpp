//============================================================================//
// This source file is part of work done by Reinder Nijhoff (reinder@infi.nl) //
// For the latest info, see http://developer.infi.nl                          //
//                                                                            //
// You're free to use the code in any way you like, modified, unmodified or   //
// cut'n'pasted into your own work.                                           //
//                                                                            //
// Part of this source is based on work by:                                   //
//    - Humus (http://esprit.campus.luth.se/~humus/)                          //
//    - Paul Baker (http://www.paulsprojects.net)                             //
//============================================================================//

#ifndef  _SET_
#define  _SET_ 1

#include <stdlib.h>
#include <string.h>

//==============================================================================
//  Set
//==============================================================================
template <class TYPE>
class Set {
public:
  Set() {
    m_count = m_capasity = 0;
    m_list = NULL;
  }

  Set(const unsigned int new_capasity) {
    m_count = 0;
    m_capasity = new_capasity;
    m_list = (TYPE *) malloc(m_capasity * sizeof(TYPE));
  }

  ~Set() {
    free(m_list);
  }

  TYPE *get_array() const { return m_list; }
  TYPE &operator [] (const unsigned int index) const { return m_list[index]; }
  TYPE &get_index(int j) const { return m_list[j]; }

  unsigned int size() const { return m_count; }

  void resize(const unsigned int new_count){
    m_capasity = m_count = new_count;
    m_list = (TYPE *) realloc(m_list, m_capasity * sizeof(TYPE));
  }

  unsigned int add(const TYPE object){
    if (m_count >= m_capasity){
      if (m_capasity) {
        m_capasity += m_capasity;
      } else {
        m_capasity = 8;
      }
      m_list = (TYPE *) realloc(m_list, m_capasity * sizeof(TYPE));
    }
    m_list[m_count] = object;
    return m_count++;
  }

  void remove(const unsigned int index){
    if (index < m_count) {
      --m_count;
      m_list[index] = m_list[m_count];
    }
  }

  void ordered_remove(const unsigned int index){
    if (index < m_count){
      --m_count;
      memmove(m_list + index, m_list + index + 1, (m_count - index) * sizeof(TYPE));
    }
  }

  void remove_object(const TYPE object){
    for (unsigned int i = 0; i < m_count; i++){
      if (object == m_list[i]){
        remove(i);
        return;
      }
    }
  }

  void clear() {
    m_count = 0;
  }

  void reset() {
    free(m_list);
    m_list = NULL;
    m_count = m_capasity = 0;
  }
private:
protected:
  unsigned int m_capasity;
  unsigned int m_count;
  TYPE * m_list;
};

#endif /* _SET_ */

