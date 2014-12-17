#include <math/matrix.h>
#include <math/tuple.h>
#include <math/min_max.h>
#include <math/inoise_generator.h>
#include "main_window.h"

using namespace Punk::Engine::Math;

MainWindow::MainWindow()
	: QMainWindow{ nullptr }
	, ui{ new Ui::MainWindow }
{
	ui->setupUi(this);		
}


MainWindow::~MainWindow() {

}

float alpha = 0.9f;

const vec2 v() {
	return vec2{ { .1f, 0.1f } };
}

INoiseGenerator* gen = INoiseGenerator::Create();

float g(const point2d& p) {	
	auto v = gen->PerlinNoise2D(p.X() / 512.0f, p.Y() / 512.0f);
	return v;
}

const point2d pk(const point2d& pk0, float t, float dt) {
	
	auto r = pk0 + v() * dt;
	return r;
}

float f(const point2d& p, float t, float dt) {
	if (p.X() < 0 || p.X() >= 512 || p.Y() < 0 || p.Y() >= 512)
		return 0;

	srand(int(p.X() + p.Y() * 512));

	float sum = 0;
	for (int i = 0; i < 10; ++i) {
		sum += powf(1.0f - alpha, i) * g(p - float(i) * v());
	}
	return sum * alpha;
}

const mat2 tensor(const point2d& p) {
	auto m = mat2{};
	float R = p.Length();
	float theta = atan2f(p.Y(), p.X());
	m.at(0, 0) = cosf(2.0f*theta);
	m.at(0, 1) = sinf(2.0f*theta);
	m.at(1, 0) = sinf(2.0f*theta);
	m.at(1, 1) = -cosf(2.0f*theta);
	m *= R;
	return m;
}

const vec2 vector_field(point2d p) {
	//point2d p0{ 1, 1 };
	//auto m = mat2{};
	//float R = p0.Length();
	//float theta = atan2f(p0.Y(), p0.X());
	//m.at(0, 0) = cosf(2.0f*theta);
	//m.at(0, 1) = sinf(2.0f*theta);
	//m.at(1, 0) = sinf(2.0f*theta);
	//m.at(1, 1) = -cosf(2.0f*theta);
	//m *= R;
	//return m * (p - p0);

	//auto m = mat2{};
	//float k = 1;
	//m.at(0, 0) = k;
	//m.at(0, 1) = 0;
	//m.at(1, 0) = 0;
	//m.at(1, 1) = k;
	//vec2 v = p - point2d{ 256.0f, 256.0f };
	//return m.Inversed() * v;

	auto m = mat2{};
	float k = 1;
	m.at(0, 0) = 0;
	m.at(0, 1) = -1;
	m.at(1, 0) = 1;
	m.at(1, 1) = 0;
	vec2 v = p - point2d{ 256.0f, 256.0f };
	return m * v;
}

int L = 64;

std::vector<point2d> compute_integral_curve(const point2d& p) {	
	float ds = 1.0f / (512.0f * 3.0f);
	std::vector<point2d> c;
	auto v = vector_field(p);
	c.push_back(p);
	float x = p.X();
	float y = p.Y();
	for (int s = 0; s < L; ++s) {
		x += ds * v.X();
		y += ds * v.Y();
		c.push_back({ x, y });
		v = vector_field({ x, y });
	}
	x = p.X();
	y = p.Y();
	v = vector_field(p);
	for (int s = 0; s > -L; --s) {
		x -= ds*v.X();
		y -= ds*v.Y();
		c.push_back({ x, y });
		v = vector_field({ x, y });
	}
	return c;
}

float compute_convolution(const QImage& image, std::vector<point2d>& c) {
	float sum = 0;
	for (auto p : c) {
		if (p.X() >= 0 && p.X() < image.width() && p.Y() >= 0 && p.Y() < image.height()) {
			sum += qGray(image.pixel(p.X(), p.Y()));
		}
	}
	sum /= (float)(2 * L + 1);
	return sum;
}

const QImage LIC(const QImage image) {
	QImage out{ image };
	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			auto c = compute_integral_curve({ float(x), float(y) });
			auto sum = compute_convolution(image, c);
			out.setPixel(x, y, qRgb(sum, sum, sum));
		}
	}
	return out; 
}

/*
	image_out = QImage{ image_in };
	for (int y = 0; y < image_in.height(); ++y) {
		for (int x = 0; x < image_in.width(); ++x) {

			auto kernel = tensor({ float(x), float(y) });
			
			float accum = 0;
			for (int kx = 0; kx < kernel.RowsCount(); ++kx) {
				float xx = x + kx;
				for (int ky = 0; ky < kernel.ColumnsCoun(); ++ky) {					
					float yy = y + ky;

					if (xx >= 0 && xx < image_in.width() && yy >= 0 && yy < image_in.height()) {
						float v = qGray(image_in.pixel(xx, yy)) / 255.0f;
						accum += kernel.at(kx, ky) * v;
					}
				}
			}

			int v = accum * 255.0f;
			image_out.setPixel(x, y, qRgb(v, v, v));
		}
	}*/


void MainWindow::createField() {

	QImage image{ 512, 512, QImage::Format::Format_RGB32 };

	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			int v = rand() % 256;
			image.setPixel(x, y, qRgb(v, v, v));
		}
	}

	QImage outp = LIC(image);
	
	ui->render_view->setScene(new QGraphicsScene());
	ui->render_view->scene()->addPixmap(QPixmap::fromImage(outp));
}