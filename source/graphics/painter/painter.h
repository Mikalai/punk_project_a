#ifndef _H_PUNK_GPU_PAINTER
#define _H_PUNK_GPU_PAINTER

#include <cstddef>
#include <config.h>
#include <vector>
#include <images/module.h>
PUNK_ENGINE_BEGIN
namespace Math
{
	class Line2D;
	class Triangle2D;
	class vec2;
	class ivec2;
	class Rect;
	class mat3;
}

namespace Graphics
{
	class PaintEngine;
	class PaintDevice;
	class Brush;
	class Pen;

	class PUNK_ENGINE_API Painter final
	{
	public:
		Painter();
		~Painter();
		void Begin(PaintDevice* device);
		void End();
		void DrawArc(float xc, float yc, float width, float height, float start_angle, float span_angle);
		void DrawChord(float xc, float yc, float width, float height, float start_angle, float span_angle);
		void DrawConvexPolygon(const Math::vec2* points, size_t count);
		void DrawConvexPolygon(const std::vector<Math::vec2>& points);
		void DrawPoint(const Math::vec2& point);
		void DrawPoint(float x, float y);
		void DrawLine(const Math::vec2& a, const Math::vec2& b);
		void DrawLine(const Math::Line2D& line);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawLines(const Math::Line2D* lines, size_t count);
		void DrawLines(const std::vector<Math::Line2D>& lines);
		void DrawEllipse(float xc, float yc, float major_axis, float minor_axis);
		void DrawEllipse(const Math::Rect& rect);
        void DrawImage(float x, float y, const ImageModule::IImage* image);
        void DrawImage(const Math::vec2& point, const ImageModule::IImage* image);
		void DrawRect(const Math::Rect& rect);
		void DrawRect(float x, float y, float width, float height);
		void DrawRoundedRect(float x, float y, float x_r, float y_r);
		void DrawText(float x, float y, const Core::String& text);
		void EraseRect(const Math::Rect& rect);
		void FillRect(const Math::Rect& rect, const Brush& brush);
		void SetOpacity(float value);
		float GetOpacity() const;
		void SetPen(const Pen& pen);
		const Pen& GetPen() const;
		PaintEngine* GetPaintEngine() const;
		void Save();
		void Restore();
		void Scale(float x, float y);
		void Translate(float x, float y);
		void SetWorldTransform(const Math::mat3& value);
		const Math::mat3& GetWorldTransform() const;
		void SetBackgroundBrush(const Brush& value);
		const Brush& GetBackgroundBrush() const;
		void SetBrush(const Brush& value);
		const Brush& GetBrush() const;

		struct PainterImpl;
		PainterImpl* impl;

	private:
		//	no copy
		Painter(const Painter&);
		Painter& operator = (const Painter&);
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_PAINTER
