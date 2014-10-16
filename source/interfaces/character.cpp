#include "character.h"
#include "body.h"
#include "body_action.h"
#include "body_temperature.h"
#include "body_power.h"
#include "location.h"
#include "environment.h"
#include "time_dependent.h"

#include <math/matrix.h>
#include <math/tuple.h>

#ifdef USE_QT
#include <QGraphicsItem>
#include <QPainter>
#include <QMatrix>
#endif

PUNK_ENGINE_BEGIN

class Character :
        public IBody,
        public IBodyActions,
        public IBodyTemperature,
        public IBodyPower,
        #ifdef USE_QT
        public QGraphicsItem,
        #endif
        public ILocation,
        public ITimeDependent
{
public:

    ~Character() {

    }

    /// IObject
    void QueryInterface(const Core::Guid& type, void** object) override {
        if (!object)
            return;
        *object = nullptr;
        if (type == Core::IID_IObject) {
            *object = (IBody*)this;
            AddRef();
        }
        if (type == IID_IBody) {
            *object = (IBody*)this;
            AddRef();
        }
        if (type == IID_IBodyActions) {
            *object = (IBodyActions*)this;
            AddRef();
        }
        if (type == IID_IBodyTemperature) {
            *object = (IBodyTemperature*)this;
            AddRef();
        }
        if (type == IID_ITimeDependent) {
            *object = (ITimeDependent*)this;
            AddRef();
        }
        if (type == IID_ILocation) {
            *object = (ILocation*)this;
            AddRef();
        }
    }

    std::uint32_t AddRef() override {
        return m_ref_count.fetch_add(1);
    }

    std::uint32_t Release() override {
        auto v = m_ref_count.fetch_sub(1);
        if (!v) {
            delete this;
        }
        return v;
    }

    /// IBody
    std::double_t GetMass() const override {
        return m_mass;
    }

    void SetMass(std::double_t value) override {
        m_mass = value;
    }

    std::double_t GetStrength() const override {
        return m_muscles;
    }

    std::double_t GetRelativeStrength() const override {
        auto weight = GetMass();
        auto muscles = GetMuscle();
        auto result = muscles / weight * 100.0;
        return result;
    }

    std::double_t GetMuscle() const override {
        return m_muscles;
    }

    void SetMuscle(std::double_t value) override {
        m_muscles = value;
        auto mass = m_fat + m_muscles;
        SetMass(mass);
    }

    std::double_t GetFat() const override {
        return m_fat;
    }

    void SetFat(std::double_t value) override {
        m_fat = value;
        auto mass = m_fat + m_muscles;
        SetMass(mass);
    }

    BodyGender GetGender() const override {
        return m_gender;
    }

    void SetGender(BodyGender value) override {
        m_gender = value;
    }

    std::double_t GetHeatRadiationAbsorbingFactor() const override {
        //  todo: add some calculations
        return 0.6;
    }

    std::double_t GetWindProtectionFactor() const override {
        //  todo: add some calculations
        return 0.7;
    }

    std::double_t GetBodySurface() const override {
        //  todo: add some calculations
        return 2.5;
    }

    std::double_t GetSpecificHeat() const override {
        return m_specific_heat;
    }

    //  BodyActions
    std::list<IBodyAction*>* GetBodyActions() override {
        return m_body_actions.get();
    }

    std::list<IBodyAction*>* GetBodyActions() const override {
        return m_body_actions.get();
    }

    bool IsDoing(const Core::String& name) const override {
        return FindBodyAction(name) != nullptr;
    }

    const IBodyAction* FindBodyAction(const Core::String& name) const override {
        auto it = std::find_if(m_body_actions->begin(), m_body_actions->end(), [&name] (const IBodyAction* action)
        {
            if (action->GetActivityName() == name)
                return true;
            return false;
        });

        if (it == m_body_actions->end())
            return nullptr;
        return *it;
    }

    //  BodyTemperature
    std::double_t GetCurrentTemperature() const override {
        return m_current_temperature;
    }

    void SetCurrentTemperature(std::double_t value) override {
        m_current_temperature = value;
    }

    std::double_t GetNormalTemperature() const override {
        return m_normal_temperature;
    }

    void SetNormalTemeperature(std::double_t value) override {
        m_normal_temperature = value;
    }

    std::double_t GetMinimalTemperature() const override {
        return m_min_temperature;
    }

    void SetMinimalTemperature(std::double_t value) override {
        m_min_temperature = value;
    }

    std::double_t GetMaximalTemperature() const override {
        return m_max_temperature;
    }

    void SetMaximalTemperature(std::double_t value) override {
        m_max_temperature = value;
    }

    //  BodyPower
    std::double_t GetTotalConsumption() const override {

    }

    std::double_t GetMetabolismConstant() const override {
        return m_metabolism_constant;
    }

    std::double_t GetMetabolism() const override {
        auto activity_power = GetActivityTotalPowerConsumption();
        auto metabolism_power = GetBodySurface() * GetMetabolismConstant();
        auto result = activity_power + metabolism_power;
        return result;
    }

    std::double_t GetActivity() const override {

    }

    std::double_t GetActivityTotalPowerConsumption() const override {

    }

    std::double_t GetExaporative() const override {

    }

    std::double_t GetHeatConvection() const override {

    }

    std::double_t GetEvaporation() const override {

    }

    std::double_t GetMaximalEvaporation() const override {

    }

    std::double_t GetSurplus() const override {

    }

    std::double_t GetLongWaveRadiation() const override {

    }

    std::double_t GetShortWaveRadiation(IHeatSources* heat_sources) const override {
        auto absorbation_factor= GetHeatRadiationAbsorbingFactor();
        auto body_surface_projection = GetBodySurface() * 0.4;
        auto result = 0.0;
        for (auto source : *heat_sources->GetHeatSources()) {
            ILocation* source_location = nullptr;
            source->QueryInterface(IID_ILocation, (void**)&source_location);
            if (source_location) {
                //  fire and local sources of heat should have position
                auto distance = GetDistance(source_location);
                result += result + absorbation_factor * body_surface_projection * source->GetSurfacePower(distance);
            } else {
                //  suns and stars are not required to have position cause they are very far away
                result += result + absorbation_factor * body_surface_projection * source->GetSurfacePower();
            }
        }
        return result;
    }

    std::double_t GetRadiation(IHeatSources* heat_sources) const override {
        auto long_radiation = GetLongWaveRadiation();
        auto short_radiation = GetShortWaveRadiation(heat_sources);
        auto result = long_radiation + short_radiation;
        return result;
    }

#ifdef USE_QT
    //  QGraphicsItem
    QRectF boundingRect() const
    {
        auto r = QRectF(-5, -5, 10, 10);
        return r;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        painter->drawEllipse(QRectF(-5, -5, 10, 10));
        painter->drawLine(0, 0, 10, 0);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        qDebug("Character clicked");
    }

#endif  //  USE_QT

    //  ILocation
    ILocation* GetParentLocation() override {
        auto p = parentItem();
        auto location = dynamic_cast<ILocation*>(p);
        return location;
    }

    const ILocation* GetParentLocation() const override {
        auto p = parentItem();
        auto location = dynamic_cast<const ILocation*>(p);
        return location;
    }

    void SetParentLocation(ILocation* value) override {
        auto p = dynamic_cast<QGraphicsItem*>(value);
        setParentItem(p);
    }

    std::uint32_t GetChildLocationsCount() const override {
        return childItems().size();
    }

    ILocation* GetChildLocation(std::uint32_t index) override {
        auto result = dynamic_cast<ILocation*>(childItems().at(index));
        return result;
    }

    const ILocation* GetChildLocation(std::uint32_t index) const override {
        auto result = dynamic_cast<const ILocation*>(childItems().at(index));
        return result;
    }

    Math::vec2 GetGlobalPosition() const override {
        auto position = pos() * sceneTransform();
        return Math::vec2{position};
    }

    Math::vec2 GetLocalPosition() const override {
        auto position = pos();
        return Math::vec2{position};
    }

    std::double_t GetDistance(const ILocation* location) const override {
        if (location->GetParentLocation() == GetParentLocation()) {
            auto result = (GetLocalPosition() - location->GetLocalPosition()).Length();
            return result;
        } else {
            auto result = (GetGlobalPosition() - location->GetGlobalPosition()).Length();
            return result;
        }
    }

    void Move(const Math::vec2& delta) override {
        auto translation = pos();
        translation = translation + delta.ToQPointF();
        setPos(translation);
    }

    void Rotate(float delta) override {
        auto angle = rotation();
        auto new_angle = angle + delta;
        setRotation(new_angle);
    }

    //  Time dependent
    void Update(const std::chrono::system_clock::time_point& current_time, std::chrono::system_clock::duration& delta) override {
        auto position = GetLocalPosition();
        auto dir = Math::vec2{QPointF(1, 0) * QMatrix().rotate(rotation())};
        position = position + dir * (float)((double)std::chrono::duration_cast<std::chrono::microseconds>(delta).count() / 1000000.0);
        setPos(position.ToQPointF());
    }

private:
    //  Object
    std::atomic<std::int32_t> m_ref_count {0};

    //  Body
    std::double_t m_mass {80.0};
    std::double_t m_muscles {65.0};
    std::double_t m_fat {15.0};
    std::double_t m_specific_heat {3470.0};
    BodyGender m_gender {BodyGender::Male};

    //  BodyActions
    std::unique_ptr<std::list<IBodyAction*>> m_body_actions {new std::list<IBodyAction*>};

    //  BodyTemperature
    std::double_t m_min_temperature {287.35};
    std::double_t m_max_temperature {319.65};
    std::double_t m_normal_temperature {309.75};
    std::double_t m_current_temperature {309.75};

    //  BodyPower
    std::double_t m_metabolism {60.0};
    std::double_t m_metabolism_constant {60.0};
};

void CharacterFactory::CreateInstance(const Core::Guid &clsid, const Core::Guid &iid, void **instance) {
    Core::IObject* o = nullptr;
    if (clsid == CLSID_Character) {
        o = (IBody*)(new Character);
        o->QueryInterface(iid, instance);
    }
}

PUNK_ENGINE_END
