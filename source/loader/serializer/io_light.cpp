//#include <attributes/light/idirectional_light.h>
//#include <attributes/light/ipoint_light.h>
//#include <attributes/light/ispot_light.h>
//#include "io_vector.h"
//#include "io_object.h"
//#include "io_light.h"
//
//PUNK_ENGINE_BEGIN
//namespace Loader {
//
//    void SaveLight(Core::Buffer* buffer, const Core::IObject* object)
//    {
//        SaveObject(buffer, object);
//    }
//
//    void LoadLight(Core::Buffer* buffer, Core::IObject* object)
//    {
//        LoadObject(buffer, object);
//    }
//
//    void SavePointLight(Core::Buffer *buffer, const Core::IObject *o)
//    {
//        SaveLight(buffer, o);
//        const Attributes::PointLight* p = Cast<const Attributes::PointLight*>(o);
//        SaveVector3f(buffer, p->GetPosition());
//        SaveVector3f(buffer, p->GetColor());
//        buffer->WriteReal32(p->GetDistance());
//        buffer->WriteReal32(p->GetEnergy());
//        buffer->WriteReal32(p->GetLinearAttenuation());
//        buffer->WriteReal32(p->GetQuadraticAttenuation());
//    }
//
//    void LoadPointLight(Core::Buffer *buffer, Core::IObject *o)
//    {
//        SaveLight(buffer, o);
//        Attributes::PointLight* p = Cast<Attributes::PointLight*>(o);
//
//        Math::vec3 position;
//        LoadVector3f(buffer, position);
//        p->SetPosition(position);
//
//        Math::vec3 color;
//        LoadVector3f(buffer, color);
//        p->SetColor(color);
//
//        p->SetDistance(buffer->ReadReal32());
//        p->SetEnergy(buffer->ReadReal32());
//        p->SetLinearAttenuation(buffer->ReadReal32());
//        p->SetQuadraticAttenuation(buffer->ReadReal32());
//    }
//
//    //	bool LightSet::Save(std::ostream& stream) const
//    //	{
//    //		IObject::Save(stream);
//    //		return true;
//    //	}
//
//    //	bool LightSet::Load(std::istream& stream)
//    //	{
//    //		IObject::Load(stream);
//    //		return true;
//    //	}
//
//    //	LightSet* LightSet::CreateFromStream(std::istream& stream)
//    //	{
//    //		std::unique_ptr<LightSet> res(new LightSet);
//    //		res->Load(stream);
//    //		return res.release();
//    //	}
//
//    //	PointLight* PointLight::CreateFromFile(const Core::String& path)
//    //	{
//    //		std::ifstream stream(path.ToStdString().c_str(), std::ios::binary);
//    //		if (!stream.is_open())
//    //			throw System::PunkInvalidArgumentException(L"Can't open file " + path);
//    //		return CreateFromStream(stream);
//    //	}
//
//    //	PointLight* PointLight::CreateFromStream(std::istream& stream)
//    //	{
//    //		std::unique_ptr<PointLight> node(new PointLight);
//    //		node->Load(stream);
//    //		return node.release();
//    //	}
//
//    void SaveDirectionalLight(Core::Buffer *buffer, const Core::IObject *o)
//    {
//        SaveLight(buffer, o);
//        const Attributes::DirectionalLight* l = Cast<const Attributes::DirectionalLight*>(o);
//        SaveVector3f(buffer, l->GetDirection());
//        SaveVector3f(buffer, l->GetColor());
//        buffer->WriteReal32(l->GetDistance());
//        buffer->WriteReal32(l->GetEnergy());
//    }
//
//    void LoadDirectionalLight(Core::Buffer *buffer, Core::IObject *o)
//    {
//        LoadLight(buffer, o);
//        Attributes::DirectionalLight* l = Cast<Attributes::DirectionalLight*>(o);
//
//        Math::vec3 direction;
//        LoadVector3f(buffer, direction);
//        l->SetDirection(direction);
//
//        Math::vec3 color;
//        LoadVector3f(buffer, color);
//        l->SetColor(color);
//
//        l->SetDistance(buffer->ReadReal32());
//        l->SetEnergy(buffer->ReadReal32());
//    }
//
//
//    void SaveSpotLight(Core::Buffer *buffer, const Core::IObject *o)
//    {
//        SaveLight(buffer, o);
//    }
//
//    void LoadSpotLight(Core::Buffer *buffer, Core::IObject *o)
//    {
//        LoadLight(buffer, o);
//    }
//}
//PUNK_ENGINE_END
