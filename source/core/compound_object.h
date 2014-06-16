//#ifndef _H_PUNK_SYSTEM_COMPOUND_OBJECT
//#define _H_PUNK_SYSTEM_COMPOUND_OBJECT

//#include <map>
//#include "object.h"

//PUNK_ENGINE_BEGIN
//namespace Core {

//    class PUNK_ENGINE_API Object
//    {
//    public:
//        Object(Object* parent = nullptr);
//        Object(const CompoundObject&) = delete;
//        Object& operator = (const CompoundObject&) = delete;
//        virtual const String ToString() const;
//        virtual ~CompoundObject();

//        bool AddChild(Object* object);

//        bool Remove(Object* object, bool depth = false);
//        bool Remove(int index);

//        Object* Find(int index);
//        const Object* Find(int index) const;

//    public:
//        typedef std::vector<Object*> CollectionType;
//        typedef CollectionType::iterator iterator;
//        typedef CollectionType::const_iterator const_iterator;

//        iterator begin() { return m_children.begin(); }
//        const_iterator begin() const { return m_children.begin(); }
//        iterator end() { return m_children.end(); }
//        const_iterator end() const { return m_children.end(); }
//        void erase(iterator it) { m_children.erase(it); }
//        void clear() { m_children.clear(); }

//    private:
//        CollectionType m_children;
//    };


//    /**
//      * if child had parent, it will be replaced, and from
//      * previous parent child will be removed
//      */
//    void PUNK_ENGINE_API Bind(CompoundObject* parent, Object* child);
//}
//PUNK_ENGINE_END

//#endif	//	_H_PUNK_SYSTEM_COMPOUND_OBJECT
