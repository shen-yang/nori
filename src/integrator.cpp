/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2012 by Wenzel Jakob and Steve Marschner.

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/camera.h>
#include <nori/sampler.h>
#include <nori/bitmap.h>

NORI_NAMESPACE_BEGIN

// 
class ImageBlock : public Eigen::Array<Color4f, NORI_BLOCK_SIZE, NORI_BLOCK_SIZE,
	Eigen::RowMajor, NORI_BLOCK_SIZE, NORI_BLOCK_SIZE> {
public:
	void setOffset(const Point2i &offset) {
		m_offset = offset;
	}

	/// Return the block offset block in pixels
	inline const Point2i &getOffset() const { return m_offset; }
	
	/// Return the block size (minus border) in pixels
	inline const Vector2i &getSize() const { return m_size; }

	void setSize(const Point2i &size) {
		m_size = size;
		resize(size.x(), size.y());
	}

	void put(const Point2f &pos, const Color3f &value) {
	}

	QString toString() {
		return QString("ImageBlock[offset=%1, size=%2]]")
			.arg(m_offset.toString())
			.arg(m_size.toString());
	}
protected:
	Point2i  m_offset;
	Vector2i m_size;
};

//// Reimplementation of the spiraling block generator by Adam Arbree
class BlockGenerator {
public:
	enum EDirection { ERight = 0, EDown, ELeft, EUp };

	BlockGenerator(const Vector2i &size, int blockSize) {
		m_numBlocks = Vector2i(
			(int) std::ceil(size.x() / (float) blockSize),
			(int) std::ceil(size.y() / (float) blockSize));
		m_blocksLeft = m_numBlocks.x() * m_numBlocks.y();
			m_blockSize = blockSize;
		m_direction = ERight;
		m_block = Point2i(m_numBlocks / 2);
		m_size = size;
		m_stepsLeft = 1;
		m_numSteps = 1;
	}

	bool next(ImageBlock &block) {
		if (m_blocksLeft == 0)
			return false;

		Point2i pos = m_block * m_blockSize;
		block.setOffset(pos);
		block.setSize((m_size - pos).cwiseMin(Vector2i::Constant(m_blockSize)));

		if (--m_blocksLeft == 0)
			return true;

		do {
			switch (m_direction) {
				case ERight: ++m_block.x(); break;
				case EDown:  ++m_block.y(); break;
				case ELeft:  --m_block.x(); break;
				case EUp:    --m_block.y(); break;
			}

			if (--m_stepsLeft == 0) {
				m_direction = (m_direction + 1) % 4;
				if (m_direction == ELeft || m_direction == ERight) 
					++m_numSteps;
				m_stepsLeft = m_numSteps;
			}
		} while ((m_block.array() < 0).any() ||
		         (m_block.array() >= m_numBlocks.array()).any());

		return true;
	}

protected:
	Point2i m_block;
	Vector2i m_numBlocks;
	Vector2i m_size;
	int m_blockSize;
	int m_numSteps;
	int m_blocksLeft;
	int m_stepsLeft;
	int m_direction;
};


void Integrator::render(const Scene *scene, Sampler *sampler) {
	const Integrator *integrator = scene->getIntegrator();
	const Camera *camera = scene->getCamera();
	Vector2i size = camera->getSize();
	
	BlockGenerator blockgen(size, NORI_BLOCK_SIZE);
	Bitmap bitmap(size);

	ImageBlock block;
	while (blockgen.next(block)) {
		cout << "Rendering " << qPrintable(block.toString()) << endl;

		Point2i offset = block.getOffset();
		Vector2i size  = block.getSize();

		for (int x=0; x<size.x(); ++x) {
			for (int y=0; y<size.y(); ++y) {
				for (uint32_t i=0; i<sampler->getSampleCount(); ++i) {
					cout << x << ", " << y  << ", " << i << endl;
					Point2f pixelSample = Point2f(x + offset.x(), y + offset.y()) + sampler->next2D();
					Point2f apertureSample = sampler->next2D();

					/* Sample a ray from the camera, and compute the incident radiance */
					Ray3f ray;
					Color3f value = camera->sampleRay(ray, pixelSample, apertureSample);
					value *= integrator->Li(scene, sampler, ray);

					block.put(pixelSample, value);
				}
			}
		}
	}
}

NORI_NAMESPACE_END
