//#ifndef TRANSFORMNODE_H
//#define TRANSFORMNODE_H

//#include "../system/object.h"
//#include "../math/mat4.h"
//#include "../math/vec3.h"
//#include "../math/quat.h"

//namespace Scene
//{
//    class TransformNode : public System::CompoundObject
//    {
//    public:
//        TransformNode(TransformNode* parent = nullptr);
//        TransformNode(const TransformNode&) = delete;
//        TransformNode& operator = (const TransformNode&) = delete;
//        virtual ~TransformNode();

//        void ObjectIndex(unsigned value);
//        unsigned ObjectIndex() const;

//        void Position(const Math::vec3& value);
//        const Math::vec3& Position() const;
//        Math::vec3& Position();

//        void Rotation(const Math::quat& value);
//        const Math::quat& Rotation() const;
//        Math::quat& Rotation();

//        void Scale(const Math::vec3& value);
//        const Math::vec3& Scale() const;
//        Math::vec3& Scale();

//        const Math::mat4 ToMatrix() const;
//        const Math::mat3 ToRotationMatrix() const;

//        const Math::vec3 Transform(const Math::vec3& value) const;
//        const Math::vec3 InversedTransform(const Math::vec3& value) const;

//        void Name(const Core::String& value);
//        const Core::String& Name() const;

//        void EntityName(const Core::String& value);
//        const Core::String& EntityName() const;

//        virtual const Core::String ToString() const override;

//    private:
//        Core::String m_name;
//        Core::String m_entity_name;
//        TransformNode* m_parent;
//        unsigned m_index;
//        Math::vec3 m_position;
//        Math::quat m_rotation;
//        Math::vec3 m_scale;

//        PUNK_OBJECT(TransformNode)
//    };
//}

//#endif // TRANSFORMNODE_H
