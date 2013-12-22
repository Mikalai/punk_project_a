//#include "time_component.h"
//#include "timer.h"
//#include "clock.h"

//PUNK_ENGINE_BEGIN
//namespace System
//{
//    REGISTER_COMPONENT(TimeComponent);

//#define TIMER_SERVICE Core::String(L"timer")
//#define CLOCK_SERVICE Core::String(L"clock")
//#define TIME_COMPONENT Core::String(L"time")

//    TimeComponent::TimeComponent()
//        : Core::Component(TIME_COMPONENT, {TIMER_SERVICE, CLOCK_SERVICE}) {}

//    Core::Object* TimeComponent::OnCreate(const Core::String &name, const Core::String &type, Core::Object **params)
//    {
//        (void)params;
//        Core::Object* o {nullptr};
//        if (type == TIMER_SERVICE)
//            o = new Timer;
//        if (type == CLOCK_SERVICE)
//            o = new Clock;
//        if (o)
//            o->SetName(name);
//        return o;
//    }
//}
//PUNK_ENGINE_END
